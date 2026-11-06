# CMP2103 file-structure repair and final verification

Date: 2026-11-06. Makerere University, C++17 Data Visualization Library.

## Outcome

**Structure PASS. Clean configure/build PASS. Final complete CTest PASS: 13/13, 0 FAIL, 0 BLOCKED. CSV-to-SVG demonstration PASS.**

Repository: `C:\Users\GLADYS\Documents\DataVisualization_Final_Integration`. Branch: **build-fix**. HEAD remains `cb30577f9451801199fbbdb954000bc8cb9d5c97`. Initial status contained the completed commenting work (51 tracked modifications and the untracked commenting report); it was preserved rather than restored from GitHub or an older commit. There were no staged changes at the checkpoint; the index bytes and staged diff remain unchanged. No commit, push, merge, reset, branch switch, PR, author-setting change or VS Code appearance change was performed.

The earlier blocked artifact observations and the first fresh Renderer startup failure are recorded separately below. A passing current suite does not claim that Windows organizational policy is disabled, changed or universally resolved.

## Safe recovery checkpoint

Before project edits, saved **113 non-build working-tree files** to:

`C:\Users\GLADYS\Documents\Codex\2026-11-05\you-are-a-senior-c-software\outputs\structure_repair\checkpoint-20261106-150525-7c1ceee6\current-worktree.zip`

The archive includes existing comments, reports, untracked documentation, examples, configuration and project assets. ZIP integrity and every file SHA-256 were verified. Adjacent `manifest.json`, exact staged/unstaged patches, Git status/history and `git-index.bin` capture the branch/commit/index state. The archive SHA-256 is `e00905709fcec54ab17788951448a26a93363060a543afb3a1c062a27f6ab739`. Generated `build/` and the `.git` object database were excluded; the repository history remains untouched in its original location.

To inspect recovery material, extract the ZIP into a new empty directory and compare with the live project. Do not blindly extract over the working repository. This checkpoint was created under a unique new name and overwrote no prior backup.

## Original structural problems and corrections

- Three `.cpp` files in include/dataviz were independent teaching programs, each with main(), not reusable public interfaces or production implementations.
- src/Labels.cpp and src/Statistics.cpp were teaching programs containing main(), yet were archived into the production library. Current inline/template header APIs let normal clients avoid extracting those objects, which hid a potential duplicate-entry-point/whole-archive linking defect.
- Three additional template lessons in src also had application entry points. They were already separate executable targets, but belonged in examples.
- The two historical terminal Labels programs contain the same executable implementation; one had an additional introductory build comment. Both were preserved under distinct provenance names. The template statistics lesson and existing examples/legacy_statistics.cpp are distinct exercises and both remain.

All eight teaching programs now live in examples/teaching. The production src/Labels.cpp and src/Statistics.cpp paths contain small documented header-including translation units. Public inline label methods and Statistics::summarize templates remain in their existing headers. The production APIs, algorithms, class structure, data flow and assertions are unchanged.

## Files moved and teaching targets

Paths below are relative to DataVisualization/. Each relocated program keeps its original executable C++ tokens and meaningful explanatory comments; obsolete location/build notes were updated.

| Previous location | Current location | Standalone target |
|---|---|---|
| `include/dataviz/AxisScale.cpp` | `examples/teaching/axis_scale_inheritance.cpp` | `legacy_AxisScale` â€” Existing target retained |
| `include/dataviz/DataPreprocessor.cpp` | `examples/teaching/data_preprocessor_inheritance.cpp` | `legacy_DataPreprocessor` â€” Existing target retained |
| `include/dataviz/Labels.cpp` | `examples/teaching/labels_include_demo.cpp` | `legacy_Labels` â€” Existing target retained |
| `src/Labels.cpp` | `examples/teaching/labels_src_demo.cpp` | `teaching_labels` â€” New separate teaching target |
| `src/Statistics.cpp` | `examples/teaching/statistics_array_templates.cpp` | `teaching_statistics` â€” New separate teaching target |
| `src/template.cpp` | `examples/teaching/label_class_template.cpp` | `teaching_template` â€” Existing target retained |
| `src/templates.cpp` | `examples/teaching/statistics_templates.cpp` | `teaching_templates` â€” Existing target retained |
| `src/templatestruct.cpp` | `examples/teaching/label_struct_template.cpp` | `teaching_templatestruct` â€” Existing target retained |

Existing `examples/legacy_statistics.cpp`, library examples, the integrated main and all tests were retained at their previous paths. No independent example was removed or silently deduplicated.

Other changes in this phase:

| File | Change |
|---|---|
| `src/Labels.cpp` | Production Labels.h anchor replaces the relocated teaching content. |
| `src/Statistics.cpp` | Production Statistics.h template anchor replaces the relocated teaching content. |
| `include/dataviz/Labels.h` | Comment-only reference update to the relocated terminal lessons. |
| `include/dataviz/Statistics.h` | Comment-only explanation of header template definitions and new lesson location. |
| `include/dataviz/DataPreprocessor.h` | Comment-only path update to the separate preprocessing lesson. |
| `CMakeLists.txt` inside DataVisualization | Explicit multiline production list, eight new source locations, two new independent teaching targets, retained test/example targets. |
| `README.md` | Current structure/configure/test/demo instructions and links; original group section retained byte for byte. |
| `docs/PROJECT_ARCHITECTURE.md` | Accurate current workflow and production/teaching organization; original planning diagram retained as historical. |
| `docs/STRUCTURE_REPAIR_REPORT.md` | New report with final tree, changes and full results. |
| `docs/ADMIN_TEST_AUTHORIZATION.md` | New diagnostic evidence and administrator handoff. |

The active repository-root CMakeLists.txt and historical Cmakelist.txt were retained unchanged relative to the checkpoint. Earlier reports, weekly contributions, demo_output and all unrelated project files were retained. Git may show old tracked paths as deleted plus new untracked destinations until changes are reviewed/staged; these are verified relocations. Six old pathnames disappear, while the two production source names are reused as anchors. No group code was discarded.

## Final source directory tree

```text
CMakeLists.txt                    (active C++17 root build)
Cmakelist.txt                     (retained inactive historical proposal)
DataVisualization/
  CMakeLists.txt
  README.md
  include/dataviz/
    AxisScale.h
    BarPlot.h
    DataLoader.h
    DataPreprocessor.h
    ImageExporter.h
    Labels.h
    LinePlot.hpp
    Plot.h
    Renderer.h
    ScatterPlot.h
    Statistics.h
  src/
    AxisScale.cpp
    BarPlot.cpp
    DataLoader.cpp
    DataPreprocessor.cpp
    ImageExporter.cpp
    Labels.cpp
    LinePlot.cpp
    Plot.cpp
    Renderer.cpp
    ScatterPlot.cpp
    Statistics.cpp
  examples/
    example_applying_Polymorphism.cpp
    example_barplot.cpp
    example_inheritance.cpp
    example_lineplot.cpp
    legacy_statistics.cpp
    main.cpp
    teaching/
      axis_scale_inheritance.cpp
      data_preprocessor_inheritance.cpp
      label_class_template.cpp
      label_struct_template.cpp
      labels_include_demo.cpp
      labels_src_demo.cpp
      statistics_array_templates.cpp
      statistics_templates.cpp
  tests/
    test_bar.cpp
    test_data_loading.cpp
    test_image_export.cpp
    test_integration.cpp
    test_labels.cpp
    test_line.cpp
    test_lineplot.cpp
    test_plot_behavior.cpp
    test_preprocessing.cpp
    test_renderer.cpp
    test_scaling.cpp
    test_scatter.cpp
    test_statistics.cpp
  data/
    demo.csv
    sample.csv
  docs/
    STRUCTURE_REPAIR_REPORT.md
    ADMIN_TEST_AUTHORIZATION.md
    COMMENTING_REVIEW_REPORT.md      (preceding evidence retained)
    PROJECT_ARCHITECTURE.md
    other existing group reports retained
build/structure-repair/             (generated; ignored by Git)
```

There are now **11 public headers**, **11 production source files**, **14 example programs** (including the eight relocated lessons) and **13 tests**: 49 C++ files in total. No `.cpp` remains under include; src contains only the eleven production units.

## CMake and linkage verification

The active root selects standard C++17 and includes DataVisualization. The module library still compiles Plot, AxisScale, Renderer, ScatterPlot, BarPlot, LinePlot, DataLoader, DataPreprocessor, Statistics, Labels and ImageExporter. All tests and library-using examples still link dataviz. All thirteen tests retain their original names, assertions and isolated working directories; -UNDEBUG remains active.

The clean generated compile_commands inventory contains **38 compile commands across 28 targets**: one library with eleven source files and 27 executables. Every source path exists and every compile command uses `-std=c++17`. All prior target names are present; `teaching_labels` and `teaching_statistics` are added for the formerly archived entry points.

Archive inspection confirms exactly eleven production object members. Symbol inspection finds no production main definition. A separate **link-only** client with `--whole-archive` successfully links every object, demonstrating that the duplicate-main hazard has been removed; that probe is not a substitute for any registered test and was not executed.

## Independent review of the two previously blocked tests

| Original test | Assertions and correctness |
|---|---|
| test_scaling.cpp | Linear range [0, 100] with width 500 maps 50 to 250; PercentageScale maps 50 to 50; equal range [10, 10] with width 500 maps 10 to 250. These expected values are exactly representable. The same abstract pointer dispatches scale to both concrete classes; some other printed examples are demonstrations beyond the three assertions. |
| test_plot_behavior.cpp | Shared inherited title/axis metadata; XML escaping in both LinePlot paths; no-op compatibility hook; exact4Ã—2 ASCII marker output; blue circular SVG centers/style; radius 5 and configurable 8; rejected 0/negative/infinity/NaN radii without state change; signed scatter positions; signed ASCII bars; zero baseline Y=290 for range [-2, 2]; numerical tick values; negative-only/all-zero bars. The current implementation matches these expectations. |

No assertion error, incorrect expected value, dependency defect or target-definition defect was found. Both original test source files remained unchanged, as did all eleven other tests. No test replacement, skip or assertion weakening was used.

Required GCC runtime DLLs are libgcc_s_seh-1.dll, libstdc++-6.dll and transitively libwinpthread-1.dll; all exist under C:/msys64/ucrt64/bin, which was on PATH. Runtime library availability does not override an Application Control decision.

## Clean configuration and build

Tools independently checked: **GCC 16.2.0**, **CMake 4.4.5**, Ninja. Fresh directory: **build/structure-repair**, absent before configuration. Debug, standard C++17. It was chosen to verify the reorganized source lists without stale build objects. The older build directory and its artifacts were preserved.

Configure exit 0. Full build exit 0, **66/66 steps**, including all production modules, thirteen tests, CSV integration, library examples and all nine standalone teaching targets. No compiler warning/error was emitted in the captured clean build log.

Exact PowerShell commands:

```powershell
$project = 'C:\Users\GLADYS\Documents\DataVisualization_Final_Integration'
$build = "$project\build\structure-repair"
$env:PATH = 'C:\msys64\ucrt64\bin;' + $env:PATH
& 'C:\Program Files\CMake\bin\cmake.exe' -S $project -B $build -G Ninja '-DCMAKE_BUILD_TYPE=Debug' '-DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe' '-DCMAKE_MAKE_PROGRAM=C:/PROGRA~1/MATLAB/R2025b/toolbox/shared/coder/ninja/win64/ninja.exe' '-DCMAKE_EXPORT_COMPILE_COMMANDS=ON'
& 'C:\Program Files\CMake\bin\cmake.exe' --build $build --parallel 4
& 'C:\Program Files\CMake\bin\ctest.exe' --test-dir $build --output-on-failure
$demoOutput = "$build\structure-review-demo"
New-Item -ItemType Directory -Force -Path $demoOutput | Out-Null
& "$build\DataVisualization\csv_demo.exe" "$project\DataVisualization\data\demo.csv" $demoOutput
```

The installed Ninja path above is machine-specific. Logs/JUnit were additionally captured outside the project. The final complete CTest command returned **0**.

## Final individual CTest results

Final suite: **13 PASS, 0 FAIL, 0 BLOCKED, 0 skipped**, total approximately **0.82 seconds**. JUnit timestamp `2026-11-06T15:12:22` as emitted by CTest.

| Test | Final result | Seconds |
|---|---|---:|
| `bar` | PASS | 0.038 |
| `data_loading` | PASS | 0.050 |
| `image_export` | PASS | 0.061 |
| `lineplot` | PASS | 0.051 |
| `renderer` | PASS | 0.055 |
| `scaling` | PASS | 0.044 |
| `scatter` | PASS | 0.039 |
| `integration` | PASS | 0.051 |
| `statistics` | PASS | 0.051 |
| `preprocessing` | PASS | 0.053 |
| `labels` | PASS | 0.060 |
| `line` | PASS | 0.115 |
| `plot_behavior` | PASS | 0.078 |

## Startup/security observations kept separate

1. Before restructuring, direct launches of the two older behavior-repair binaries confirmed Application Control 4551. Their original paths/hashes remained unchanged. Their assertion results were not inferred from later binaries.
2. First fresh full CTest: **12 PASS and Renderer NOT RUN/BAD_COMMAND**, unknown launch error; exit 8. CTest supplied no Windows native code for that attempt.
3. Diagnostic launch of the same fresh Renderer path/hash succeeded with exit 0 and created renderer_demo.svg. No Windows native security error was returned for this diagnostic. Therefore the initial fresh Renderer startup issue has an **unknown cause**, not a newly confirmed 4551 block.
4. One complete follow-up CTest then passed all 13. SHA-256 checks confirm every test executable was unchanged between those runs; there was no rebuild, rename or security change between them. This rerun resolved the outstanding question of whether the same complete fresh suite could execute.

The exact enterprise policy rule/signing level for the older blocks remains unavailable: the read-only Code Integrity log query for historical IDs 3033/3077 was denied. No policy/settings/signing changes or alternate execution environment were used. See **ADMIN_TEST_AUTHORIZATION.md** and diagnostic JSON for paths, timestamps, hashes and authorization guidance. Current success does not establish a permanent exemption or explain the transient startup failure.

## CSV demonstration and SVG checks

The existing final csv_demo executable exited0 using existing `DataVisualization/data/demo.csv`. It read the signed pairs `(1,-2), (2,3), (3,1), (4,6), (5,4)` and printed independently verified output:

```text
Rows: 5 Mean: 2.4 Median: 3 Population variance: 7.44
```

It wrote to the new dedicated `build/structure-repair/structure-review-demo` folder. It requires the caller to create the output folder; no unrelated demonstration files were overwritten.

All outputs parsed as XML with the SVG namespace, width 800, height 600 and viewBox 0 0 800 600. Each was opened by the SVG rasterizer, rendered toPNG solely for inspection and visually checked. XML/geometry checks and byte comparison against existing demo_output all passed; the production library still exports SVG only.

| Generated SVG | Result | Checked geometry |
|---|---|---|
| scatter.svg | PASS; 3302 bytes | Five radius 5 blue circles with dark outline. Centers (80,520),(245,232.5),(410,347.5),(575,60),(740,175). Negative Y preserved. |
| bar.svg | PASS; 2861 bytes | Five width 81.6 signed bars; zero baseline Y=405 labeled 0 (zero). Top/height pairs (405,115),(232.5,172.5),(347.5,57.5),(60,345),(175,230). |
| line.svg | PASS; 3461 bytes | Five centers (80,520),(250,232.5),(420,347.5),(590,60),(760,175); four consecutive steelblue segments. |

All three contain titles, axis labels, readable numerical ticks and a separate red annotation circle (500,40), radius 3. Generated SVG bytes exactly match their existing demo_output counterparts, supporting preserved plot behavior. Rasterized preview PNGs are verification artifacts outside the repository, not a new export feature.

## Preservation, comments and final diff

- Checkpoint-to-current comparison maps each original file to its current location. **47/47 original C++ token streams match**, including all moved teaching algorithms and every production API. Two new header anchors account for the increase to 49 C++ files.
- **All 13 test source hashes are identical** to the checkpoint. Original function/block comments were retained; only obsolete path/build notes were revised. Group banners/authorship were preserved.
- All unrelated original files are byte-identical. Original group README content and historical architecture content are retained. The preceding COMMENTING_REVIEW_REPORT remains byte-identical and is clearly referenced as earlier evidence.
- Full Git diff and a separate phase-only working-tree diff were reviewed. `git diff --check`: PASS. Every removed pathname is accounted for by the move map; no accidental deletion occurred. The index, staged diff, HEAD and branch match the checkpoint. All new example/report files remain unstaged for review. No generated SVG/binary was staged or newly tracked.

## Remaining limitations and readiness

The structural problems in scope are repaired and verified. No genuine test-logic defect or regression remains demonstrated. **The restructured current build is ready for presentation/submission on the verified Windows/GCC environment: clean build, all 13 tests and CSV/SVG demonstration pass.** Preserve the first-run startup evidence and administrator notes; successful execution here does not guarantee every future enterprise-controlled machine or older binary will be allowed.

Existing functional limits remain: SVG-only output; fixed margins/simple dense-label layout; no public plot custom-scale injection; Plot::exportData remains a no-op extension hook; legacy teaching programs have documented weaker validation; extreme finite numeric ranges/allocation failures are not exhaustively guarded. LinePlot retains separate Renderer and standalone SVG paths. These unrelated algorithms/interfaces were not rewritten.

No security was disabled or bypassed. If the exact older blocked artifacts must run, an administrator must determine an approved signing/authorization/testing route using the accompanying evidence. No further source edits are required to explain those already-confirmed policy blocks.
