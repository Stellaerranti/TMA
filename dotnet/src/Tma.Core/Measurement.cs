using System.Globalization;

namespace Tma.Core;

public sealed record MeasurementSettings(double KA, double KB, double KM,
    double TemperatureCorrection, double TargetTemperature, double HoldSeconds = 0)
{
    public void Validate()
    {
        double[] values = [KA, KB, KM, TemperatureCorrection, TargetTemperature, HoldSeconds];
        if (values.Any(v => !double.IsFinite(v)))
            throw new ArgumentException("All settings must be finite numbers.");
        if (TemperatureCorrection <= 0 || TargetTemperature <= 40 || HoldSeconds < 0)
            throw new ArgumentException("dT must be positive, Tend must exceed 40 °C, and hold time cannot be negative.");
    }
}

public readonly record struct AdcSample(double ThermocoupleVolts, double AmplitudeVolts,
    double MomentVolts, double AuxiliaryVolts = 0);

public enum HeatingStage { Warmup, Ramp, Hold, Cooling, Complete }

public sealed record Measurement(double ThermocoupleMillivolts, double Moment,
    double Temperature, double ElapsedSeconds, double OutputVolts, HeatingStage Stage);

public sealed class MeasurementEngine
{
    public const int SamplesPerMeasurement = 50;
    private readonly MeasurementSettings settings;
    private int count;
    private double thermoSum, amplitudeSum, momentSum;
    private double holdStarted;
    private double lastElapsed = -1;
    public HeatingStage Stage { get; private set; }

    public MeasurementEngine(MeasurementSettings settings)
    {
        settings.Validate();
        this.settings = settings;
    }

    // The legacy chrom() polynomial: ADC volts -> amplified millivolts / 100 -> °C.
    public static double TemperatureFromVolts(double volts, double correction)
    {
        double u = volts * 10 * correction;
        return (((-1.2306e-5 * u + 0.002103) * u - 0.1326) * u + 15.151) * u;
    }

    public Measurement? Add(AdcSample sample, double elapsedSeconds)
    {
        if (!double.IsFinite(elapsedSeconds) || elapsedSeconds < 0 || elapsedSeconds < lastElapsed)
            throw new ArgumentException("Elapsed time must be finite, nonnegative, and monotonic.");
        if (!double.IsFinite(sample.ThermocoupleVolts) || !double.IsFinite(sample.AmplitudeVolts) ||
            !double.IsFinite(sample.MomentVolts) || !double.IsFinite(sample.AuxiliaryVolts))
            throw new InvalidOperationException("The device returned an invalid voltage.");
        lastElapsed = elapsedSeconds;
        thermoSum += sample.ThermocoupleVolts;
        amplitudeSum += sample.AmplitudeVolts;
        momentSum += sample.MomentVolts;
        if (++count < SamplesPerMeasurement) return null;

        double volts = thermoSum / count;
        double amplitude = amplitudeSum;
        double moment = momentSum;
        count = 0;
        thermoSum = amplitudeSum = momentSum = 0;
        if (Math.Abs(amplitude) < 1e-12)
            throw new InvalidOperationException("The amplitude channel is zero; the moment ratio cannot be calculated.");

        double temperature = TemperatureFromVolts(volts, settings.TemperatureCorrection);
        double scaledMoment = settings.KM * moment / amplitude;
        if (!double.IsFinite(temperature) || !double.IsFinite(scaledMoment))
            throw new InvalidOperationException("The calculated measurement exceeds the numeric range.");
        double output = UpdateHeating(temperature, elapsedSeconds);
        return new(volts * 1000, scaledMoment, temperature, elapsedSeconds, output, Stage);
    }

    private double UpdateHeating(double temperature, double elapsed)
    {
        // Sequential transitions preserve the legacy formulas, with persistent hold timing.
        if (Stage == HeatingStage.Warmup && temperature > 35) Stage = HeatingStage.Ramp;
        if (Stage == HeatingStage.Ramp && temperature >= settings.TargetTemperature - 5)
        {
            Stage = HeatingStage.Hold;
            holdStarted = elapsed;
        }
        if (Stage == HeatingStage.Hold && elapsed - holdStarted >= settings.HoldSeconds)
            Stage = HeatingStage.Cooling;
        if (Stage == HeatingStage.Cooling && temperature < 45) Stage = HeatingStage.Complete;
        double output = Stage switch
        {
            HeatingStage.Warmup => 3.5,
            HeatingStage.Ramp => settings.KA * temperature + settings.KB,
            HeatingStage.Hold => 0.263 * Math.Pow(settings.TargetTemperature, 0.573),
            HeatingStage.Cooling => 0.3 * (settings.KA * temperature + settings.KB),
            _ => 0
        };
        if (!double.IsFinite(output)) throw new InvalidOperationException("The calculated heater output is invalid.");
        return Math.Clamp(output, 0, 9.5);
    }
}

public static class MeasurementFile
{
    public const string Header = "TERMO EDS,mV\tM\tT,gradC\tt,sec";
    public static StreamWriter OpenAppend(string path)
    {
        var writer = new StreamWriter(path, append: true) { AutoFlush = true };
        if (writer.BaseStream.Length == 0) writer.WriteLine(Header);
        return writer;
    }

    public static void Write(TextWriter writer, Measurement value) =>
        writer.WriteLine(string.Join('\t', new[] { value.ThermocoupleMillivolts, value.Moment,
            value.Temperature, value.ElapsedSeconds }.Select(v => v.ToString("G9", CultureInfo.InvariantCulture))));
}
