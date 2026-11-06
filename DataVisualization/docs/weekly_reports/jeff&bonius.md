# Weekly Progress Report — Week 1: Core Classes & Encapsulation

## 1. Task Requirements
* Establish the core repository structure and collaboration workflow.
* Implement foundational C++ classes demonstrating proper encapsulation (`AxisScale` and `BarPlot`).
* Set up modular header/source separation under `include/dataviz/` and `src/`.

## 2. Implementation Strategy
* **Encapsulation:** Isolated data bounds and coordinate transformation logic inside `AxisScale`.
* **Modularity:** Kept `BarPlot` independent of global rendering engines for Week 1, using an ASCII-based text renderer to validate core calculations prior to full graphical pipeline integration.
* **Collaboration:** Followed branch-per-task guidelines (`git checkout -b bonius-axis-scale` / `git checkout -b jeff-bar-plot`).

## 3. Key Decisions & Approaches
* Handled edge cases such as zero-width data ranges in `AxisScale` to prevent division-by-zero errors.
* Utilized standard library algorithms (`std::max_element`) for dynamic scaling bounds.

## 4. Testing & Verification
* Tested component boundary values (negative inputs, zero ranges, and large datasets).
* Verified terminal rendering output for visual correctness.

## 5. Working Example (Inputs & Outputs)

 ### Input Code (`examples/main.cpp`)
```cpp
#include "dataviz/BarPlot.h"

int main() {
    BarPlot salesPlot("Q3 Regional Sales");
    salesPlot.addBar("North", 150.5);
    salesPlot.addBar("South", 85.0);
    salesPlot.addBar("East", 200.0);
    salesPlot.addBar("West", 120.0);

    salesPlot.renderAscii();
    return 0;
}
