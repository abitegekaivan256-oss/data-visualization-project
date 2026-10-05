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
