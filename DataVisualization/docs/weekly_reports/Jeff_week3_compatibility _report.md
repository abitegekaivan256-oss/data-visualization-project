Challenges faced: 
Realised that with changing weeks and making sure the project build implements, classes, inheritance and polymorphism, had to make ammendments to the initial plot.h code and plot.cpp, axis scale codes so that my week 3 bar plot data codes are compatible. I greatly appreciate my team members, for the job well done, and strongly hope they peruse through and second my ammendments,
Also experienced conflicts with main branch that I had to resolve using the resolve merge editor, learnt how to accept incoming changes or keep the current
It took me weeks of code and my final recommendations are how I wish this was communicated at the begining of the program, it would be fruitful cause I for one have learnt alot and wish to continue implementing, I now strongly believe I can sit with MIT coders and other app developers and reason at the same rythmn.

# Weekly Progress Report — Week 3: Polymorphism & Dynamic Dispatch

## 1. Task Requirements
* Convert `Plot` into an abstract base class using pure virtual functions (`render() = 0`).
* Support heterogeneous collections (`std::vector<Plot*>`) rendered dynamically at runtime.
* Ensure proper virtual destructors (`virtual ~Plot() = default`) to prevent memory leaks.

## 2. Implementation Strategy
Abstract Class Design:** Made `Plot::render() const = 0` pure virtual.
Dynamic Dispatch:** Updated execution main loop to iterate through base class pointers `Plot*` and trigger virtual methods dynamically.

## 3. Working Example

### Input Code (`examples/main.cpp`)
```cpp
#include "dataviz/BarPlot.h"
#include "dataviz/ScatterPlot.h"
#include <vector>

int main() {
    std::vector<Plot*> dashboard;

    BarPlot* sales = new BarPlot("Regional Sales");
    sales->addBar("North", 120.0);
    sales->addBar("South", 85.0);

    ScatterPlot* correlation = new ScatterPlot("Price vs Quantity", 'X');
    correlation->addPoint(10.0, 50.0);
    correlation->addPoint(25.0, 120.0);

    dashboard.push_back(sales);
    dashboard.push_back(correlation);

    // Polymorphic loop
    for (const auto* plot : dashboard) {
        plot->render();
    }

    // Cleanup
    for (auto* plot : dashboard) delete plot;
    return 0;
}