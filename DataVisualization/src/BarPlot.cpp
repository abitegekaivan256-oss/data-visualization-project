#include "dataviz/BarPlot.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

BarPlot::BarPlot(const std::string& name) : Plot(name) {}

void BarPlot::addBar(const std::string& category, double value) {
    if (!std::isfinite(value)) throw std::invalid_argument("Bar must be finite");
    categories.push_back(category);
    values.push_back(value);
}

void BarPlot::renderAscii(int width) const {
    if (width <= 0) throw std::invalid_argument("Width must be positive");
    std::cout << "\n=== Bar Plot: " << title << " ===\n";
    if (values.empty()) {
        std::cout << "[No data available]\n";
        return;
    }
    const auto bounds = std::minmax_element(values.begin(), values.end());
    const double lo = std::min(0.0, *bounds.first);
    const double hi = std::max(0.0, *bounds.second);
    dataviz::LinearScale scale(lo, hi, width);
    const int zero = static_cast<int>(std::lround(scale.scale(0)));
    for (std::size_t i = 0; i < values.size(); ++i) {
        const int end = static_cast<int>(std::lround(scale.scale(values[i])));
        std::string row(width + 1, ' ');
        for (int j = std::min(zero, end); j <= std::max(zero, end); ++j)
            row[j] = '#';
        row[zero] = '|';
        std::cout << std::setw(12) << std::left << categories[i] << " "
                  << row << " (" << values[i] << ")\n";
    }
    std::cout << "| = zero\n";
}

void BarPlot::render(dataviz::Renderer& renderer) const {
    if (values.empty()) throw std::invalid_argument("Empty bar plot");
    const double bottom = renderer.height() - 80, right = renderer.width() - 40;
    const auto bounds = std::minmax_element(values.begin(), values.end());
    const double lo = std::min(0.0, *bounds.first), hi = std::max(0.0, *bounds.second);
    dataviz::LinearScale scale(lo, hi, bottom - 60);
    const double baseline = bottom - scale.scale(0);
    const double slot = (right - 80) / values.size();
    renderer.drawAxes(80, 60, right, bottom);
    renderer.drawNumericTicks(80, 60, right, bottom, 0, 1, lo, hi, false);
    renderer.drawText(80, 30, title, 22);
    renderer.drawText(80, bottom + 60, xAxisLabel);
    renderer.drawText(5, 35, yAxisLabel);
    for (std::size_t i = 0; i < values.size(); ++i) {
        const double x = 80 + (i + .5) * slot;
        const double y = bottom - scale.scale(values[i]);
        renderer.drawRectangle(x - slot * .3, std::min(y, baseline),
                               slot * .6, std::abs(y - baseline));
        renderer.drawText(x - slot * .3, bottom + 20, categories[i], 11);
    }
    // Draw last so the reference remains visible over every bar.
    renderer.drawLine(80, baseline, right, baseline, "#475569", 1);
    renderer.drawText(right - 50, baseline - 6, "0 (zero)", 11, "#475569");
}
