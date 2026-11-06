// Matching declarations and AxisScale provide the plot interface and coordinate mapping.
// algorithm finds bounds, cmath validates numbers, iostream prints the grid, and stdexcept reports bad input.
#include "dataviz/ScatterPlot.h"
#include "dataviz/AxisScale.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace dataviz {
// Construct the base metadata and store the terminal marker.
// Permit visible ASCII characters only; spaces and control characters would hide grid points.
ScatterPlot::ScatterPlot(const std::string &name, char marker) : Plot(name), marker_(marker) {
    if (marker < 33 || marker > 126)
        throw std::invalid_argument("Marker must be printable ASCII");
}

// Delegate shared setup to the simpler constructor, then validate paired input.
// Copy points through addPoint so both construction paths enforce finite coordinates.
ScatterPlot::ScatterPlot(const std::vector<double> &x, const std::vector<double> &y,
                         const std::string &name, char marker)
    : ScatterPlot(name, marker) {
    if (x.empty() || x.size() != y.size())
        throw std::invalid_argument("Nonempty, equally sized coordinates required");
    // Corresponding vector positions are one observation; preserve the caller's order.
    for (std::size_t i = 0; i < x.size(); ++i)
        addPoint(x[i], y[i]);
}

// Input: requested SVG radius in pixels. Output: update the object, or throw invalid_argument.
// Check before assignment so a bad request leaves the previous radius unchanged.
void ScatterPlot::setMarkerRadius(double radius) {
    if (!std::isfinite(radius) || radius <= 0)
        throw std::invalid_argument("Marker radius must be positive and finite");
    markerRadius_ = radius;
}

// Store one observation after validating both coordinates. Negative finite values are valid.
// No screen mapping is performed yet because the final range may change as points are added.
void ScatterPlot::addPoint(double x, double y) {
    if (!std::isfinite(x) || !std::isfinite(y))
        throw std::invalid_argument("Coordinates must be finite");
    xValues.push_back(x);
    yValues.push_back(y);
}

// Read-only observation count. Returning size_t matches the vector's size representation.
std::size_t ScatterPlot::pointCount() const {
    return xValues.size();
}

// Render the stored observations onto the caller's existing canvas.
// Empty data is rejected; unsuitable canvas/range values can also be rejected by scales or Renderer.
void ScatterPlot::draw(Renderer &renderer) const {
    if (xValues.empty())
        throw std::invalid_argument("Empty scatter plot");
    // Find the minimum and maximum without reordering the coordinate vectors.
    // Each returned pair contains iterators; dereferencing them obtains the endpoint values.
    const auto xr = std::minmax_element(xValues.begin(), xValues.end());
    const auto yr = std::minmax_element(yValues.begin(), yValues.end());
    // Reserve margins for titles and numerical labels. SVG positions are measured in pixels.
    const double left = 80, right = renderer.width() - 60;
    const double top = 60, bottom = renderer.height() - 80;
    // Map each data range into the available drawing distance. LinearScale centers
    // observations on a constant-valued axis instead of dividing by zero.
    LinearScale xs(*xr.first, *xr.second, right - left);
    LinearScale ys(*yr.first, *yr.second, bottom - top);
    // Draw the frame and its values before the data, so circles remain visible over the axes.
    // Metadata strings come from the Plot base class rather than duplicate local fields.
    renderer.drawAxes(left, top, right, bottom);
    renderer.drawNumericTicks(left, top, right, bottom, *xr.first, *xr.second, *yr.first,
                              *yr.second);
    renderer.drawText(left, 30, title, 22);
    renderer.drawText(left, bottom + 55, xAxisLabel);
    renderer.drawText(5, 35, yAxisLabel);
    // X starts at the left margin. Y starts at bottom and is inverted because SVG Y
    // grows downward. Use the validated radius with a consistent blue fill and dark outline.
    for (std::size_t i = 0; i < xValues.size(); ++i)
        renderer.drawOutlinedPoint(left + xs.scale(xValues[i]), bottom - ys.scale(yValues[i]),
                                   markerRadius_, "#2563eb", "#0f172a", 1.25);
}

// Print a terminal representation using the configured character rather than SVG circles.
// Positive width/height are required; an empty dataset simply produces no grid output.
void ScatterPlot::renderAscii(int width, int height) const {
    if (width <= 0 || height <= 0)
        throw std::invalid_argument("Grid dimensions must be positive");
    if (xValues.empty())
        return;
    // Calculate independent horizontal and vertical ranges from the stored pairs.
    const auto xr = std::minmax_element(xValues.begin(), xValues.end());
    const auto yr = std::minmax_element(yValues.begin(), yValues.end());
    LinearScale xs(*xr.first, *xr.second, width);
    LinearScale ys(*yr.first, *yr.second, height);
    // Allocate coordinates 0..width and 0..height, including both endpoints.
    // Every row is a string of spaces until an observation occupies a cell.
    std::vector<std::string> grid(height + 1, std::string(width + 1, ' '));
    // Convert mapped double distances to integer cell indices and invert the row index.
    // Multiple observations in the same cell share one visible marker.
    for (std::size_t i = 0; i < xValues.size(); ++i)
        grid[height - static_cast<int>(ys.scale(yValues[i]))]
            [static_cast<int>(xs.scale(xValues[i]))] = marker_;
    // Print each completed row. This changes console output, not the stored plot data.
    for (const auto &row : grid)
        std::cout << row << '\n';
}
}
