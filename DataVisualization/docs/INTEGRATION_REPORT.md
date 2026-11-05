# Integration repair report
Date: 2026-11-05
Branch: integration-repair. No commits, history rewrites, pushes, merges, or author configuration changes were made.

## Verification
CMake 4.4.5 and GCC 16.2.0: full Debug build succeeded with C++17.
All 11 production translation units are linked into libdataviz.a.
All 11 original test files now have runnable targets, plus one integration test.
CTest: 10/12 passed. Renderer and statistics executables were BLOCKED by Windows Application Control before execution. These are not passing tests; administrative policy resolution is required before full verification can be claimed.
Existing assertions were retained; -UNDEBUG keeps assertions enabled.
Integration tests validate CSV parsing, paired-row filtering, statistics, polymorphic plot rendering, SVG export and annotation escaping.
CSV demo completed: count 5, mean 2.4, median 3, population variance 7.44.
Generated scatter.svg, bar.svg, line.svg in DataVisualization/output/integration.

## Changes
- Added correctly named root and library CMakeLists.txt; retained the original misnamed Cmakelist.txt as historical material.
- Repaired Plot as an abstract Renderer-based interface; removed unusable abstract AxisScale members and unimplemented scale setters.
- Reconciled ScatterPlot declarations/definitions, namespace compatibility, incremental input, ASCII output, and removed a conflict marker.
- Implemented signed SVG bars and rejected nonfinite bar input.
- Made LinePlot derive from Plot and share Renderer Point, eliminating duplicate definitions. Retained the working standalone saveSvg implementation.
- Retained AxisScale, CSV loader, Renderer and ImageExporter implementations; exposed renderer dimensions for plot layout.
- Added paired numeric preprocessing with explicit Reject/DropRow policies; rows are dropped together to preserve X/Y alignment.
- Added templated statistics with finite-input validation, median and population variance.
- Added encapsulated Label, AxisLabel and Annotation interfaces with polymorphic rendering.
- Completed the CSV-to-SVG demonstration and added tests to the four former placeholder test files.
- Preserved standalone statistics teaching implementation in examples/legacy_statistics.cpp. Built original template and legacy demonstrations separately to avoid multiple main definitions.
- Updated polymorphism example; renamed the inheritance example to remove '&', which broke Windows linker command parsing.
- Original contributor attribution remains available in preserved Git history and historical documentation; integration edits are uncommitted.

## Reproduction (PowerShell)
```powershell
$env:PATH = "C:\msys64\ucrt64\bin;" + $env:PATH
Set-Location "C:\Users\GLADYS\Documents\DataVisualization_Final_Integration"
& "C:\Program Files\CMake\bin\cmake.exe" -S . -B build/cmake -G Ninja "-DCMAKE_MAKE_PROGRAM=C:/Program Files/MATLAB/R2025b/toolbox/shared/coder/ninja/win64/ninja.exe" -DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe -DCMAKE_BUILD_TYPE=Debug
& "C:\Program Files\CMake\bin\cmake.exe" --build build/cmake -j 4
& "C:\Program Files\CMake\bin\ctest.exe" --test-dir build/cmake --output-on-failure
& ./build/cmake/DataVisualization/csv_demo.exe DataVisualization/data/demo.csv DataVisualization/output/integration
```
Ninja's location is machine-specific; supply another installed Ninja through CMAKE_MAKE_PROGRAM on other machines.
Run from a fresh build directory for an independent clean build.

## Remaining limitations
- Full test approval is pending the two Windows Application Control blocks. No bypass was attempted.
- SVG only; no PNG/JPEG raster conversion.
- Standalone LinePlot::saveSvg retains its richer tick/grid layout; Renderer-based plots have simpler axes and labels. Custom scale setters from the broken original Plot interface are not supported.
- Annotations use canvas coordinates. Automatic annotation placement, legends, label collision avoidance, clipping and categorical axis layout are not implemented.
- Demo uses the first two CSV columns and rejects invalid/missing numbers. Library callers can explicitly choose DropRow.
- CSV parsing preserves the original trimming policy, including trimming quoted field edges.
- Extreme finite magnitudes may overflow arithmetic; this was not verified as a supported numerical domain.
- Legacy teaching programs remain educational examples, not production interfaces.
- Generated SVGs were parsed as XML; no browser-based visual QA was performed.
