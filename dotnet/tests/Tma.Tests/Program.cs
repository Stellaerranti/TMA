using System.Globalization;
using Tma.Core;

int passed = 0;
void Test(string name, Action test)
{
    try { test(); Console.WriteLine($"PASS {name}"); passed++; }
    catch (Exception e) { Console.Error.WriteLine($"FAIL {name}: {e}"); Environment.Exit(1); }
}
void Near(double expected, double actual, double tolerance = 1e-8)
{
    if (Math.Abs(expected - actual) > tolerance) throw new Exception($"Expected {expected}, got {actual}");
}
void Throws<T>(Action action) where T : Exception
{
    try { action(); } catch (T) { return; }
    throw new Exception($"Expected {typeof(T).Name}");
}
MeasurementSettings Settings(double hold = 0) => new(0.03, 1, 2, 1, 80, hold);
Measurement Batch(MeasurementEngine engine, double volts, double seconds, double amplitude = 2, double moment = 3)
{
    Measurement? result = null;
    for (int i = 0; i < 50; i++) result = engine.Add(new(volts, amplitude, moment), seconds);
    return result ?? throw new Exception("No measurement emitted");
}

Test("Legacy thermocouple polynomial regression", () =>
{
    Near(0, MeasurementEngine.TemperatureFromVolts(0, 1));
    Near(15.020490694, MeasurementEngine.TemperatureFromVolts(0.1, 1));
    Near(72.69518375, MeasurementEngine.TemperatureFromVolts(0.5, 1));
    Near(MeasurementEngine.TemperatureFromVolts(0.2, 1), MeasurementEngine.TemperatureFromVolts(0.1, 2));
});
Test("Exactly 50 samples; average volts before nonlinear conversion", () =>
{
    var engine = new MeasurementEngine(Settings());
    for (int i = 0; i < 49; i++)
        if (engine.Add(new(i % 2 == 0 ? 0.1 : 0.3, 2, 3), i / 10.0) is not null) throw new Exception("Early result");
    var result = engine.Add(new(0.3, 2, 3), 4.9)!;
    Near(200, result.ThermocoupleMillivolts);
    Near(MeasurementEngine.TemperatureFromVolts(0.2, 1), result.Temperature);
    Near(3, result.Moment);
    Near(4.9, result.ElapsedSeconds);
    Near(3.5, result.OutputVolts);
    if (engine.Add(new(0.1, 2, 3), 5) is not null) throw new Exception("Accumulator did not reset");
});
Test("Hold timing persists across batches and midnight", () =>
{
    var engine = new MeasurementEngine(Settings(30));
    if (Batch(engine, 0.3, 86380).Stage != HeatingStage.Ramp) throw new Exception("Ramp missing");
    var hold = Batch(engine, 0.55, 86390);
    if (hold.Stage != HeatingStage.Hold) throw new Exception("Hold missing");
    Near(0.263 * Math.Pow(80, 0.573), hold.OutputVolts);
    if (Batch(engine, 0.55, 86410).Stage != HeatingStage.Hold) throw new Exception("Hold ended early");
    if (Batch(engine, 0.55, 86420).Stage != HeatingStage.Cooling) throw new Exception("Cooling missing");
    var complete = Batch(engine, 0.2, 86425);
    if (complete.Stage != HeatingStage.Complete) throw new Exception("Completion missing");
    Near(0, complete.OutputVolts);
});
Test("First hot reading advances to hold instead of staying in warmup", () =>
{
    if (Batch(new MeasurementEngine(Settings(30)), 0.6, 5).Stage != HeatingStage.Hold)
        throw new Exception("Hot startup transition failed");
});
Test("Zero hold follows legacy immediate cooling", () =>
{
    if (Batch(new MeasurementEngine(Settings()), 0.6, 5).Stage != HeatingStage.Cooling)
        throw new Exception("Zero hold transition failed");
});
Test("Output is limited to 0–9.5 V", () =>
{
    Near(9.5, Batch(new MeasurementEngine(new(100, 100, 1, 1, 80)), 0.3, 5).OutputVolts);
    Near(0, Batch(new MeasurementEngine(new(-100, -100, 1, 1, 80)), 0.3, 5).OutputVolts);
});
Test("Invalid settings, samples, time and zero denominator are rejected", () =>
{
    Throws<ArgumentException>(() => new MeasurementEngine(Settings() with { KA = double.NaN }));
    Throws<ArgumentException>(() => new MeasurementEngine(Settings() with { TemperatureCorrection = 0 }));
    Throws<ArgumentException>(() => new MeasurementEngine(Settings() with { TargetTemperature = 35 }));
    Throws<ArgumentException>(() => new MeasurementEngine(Settings() with { HoldSeconds = -1 }));
    var engine = new MeasurementEngine(Settings());
    Throws<InvalidOperationException>(() => engine.Add(new(double.NaN, 1, 1), 0));
    Throws<InvalidOperationException>(() => Batch(engine, 0.1, 5, amplitude: 0));
    Throws<ArgumentException>(() => engine.Add(new(0.1, 1, 1), 4));
});
Test("Export preserves four columns, appends once and ignores locale", () =>
{
    string path = Path.Combine(Path.GetTempPath(), Guid.NewGuid() + ".jr6");
    var previous = CultureInfo.CurrentCulture;
    try
    {
        CultureInfo.CurrentCulture = CultureInfo.GetCultureInfo("ru-RU");
        var value = new Measurement(12.5, 3.25, 20.5, 5.1, 0, HeatingStage.Complete);
        using (var writer = MeasurementFile.OpenAppend(path)) MeasurementFile.Write(writer, value);
        using (var writer = MeasurementFile.OpenAppend(path)) MeasurementFile.Write(writer, value);
        var lines = File.ReadAllLines(path);
        if (lines.Length != 3 || lines[0] != MeasurementFile.Header || lines[1] != "12.5\t3.25\t20.5\t5.1")
            throw new Exception("Unexpected export contents");
    }
    finally { CultureInfo.CurrentCulture = previous; File.Delete(path); }
});
Test("Long simulation completes a heating cycle with finite measurements", () =>
{
    using var device = new SimulationDevice(1);
    var engine = new MeasurementEngine(Settings(30));
    device.Start();
    Measurement? last = null;
    for (int i = 1; i <= 60000; i++)
    {
        var now = TimeSpan.FromSeconds(i / 10.0);
        var result = engine.Add(device.Read(now), now.TotalSeconds);
        if (result is null) continue;
        device.SetOutput(result.OutputVolts);
        last = result;
        if (result.Stage == HeatingStage.Complete) break;
    }
    if (last?.Stage != HeatingStage.Complete) throw new Exception("Cycle did not complete");
    device.Stop();
    Throws<InvalidOperationException>(() => device.Read(TimeSpan.Zero));
    device.Start();
    Near(22, MeasurementEngine.TemperatureFromVolts(device.Read(TimeSpan.Zero).ThermocoupleVolts, 1));
});
Test("Missing hardware fails explicitly; never substitutes simulated readings", () =>
{
    using var device = new ZetlabDevice();
    Throws<NotSupportedException>(device.Start);
    Throws<NotSupportedException>(() => device.Read(TimeSpan.Zero));
    device.Stop();
});
Console.WriteLine($"{passed} tests passed.");
