namespace Tma.Core;

/// <summary>Device boundary. Implement against verified vendor SDK signatures when available.</summary>
public interface IAcquisitionDevice : IDisposable
{
    void Start();
    AdcSample Read(TimeSpan elapsed);
    void SetOutput(double volts);
    void Stop();
}

/// <summary>Deterministic synthetic data; never connects to or controls physical equipment.</summary>
public sealed class SimulationDevice : IAcquisitionDevice
{
    private readonly double correction;
    private bool running;
    private double output;
    private double temperature = 22;
    private double previousSeconds;

    public SimulationDevice(double correction) => this.correction = correction > 0 && double.IsFinite(correction)
        ? correction : throw new ArgumentOutOfRangeException(nameof(correction));

    public void Start()
    {
        temperature = 22;
        previousSeconds = output = 0;
        running = true;
    }

    public AdcSample Read(TimeSpan elapsed)
    {
        if (!running) throw new InvalidOperationException("Simulation is stopped.");
        double dt = Math.Clamp(elapsed.TotalSeconds - previousSeconds, 0, 1);
        previousSeconds = elapsed.TotalSeconds;
        temperature += (output * 0.8 - (temperature - 22) * 0.04) * dt;
        // Invert the same polynomial within the simulation's supported temperature range.
        double low = 0, high = 2;
        for (int i = 0; i < 60; i++)
        {
            double mid = (low + high) / 2;
            if (MeasurementEngine.TemperatureFromVolts(mid, 1) < temperature) low = mid;
            else high = mid;
        }
        double amplitude = 1 + 0.01 * Math.Sin(elapsed.TotalSeconds);
        return new((low + high) / (2 * correction), amplitude,
            amplitude * (0.5 + temperature / 200 + 0.01 * Math.Sin(elapsed.TotalSeconds / 3)));
    }

    public void SetOutput(double volts)
    {
        if (!running) throw new InvalidOperationException("Simulation is stopped.");
        if (!double.IsFinite(volts) || volts < 0 || volts > 9.5)
            throw new ArgumentOutOfRangeException(nameof(volts));
        output = volts;
    }
    public void Stop() { output = 0; running = false; }
    public void Dispose() => Stop();
}

public sealed class ZetlabDevice : IAcquisitionDevice
{
    private static NotSupportedException MissingSdk() => new(
        "ZETLAB hardware support is pending: Zadc_int.h, zet_declaration.h, and the matching vendor library/driver are missing. Select Simulation to try the application.");
    public void Start() => throw MissingSdk();
    public AdcSample Read(TimeSpan elapsed) => throw MissingSdk();
    public void SetOutput(double volts) => throw MissingSdk();
    public void Stop() { }
    public void Dispose() { }
}
