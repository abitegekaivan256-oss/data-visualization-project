// Include this class's declarations. algorithm finds ranges, cmath validates numbers,
// fstream writes files, iomanip formats SVG numbers, and stdexcept communicates invalid input or I/O.
#include "dataviz/LinePlot.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <string>

namespace dataviz {
namespace {
// File-local helper: return text safe to place inside SVG/XML.
// Escape markup delimiters and quotes so user labels are displayed as text, not interpreted as tags.
std::string escapeXml(const std::string &value) {
    std::string out;
    // Visit every character. switch chooses an entity for special XML characters
    // and copies ordinary characters unchanged into the returned string.
    for (char ch : value) {
        switch (ch) {
        case '&':
            out += "&amp;";
            break;
        case '<':
            out += "&lt;";
            break;
        case '>':
            out += "&gt;";
            break;
        case '"':
            out += "&quot;";
            break;
        case '\'':
            out += "&apos;";
            break;
        default:
            out += ch;
        }
    }
    return out;
}
} // namespace

// Initialize inherited metadata, then reuse setData for paired-coordinate validation.
// The constructor throws if the two input vectors cannot form a valid series.
LinePlot::LinePlot(const std::vector<double> &x, const std::vector<double> &y) : Plot("Line Plot") {
    setData(x, y);
}

// Replace the stored series with equally sized, finite X/Y vectors.
// Check the whole input before assignment, so validation errors preserve existing data.
void LinePlot::setData(const std::vector<double> &x, const std::vector<double> &y) {
    if (x.size() != y.size()) {
        throw std::invalid_argument("X and Y must contain the same number of values");
    }
    // Equal lengths make the same index safe in both vectors. Negative finite values are valid.
    for (std::size_t i = 0; i < x.size(); ++i) {
        if (!std::isfinite(x[i]) || !std::isfinite(y[i])) {
            throw std::invalid_argument("Plot coordinates must be finite numbers");
        }
    }
    // Only validated inputs reach the copies. The caller's vectors keep their original values.
    x_values_ = x;
    y_values_ = y;
}

// The vector length is the observation count; this read-only operation cannot throw.
std::size_t LinePlot::size() const noexcept {
    return x_values_.size();
}

// Return geometric segments in data coordinates, without rendering or sorting.
// A singleton has a point but no connection; an empty series also returns an empty vector.
std::vector<LineSegment> LinePlot::segments() const {
    std::vector<LineSegment> lines;
    if (size() < 2)
        return lines;
    // n observations need n-1 connections. Reserve capacity without creating extra elements.
    lines.reserve(size() - 1);
    // Begin at the second point so i-1 is valid. Connect each point to its predecessor.
    for (std::size_t i = 1; i < size(); ++i) {
        lines.push_back({{x_values_[i - 1], y_values_[i - 1]}, {x_values_[i], y_values_[i]}});
    }
    return lines;
}

// Direct SVG-writing API: validate data/canvas, calculate coordinates, then write a complete file.
// This path is separate from render(Renderer&), but both read Plot's shared title/label strings.
// invalid_argument reports unusable input; runtime_error reports opening or writing failure.
void LinePlot::saveSvg(const std::string &filename, unsigned width, unsigned height) const {
    if (size() == 0)
        throw std::invalid_argument("Cannot plot an empty dataset");
    if (width < 200 || height < 160) {
        throw std::invalid_argument("SVG canvas must be at least 200x160");
    }
    // Open the requested output path. Parent folders must already exist.
    // Unlike SvgImageExporter, this direct method does not validate a .svg filename suffix.
    std::ofstream out(filename);
    if (!out)
        throw std::runtime_error("Unable to open SVG output file: " + filename);
    // Use consistent decimal text in this SVG. Margins leave room for the title, ticks and labels.
    out << std::fixed << std::setprecision(3);
    const double left = 75.0, right = static_cast<double>(width) - 25.0;
    const double top = 65.0, bottom = static_cast<double>(height) - 65.0;
    // Find ranges without sorting or changing the original observation order.
    const auto xr = std::minmax_element(x_values_.begin(), x_values_.end());
    const auto yr = std::minmax_element(y_values_.begin(), y_values_.end());
    double xmin = *xr.first, xmax = *xr.second;
    double ymin = *yr.first, ymax = *yr.second;
    // Expand a constant axis to a small visible interval. This avoids a zero denominator
    // in this standalone layout and places equal observations at its center.
    if (xmin == xmax) {
        xmin -= 1.0;
        xmax += 1.0;
    }
    if (ymin == ymax) {
        ymin -= 1.0;
        ymax += 1.0;
    }
    // These small local functions capture the calculated bounds/margins by reference.
    // xpix adds the left offset; ypix subtracts from bottom to account for SVG's downward Y direction.
    const auto xpix = [&](double v) { return left + (v - xmin) / (xmax - xmin) * (right - left); };
    const auto ypix = [&](double v) {
        return bottom - (v - ymin) / (ymax - ymin) * (bottom - top);
    };

    // Start a complete SVG document with explicit canvas size and viewBox.
    // The white background rectangle makes the output consistent in different viewers.
    out << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << width << "\" height=\"" << height
        << "\" viewBox=\"0 0 " << width << ' ' << height << "\">\n";
    out << "<rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";
    out << "<g stroke=\"#dbe4ec\" stroke-width=\"1\">\n";
    // Draw six evenly spaced grid positions, including both endpoints.
    // Each iteration writes one vertical and one horizontal grid line.
    for (int i = 0; i <= 5; ++i) {
        double xp = left + i * (right - left) / 5.0;
        double yp = top + i * (bottom - top) / 5.0;
        out << "<line x1=\"" << xp << "\" y1=\"" << top << "\" x2=\"" << xp << "\" y2=\"" << bottom
            << "\"/>\n";
        out << "<line x1=\"" << left << "\" y1=\"" << yp << "\" x2=\"" << right << "\" y2=\"" << yp
            << "\"/>\n";
    }
    // Close the grid group and draw the left/bottom axis outline as one SVG path.
    out << "</g>\n<path d=\"M " << left << ' ' << top << " V " << bottom << " H " << right
        << "\" fill=\"none\" stroke=\"#334155\" stroke-width=\"2\"/>\n";
    out << "<g font-family=\"Arial,sans-serif\" fill=\"#334155\" font-size=\"12\">\n";
    // Label those same six positions with interpolated data values.
    // text-anchor aligns tick text with its corresponding tick rather than with the string's left edge.
    for (int i = 0; i <= 5; ++i) {
        double fraction = i / 5.0;
        out << "<text x=\"" << left + fraction * (right - left) << "\" y=\"" << bottom + 20
            << "\" text-anchor=\"middle\">" << xmin + fraction * (xmax - xmin) << "</text>\n";
        out << "<text x=\"" << left - 10 << "\" y=\"" << bottom - fraction * (bottom - top) + 4
            << "\" text-anchor=\"end\">" << ymin + fraction * (ymax - ymin) << "</text>\n";
    }
    out << "</g>\n<g font-family=\"Arial,sans-serif\" fill=\"#0f172a\">\n";
    // Escape all inherited metadata before inserting it into XML text.
    // The standalone Y label uses an SVG rotation; the shared Renderer layout is different.
    out << "<text x=\"" << width / 2
        << "\" y=\"30\" text-anchor=\"middle\" font-size=\"20\" font-weight=\"bold\">"
        << escapeXml(title) << "</text>\n";
    out << "<text x=\"" << width / 2 << "\" y=\"" << height - 15
        << "\" text-anchor=\"middle\" font-size=\"14\">" << escapeXml(xAxisLabel) << "</text>\n";
    out << "<text transform=\"translate(20 " << height / 2
        << ") rotate(-90)\" text-anchor=\"middle\" font-size=\"14\">" << escapeXml(yAxisLabel)
        << "</text>\n</g>\n";
    // A polyline connects the supplied points in their original order.
    // Write every mapped X,Y pair into its points attribute, then add visible point circles.
    out << "<polyline fill=\"none\" stroke=\"#2563eb\" stroke-width=\"2.5\" points=\"";
    // Emit the complete connected path; no sorting is performed during export.
    for (std::size_t i = 0; i < size(); ++i) {
        out << xpix(x_values_[i]) << ',' << ypix(y_values_[i]) << ' ';
    }
    out << "\"/>\n";
    // A circle makes each observation visible, including a one-point dataset with no line segment.
    for (std::size_t i = 0; i < size(); ++i) {
        out << "<circle cx=\"" << xpix(x_values_[i]) << "\" cy=\"" << ypix(y_values_[i])
            << "\" r=\"3.5\" fill=\"#2563eb\"/>\n";
    }
    out << "</svg>\n";
    // Check the stream after writing all elements so a write failure is not reported as success.
    if (!out)
        throw std::runtime_error("Failed to write SVG file: " + filename);
}

} // namespace dataviz

// The shared Renderer path below reuses the library's linear scaling implementation.
#include "dataviz/AxisScale.h"

namespace dataviz {
// Populate an existing renderer with this line series, axes, ticks and inherited metadata.
// Empty data is invalid; the scales/renderer also reject unusable canvas distances.
// Saving a file is deliberately left to the caller or ImageExporter.
void LinePlot::render(Renderer &renderer) const {
    if (size() == 0)
        throw std::invalid_argument("Empty line plot");
    // Calculate data ranges and usable canvas bounds without modifying stored coordinates.
    const auto xr = std::minmax_element(x_values_.begin(), x_values_.end());
    const auto yr = std::minmax_element(y_values_.begin(), y_values_.end());
    const double right = renderer.width() - 40, bottom = renderer.height() - 80;
    // Each local scale handles its own data range, including the equal-range midpoint case.
    LinearScale xs(*xr.first, *xr.second, right - 80);
    LinearScale ys(*yr.first, *yr.second, bottom - 60);
    std::vector<Point> points;
    // Build screen-coordinate points for the drawing service. Preserve their order
    // and invert Y so larger data values appear higher on the canvas.
    for (std::size_t i = 0; i < size(); ++i) {
        points.push_back({80 + xs.scale(x_values_[i]), bottom - ys.scale(y_values_[i])});
    }
    // Compose the frame and labels first, then the connected line and its point markers.
    // Renderer handles SVG element construction; this class supplies geometry and meaning.
    renderer.drawAxes(80, 60, right, bottom);
    renderer.drawNumericTicks(80, 60, right, bottom, *xr.first, *xr.second, *yr.first, *yr.second);
    renderer.drawText(80, 30, title, 22);
    renderer.drawText(80, renderer.height() - 20, xAxisLabel);
    renderer.drawText(5, 35, yAxisLabel);
    renderer.drawPolyline(points);
    renderer.drawScatter(points);
}
}
