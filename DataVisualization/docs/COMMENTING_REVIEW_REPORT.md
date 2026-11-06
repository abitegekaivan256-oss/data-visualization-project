# CMP2103 complete code commenting and verification report

Date: 2026-11-06. Makerere University, CEDAT. C++17 Data Visualization Library.

## Result and scope

**Commenting/formatting: PASS. Build: PASS. Final tests: 11 PASS, 0 software FAIL, 2 BLOCKED. CSV-to-SVG demonstration: PASS. Full verification remains BLOCKED.**

Reviewed repository: `C:\Users\GLADYS\Documents\DataVisualization_Final_Integration`.
Branch: `build-fix`. HEAD before and after: `cb30577f9451801199fbbdb954000bc8cb9d5c97`.
The branch started one commit ahead of its existing origin tracking reference; no network synchronization was attempted.
The index and working tree were clean at the start. The recovery work was already present in this current commit; no older snapshot or GitHub main was substituted.

All 47 tracked C++ headers/implementation/example/test files and all 3 tracked build records were reviewed and commented. Comments explain actual behavior, parameters, return/error contracts, significant branches and loops, validation, mathematics, ownership, coordinate mapping and OOP. Formatting expands compact statements while retaining their executable tokens. The README now has a current usage/verification preface, retaining its original text. This report is new.

No algorithms, declarations, signatures, includes, constants, string literals, assertions or CMake command tokens were changed. No code simplification or functional repair was attempted in this documentation pass.

## Preservation and diff review

- Captured exact pre-edit copies of all 50 source/build files plus Git status, history and staged/unstaged patches before edits.
- Compared every current C++ file using a lexer that retains literals, identifiers, numbers and operators while excluding comments and insignificant whitespace: **47/47 PASS**. CMake command-token comparison: **3/3 PASS**. This is a source-equivalence check, not a claim that Debug executable bytes stay identical after line-number changes.
- Full Git diff saved and reviewed with the token comparison, module audits and whitespace check. `git diff --check`: **PASS**. No tracked files were deleted. Current tracked source/build inventory exactly matches the 50-file baseline.
- HEAD, branch, staged diff and index bytes stayed unchanged. Index SHA-256: `7d1665d095508fe2403638e78f9899cd29feb7336703e19d21dd80a23fcd843d`. Existing contributor banners and historical teaching implementations were retained.
- Final intentional source-tree changes: 50 tracked source/build files, 1 tracked README, and this new report. No generated binaries, test fixtures or SVGs were staged or newly tracked; build outputs remain under the ignored `build/` directory. A separate delivery copy of SVGs/evidence is outside the repository.
- No commit, push, merge, branch switch, reset, pull, PR creation, author-setting change, security change or VS Code appearance change was performed.

## Module connections and actual OOP

The demo loads a string `DataSet` with `DataLoader::loadCSV`, then `DataPreprocessor::numericPairs` extracts paired finite X/Y vectors. `Statistics::summarize` consumes Y independently. The same coordinates feed scatter/line plots, while X values are formatted as category names for bars. A non-owning `Plot*` array dispatches `render` virtually. Plots use local linear scales to produce pixel coordinates and ask `Renderer` to build SVG primitives. `Annotation` adds a red point and escaped text. `ImageExporter` delegates through the SVG strategy to `Renderer::saveSVG`.

| Concept | Actual project evidence |
|---|---|
| Encapsulation | Plot vectors, Renderer content/dimensions, scale range, label text and exporter error state are accessed through their interfaces. Plot metadata is protected for derived access; public DataSet/Summary fields are deliberately simple value records. |
| Inheritance | ScatterPlot, BarPlot and LinePlot derive from Plot; LinearScale/PercentageScale derive from AxisScale; AxisLabel/Annotation derive from Label; SvgImageExporter derives from ExportStrategy. |
| Runtime polymorphism | Plot pointers dispatch render; AxisScale pointers dispatch scale; Label references dispatch Annotation rendering; ExportStrategy references dispatch exportPlot. |
| Abstraction | Plot, AxisScale and ExportStrategy declare pure virtual contracts and cannot be directly instantiated. Renderer itself is concrete. |
| Constructors/destructors | Constructors initialize metadata/data/ranges and validate where implemented; virtual base destructors support safe polymorphic destruction. Standard containers/streams own their resources. |
| Templates | Statistics has a static member-function template over numeric vectors. Preserved teaching files demonstrate class/function templates separately. DataLoader/DataPreprocessor/Statistics static utilities do not invent an inheritance hierarchy. |
| Overrides/access | Comments distinguish public API, protected base/strategy helpers, private state, runtime virtual dispatch, and compile-time override signature checks. |

Responsibilities cross-checked against the existing README and `docs/TEAM_FILE_OWNERSHIP.md`: Jackson—loading/export; Gladys—preprocessing/statistics; Adrian—scatter/Renderer coordination; Bonius—scaling; Ivan—labels/report coordination; Sandra—line plots; Jeff—bar plots; integration—group. These are recorded assignments, not new authorship claims. Some historical documents use obsolete filenames; the actual line header is `LinePlot.hpp`.

## Every source/build file reviewed and modified

All paths in this inventory are relative to the repository root above. Every row was modified solely with comments and/or whitespace.

| File | Change type | Main explanations |
|---|---|---|
| `DataVisualization/examples/example_applying_Polymorphism.cpp` | Comments/whitespace | Plot pointer array, virtual dispatch, separate canvases and existing smoke-example limits. |
| `DataVisualization/examples/example_barplot.cpp` | Comments/whitespace | Small category/value example, signed ASCII output and normal process completion. |
| `DataVisualization/examples/example_inheritance.cpp` | Comments/whitespace | Derived plots reuse base metadata/behavior; concrete objects and their inherited calls. |
| `DataVisualization/examples/example_lineplot.cpp` | Comments/whitespace | Ordered vectors, standalone SVG export and catch/report behavior. |
| `DataVisualization/examples/legacy_statistics.cpp` | Comments/whitespace | Preserved double-array statistics exercise, helper preconditions, calculations, loops and terminal demonstration. |
| `DataVisualization/examples/main.cpp` | Comments/whitespace | Complete CSV workflow, Reject policy, stats separate from plot input, Plot* dispatch, annotation, existing output directory and export exceptions. |
| `DataVisualization/include/dataviz/AxisScale.cpp` | Comments/whitespace | Separate teaching executable, abstract dispatch, range normalization, equal midpoint and non-owning pointer examples. |
| `DataVisualization/include/dataviz/AxisScale.h` | Comments/whitespace | Abstract scale contract, private range, construction/validation, virtual methods, LinearScale and PercentageScale. |
| `DataVisualization/include/dataviz/BarPlot.h` | Comments/whitespace | Encapsulated categories/values, signed input, getter lifetime, virtual renderer and ASCII width. |
| `DataVisualization/include/dataviz/DataLoader.h` | Comments/whitespace | DataSet ownership, public fields, dimensions, zero-based access, conversion contracts, loader exceptions. |
| `DataVisualization/include/dataviz/DataPreprocessor.cpp` | Comments/whitespace | Separate teaching hierarchy, copied getters, NaN/infinity zero replacement and explicit write-back; differs from production Reject/DropRow. |
| `DataVisualization/include/dataviz/DataPreprocessor.h` | Comments/whitespace | Stateless production utility, Reject/DropRow policy, paired vectors, column parameters and errors. |
| `DataVisualization/include/dataviz/ImageExporter.h` | Comments/whitespace | Abstract strategy, virtual destruction/dispatch, override signature checks, private error and protected path helper, static convenience API. |
| `DataVisualization/include/dataviz/Labels.cpp` | Comments/whitespace | Separate historical labels executable, private state, constructors, display override, association and non-owning objects. |
| `DataVisualization/include/dataviz/Labels.h` | Comments/whitespace | Production private text, constructors, reference lifetime, virtual destructor/render, AxisLabel reuse and Annotation override. |
| `DataVisualization/include/dataviz/LinePlot.hpp` | Comments/whitespace | Inherited metadata, LineSegment values, constructors, data/size/segment contracts, validation and standalone export. |
| `DataVisualization/include/dataviz/Plot.h` | Comments/whitespace | Protected shared metadata, public getters/setters, abstract render, virtual destructor and no-op exportData compatibility hook. |
| `DataVisualization/include/dataviz/Renderer.h` | Comments/whitespace | Concrete drawing responsibility, pixel convention, Point structure, every drawing contract, dimensions and private helpers. |
| `DataVisualization/include/dataviz/ScatterPlot.h` | Comments/whitespace | Public inheritance, paired private vectors, constructors, ASCII glyph versus SVG radius, validation and rendering/export methods. |
| `DataVisualization/include/dataviz/Statistics.h` | Comments/whitespace | Summary fields, member-function template, input copy, Welford mean/variance, sorting, odd/even median, population standard deviation. |
| `DataVisualization/src/AxisScale.cpp` | Comments/whitespace | Validation before update, normalization, negative ranges, constant-range midpoint and extrapolation. |
| `DataVisualization/src/BarPlot.cpp` | Comments/whitespace | Signed ASCII zero column, zero-inclusive SVG ranges, category placement, nonnegative rectangle geometry and visible zero line. |
| `DataVisualization/src/DataLoader.cpp` | Comments/whitespace | CSV flags and local lambdas, quoted/newline/escaped fields, CRLF and EOF, whitespace, conversion consumption, rectangular rows and errors. |
| `DataVisualization/src/DataPreprocessor.cpp` | Comments/whitespace | Per-row numeric extraction, finite checks, keeping X/Y together, reject versus skip, empty results. |
| `DataVisualization/src/ImageExporter.cpp` | Comments/whitespace | Actual case-sensitive .svg validation, bool/error behavior, clear diagnostics, Renderer delegation and no directory creation. |
| `DataVisualization/src/Labels.cpp` | Comments/whitespace | Preserved separate global-class teaching program with main, inheritance, display dispatch, association and stack-object lifetime. |
| `DataVisualization/src/LinePlot.cpp` | Comments/whitespace | Input-order segments, reserve/loop, XML escaping, local coordinate lambdas, constant ranges, standalone grid/ticks and shared Renderer path. |
| `DataVisualization/src/Plot.cpp` | Comments/whitespace | Why this production translation unit remains although base methods are inline. |
| `DataVisualization/src/Renderer.cpp` | Comments/whitespace | Canvas background/order, validation, five XML entities, primitive attributes, polyline/bar loops, save status and numeric-tick math/formatting. |
| `DataVisualization/src/ScatterPlot.cpp` | Comments/whitespace | Delegating constructors, finite values/radius, bounds, local axis scales, downward SVG Y, filled circles and ASCII grid/index/overlap handling. |
| `DataVisualization/src/Statistics.cpp` | Comments/whitespace | Preserved array-template teaching functions and main, loop mathematics and positive-count preconditions; distinguished from production Summary. |
| `DataVisualization/src/template.cpp` | Comments/whitespace | Standalone class-template exercise, coordinate type parameter, private members, base construction and runtime virtual dispatch. |
| `DataVisualization/src/templates.cpp` | Comments/whitespace | Standalone array-template statistics, positive-count assumptions, search/sum loops, squared deviations and display guard. |
| `DataVisualization/src/templatestruct.cpp` | Comments/whitespace | Public struct versus private class, initialization, inheritance, virtual display, direct field updates and pointers. |
| `DataVisualization/tests/test_bar.cpp` | Comments/whitespace | Bar construction/count and exact signed ASCII zero-column expectations. |
| `DataVisualization/tests/test_data_loading.cpp` | Comments/whitespace | CSV fixtures, dimensions, quoted/missing/numeric access, rectangular validation and exception expectations. |
| `DataVisualization/tests/test_image_export.cpp` | Comments/whitespace | Strategy inheritance/dispatch, private diagnostics through getters, saved SVG and invalid output requests. |
| `DataVisualization/tests/test_integration.cpp` | Comments/whitespace | Reject/DropRow through statistics, three polymorphic plots, annotation XML escaping, exports and constant range. |
| `DataVisualization/tests/test_labels.cpp` | Comments/whitespace | Text mutation, base-reference annotation dispatch and escaped SVG text. |
| `DataVisualization/tests/test_line.cpp` | Comments/whitespace | Minimal valid segment/data path and invalid input expectations. |
| `DataVisualization/tests/test_lineplot.cpp` | Comments/whitespace | Data validation, metadata, ordered segments, standalone SVG output and exception checks. |
| `DataVisualization/tests/test_plot_behavior.cpp` | Comments/whitespace | Shared base metadata, compatibility hook, ASCII glyph, circular marker radius/style/positions, signed data, ticks and signed zero baselines. |
| `DataVisualization/tests/test_preprocessing.cpp` | Comments/whitespace | Paired extraction, missing/nonfinite rejection, dropped rows, indices and no remaining valid data. |
| `DataVisualization/tests/test_renderer.cpp` | Comments/whitespace | Primitive drawing smoke test and save success; explicitly distinguishes export success from geometry assertions. |
| `DataVisualization/tests/test_scaling.cpp` | Comments/whitespace | Linear/percentage dispatch, constant range and the numeric assertions beyond printed examples. |
| `DataVisualization/tests/test_scatter.cpp` | Comments/whitespace | Point count/render smoke checks and invalid vectors; explicitly states limits of its SVG assertions. |
| `DataVisualization/tests/test_statistics.cpp` | Comments/whitespace | Production Summary expectations, numeric tolerances, odd/even median and rejected empty/nonfinite inputs. |
| `CMakeLists.txt` | Comments/whitespace | CMake minimum/project, mandatory C++17, extensions disabled, CTest and module inclusion. |
| `DataVisualization/CMakeLists.txt` | Comments/whitespace | All eleven library source units, public include propagation, warning flags, thirteen assert-enabled isolated tests and separate examples/legacy executables. |
| `Cmakelist.txt` | Comments/whitespace | Historical misnamed build proposal; explicitly identifies that CMake does not select it as the active root configuration. |

Additional documentation changes: `DataVisualization/README.md` (current instructions prefixed; original text retained byte for byte), and `DataVisualization/docs/COMMENTING_REVIEW_REPORT.md` (this new report).
Supporting documents consulted without modification: `docs/TEAM_FILE_OWNERSHIP.md`, `docs/PROJECT_ARCHITECTURE.md`, `docs/BEHAVIOR_REPAIR_REPORT.md`, and existing integration/verification documentation where relevant. Existing reports and historical generated examples were preserved.

## Compilation and production coverage

Compiler: **GCC 16.2.0**, `C:\msys64\ucrt64\bin\g++.exe`.
CMake: **4.4.5**, `C:\Program Files\CMake\bin\cmake.exe`.
Existing working build reused: `build/behavior-repair`, Ninja, Debug. CMake automatically regenerated successfully after the comment changes. No clean-directory reset was needed for this comment-only task.

Full builds completed successfully, including all examples and preserved teaching targets. The final full formatting rebuild completed all 62 steps, followed by a successful two-step csv_demo rebuild after one final comment correction. No compiler warnings or errors were emitted in these captured build logs.

Archive membership and compile_commands inspection confirm all **11** production objects, each with `-std=c++17`: Plot, AxisScale, Renderer, ScatterPlot, BarPlot, LinePlot, DataLoader, DataPreprocessor, Statistics, Labels, ImageExporter.
Labels.cpp and Statistics.cpp still contain teaching main functions, described under remaining issues; compiling all source objects does not prove those unused archive objects are suitable for every consumer/link mode.

Reproduce this existing build in PowerShell:

```powershell
$project = 'C:\Users\GLADYS\Documents\DataVisualization_Final_Integration'
$env:PATH = 'C:\msys64\ucrt64\bin;' + $env:PATH
& 'C:\Program Files\CMake\bin\cmake.exe' --build "$project\build\behavior-repair" --parallel 4
& 'C:\Program Files\CMake\bin\ctest.exe' --test-dir "$project\build\behavior-repair" --output-on-failure
```

These are the commands actually used, with logs/JUnit files additionally captured outside the project. Assertions remain enabled by the existing test target `-UNDEBUG` setting. No tests were weakened or excluded.

## All 13 final CTest results

CTest exit code: **8**, because two programs could not start. CTest labels them BAD_COMMAND/failures; this report classifies them as BLOCKED based on the independent Windows launch errors. Final total time: approximately 14.28 seconds.

| Test name | Final result | Evidence |
|---|---|---|
| `bar` | PASS | Exit 0; 1.69 s. |
| `data_loading` | PASS | Exit 0; 1.70 s. |
| `image_export` | PASS | Exit 0; 0.95 s. |
| `lineplot` | PASS | Exit 0; 0.81 s. |
| `renderer` | PASS | Exit 0; 0.89 s. |
| `scaling` | BLOCKED — not run | Application Control 4551; no test assertions executed. |
| `scatter` | PASS | Exit 0; 1.08 s. |
| `integration` | PASS | Exit 0; 1.09 s. |
| `statistics` | PASS | Exit 0; 1.25 s. |
| `preprocessing` | PASS | Exit 0; 1.00 s. |
| `labels` | PASS | Exit 0; 0.83 s. |
| `line` | PASS | Exit 0; 0.78 s. |
| `plot_behavior` | BLOCKED — not run | Application Control 4551; no test assertions executed. |

The earlier build in this same pass had 9 PASS and 4 BLOCKED (bar, data_loading, renderer, labels); scaling and plot_behavior passed on that earlier build. Final formatting changed Debug binary hashes, as expected from source line information. The final build passes those earlier four tests, but scaling and plot_behavior are now blocked. Results from different binaries are **not combined into a claim of 13/13 passing on the final build**.

Some existing individual tests are smoke tests, particularly Renderer/ScatterPlot. The comments accurately describe their assertion limits. Broader marker/signed-chart checks are present in plot_behavior, but that test did not run for the final binary. The independently verified CSV geometry supplies useful evidence without replacing the blocked test.

## Windows Application Control: confirmed block and limits

A direct diagnostic launch in the same authorized test directory confirmed `System.ComponentModel.Win32Exception`, native code **4551**, with **“An Application Control policy has blocked this file.”** Both final blocked executables are unsigned (`NotSigned`). No policy setting, signing state, path, filename, executable bytes or execution environment was altered to work around security.

Final paths:

- `C:\Users\GLADYS\Documents\DataVisualization_Final_Integration\build\behavior-repair\DataVisualization\test_scaling.exe`
- `C:\Users\GLADYS\Documents\DataVisualization_Final_Integration\build\behavior-repair\DataVisualization\test_plot_behavior.exe`

| Executable | Bytes | SHA-256 |
|---|---:|---|
| test_scaling.exe | 91476 | `407693E3CDEA8F7F0F9FCD68A73D192B7120AB33BEBA6BC9DE37A3277AC7F4FD` |
| test_plot_behavior.exe | 1159220 | `8B4EDA1FFF2E295BAC26B641CFE462FF526D5885370D68422C001CA7F705CC83` |

Reading `Microsoft-Windows-CodeIntegrity/Operational` for events 3033/3077 was denied with “Attempted to perform an unauthorized operation.” The event IDs in the user’s earlier report are historical context, not newly observed events. The exact policy ID, signer requirement or signing level therefore remains **unknown**. Unsigned status alone does not prove the cause; other unsigned tests in the same directory passed, so a blanket location/unsigned-file explanation is not established.

An administrator can correlate the final test timestamp (JUnit: `2026-11-06T14:46:41`, as emitted by CTest), paths and SHA-256 values with Code Integrity events and the organization’s active policy, then provide an approved test/signing environment. No alternate execution environment was assumed authorized. Until the two final executables run under approved policy, their assertions remain unverified.

## CSV demonstration and SVG verification

Input: `DataVisualization/data/demo.csv` (not the separate positive-only `sample.csv`). Paired rows: `(1,-2), (2,3), (3,1), (4,6), (5,4)`.
The final csv_demo executable exited **0**, printing:

```text
Rows: 5 Mean: 2.4 Median: 3 Population variance: 7.44
```

The current application requires an existing destination directory. A new isolated directory was created for this review; the repository’s earlier demo_output files were not overwritten:

```powershell
$demoOutput = "$project\build\behavior-repair\comment-review-demo"
New-Item -ItemType Directory -Force -Path $demoOutput | Out-Null
& "$project\build\behavior-repair\DataVisualization\csv_demo.exe" "$project\DataVisualization\data\demo.csv" $demoOutput
```

All three SVGs were parsed as XML with the correct SVG namespace, opened by the SVG rasterizer, rendered and visually inspected at 800×600. Titles, numerical ticks, X/Y labels, annotation, blue markers, signed bar baseline and line segments were visible. Every generated file matches its pre-existing repository demo_output counterpart **byte for byte**.

| SVG | Result | Verified geometry |
|---|---|---|
| scatter.svg | PASS, 3302 bytes | Five blue filled circles, dark outline, radius 5. Centers: (80,520), (245,232.5), (410,347.5), (575,60), (740,175). Negative Y=-2 correctly maps to the lower endpoint. |
| bar.svg | PASS, 2861 bytes | Five signed rectangles, width 81.6. Zero baseline Y=405 with “0 (zero)” label. Negative bar extends downward to Y=520; positive bars extend upward to their scaled Y values. |
| line.svg | PASS, 3461 bytes | Five data centers: (80,520), (250,232.5), (420,347.5), (590,60), (760,175), joined by four consecutive steelblue segments. |

The red annotation circle at (500,40), radius 3, is separate from the five data observations. Scatter’s right margin differs from LinePlot’s; this is existing behavior. Every verified Y position follows `520 - (y + 2) / 8 * 460` for this dataset. The bar rectangle top/height pairs are (405,115), (232.5,172.5), (347.5,57.5), (60,345), (175,230).

## Remaining issues and proposed changes requiring approval

1. **Two final tests are security-blocked.** No assertion failure was demonstrated, but full final verification cannot be claimed. Have an administrator provide an approved environment and rerun all 13 tests for the same source revision.
2. **Teaching main functions in production archive sources.** Current src/Labels.cpp and src/Statistics.cpp contain standalone teaching main functions while CMake archives them into dataviz. The production APIs are inline/header based, so current consumers normally leave those objects unextracted. Whole-archive, shared-library or future linkage can expose duplicate entry points. Proposal: retain the teaching implementations in explicit separate executable targets and remove entry-point objects from the library target. This changes build structure and has NOT been done.
3. **Duplicate LinePlot rendering paths.** Standalone saveSvg has richer grid/tick/rotation code; Renderer rendering shares the other plot infrastructure. Proposal: extract named mapping/layout helpers while preserving each public output contract. No consolidation was done.
4. **Compact statistics expressions and CSV state flags.** The median ternary and incremental `++n` expression are now explained; explicit if/else and a named parser-state enum/helper functions could be easier for beginners. Those would change executable tokens/control structure and await approval.
5. **Legacy teaching preconditions differ from production validation.** Array helpers assume valid arrays/positive counts; teaching preprocessing replaces nonfinite values with zero, whereas production numericPairs rejects or drops whole rows. Comments distinguish these policies. Adding legacy guards or unifying interfaces is a functional decision.
6. **Numerical/resource/layout limits.** Extreme finite values can overflow sums/range arithmetic. Parallel vector insertion can lose its size invariant on allocation failure. Very large ASCII sizes/radii, dense/long labels and fixed margins have no comprehensive resource/layout policy. Proposal: define limits and stronger storage/numerical behavior with targeted tests. None was introduced here.
7. **Formatting and documentation differences.** Renderer numeric tick formatting explicitly uses the classic locale while another numeric string helper uses its stream locale. Historical architecture/report text mentions PNG or older filenames, although current export is SVG only; the README preface and this report state current behavior without deleting those historical contributions. A full historical-document rewrite was not performed.
8. **Compatibility limits remain explicit.** Plot::exportData is a preserved no-op extension hook, not a data-file exporter. Scale classes exist, but plot rendering builds its own local linear scales; comments do not imply a public custom-scale injection API. No missing compatibility feature was silently invented.

These proposals are for a separately approved functional change. No permission is needed to retain the completed comments/whitespace documentation pass; no proposed refactor has been applied.

## Readiness assessment

The complete source is now easier to explain in a line-by-line defense, the current build succeeds, and the sample CSV-to-SVG demonstration is verified. **Ready for a supervised presentation of the verified workflow, with the two security blocks and the teaching/library distinction disclosed. Not fully verified for final submission or unrestricted library release.** Full submission sign-off requires the two blocked final tests to run in an approved environment and a decision on the retained teaching-entry-point/library structure. Existing historical reports should not be cited as current test results.
