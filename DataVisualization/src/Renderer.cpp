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
// IMPLEMENTATION STATUS: NOT YET IMPLEMENTED
// ============================================================================
#include "dataviz/Renderer.h"

#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace dataviz {
namespace {
std::string number(double value) {
    std::ostringstream stream;
    stream << value;
    return stream.str();
}
}

Renderer::Renderer(int width, int height) : width_(width), height_(height) {
    if (width <= 0 || height <= 0)
        throw std::invalid_argument("Canvas dimensions must be positive");
    clear();
}

bool Renderer::finite(double value) { return std::isfinite(value); }

std::string Renderer::escapeXML(const std::string& input) {
    std::string escaped;
    for (char c : input) {
        switch (c) {
            case '&': escaped += "&amp;"; break;
            case '<': escaped += "&lt;"; break;
            case '>': escaped += "&gt;"; break;
            case '\"': escaped += "&quot;"; break;
            case '\'': escaped += "&apos;"; break;
            default: escaped += c;
        }
    }
    return escaped;
}

void Renderer::clear(const std::string& background) {
    elements_.clear();
    elements_.push_back("<rect width=\"100%\" height=\"100%\" fill=\"" +
                        escapeXML(background) + "\"/>");
}

void Renderer::drawLine(double x1, double y1, double x2, double y2,
                        const std::string& color, double strokeWidth) {
    if (!finite(x1) || !finite(y1) || !finite(x2) || !finite(y2) ||
        !finite(strokeWidth) || strokeWidth <= 0)
        throw std::invalid_argument("Invalid line coordinates or width");
    elements_.push_back("<line x1=\"" + number(x1) + "\" y1=\"" + number(y1) +
                        "\" x2=\"" + number(x2) + "\" y2=\"" + number(y2) +
                        "\" stroke=\"" + escapeXML(color) + "\" stroke-width=\"" +
                        number(strokeWidth) + "\"/>");
}

void Renderer::drawPoint(double x, double y, double radius, const std::string& color) {
    if (!finite(x) || !finite(y) || !finite(radius) || radius <= 0)
        throw std::invalid_argument("Invalid point coordinates or radius");
    elements_.push_back("<circle cx=\"" + number(x) + "\" cy=\"" + number(y) +
                        "\" r=\"" + number(radius) + "\" fill=\"" +
                        escapeXML(color) + "\"/>");
}

void Renderer::drawRectangle(double x, double y, double width, double height,
                             const std::string& fill) {
    if (!finite(x) || !finite(y) || !finite(width) || !finite(height) ||
        width < 0 || height < 0)
        throw std::invalid_argument("Invalid rectangle dimensions");
    elements_.push_back("<rect x=\"" + number(x) + "\" y=\"" + number(y) +
                        "\" width=\"" + number(width) + "\" height=\"" +
                        number(height) + "\" fill=\"" + escapeXML(fill) + "\"/>");
}

void Renderer::drawText(double x, double y, const std::string& text,
                        int fontSize, const std::string& color) {
    if (!finite(x) || !finite(y) || fontSize <= 0)
        throw std::invalid_argument("Invalid text position or font size");
    elements_.push_back("<text x=\"" + number(x) + "\" y=\"" + number(y) +
                        "\" font-size=\"" + number(fontSize) +
                        "\" fill=\"" + escapeXML(color) +
                        "\" font-family=\"Arial,sans-serif\">" + escapeXML(text) + "</text>");
}

void Renderer::drawAxes(double left, double top, double right, double bottom) {
    if (!(left < right && top < bottom))
        throw std::invalid_argument("Invalid plotting area");
    drawLine(left, bottom, right, bottom);
    drawLine(left, bottom, left, top);
}

void Renderer::drawScatter(const std::vector<Point>& points, const std::string& color) {
    for (const Point& p : points) drawPoint(p.x, p.y, 4.0, color);
}

void Renderer::drawPolyline(const std::vector<Point>& points, const std::string& color) {
    for (std::size_t i = 1; i < points.size(); ++i)
        drawLine(points[i-1].x, points[i-1].y, points[i].x, points[i].y, color);
}

void Renderer::drawBars(const std::vector<double>& xCenters,
                        const std::vector<double>& heights,
                        double baselineY, double barWidth, const std::string& color) {
    if (xCenters.size() != heights.size() || !finite(baselineY) ||
        !finite(barWidth) || barWidth <= 0)
        throw std::invalid_argument("Invalid bar data or width");
    for (std::size_t i = 0; i < xCenters.size(); ++i) {
        if (!finite(xCenters[i]) || !finite(heights[i]))
            throw std::invalid_argument("Invalid bar coordinate");
        double endY = baselineY - heights[i];
        drawRectangle(xCenters[i] - barWidth / 2.0,
                      std::min(endY, baselineY), barWidth,
                      std::abs(heights[i]), color);
    }
}

bool Renderer::saveSVG(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) return false;
    out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    out << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << width_
        << "\" height=\"" << height_ << "\" viewBox=\"0 0 " << width_ << ' '
        << height_ << "\">\n";
    for (const std::string& element : elements_) out << "  " << element << '\n';
    out << "</svg>\n";
    return static_cast<bool>(out);
}
} // namespace dataviz