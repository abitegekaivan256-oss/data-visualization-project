# Team File Ownership

Open this page if you are unsure where to work. The same instructions are also written at the top of each allocated file.

| Member | Main responsibility | Files to work on |
|---|---|---|
| Jackson | Data loading | `DataLoader.h`, `DataLoader.cpp`, `test_data_loading.cpp` |
| Gladys | Preprocessing + statistics | `DataPreprocessor.h/.cpp`, `Statistics.h/.cpp`, related tests |
| Adrian | Scatter plots + rendering coordination | `ScatterPlot.h/.cpp`, `test_scatter.cpp`; coordinate `Renderer` |
| Sandra | Line plots | `LinePlot.h`, `LinePlot.cpp`, `test_line.cpp` |
| Jeff | Bar plots | `BarPlot.h`, `BarPlot.cpp`, `test_bar.cpp` |
| Bonius | Axis scaling | `AxisScale.h`, `AxisScale.cpp`, `test_scaling.cpp` |
| Ivan | Labels/annotations + report compilation | `Labels.h/.cpp`, `test_labels.cpp`, `docs/weekly_reports/` |
| Group | Common integration | `Plot.h/.cpp`, `examples/main.cpp` |
| Jackson + Group | Image export | `ImageExporter.h/.cpp` |

## Shared-file rule
`Plot`, `Renderer`, `ImageExporter`, and `examples/main.cpp` affect several modules. Discuss changes to these files before editing them.

## Before you start
1. Pull the latest `main`.
2. Open the files carrying your name.
3. Implement only the agreed weekly target.
4. Test it.
5. Commit the intended files only.
6. Pull once more before pushing.
