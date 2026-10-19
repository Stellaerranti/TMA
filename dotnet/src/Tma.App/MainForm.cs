using System.Diagnostics;
using System.Globalization;
using System.Runtime.InteropServices;
using Tma.Core;

namespace Tma.App;

public sealed class MainForm : Form
{
    private readonly PlotControl momentPlot = new() { PlotTitle = "Moment / temperature", XTitle = "Moment (KM × channel 2 / channel 1)", YTitle = "Temperature (°C)" };
    private readonly PlotControl timePlot = new() { PlotTitle = "Temperature / time", XTitle = "Elapsed time (s)", YTitle = "Temperature (°C)" };
    private readonly ComboBox deviceChoice = new() { DropDownStyle = ComboBoxStyle.DropDownList, Width = 270 };
    private readonly Button start = new() { Text = "Start", AutoSize = true };
    private readonly Button stop = new() { Text = "Stop", AutoSize = true, Enabled = false };
    private readonly Button outputButton = new() { Text = "Output file…", AutoSize = true };
    private readonly Label outputLabel = new() { Text = "No output file selected", AutoSize = true, Padding = new Padding(6, 8, 0, 0) };
    private readonly Label status = new() { Text = "Ready. Select Simulation to try the app without hardware.", Dock = DockStyle.Fill, AutoSize = true };
    private readonly Label readings = new() { Text = "No measurements", Dock = DockStyle.Fill, AutoSize = true };
    private readonly Dictionary<string, TextBox> inputs = [];
    private readonly System.Windows.Forms.Timer timer = new() { Interval = 100 };
    private readonly Stopwatch elapsed = new();
    private IAcquisitionDevice? device;
    private MeasurementEngine? engine;
    private StreamWriter? writer;
    private string? outputPath;
    private int measurementCount;
    private bool running;

    public MainForm()
    {
        Text = "TMA — .NET";
        ClientSize = new Size(1180, 730);
        MinimumSize = new Size(960, 650);
        StartPosition = FormStartPosition.CenterScreen;
        Font = new Font("Segoe UI", 10);
        var layout = new TableLayoutPanel { Dock = DockStyle.Fill, ColumnCount = 2, RowCount = 5, Padding = new Padding(12) };
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50));
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50));
        layout.RowStyles.Add(new RowStyle(SizeType.Absolute, 48));
        layout.RowStyles.Add(new RowStyle(SizeType.Percent, 100));
        layout.RowStyles.Add(new RowStyle(SizeType.Absolute, 160));
        layout.RowStyles.Add(new RowStyle(SizeType.Absolute, 35));
        layout.RowStyles.Add(new RowStyle(SizeType.Absolute, 48));
        var toolbar = new FlowLayoutPanel { Dock = DockStyle.Fill, WrapContents = false };
        toolbar.Controls.Add(outputButton);
        toolbar.Controls.Add(outputLabel);
        layout.Controls.Add(toolbar, 0, 0);
        layout.SetColumnSpan(toolbar, 2);
        layout.Controls.Add(momentPlot, 0, 1);
        layout.Controls.Add(timePlot, 1, 1);

        var settings = new TableLayoutPanel { Dock = DockStyle.Fill, ColumnCount = 4, RowCount = 3, Padding = new Padding(0, 12, 12, 0) };
        settings.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 55));
        settings.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50));
        settings.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 100));
        settings.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50));
        for (int row = 0; row < 3; row++) settings.RowStyles.Add(new RowStyle(SizeType.Percent, 100f / 3));
        AddInput(settings, "KA", "0.03", 0, 0);
        AddInput(settings, "KB", "1", 0, 1);
        AddInput(settings, "KM", "1", 0, 2);
        AddInput(settings, "Tend (°C)", "80", 2, 0);
        AddInput(settings, "dT", "1", 2, 1);
        AddInput(settings, "Hold (s)", "0", 2, 2);
        layout.Controls.Add(settings, 0, 2);

        var actions = new FlowLayoutPanel { Dock = DockStyle.Fill, FlowDirection = FlowDirection.TopDown, Padding = new Padding(14, 12, 0, 0), WrapContents = false };
        deviceChoice.Items.AddRange(["ZETLAB hardware (SDK missing)", "Simulation — synthetic data"]);
        deviceChoice.SelectedIndex = 0;
        actions.Controls.Add(deviceChoice);
        var buttons = new FlowLayoutPanel { AutoSize = true, WrapContents = false };
        buttons.Controls.Add(start);
        buttons.Controls.Add(stop);
        actions.Controls.Add(buttons);
        actions.Controls.Add(new Label { Text = "50 samples per measurement · 100 ms polling", AutoSize = true });
        layout.Controls.Add(actions, 1, 2);
        layout.Controls.Add(readings, 0, 3);
        layout.SetColumnSpan(readings, 2);
        layout.Controls.Add(status, 0, 4);
        layout.SetColumnSpan(status, 2);
        Controls.Add(layout);
        outputButton.Click += (_, _) => SelectOutput();
        start.Click += (_, _) => StartMeasurement();
        stop.Click += (_, _) => StopMeasurement("Stopped. Heater output is zero.");
        timer.Tick += (_, _) => PollDevice();
        deviceChoice.SelectedIndexChanged += (_, _) => status.Text = deviceChoice.SelectedIndex == 1
            ? "SIMULATION — synthetic measurements; no physical equipment is connected."
            : "Hardware support is pending the missing ZETLAB SDK and driver.";
        FormClosing += (_, _) => StopMeasurement("Stopped.");
    }

    private void AddInput(TableLayoutPanel panel, string name, string initial, int column, int row)
    {
        panel.Controls.Add(new Label { Text = name, Dock = DockStyle.Fill, TextAlign = ContentAlignment.MiddleLeft }, column, row);
        var input = new TextBox { Text = initial, Dock = DockStyle.Fill, AccessibleName = name };
        panel.Controls.Add(input, column + 1, row);
        inputs.Add(name, input);
    }

    private double ReadNumber(string name)
    {
        string text = inputs[name].Text.Trim();
        if ((double.TryParse(text, NumberStyles.Float, CultureInfo.CurrentCulture, out double value) ||
            double.TryParse(text, NumberStyles.Float, CultureInfo.InvariantCulture, out value)) && double.IsFinite(value)) return value;
        throw new ArgumentException($"Enter a finite number for {name}.");
    }

    private void SelectOutput()
    {
        using var dialog = new SaveFileDialog { Filter = "Output files (*.jr6)|*.jr6|Text files (*.txt)|*.txt|All files (*.*)|*.*", DefaultExt = "jr6", AddExtension = true, OverwritePrompt = false };
        if (dialog.ShowDialog(this) != DialogResult.OK) return;
        if (File.Exists(dialog.FileName) && new FileInfo(dialog.FileName).Length > 0 &&
            MessageBox.Show(this, "Append new measurements to this existing file?", "Output file", MessageBoxButtons.OKCancel) != DialogResult.OK) return;
        outputPath = dialog.FileName;
        outputLabel.Text = Path.GetFileName(outputPath) + " (append)";
        status.Text = "Measurements will be appended to " + outputPath;
    }

    private void StartMeasurement()
    {
        try
        {
            var settings = new MeasurementSettings(ReadNumber("KA"), ReadNumber("KB"), ReadNumber("KM"),
                ReadNumber("dT"), ReadNumber("Tend (°C)"), ReadNumber("Hold (s)"));
            engine = new MeasurementEngine(settings);
            device = deviceChoice.SelectedIndex == 1 ? new SimulationDevice(settings.TemperatureCorrection) : new ZetlabDevice();
            device.Start();
            if (outputPath is not null) writer = MeasurementFile.OpenAppend(outputPath);
            momentPlot.Clear();
            timePlot.Clear();
            measurementCount = 0;
            elapsed.Restart();
            running = true;
            SetRunningControls(true);
            timer.Start();
            status.Text = "SIMULATION RUNNING — synthetic data. " + (writer is null ? "No file selected; measurements are displayed only." : "Writing to " + outputPath);
        }
        catch (Exception error)
        {
            StopMeasurement("Unable to start.");
            MessageBox.Show(this, error.Message, "Cannot start measurement", MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }
    }

    private void PollDevice()
    {
        if (!running || device is null || engine is null) return;
        try
        {
            var now = elapsed.Elapsed;
            Measurement? value = engine.Add(device.Read(now), now.TotalSeconds);
            if (value is null) return;
            device.SetOutput(value.OutputVolts);
            if (writer is not null) MeasurementFile.Write(writer, value);
            Display(value);
            // Refresh the idle timer without altering persistent system power settings.
            _ = SetThreadExecutionState(0x00000003);
            if (value.Stage == HeatingStage.Complete) StopMeasurement("Heating cycle complete. Output is zero.");
        }
        catch (Exception error)
        {
            StopMeasurement("Acquisition stopped after an error.");
            MessageBox.Show(this, error.Message, "Measurement error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }

    private void Display(Measurement value)
    {
        timePlot.Add(value.ElapsedSeconds, value.Temperature);
        momentPlot.Add(value.Moment, value.Temperature);
        readings.Text = $"{++measurementCount:N0} measurements    T = {value.Temperature:F2} °C    M = {value.Moment:G5}    t = {value.ElapsedSeconds:F1} s    Output = {value.OutputVolts:F2} V    Stage: {value.Stage}";
    }

    private void StopMeasurement(string message)
    {
        timer.Stop();
        elapsed.Stop();
        running = false;
        var errors = new List<string>();
        if (device is not null)
        {
            try { device.Stop(); } catch (Exception error) { errors.Add(error.Message); }
            try { device.Dispose(); } catch (Exception error) { errors.Add(error.Message); }
            device = null;
        }
        try { writer?.Dispose(); } catch (Exception error) { errors.Add(error.Message); }
        writer = null;
        SetRunningControls(false);
        status.Text = errors.Count == 0 ? message : "Shutdown error: " + string.Join("; ", errors);
    }

    private void SetRunningControls(bool value)
    {
        start.Enabled = outputButton.Enabled = deviceChoice.Enabled = !value;
        stop.Enabled = value;
        foreach (var input in inputs.Values) input.Enabled = !value;
    }

    internal void PopulatePreview()
    {
        deviceChoice.SelectedIndex = 1;
        inputs["Hold (s)"].Text = "30";
        using var simulation = new SimulationDevice(1);
        var previewEngine = new MeasurementEngine(new(0.03, 1, 1, 1, 80, 30));
        simulation.Start();
        for (int i = 1; i <= 3000; i++)
        {
            TimeSpan now = TimeSpan.FromSeconds(i / 10.0);
            var value = previewEngine.Add(simulation.Read(now), now.TotalSeconds);
            if (value is null) continue;
            simulation.SetOutput(value.OutputVolts);
            Display(value);
            if (value.Stage == HeatingStage.Complete) break;
        }
        status.Text = "SIMULATION PREVIEW — synthetic data; no physical equipment is connected.";
    }

    protected override void Dispose(bool disposing)
    {
        if (disposing)
        {
            StopMeasurement("Stopped.");
            timer.Dispose();
        }
        base.Dispose(disposing);
    }

    [DllImport("kernel32.dll")]
    private static extern uint SetThreadExecutionState(uint flags);
}
