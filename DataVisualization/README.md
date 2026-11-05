# CMP2103 Data Visualization Library

C++17 library for CSV loading, paired numeric preprocessing, statistics and SVG plots. The CMake target `dataviz` compiles all 11 production translation units. Public headers live in `DataVisualization/include/dataviz` relative to the repository root.

## Build and test (PowerShell)
Requires GCC 16.2.0, CMake 4.4.5 and Ninja on this machine. The Ninja path below is machine-specific.
```powershell
$env:PATH = "C:\msys64\ucrt64\bin;" + $env:PATH
Set-Location "C:\Users\GLADYS\Documents\DataVisualization_Final_Integration"
& "C:\Program Files\CMake\bin\cmake.exe" -S . -B build/behavior-repair -G Ninja "-DCMAKE_MAKE_PROGRAM=C:/Program Files/MATLAB/R2025b/toolbox/shared/coder/ninja/win64/ninja.exe" -DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
& "C:\Program Files\CMake\bin\cmake.exe" --build build/behavior-repair -j 4
& "C:\Program Files\CMake\bin\ctest.exe" --test-dir build/behavior-repair --output-on-failure --output-junit results.xml
& ./build/behavior-repair/DataVisualization/csv_demo.exe DataVisualization/data/demo.csv build/behavior-repair/svg
```
Use a new, absent build directory when verifying a clean build. See [latest repair report](docs/BEHAVIOR_REPAIR_REPORT.md) for actual results; do not interpret a blocked executable as a passing test. Windows Application Control must remain enabled.

## Implemented behavior
- Plot owns title and axis labels. All plot types share setters and getters, including LinePlot's standalone SVG path.
- ScatterPlot preserves printable ASCII markers in terminal grids. SVG uses blue filled circles with a dark outline and a default radius of 5 pixels. Use setMarkerRadius(radius) to set a positive finite radius; getMarkerRadius() returns it.
- BarPlot supports positive, negative and zero values. Terminal bars share a `|` zero column. SVG bars share an explicitly drawn and labeled zero baseline.
- Renderer-based numerical axes display six ticks; constant-valued axes display a single centered tick. Bar categories remain categorical labels.
- LinePlot preserves observation order and validates finite, equally sized coordinates.
- DataLoader supports quoted CSV fields; DataPreprocessor offers Reject or DropRow policies that preserve X/Y pairing.
- Statistics::summarize is templated and reports count, sum, extrema, mean, median, population variance and standard deviation.
- Labels and annotations render through Renderer. ImageExporter supports SVG with explicit failure reporting.
- Original teaching demonstrations compile as separate executables. Existing contributor history is preserved.

## API compatibility
`setTitle`, `setXLabel`, `setYLabel`, `setAxisLabels`, `getTitle`, `getXAxisLabel` and `getYAxisLabel` use shared Plot state.
The virtual no-argument `exportData() const` hook is restored with its original no-op default. It is not a data-file writer. Use ImageExporter for SVG or override the hook for application-specific data export.
The old `setXScale(dMin,dMax,pMin,pMax)` and `setYScale(...)` declarations remain intentionally removed: they had no implementation and the original abstract AxisScale members could not be instantiated. All current plots autoscale. Applications needing custom viewport mapping should use LinearScale with Renderer primitives. This is a documented source-level breaking change, not a silent no-op.
`render(Renderer&) const` replaces the old unimplemented no-argument render contract.
Global Plot, ScatterPlot and BarPlot names remain available; LinePlot and the shared rendering/data interfaces use namespace dataviz.

## Limits
SVG only; no raster conversion. ASCII markers are printable glyphs; SVG scatter markers are outlined circles. Tick labels use four significant digits; automatic label collision avoidance for dense categories or very small canvases is not provided. No custom plot ranges, clipping, legends or automatic annotation placement. Annotations use canvas coordinates. Very large finite values may overflow statistics/scaling arithmetic.
Standalone LinePlot::saveSvg retains its own richer layout but uses identical shared metadata. The demo uses the first two CSV columns and rejects invalid values. CSV retains the original field-trimming behavior.
Historical development reports in docs describe earlier designs; current headers and this README define the supported API.
