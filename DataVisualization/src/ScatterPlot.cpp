// ============================================================================
// DATA VISUALIZATION LIBRARY IN C++
//
// MODULE: SCATTER PLOT
// ASSIGNED TO: ADRIAN
//
// YOUR RESPONSIBILITIES:
// 1. Accept x and y datasets.
// 2. Use AxisScale to map data to plot coordinates.
// 3. Represent each observation as a point.
// 4. Pass drawing requirements to Renderer.
//
// MAIN FILES:
// - include/dataviz/ScatterPlot.h
// - src/ScatterPlot.cpp
// - tests/test_scatter.cpp
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

// ============================================================
// DATA VISUALIZATION LIBRARY IN C++
// MODULE: SCATTER PLOT
// ASSIGNED TO: ADRIAN
//
// DEPENDENCIES:
// AxisScale - coordinate transformation
// Renderer  - drawing and SVG export
// ============================================================

#include "dataviz/ScatterPlot.h"
#include "dataviz/AxisScale.h"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>

using namespace std;

namespace dataviz {

ScatterPlot::ScatterPlot(
    const vector<double>& x,
    const vector<double>& y)
{
    if (x.empty() || y.empty()) {
        throw invalid_argument("Data cannot be empty");
    }

    if (x.size() != y.size()) {
        throw invalid_argument("Data sizes must match");
    }

    for (int i = 0; i < (int)x.size(); i++) {
        if (!isfinite(x[i]) || !isfinite(y[i])) {
            throw invalid_argument("Invalid data value");
        }
    }

    xValues = x;
    yValues = y;
}

size_t ScatterPlot::pointCount() const {
    return xValues.size();
}

void ScatterPlot::draw(Renderer& renderer) const {

    double minX = xValues[0];
    double maxX = xValues[0];
    double minY = yValues[0];
    double maxY = yValues[0];

    // Find minimum and maximum values
    for (int i = 0; i < (int)xValues.size(); i++) {

        if (xValues[i] < minX)
            minX = xValues[i];

        if (xValues[i] > maxX)
            maxX = xValues[i];

        if (yValues[i] < minY)
            minY = yValues[i];

        if (yValues[i] > maxY)
            maxY = yValues[i];
    }

    // Plot area
    double left = 80;
    double right = 740;
    double top = 60;
    double bottom = 520;

    // Scale the data
    LinearScale xScale(minX, maxX, right - left);
    LinearScale yScale(minY, maxY, bottom - top);

    // Draw axes
    renderer.drawAxes(left, top, right, bottom);

    // Draw the points
    for (int i = 0; i < (int)xValues.size(); i++) {

        double x = left + xScale.scale(xValues[i]);
        double y = bottom - yScale.scale(yValues[i]);

        renderer.drawPoint(x, y, 4, "blue");
    }
}

}
