# Final engineering verification — FAIL / incomplete
Date: 2026-11-05. Branch: integration-repair.
No production source or test changes were made during this verification. No Git author changes, commits, pushes, merges, security-policy changes or bypasses.

## Clean build: PASS
Fresh directory: build/final-verification (confirmed absent before configure).
GCC 16.2.0, CMake 4.4.5, Ninja, Debug, C++17. All 60 build steps completed.
Compile database and archive member listing independently confirm all 11 production translation units:
Plot.cpp, AxisScale.cpp, Renderer.cpp, ScatterPlot.cpp, BarPlot.cpp, LinePlot.cpp, DataLoader.cpp, DataPreprocessor.cpp, Statistics.cpp, Labels.cpp, ImageExporter.cpp.
Statistics and Labels are primarily header implementations, but their translation units are still compiled and archived.

## Complete clean-suite results
| Test | Result |
|---|---|
| bar | PASS |
| data_loading | PASS |
| image_export | PASS |
| lineplot | BLOCKED / NOT RUN (CTest BAD_COMMAND) |
| renderer | PASS |
| scaling | PASS |
| scatter | BLOCKED / NOT RUN (CTest BAD_COMMAND) |
| integration | PASS |
| statistics | BLOCKED / NOT RUN (CTest BAD_COMMAND) |
| preprocessing | BLOCKED / NOT RUN (CTest BAD_COMMAND) |
| labels | PASS |
| line | PASS |

8/12 passed; 4 failed to start; no executed test reported an assertion failure. Total CTest time: 20.25 seconds.
Do not combine old-build passes with new-build passes to claim a fully passing clean suite.

## Windows Application Control investigation: PARTIAL / BLOCKED
Both ORIGINAL build/cmake renderer and statistics executables reproduce:
NativeErrorCode=4551; HResult=-2147467259 (0x80004005).
Exact Windows message: "An Application Control policy has blocked this file."
CTest originally surfaced only BAD_COMMAND / [unknown error].
Both original binaries are NotSigned. A passing original test_line.exe is also NotSigned. Therefore missing signatures alone do not establish the causal rule.
The fresh renderer executable passes while original renderer remains blocked. Other tests in the same fresh output directory pass while four cannot launch. This does not establish a blanket directory restriction; executable identity/reputation or another policy condition is possible, but unproven.
Code Integrity and AppLocker event-log reads failed with "Attempted to perform an unauthorized operation." Exact policy ID, rule and enforcement source could not be determined.
Follow-up native-error diagnostics for the four fresh launch failures were rejected by automatic approval review: "approval required by policy, but AskForApproval::Granular.sandbox_approval is false". Their individual Windows native codes were therefore not confirmed.
No files were relocated to evade policy; no signing, exclusions, policy modifications or security disabling was attempted.

## Alternate environment: BLOCKED
WSL reports it is not installed. Docker was not found on PATH. No authorized alternative runner was available in this session. No remote upload or new environment installation was attempted.
An administrator can review the denied Code Integrity/AppLocker events and authorize an appropriate trusted build/test environment.

## SVG structure and plotted values: PASS; presentation caveat
Checked both existing DataVisualization/output/integration SVGs and fresh build/final-verification/svg outputs.
All have SVG namespace, 800x600 dimensions/viewBox, five observations and well-formed XML.
Input pairs: (1,-2), (2,3), (3,1), (4,6), (5,4).
Scatter pixel X: 80,245,410,575,740.
Line pixel X: 80,250,420,590,760.
Both pixel Y: 520,232.5,347.5,60,175.
All four line segments join consecutive expected observations.
Bar baseline is y=405; rectangle top/height pairs:
(405,115), (232.5,172.5), (347.5,57.5), (60,345), (175,230).
These correctly encode -2,3,1,6,4, including the negative bar.
The bar plot does NOT draw or label its zero baseline: its visible horizontal axis is at y=520. This makes signed values difficult to interpret. Shared-renderer graphs also lack numeric tick labels. Geometry is correct; presentation is not release-quality.
Checks were structural/numerical, not browser visual rendering.
Fresh demo reports count 5, mean 2.4, median 3, population variance 7.44.

## README instructions: build/demo PASS; all-tests claim BLOCKED
Executed the documented compiler, generator, flags and commands with only build/cmake replaced by the fresh directory and demo output redirected there. Configure, build and demo succeed.
The README's 10/12 status describes the previous build, not this clean result; this report supersedes it.
Ninja path is machine-specific. Public header paths in README are relative to DataVisualization, not repository root.
Historical README content is explicitly marked obsolete and still contains old interfaces.

## Diff and functionality audit: FAIL for complete functionality
git diff --check passes.
Findings:
1. LinePlot retains title_/x_label_/y_label_ separate from Plot's title/xAxisLabel/yAxisLabel. Inherited setAxisLabels does not change rendered line labels; getTitle reports the base default even after LinePlot::setTitle. Common interface behavior is inconsistent.
2. ScatterPlot's incremental constructor discards the requested marker and renderAscii always uses '*'.
3. Original working getXAxisLabel/getYAxisLabel getters were removed. Custom-scale setters and exportData were removed too (the scale setters were previously unimplemented). These are public API changes.
4. BarPlot's ASCII renderer has no meaningful negative-bar rendering; signed SVG geometry does work.
5. Existing smoke tests for bar/scaling/renderer are limited; passing them is not comprehensive functional coverage.
6. Compressed formatting and stale implementation comments remain; a successful build is not proof of professional release readiness.
Original standalone statistics is preserved as legacy_statistics.cpp and compiled separately. The inheritance example was renamed to remove '&', not discarded.
No repair-generated binaries, object files or new SVGs are tracked. Build directory is ignored; generated integration SVGs are ignored. Several historical SVGs were already tracked in HEAD and remain unchanged.
New CMake/header/test files remain untracked pending a future user-authorized commit.

## Credentials/secrets audit: PASS within inspected repair scope
Reviewed changed and untracked non-ignored repair text and ran patterns for private-key headers, AWS access IDs, GitHub/OpenAI-style tokens and quoted password/API-key/secret/token assignments: zero matching files.
No credentials or secrets were identified as introduced by the repair. This is a scoped code/content review and pattern scan, not proof against arbitrary obfuscation or a full historical secret audit.

## Exact reproduction commands (PowerShell)
```powershell
$env:PATH = "C:\msys64\ucrt64\bin;" + $env:PATH
Set-Location "C:\Users\GLADYS\Documents\DataVisualization_Final_Integration"
& "C:\Program Files\CMake\bin\cmake.exe" -S . -B build/final-verification -G Ninja "-DCMAKE_MAKE_PROGRAM=C:/Program Files/MATLAB/R2025b/toolbox/shared/coder/ninja/win64/ninja.exe" -DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
& "C:\Program Files\CMake\bin\cmake.exe" --build build/final-verification -j 4
& "C:\Program Files\CMake\bin\ctest.exe" --test-dir build/final-verification --output-on-failure --output-junit results.xml
& ./build/final-verification/DataVisualization/csv_demo.exe DataVisualization/data/demo.csv build/final-verification/svg
```
For another genuinely clean run, use a new absent build directory. Resolve policy through the administrator rather than changing paths to avoid enforcement.

Final decision: FAIL release verification. Build and data geometry pass, but a complete clean test pass is blocked and API/presentation defects remain.
