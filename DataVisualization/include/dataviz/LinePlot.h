// ============================================================================
// DATA VISUALIZATION LIBRARY IN C++
//
// MODULE: LINE PLOT
// ASSIGNED TO: SANDRA
//
// YOUR RESPONSIBILITIES:
// 1. Accept ordered x and y datasets.
// 2. Use AxisScale to map data to plot coordinates.
// 3. Connect consecutive points.
// 4. Pass drawing requirements to Renderer.
//
// MAIN FILES:
// - include/dataviz/LinePlot.h
// - src/LinePlot.cpp
// - tests/test_line.cpp
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
// IMPLEMENTATION STATUS: NOT YET IMPLEMENTED
// ============================================================================

#ifndef LINE_PLOT_H
#define LINE_PLOT_H

#include <vector>
#include "Plot.h"
#include "AxisScale.h"
#include "Renderer.h"

namespace dataviz {

class LinePlot : public Plot {
private:
    // Store the raw data points passed by the user
    std::vector<double> x_values_;
    std::vector<double> y_values_;

public:
    LinePlot();
    virtual ~LinePlot() = default;

    // Save the coordinate lists for plotting
    void setData(const std::vector<double>& x, const std::vector<double>& y);

    // Map data points using AxisScale and draw lines between them using Renderer
    void render(Renderer& renderer, const AxisScale& xScale, const AxisScale& yScale) const override;
};

} // namespace dataviz

#endif