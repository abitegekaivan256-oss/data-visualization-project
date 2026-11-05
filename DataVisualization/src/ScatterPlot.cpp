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
#include "dataviz/ScatterPlot.h"
#include <iostream>
#include <algorithm>

ScatterPlot::ScatterPlot(const std::string& plotTitle, char marker)
    : Plot(plotTitle), pointMarker(marker) {}

void ScatterPlot::addPoint(double x, double y) {
    points.push_back({x, y});
}

void ScatterPlot::renderAscii(int gridWidth, int gridHeight) const {
    std::cout << "\n========================================\n";
    std::cout << " SCATTER PLOT: " << title << "\n";
    std::cout << " X: " << xAxisLabel << " | Y: " << yAxisLabel << "\n";
    std::cout << "========================================\n";

    if (points.empty()) {
        std::cout << "[No points to plot]\n";
        return;
    }

    // Determine data bounds
    double minX = points[0].first, maxX = points[0].first;
    double minY = points[0].second, maxY = points[0].second;

    for (const auto& p : points) {
        minX = std::min(minX, p.first);
        maxX = std::max(maxX, p.first);
        minY = std::min(minY, p.second);
        maxY = std::max(maxY, p.second);
    }

    AxisScale scaleX(minX, maxX, 0, gridWidth - 1);
    AxisScale scaleY(minY, maxY, 0, gridHeight - 1);

    // Grid buffer initialization
    std::vector<std::string> grid(gridHeight, std::string(gridWidth, ' '));

    for (const auto& p : points) {
        int xPos = static_cast<int>(scaleX.scale(p.first));
        int yPos = static_cast<int>(scaleY.scale(p.second));
        // Flip Y for terminal rendering top-to-bottom
        int invertedY = (gridHeight - 1) - yPos;
        grid[invertedY][xPos] = pointMarker;
    }

    // Render grid
    for (int r = 0; r < gridHeight; ++r) {
        std::cout << "|" << grid[r] << "|\n";
    }
    std::cout << "+" << std::string(gridWidth, '-') << "+\n";
}