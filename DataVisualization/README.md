# Data Visualization Library in C++

## Project purpose
Design and implement a reusable C++ data-visualization library supporting:
- Data loading
- Data preprocessing and statistical summaries
- Scatter plots
- Line plots
- Bar plots
- Axis scaling
- Labels and annotations
- Plot rendering
- Image export

This repository is intentionally a **project scaffold**. The algorithms have not been implemented yet. Every allocated source/header/test file now identifies its owner, responsibilities, dependencies, and team rules so a member can open the project and immediately know where to work.

## Team allocation
| Member | Responsibility | Main files |
|---|---|---|
| Jackson | Data loading | `DataLoader.h/.cpp` |
| Gladys | Data preprocessing + statistical summaries | `DataPreprocessor.h/.cpp`, `Statistics.h/.cpp` |
| Adrian | Scatter plots; rendering coordination | `ScatterPlot.h/.cpp`, shared `Renderer` |
| Sandra | Line plots | `LinePlot.h/.cpp` |
| Jeff | Bar plots | `BarPlot.h/.cpp` |
| Bonius | Axis scaling | `AxisScale.h/.cpp` |
| Ivan | Labels and annotations; report compilation | `Labels.h/.cpp`, `docs/weekly_reports/` |
| Group | Common plot design/integration | `Plot.h/.cpp`, `examples/main.cpp` |
| Jackson + group | Image export | `ImageExporter.h/.cpp` |

## Folder structure
- `include/dataviz/` — class/interface headers
- `src/` — implementations
- `examples/` — final integration program
- `data/` — sample input data
- `tests/` — component tests
- `output/` — generated plots/images
- `docs/weekly_reports/` — weekly progress reports
- `docs/diagrams/` — architecture/UML/flow diagrams

## Simple shared-main collaboration workflow
For the first stage, the group can work from the same `main` branch because the project is separated into member-owned files.

1. One member creates the GitHub repository and pushes this scaffold to `main`.
2. Add all colleagues as collaborators.
3. Everyone clones the same repository.
4. Before starting work, run `git pull origin main`.
5. Work mainly in the files carrying your name.
6. Compile/test your own component.
7. Commit only intentional changes with a clear message.
8. Run `git pull origin main` again before pushing and resolve any conflict carefully.
9. Push to `main`.
10. If two people need to change the same shared file (`Plot`, `Renderer`, `ImageExporter`, or `main.cpp`), coordinate first.

> If merge conflicts become frequent, move to member branches and Pull Requests. The architecture already supports that transition.

## Initial Git commands for the project owner
```bash
git init
git add .
git commit -m "Create initial data visualization project scaffold"
git branch -M main
git remote add origin <YOUR-GITHUB-REPOSITORY-URL>
git push -u origin main
```

## Commands for each colleague
```bash
git clone <YOUR-GITHUB-REPOSITORY-URL>
cd DataVisualization
git pull origin main
```

After making and testing changes:
```bash
git add <your-files>
git commit -m "Implement <component name>"
git pull origin main
git push origin main
```

Avoid `git add .` when possible; adding only your intended files reduces accidental changes to another member's work.

## Weekly reporting
Each report should record: objective, previous version, modification made, design/implementation, testing, results/screenshots, challenges, solutions, limitations, and next week's planned modification.

## Important team rule
Do not create seven separate projects. All components must remain inside this single repository and be integrated through the shared architecture.
