#include "dataviz/ScatterPlot.h"
#include "dataviz/AxisScale.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace dataviz {
ScatterPlot::ScatterPlot(const std::string& name, char marker)
    : Plot(name), marker_(marker) {
    if (marker < 33 || marker > 126)
        throw std::invalid_argument("Marker must be printable ASCII");
}

ScatterPlot::ScatterPlot(const std::vector<double>& x, const std::vector<double>& y,
                         const std::string& name, char marker)
    : ScatterPlot(name, marker) {
    if (x.empty() || x.size() != y.size())
        throw std::invalid_argument("Nonempty, equally sized coordinates required");
    for (std::size_t i = 0; i < x.size(); ++i) addPoint(x[i], y[i]);
}

void ScatterPlot::setMarkerRadius(double radius) {
    if (!std::isfinite(radius) || radius <= 0)
        throw std::invalid_argument("Marker radius must be positive and finite");
    markerRadius_ = radius;
}

void ScatterPlot::addPoint(double x, double y) {
    if (!std::isfinite(x) || !std::isfinite(y))
        throw std::invalid_argument("Coordinates must be finite");
    xValues.push_back(x);
    yValues.push_back(y);
}

std::size_t ScatterPlot::pointCount() const { return xValues.size(); }

void ScatterPlot::draw(Renderer& renderer) const {
    if (xValues.empty()) throw std::invalid_argument("Empty scatter plot");
    const auto xr = std::minmax_element(xValues.begin(), xValues.end());
    const auto yr = std::minmax_element(yValues.begin(), yValues.end());
    const double left = 80, right = renderer.width() - 60;
    const double top = 60, bottom = renderer.height() - 80;
    LinearScale xs(*xr.first, *xr.second, right - left);
    LinearScale ys(*yr.first, *yr.second, bottom - top);
    renderer.drawAxes(left, top, right, bottom);
    renderer.drawNumericTicks(left, top, right, bottom, *xr.first, *xr.second,
                              *yr.first, *yr.second);
    renderer.drawText(left, 30, title, 22);
    renderer.drawText(left, bottom + 55, xAxisLabel);
    renderer.drawText(5, 35, yAxisLabel);
    for (std::size_t i = 0; i < xValues.size(); ++i)
        renderer.drawOutlinedPoint(left + xs.scale(xValues[i]), bottom - ys.scale(yValues[i]), markerRadius_, "#2563eb", "#0f172a", 1.25);
}

void ScatterPlot::renderAscii(int width, int height) const {
    if (width <= 0 || height <= 0)
        throw std::invalid_argument("Grid dimensions must be positive");
    if (xValues.empty()) return;
    const auto xr = std::minmax_element(xValues.begin(), xValues.end());
    const auto yr = std::minmax_element(yValues.begin(), yValues.end());
    LinearScale xs(*xr.first, *xr.second, width);
    LinearScale ys(*yr.first, *yr.second, height);
    std::vector<std::string> grid(height + 1, std::string(width + 1, ' '));
    for (std::size_t i = 0; i < xValues.size(); ++i)
        grid[height - static_cast<int>(ys.scale(yValues[i]))]
            [static_cast<int>(xs.scale(xValues[i]))] = marker_;
    for (const auto& row : grid) std::cout << row << '\n';
}
}
