// Include the matching interface. algorithm finds ranges, cmath supplies finite/rounding
// operations, iomanip aligns category labels, iostream prints, and stdexcept reports invalid input.
#include "dataviz/BarPlot.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

// Reuse Plot's constructor for the title; vectors start empty and manage their own memory.
BarPlot::BarPlot(const std::string &name) : Plot(name) {
}

// Input: category text and its numeric magnitude. Output: append to the two series.
// Reject nonfinite values before changing the vectors; signed and zero values are accepted.
void BarPlot::addBar(const std::string &category, double value) {
    if (!std::isfinite(value))
        throw std::invalid_argument("Bar must be finite");
    categories.push_back(category);
    values.push_back(value);
}

// Print bars in a grid with a consistent zero column. No file is exported.
// Reject an unusable width and print an explanatory message if there are no values.
void BarPlot::renderAscii(int width) const {
    if (width <= 0)
        throw std::invalid_argument("Width must be positive");
    std::cout << "\n=== Bar Plot: " << title << " ===\n";
    if (values.empty()) {
        std::cout << "[No data available]\n";
        return;
    }
    // Include zero in the range even if all values share a sign. Otherwise the bar
    // lengths would measure distance from the smallest observation rather than from zero.
    const auto bounds = std::minmax_element(values.begin(), values.end());
    const double lo = std::min(0.0, *bounds.first);
    const double hi = std::max(0.0, *bounds.second);
    dataviz::LinearScale scale(lo, hi, width);
    // Round the mapped zero position to the nearest character column.
    // An all-zero dataset uses LinearScale's midpoint rule.
    const int zero = static_cast<int>(std::lround(scale.scale(0)));
    // Build each row independently. Width+1 permits both mapped endpoints, 0 and width.
    for (std::size_t i = 0; i < values.size(); ++i) {
        const int end = static_cast<int>(std::lround(scale.scale(values[i])));
        std::string row(width + 1, ' ');
        // Fill between zero and the value: negative bars extend left, positive bars right.
        // Taking min/max lets one loop handle either sign without negative string indices.
        for (int j = std::min(zero, end); j <= std::max(zero, end); ++j)
            row[j] = '#';
        // Restore the reference column after filling. A zero-valued bar is just this marker.
        row[zero] = '|';
        // Align the category, then show both the visual row and the original numeric value.
        std::cout << std::setw(12) << std::left << categories[i] << " " << row << " (" << values[i]
                  << ")\n";
    }
    std::cout << "| = zero\n";
}

// Populate a Renderer with signed bars, numerical Y ticks and categorical X labels.
// The method is const: drawing does not modify stored data or inherited metadata.
void BarPlot::render(dataviz::Renderer &renderer) const {
    if (values.empty())
        throw std::invalid_argument("Empty bar plot");
    const double bottom = renderer.height() - 80, right = renderer.width() - 40;
    // Reserve a Y range that contains zero and every value, preserving negative magnitudes.
    const auto bounds = std::minmax_element(values.begin(), values.end());
    const double lo = std::min(0.0, *bounds.first), hi = std::max(0.0, *bounds.second);
    dataviz::LinearScale scale(lo, hi, bottom - 60);
    // Map numeric zero once. SVG Y grows downward, so subtract the scaled distance.
    // Equal category slots determine the horizontal spacing; bar width is 60% of a slot.
    const double baseline = bottom - scale.scale(0);
    const double slot = (right - 80) / values.size();
    // The X axis has category strings rather than numeric ticks (includeX=false).
    // Titles and labels come from Plot, while the numerical scale is local to this render.
    renderer.drawAxes(80, 60, right, bottom);
    renderer.drawNumericTicks(80, 60, right, bottom, 0, 1, lo, hi, false);
    renderer.drawText(80, 30, title, 22);
    renderer.drawText(80, bottom + 60, xAxisLabel);
    renderer.drawText(5, 35, yAxisLabel);
    // Place the bar center halfway through its category slot and map its endpoint.
    // Use the upper endpoint as rectangle top and an absolute height, so either sign works.
    for (std::size_t i = 0; i < values.size(); ++i) {
        const double x = 80 + (i + .5) * slot;
        const double y = bottom - scale.scale(values[i]);
        renderer.drawRectangle(x - slot * .3, std::min(y, baseline), slot * .6,
                               std::abs(y - baseline));
        // Print the category under its bar; this implementation does not automatically avoid collisions.
        renderer.drawText(x - slot * .3, bottom + 20, categories[i], 11);
    }
    // Draw last so the reference remains visible over every bar.
    renderer.drawLine(80, baseline, right, baseline, "#475569", 1);
    renderer.drawText(right - 50, baseline - 6, "0 (zero)", 11, "#475569");
}
