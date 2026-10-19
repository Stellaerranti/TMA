namespace Tma.App;

internal static class Program
{
    [STAThread]
    private static int Main(string[] args)
    {
        ApplicationConfiguration.Initialize();
        using var form = new MainForm();
        if (args.Length == 2 && args[0] == "--smoke-test")
        {
            form.Show();
            Application.DoEvents();
            form.PopulatePreview();
            Application.DoEvents();
            using var bitmap = new Bitmap(form.Width, form.Height);
            form.DrawToBitmap(bitmap, new Rectangle(Point.Empty, bitmap.Size));
            bitmap.Save(args[1]);
            form.ClientSize = new Size(960, 650);
            Application.DoEvents();
            using var compact = new Bitmap(form.Width, form.Height);
            form.DrawToBitmap(compact, new Rectangle(Point.Empty, compact.Size));
            compact.Save(Path.Combine(Path.GetDirectoryName(args[1])!, Path.GetFileNameWithoutExtension(args[1]) + "-compact.png"));
            form.Close();
            return 0;
        }
        Application.Run(form);
        return 0;
    }
}
