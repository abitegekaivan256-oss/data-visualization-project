// ============================================================================
// DATA VISUALIZATION LIBRARY IN C++
//
// MODULE: BAR PLOT
// ASSIGNED TO: JEFF
//
// YOUR RESPONSIBILITIES:
// 1. Accept categories/values.
// 2. Determine bar positions, widths and heights.
// 3. Use AxisScale where appropriate.
// 4. Pass drawing requirements to Renderer.
//
// MAIN FILES:
// - include/dataviz/BarPlot.h
// - src/BarPlot.cpp
// - tests/test_bar.cpp
//
// DEPENDENCIES / COORDINATION:
// - AxisScale (Bonius)
// - Renderer (Adrian + Group)
// - Plot (Group)
//
// TEAM RULES:
// - Work mainly in your allocated files.
// - Pull the latest repository before starting work.
// - Discuss changes to shared interfaces before editing them.
// - Compile/test your component before committing.
// - Use a clear commit message describing what changed.
//
// ============================================================================
#ifndef BAR_PLOT_H
#define BAR_PLOT_H

#include <string>
#include <vector>
#include "dataviz/AxisScale.h"
#include "dataviz/Plot.h"



// Category/value plot with signed ASCII and SVG rendering.
class BarPlot : public Plot {
private:
    std::vector<std::string> categories;
    std::vector<double> values;

public:
// Constructor to initialize the bar plot with a title
    BarPlot(const std::string& plotTitle);

    void render(dataviz::Renderer&) const override;
    void addBar(const std::string& category, double value);
    void renderAscii(int terminalWidth = 50) const;// Render a simple ASCII representation of the bar plot in the terminal.

    // Getters for integration
    const std::vector<std::string>& getCategories() const { return categories; }
    const std::vector<double>& getValues() const { return values; }
};

#endif // BAR_PLOT_H
