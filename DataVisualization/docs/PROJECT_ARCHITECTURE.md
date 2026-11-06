# Current Project Architecture

The reusable library and standalone teaching programs have separate roles. See [the structure repair report](STRUCTURE_REPAIR_REPORT.md) for the exact moved-file inventory and final verification results.

## Data and rendering workflow

```text
CSV file
   |
   v
DataLoader::loadCSV
   |
   v
DataSet (string rows and column names)
   |
   v
DataPreprocessor::numericPairs
   |
   +---- Y values ----> Statistics::summarize ----> Summary
   |
   +---- paired X/Y ----> ScatterPlot / LinePlot / BarPlot
                                   |
                    Plot::render dispatches to the concrete plot
                                   |
                    local data-to-pixel coordinate scaling
                                   |
                                   v
                               Renderer <---- Label / Annotation rendering
                                   |
                                   v
                     ImageExporter / SvgImageExporter
                                   |
                                   v
                            SVG files on disk
```

`examples/main.cpp` is the integration example. Statistics and plots consume the cleaned data independently; a statistical Summary is not a required input to the plots. The bar example formats X values as category names and uses the paired Y values as bar heights.

Production Renderer paths use local linear scales to map data into plot margins. SVG Y coordinates increase down the page, so plotting reverses the normalized Y direction. Signed bars include zero in their range and draw each rectangle between the scaled value and zero baseline. The separate `LinePlot::saveSvg` path provides its own layout and grid logic. Plots do not expose a custom-scale injection API.

Renderer collects drawing elements and escapes XML text. `Annotation::render` adds a red point and text. `ImageExporter::exportSVG` delegates through `SvgImageExporter` to the Renderer file writer. The only implemented image export format is SVG; PNG/JPEG export is not implemented. The current demo expects the caller to create its output directory.

## Source organization

| Location | Responsibility |
|---|---|
| `include/dataviz/*.h`, `*.hpp` | Public production interfaces. Templates and small inline methods remain in headers where required or already implemented. |
| `src/` | Eleven production translation units: Plot, AxisScale, Renderer, ScatterPlot, BarPlot, LinePlot, DataLoader, DataPreprocessor, Statistics, Labels and ImageExporter. No application `main()` belongs here. |
| `examples/teaching/` | Eight preserved standalone lessons moved out of include/src. Each is built independently; historical global classes do not replace the production dataviz classes. |
| `examples/` | CSV integration, inheritance/polymorphism/plot demonstrations and the preserved double-array statistics lesson. |
| `tests/` | Thirteen original test programs linked against the same production library. |
| `data/` | Input CSV fixtures. `demo.csv` is the signed five-row integration dataset; `sample.csv` is a different dataset. |
| Repository `CMakeLists.txt` | Selects C++17, enables testing and includes the module directory. |
| Module `CMakeLists.txt` | Lists production sources, independent executable targets and all thirteen tests. |

Production `Statistics::summarize` is a member-function template in `Statistics.h`. Production SVG Label, AxisLabel and Annotation methods are inline in `Labels.h`. Their `.cpp` files are header-including production translation units. The earlier array-statistics and terminal-label programs live under `examples/teaching/` with their own entry points.

## Actual object-oriented relationships

- `Plot` is abstract and owns shared metadata. ScatterPlot, BarPlot and LinePlot override virtual render; the CSV demo calls them through non-owning Plot pointers.
- `AxisScale` is abstract; LinearScale and PercentageScale implement scale.
- Production AxisLabel and Annotation inherit Label. Annotation overrides rendering. Historical terminal Labels lessons use a different association and are separate examples.
- ExportStrategy is abstract; SvgImageExporter overrides exportPlot. Renderer is a concrete drawing class.
- DataLoader, DataPreprocessor and Statistics expose stateless utility operations. DataSet and Summary are public value records. These utilities do not have an invented inheritance hierarchy.

## Historical planning diagram retained

The original document below is retained as coursework history. Its final `PNG / Image` label describes an earlier plan, not an implemented exporter, and its arrows simplify dependencies. The workflow above describes the current code.

# Project Architecture

```text
CSV / Data File
      |
      v
  DataLoader
      |
      v
DataPreprocessor ----> Statistics
      |
      v
     Plot
  /    |    \
 v     v     v
Scatter Line   Bar
   \    |    /
    AxisScale
        |
      Labels
        |
     Renderer
        |
  ImageExporter
        |
   PNG / Image
```

`examples/main.cpp` is the integration point for all completed components.
