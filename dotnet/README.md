# TMA — C# / .NET migration

Windows Forms application targeting .NET 10. The old C++/CLI project remains unchanged. No third-party NuGet packages or C++ build tools are required.

## Build and run

Install the .NET 10 SDK on Windows, then from this directory:

```powershell
dotnet build TMA.NET.slnx -c Release
dotnet run --project src/Tma.App -c Release
dotnet run --project tests/Tma.Tests -c Release
```

The published app is also available in `publish/Tma.App.exe` when supplied with this migration. It requires the .NET 10 Windows Desktop Runtime. To publish again:

```powershell
dotnet publish src/Tma.App -c Release -o publish
```

## Use

1. Select **Simulation — synthetic data** to exercise the program without equipment. The default ZETLAB option reports that the SDK is missing and cannot start.
2. Enter KA, KB, KM, Tend, dT, and hold seconds. Supplied numbers are demonstration settings, not calibrated instrument settings. Both the current locale and invariant decimal notation are accepted.
3. Optionally select **Output file…**. Measurements append to that file; a new file receives a header. Existing files are never overwritten. With no output selected, results appear only in the plots. Each run restarts elapsed time at zero; appended runs share the same file without an extra header.
4. Click **Start**. The app polls every 100 ms and produces one averaged measurement after 50 samples (nominally every five seconds). **Stop**, closing the window, completion, or an acquisition/file error stops the device and releases resources. A new run resets all acquisition and heating state.

The moment plot uses moment on X and temperature on Y, matching the intended `Ht_point` assignment in the C++ source. The time plot uses elapsed seconds on X and temperature on Y. Display history is bounded to 20,000 points; file output retains all measurements. Plot lines use straight segments instead of the original spline interpolation.

## Hardware integration is pending

The supplied repository lacks `Zadc_int.h`, `zet_declaration.h`, `Zadc.lib`, the matching runtime DLL, and `MyForm.resx`. In particular, the missing declaration header contains device identity and buffer configuration, so a correct native interop ABI cannot be inferred from the call sites alone. The existing compiled executable is not a replacement for these source dependencies.

`IAcquisitionDevice` separates device lifetime, reads, and output writes from the measurement engine and UI. `ZetlabDevice` currently rejects Start/Read/SetOutput explicitly. No native calls, device control, or silent simulation fallback are implemented. To finish this part, obtain the actual SDK and device configuration; verify calling convention, integer widths, DLL architecture, error codes, channel order, scaling, and buffer ownership; implement the adapter; then validate acquisition and zero-output shutdown on the equipment. Choose x86 or x64 to match the vendor DLL when publishing.

## Preserved calculations and intentional corrections

- 50 ADC samples are averaged before the legacy `chrom()` polynomial: `u = volts * 1000 / 100 * dT`; `T = (((-1.2306e-5*u + 0.002103)*u - 0.1326)*u + 15.151)*u`.
- Moment is `KM * sum(channel 2) / sum(channel 1)`. Output columns remain thermocouple mV, moment, temperature °C, elapsed seconds. Files are UTF-8 tab-separated with invariant numeric formatting and an English header. They retain the `.jr6` extension and column order, but compatibility with an external JR6 reader has not been verified.
- Warmup output is 3.5 V; ramp is `KA*T + KB`; hold is `0.263*Tend^0.573`; cooling is `0.3*(KA*T + KB)`; complete output is zero. Ramp begins above 35 °C, hold begins at `Tend - 5`, and cooling completes below 45 °C. Stage transitions are sequential within each measurement.
- `EXPOS_time` was zero-initialized and never assigned in the source. **Hold (s)** exposes this setting, defaults to zero, and uses persistent monotonic elapsed time instead of local stack time variables. Elapsed seconds now advance; the source's `float_now` never changed.
- A first measurement already above the hold threshold now enters hold. The source could remain stuck in warmup. Tend must exceed 40 °C to keep the original thresholds consistent.
- Output is clamped to **0–9.5 V**. The source had only an upper clamp. Nonfinite input and a zero amplitude denominator stop acquisition with an explicit error.
- Startup no longer immediately stops and frees the ADC/DAC buffers. The C++ Start handler called both shutdown functions immediately after starting. Shutdown is handled once per active device lifetime; fresh runs create fresh state.
- Managed bounded plot storage replaces the inconsistent 20,000-element arrays / 200,000-element wrap limit. The legacy thermocouple `.dat` table is not used by `chrom()` and is not needed for the migrated polynomial.

## Layout

- `src/Tma.Core`: settings, polynomial, aggregation, heating controller, file format, device interface and simulator.
- `src/Tma.App`: Windows Forms controls, two plots, session lifecycle and error reporting.
- `tests/Tma.Tests`: dependency-free executable regression tests for calculations, timing, transitions, validation, export, and a complete simulated cycle. A failing test returns a nonzero exit code.

Hardware equivalence and calibration remain unverified until the SDK and real equipment are available. Simulation validates the software flow, not physical measurement accuracy.
