#include "dataviz/BarPlot.h"
#include "dataviz/ScatterPlot.h"
#include <iostream>
#include <vector>

// BarPlot is abstract, so provide its required rendering implementation.
class RenderableBarPlot : public BarPlot {
public:
    using BarPlot::BarPlot;

    void render() const override {
        std::cout << "Rendering bar plot\n";
    }
};

// ScatterPlot is abstract, so provide the rendering implementation required
// for use in this polymorphic example.
class RenderableScatterPlot : public ScatterPlot {
public:
    using ScatterPlot::ScatterPlot;

    void render() const override {
        std::cout << "Rendering scatter plot\n";
    }
};

int main() {
    std::vector<Plot*> dashboard;

// Create instances of the concrete subclasses
    RenderableBarPlot* sales = new RenderableBarPlot("Regional Sales");
    sales->addBar("North", 120.0);
    sales->addBar("South", 85.0);

// Create a scatter plot for correlation analysis
//renderableScatterPlot helps to create a scatter plot that can be rendered, as ScatterPlot is abstract and cannot be instantiated directly.
    RenderableScatterPlot* correlation = new RenderableScatterPlot("Price vs Quantity", 'X');
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