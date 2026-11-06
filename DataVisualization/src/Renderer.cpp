// ============================================================================
// DATA VISUALIZATION LIBRARY IN C++
//
// MODULE: PLOT RENDERING
// ASSIGNED TO: ADRIAN + GROUP
//
// YOUR RESPONSIBILITIES:
// 1. Define the common rendering path used by plot types.
// 2. Draw axes, plot primitives and text using the chosen rendering approach.
// 3. Coordinate interface changes with plotting members.
//
// MAIN FILES:
// - include/dataviz/Renderer.h
// - src/Renderer.cpp
//
// DEPENDENCIES / COORDINATION:
// - ScatterPlot
// - LinePlot
// - BarPlot
// - AxisScale
// - Labels
//
// TEAM RULES:
// - Work mainly in your allocated files.
// - Pull the latest repository before starting work.
// - Discuss changes to shared interfaces before editing them.
// - Compile/test your component before committing.
// - Use a clear commit message describing what changed.
//
// ============================================================================
#include "dataviz/Renderer.h"

// isfinite and abs validate coordinates and calculate signed-bar dimensions.
#include <cmath>
// ofstream writes the final SVG document to disk.
#include <fstream>
// ostringstream converts numbers into SVG attribute text.
#include <sstream>
// invalid_argument reports invalid drawing requests to the caller.
#include <stdexcept>

namespace dataviz {
// The unnamed namespace keeps this free helper local to this source file.
namespace {
// Convert one numeric attribute to text using the stream's current formatting.
// This helper returns a string and performs no coordinate transformation.
std::string number(double value) {
    std::ostringstream stream;
    stream << value;
    return stream.str();
}
}

// Initialize the canvas dimensions before the constructor body runs.
// A valid renderer starts with a white background; invalid sizes throw before
// the object can be used. Parameters and defaults are declared in Renderer.h.
Renderer::Renderer(int width, int height) : width_(width), height_(height) {
    if (width <= 0 || height <= 0)
        throw std::invalid_argument("Canvas dimensions must be positive");
    // clear creates the background element that later drawing appears over.
    clear();
}

// Central finite-value check used by drawing validation. A NaN or infinite
// coordinate cannot describe a meaningful finite SVG position.
bool Renderer::finite(double value) {
    return std::isfinite(value);
}

// Return an escaped copy, leaving the caller's string unchanged. The five
// XML-reserved characters have special meanings in text or quoted attributes.
std::string Renderer::escapeXML(const std::string &input) {
    std::string escaped;
    // Inspect each character so ordinary text is preserved and reserved
    // characters become XML entities such as &amp; or &lt;.
    for (char c : input) {
        // Only reserved characters need substitution; default copies the rest.
        switch (c) {
        case '&':
            escaped += "&amp;";
            break;
        case '<':
            escaped += "&lt;";
            break;
        case '>':
            escaped += "&gt;";
            break;
        case '\"':
            escaped += "&quot;";
            break;
        case '\'':
            escaped += "&apos;";
            break;
        default:
            escaped += c;
        }
    }
    return escaped;
}

// Start a new drawing with the requested background color. Escaping the
// color protects the quoted fill attribute; this does not save a file.
void Renderer::clear(const std::string &background) {
    // Remove all old shapes so reuse of a Renderer does not mix two plots.
    elements_.clear();
    elements_.push_back("<rect width=\"100%\" height=\"100%\" fill=\"" + escapeXML(background) +
                        "\"/>");
}

// Add one line from (x1,y1) to (x2,y2). Reject nonfinite endpoints and
// nonpositive stroke widths, then append the SVG element in drawing order.
void Renderer::drawLine(double x1, double y1, double x2, double y2, const std::string &color,
                        double strokeWidth) {
    if (!finite(x1) || !finite(y1) || !finite(x2) || !finite(y2) || !finite(strokeWidth) ||
        strokeWidth <= 0)
        throw std::invalid_argument("Invalid line coordinates or width");
    elements_.push_back("<line x1=\"" + number(x1) + "\" y1=\"" + number(y1) + "\" x2=\"" +
                        number(x2) + "\" y2=\"" + number(y2) + "\" stroke=\"" + escapeXML(color) +
                        "\" stroke-width=\"" + number(strokeWidth) + "\"/>");
}

// Add a filled circular marker. Inputs are already pixel coordinates;
// plot classes, not this function, perform data-to-pixel scaling.
void Renderer::drawPoint(double x, double y, double radius, const std::string &color) {
    if (!finite(x) || !finite(y) || !finite(radius) || radius <= 0)
        throw std::invalid_argument("Invalid point coordinates or radius");
    elements_.push_back("<circle cx=\"" + number(x) + "\" cy=\"" + number(y) + "\" r=\"" +
                        number(radius) + "\" fill=\"" + escapeXML(color) + "\"/>");
}

// Add a rectangle using its top-left position and dimensions. A zero width
// or height is legal, which allows the representation of a zero-valued bar.
void Renderer::drawRectangle(double x, double y, double width, double height,
                             const std::string &fill) {
    if (!finite(x) || !finite(y) || !finite(width) || !finite(height) || width < 0 || height < 0)
        throw std::invalid_argument("Invalid rectangle dimensions");
    elements_.push_back("<rect x=\"" + number(x) + "\" y=\"" + number(y) + "\" width=\"" +
                        number(width) + "\" height=\"" + number(height) + "\" fill=\"" +
                        escapeXML(fill) + "\"/>");
}

// Add an SVG text element. Position and font size must be usable; the text
// and color are escaped separately because they occupy different XML fields.
void Renderer::drawText(double x, double y, const std::string &text, int fontSize,
                        const std::string &color) {
    if (!finite(x) || !finite(y) || fontSize <= 0)
        throw std::invalid_argument("Invalid text position or font size");
    elements_.push_back("<text x=\"" + number(x) + "\" y=\"" + number(y) + "\" font-size=\"" +
                        number(fontSize) + "\" fill=\"" + escapeXML(color) +
                        "\" font-family=\"Arial,sans-serif\">" + escapeXML(text) + "</text>");
}

// Draw the bottom horizontal axis and left vertical axis for the supplied
// plot bounds. The corner ordering must describe a positive-area rectangle.
void Renderer::drawAxes(double left, double top, double right, double bottom) {
    if (!(left < right && top < bottom))
        throw std::invalid_argument("Invalid plotting area");
    drawLine(left, bottom, right, bottom);
    drawLine(left, bottom, left, top);
}

// Reuse drawPoint for every supplied pixel point. Validation is delegated
// to that primitive, so this function does not duplicate circle construction.
void Renderer::drawScatter(const std::vector<Point> &points, const std::string &color) {
    for (const Point &p : points)
        drawPoint(p.x, p.y, 4.0, color);
}

// Connect each observation to its predecessor, preserving input order.
// Empty or single-point vectors naturally produce no connecting segments.
void Renderer::drawPolyline(const std::vector<Point> &points, const std::string &color) {
    // Begin at index 1 because every segment requires both i-1 and i.
    for (std::size_t i = 1; i < points.size(); ++i)
        drawLine(points[i - 1].x, points[i - 1].y, points[i].x, points[i].y, color);
}

// xCenters and heights describe bar geometry in pixels. Reject mismatched
// vectors, an invalid baseline or nonpositive width before the drawing loop.
// Individual invalid entries throw when reached; earlier bars may already exist.
void Renderer::drawBars(const std::vector<double> &xCenters, const std::vector<double> &heights,
                        double baselineY, double barWidth, const std::string &color) {
    if (xCenters.size() != heights.size() || !finite(baselineY) || !finite(barWidth) ||
        barWidth <= 0)
        throw std::invalid_argument("Invalid bar data or width");
    for (std::size_t i = 0; i < xCenters.size(); ++i) {
        if (!finite(xCenters[i]) || !finite(heights[i]))
            throw std::invalid_argument("Invalid bar coordinate");
        // SVG Y increases downward. Subtraction makes positive heights extend
        // upward; a negative height puts the far endpoint below the baseline.
        double endY = baselineY - heights[i];
        // A rectangle needs its upper-left corner and a nonnegative height.
        // min selects the upper endpoint for either sign; abs supplies its size.
        drawRectangle(xCenters[i] - barWidth / 2.0, std::min(endY, baselineY), barWidth,
                      std::abs(heights[i]), color);
    }
}

// Serialize the existing canvas to filename without recalculating plot data.
// Returns false on open/write failure. The caller must create directories and
// may choose whether to turn this boolean failure into an exception.
bool Renderer::saveSVG(const std::string &filename) const {
    // Opening the stream is the first operation that touches the output file.
    std::ofstream out(filename);
    if (!out)
        return false;
    // The root element declares SVG's namespace, dimensions and viewBox.
    // Shape strings follow in the same order they were originally drawn.
    out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    out << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << width_ << "\" height=\""
        << height_ << "\" viewBox=\"0 0 " << width_ << ' ' << height_ << "\">\n";
    for (const std::string &element : elements_)
        out << "  " << element << '\n';
    out << "</svg>\n";
    // A stream can fail after opening, so also report the final write state.
    return static_cast<bool>(out);
}
} // namespace dataviz
// setprecision controls the compact numerical tick labels.
#include <iomanip>
// A classic locale ensures decimal points do not change with the computer locale.
#include <locale>
namespace dataviz {
// Convert data-range values into readable tick text and pixel positions.
// Throws invalid_argument for nonfinite/reversed ranges or invalid plot bounds.
// This method adds elements but leaves numerical scaling of data to the plots.
void Renderer::drawNumericTicks(double left, double top, double right, double bottom, double xmin,
                                double xmax, double ymin, double ymax, bool includeX) {
    if (!finite(xmin) || !finite(xmax) || !finite(ymin) || !finite(ymax) || xmin > xmax ||
        ymin > ymax || !(left < right && top < bottom))
        throw std::invalid_argument("Invalid tick range");
    // This local lambda is a small formatting helper. Four significant digits
    // keep labels concise, and the classic locale keeps their decimal syntax stable.
    const auto label = [](double value) {
        std::ostringstream out;
        out.imbue(std::locale::classic());
        out << std::setprecision(4) << value;
        return out.str();
    };
    // Six equally spaced fractions include both range endpoints (0 and 1).
    for (int i = 0; i <= 5; ++i) {
        // Division by 5.0 performs floating-point division rather than truncation.
        const double f = i / 5.0;
        // A varying X range gets six ticks. A constant range gets one centered
        // tick only, avoiding six repeated labels at the same value.
        if (includeX && (xmin != xmax || i == 0)) {
            const double pos = xmin == xmax ? .5 : f;
            const double x = left + pos * (right - left);
            drawLine(x, bottom, x, bottom + 4, "#64748b", 1);
            // Interpolate the data value using the same fraction as its pixel position.
            // At fractions 0 and 1 this gives xmin and xmax respectively.
            drawText(x - 10, bottom + 20, label((1 - pos) * xmin + pos * xmax), 11);
        }
        // Y ticks use bottom minus distance because screen Y grows downward.
        // The same midpoint rule handles an equal minimum and maximum.
        if (ymin != ymax || i == 0) {
            const double pos = ymin == ymax ? .5 : f;
            const double y = bottom - pos * (bottom - top);
            drawLine(left - 4, y, left, y, "#64748b", 1);
            // The weighted value matches this tick position; +4 adjusts the text baseline.
            drawText(8, y + 4, label((1 - pos) * ymin + pos * ymax), 11);
        }
    }
}
}

namespace dataviz {
// Add an outlined circle for the scatter plot's visible SVG markers.
// Reject invalid center/radius/outline width, then append one escaped SVG element.
void Renderer::drawOutlinedPoint(double x, double y, double radius, const std::string &fill,
                                 const std::string &outline, double outlineWidth) {
    if (!finite(x) || !finite(y) || !finite(radius) || radius <= 0 || !finite(outlineWidth) ||
        outlineWidth <= 0)
        throw std::invalid_argument("Invalid outlined point");
    elements_.push_back("<circle cx=\"" + number(x) + "\" cy=\"" + number(y) + "\" r=\"" +
                        number(radius) + "\" fill=\"" + escapeXML(fill) + "\" stroke=\"" +
                        escapeXML(outline) + "\" stroke-width=\"" + number(outlineWidth) + "\"/>");
}
}
