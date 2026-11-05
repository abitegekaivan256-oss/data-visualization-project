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
// IMPLEMENTATION STATUS: NOT YET IMPLEMENTED
// ============================================================================

// BarPlot is a utility class that provides functionality for creating and rendering bar plots. It accepts categories and corresponding values, determines the positions, widths, and heights of the bars, and uses the AxisScale class to map data values to pixel coordinates. The class also provides a method to render a simple ASCII representation of the bar plot in the terminal.
 #include "dataviz/BarPlot.h"
#include <iostream>
#include <algorithm>
#include <iomanip> //

BarPlot::BarPlot(const std::string& plotTitle) : title(plotTitle) {}

void BarPlot::addBar(const std::string& category, double value) {
    categories.push_back(category);
    values.push_back(value);
}

void BarPlot::renderAscii(int terminalWidth) const {
    std::cout << "\n=== Bar Plot: " << title << " ===\n";
    if (values.empty()) {
        std::cout << "[No data available]\n";
        return;
    }

    double maxVal = *std::max_element(values.begin(), values.end());
    AxisScale scale(0.0, maxVal > 0 ? maxVal : 1.0, 0.0, static_cast<double>(terminalWidth));

    for (size_t i = 0; i < categories.size(); ++i) {
        int barLength = static_cast<int>(scale.scale(values[i]));
        std::cout << std::setw(12) << std::left << categories[i] << " | ";
        for (int j = 0; j < barLength; ++j) {
            std::cout << "█";
        }
        std::cout << " (" << values[i] << ")\n";
    }
    std::cout << "----------------------------------------\n";
}



 // namespace dataviz
