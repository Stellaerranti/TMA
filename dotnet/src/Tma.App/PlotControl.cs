using System.ComponentModel;
using System.Drawing.Drawing2D;
using System.Globalization;

namespace Tma.App;

internal sealed class PlotControl : Control
{
    private readonly List<(double X, double Y)> points = [];
    [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
    public string XTitle { get; init; } = "";
    [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
    public string YTitle { get; init; } = "";
    [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
    public string PlotTitle { get; init; } = "";
    public PlotControl()
    {
        DoubleBuffered = true;
        BackColor = Color.White;
        Dock = DockStyle.Fill;
        MinimumSize = new Size(280, 240);
    }

    public void Add(double x, double y)
    {
        // Bound display history; every measurement still goes to the selected file.
        if (points.Count >= 20000) points.RemoveRange(0, 1000);
        points.Add((x, y));
        Invalidate();
    }
    public void Clear() { points.Clear(); Invalidate(); }

    protected override void OnPaint(PaintEventArgs e)
    {
        base.OnPaint(e);
        var g = e.Graphics;
        g.SmoothingMode = SmoothingMode.AntiAlias;
        var area = new RectangleF(78, 64, Math.Max(1, Width - 103), Math.Max(1, Height - 128));
        using var titleFont = new Font(Font, FontStyle.Bold);
        g.DrawString(PlotTitle, titleFont, Brushes.Black, 18, 14);
        double xMin = points.Count == 0 ? 0 : points.Min(p => p.X);
        double xMax = points.Count == 0 ? 1 : points.Max(p => p.X);
        double yMin = points.Count == 0 ? 0 : points.Min(p => p.Y);
        double yMax = points.Count == 0 ? 100 : points.Max(p => p.Y);
        Expand(ref xMin, ref xMax);
        Expand(ref yMin, ref yMax);
        using var grid = new Pen(Color.FromArgb(230, 234, 240));
        using var center = new StringFormat { Alignment = StringAlignment.Center };
        for (int i = 0; i <= 4; i++)
        {
            float x = area.Left + area.Width * i / 4;
            float y = area.Bottom - area.Height * i / 4;
            g.DrawLine(grid, x, area.Top, x, area.Bottom);
            g.DrawLine(grid, area.Left, y, area.Right, y);
            g.DrawString(Format(xMin + (xMax - xMin) * i / 4), Font, Brushes.DimGray,
                new RectangleF(x - 45, area.Bottom + 8, 90, 24), center);
            g.DrawString(Format(yMin + (yMax - yMin) * i / 4), Font, Brushes.DimGray, 3, y - 9);
        }
        g.DrawRectangle(Pens.Gray, area.X, area.Y, area.Width, area.Height);
        g.DrawString(XTitle, Font, Brushes.Black, new RectangleF(area.Left, Height - 28, area.Width, 25), center);
        g.DrawString(YTitle, Font, Brushes.DimGray, area.Left, area.Top - 24);
        if (points.Count > 1)
        {
            var screen = points.Select(p => new PointF(
                area.Left + (float)((p.X - xMin) / (xMax - xMin)) * area.Width,
                area.Bottom - (float)((p.Y - yMin) / (yMax - yMin)) * area.Height)).ToArray();
            using var line = new Pen(Color.FromArgb(32, 110, 190), 2);
            g.DrawLines(line, screen);
        }
        else if (points.Count == 1)
            g.FillEllipse(Brushes.SteelBlue, area.Left + area.Width / 2 - 3, area.Top + area.Height / 2 - 3, 6, 6);
    }

    private static string Format(double v) => v.ToString("G4", CultureInfo.InvariantCulture);
    private static void Expand(ref double min, ref double max)
    {
        if (max - min < 1e-9) { min -= 0.5; max += 0.5; }
        else { double margin = (max - min) * 0.05; min -= margin; max += margin; }
    }
}
