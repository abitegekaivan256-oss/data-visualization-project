# Application Control evidence for CMP2103 test programs

Date: 2026-11-06. Repository: `C:\Users\GLADYS\Documents\DataVisualization_Final_Integration`. Branch: build-fix; HEAD: `cb30577f9451801199fbbdb954000bc8cb9d5c97` with uncommitted documentation/structure changes.

## Current outcome

The new, clean `build/structure-repair` configuration builds successfully and the final full CTest run executes **all 13 original tests successfully**. Test source files are byte-identical to the checkpoint. No Windows policy, certificate, executable name, assertion or compiler/runtime security setting was changed. There is no current test block in that final run.

The two earlier `build/behavior-repair` artifacts were separately diagnosed at the beginning of this task and **remain confirmed blocked artifacts in that observation**. Passing current build results do not establish that those older binary hashes are authorized or that the organizational policy has been repaired.

## Confirmed older blocked executables

- `C:\Users\GLADYS\Documents\DataVisualization_Final_Integration\build\behavior-repair\DataVisualization\test_scaling.exe`
- `C:\Users\GLADYS\Documents\DataVisualization_Final_Integration\build\behavior-repair\DataVisualization\test_plot_behavior.exe`

Both direct attempts failed before the process started with `System.ComponentModel.Win32Exception`, native error **4551**, HRESULT **-2147467259**, and the message **“An Application Control policy has blocked this file.”** Both signatures were `NotSigned`.

| Old test artifact | Diagnostic timestamp (UTC) | Bytes | SHA-256 |
|---|---|---:|---|
| `scaling` | `2026-11-06T12:06:00.2657559Z` | 91476 | `407693E3CDEA8F7F0F9FCD68A73D192B7120AB33BEBA6BC9DE37A3277AC7F4FD` |
| `plot_behavior` | `2026-11-06T12:06:00.6693052Z` | 1159220 | `8B4EDA1FFF2E295BAC26B641CFE462FF526D5885370D68422C001CA7F705CC83` |

Full exception text and end timestamps are in `launch-before.json`. UTC +03:00 is Africa/Nairobi local time; the attempts occurred at approximately 15:06 local time.

## Event/policy evidence and limits

An authorized read-only query of `Microsoft-Windows-CodeIntegrity/Operational`, event IDs **3033 and 3077**, returned **“Attempted to perform an unauthorized operation.”** Those event IDs were supplied by the preceding historical report; no new event record ID, policy ID or signing-level data was accessible in this session.

Application Control is confirmed for the two older artifacts by the native errors. The exact active rule, signer requirement, hash reputation or location restriction cannot be determined from the accessible evidence. Unsigned status alone does not establish the cause. Current tests in the same development environment can execute, and the current copies have different hashes following the legitimate clean structural rebuild.

## Current executable identities and launch history

- `C:\Users\GLADYS\Documents\DataVisualization_Final_Integration\build\structure-repair\DataVisualization\test_scaling.exe`
- `C:\Users\GLADYS\Documents\DataVisualization_Final_Integration\build\structure-repair\DataVisualization\test_plot_behavior.exe`
- `C:\Users\GLADYS\Documents\DataVisualization_Final_Integration\build\structure-repair\DataVisualization\test_renderer.exe`

| Current test | SHA-256 | Current observed status |
|---|---|---|
| `scaling` | `B6FF630E76D865CC838C3F01665BD53ABFC7B25C4C6D58B7007CB84F99877E28` | PASS in final CTest |
| `plot_behavior` | `DF1036B1C0F7592DC6647994FC05F1AB0BF292A12D4BA5E09121F359F66423DA` | PASS in final CTest |
| `renderer` | `70C370FA7CB57945230D1BBFC295ABA9E0E0F38F0B005EE960C81DCB021EC665` | PASS in final CTest |

The first fresh CTest run had 12 PASS and one Renderer NOT RUN/BAD_COMMAND with an unknown launch error. A diagnostic launch of that same Renderer path/hash then succeeded (exit 0) at `2026-11-06T12:11:31.0561341Z` through `2026-11-06T12:11:41.7016431Z` UTC. It did not produce a native security error, so the first Renderer launch is not represented as a confirmed 4551 event. A single full follow-up CTest run then passed 13/13 (0.82 seconds; JUnit timestamp `2026-11-06T15:12:22` as emitted by CTest). All 13 executable hashes remained unchanged between the two runs; no rebuild or policy change occurred between them. The transient launch failure's exact cause remains unknown.

## Administrator actions if older artifacts must execute

Use the paths, hashes, UTC timestamps and full errors above to correlate the older attempts with Code Integrity records and the organization's active policy. Determine whether the approved route is its standard signing/authorization process or an existing approved development environment. Obtain organizational authorization before any policy/signing change or execution on another environment. Preserve the unchanged original test sources and rerun the full CTest suite after authorization; do not substitute or weaken the tests.

The final current suite already ran successfully in the existing authorized environment. No alternate environment, security override, executable renaming, signing change or block-evasion step was used. No assertion is inferred to pass for the exact older blocked binaries.

The required GCC runtime DLLs are `libgcc_s_seh-1.dll`, `libstdc++-6.dll` and transitively `libwinpthread-1.dll`, available in `C:\msys64\ucrt64\bin`. That directory was on PATH for the build/tests. Missing runtime DLLs and Application Control 4551 are separate error categories.
