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
#ifndef DATAVIZ_RENDERER_H
#define DATAVIZ_RENDERER_H

#include <string>
#include <vector>

namespace dataviz {

struct Point {
    double x;
    double y;
};

class Renderer {
public:
    Renderer(int width = 800, int height = 600);

    void clear(const std::string& background = "white");
    void drawLine(double x1, double y1, double x2, double y2,
                  const std::string& color = "black", double strokeWidth = 2.0);
    void drawPoint(double x, double y, double radius = 4.0,
                   const std::string& color = "steelblue");
    void drawRectangle(double x, double y, double width, double height,
                       const std::string& fill = "steelblue");
    void drawText(double x, double y, const std::string& text,
                  int fontSize = 14, const std::string& color = "black");
    void drawAxes(double left, double top, double right, double bottom);
    void drawScatter(const std::vector<Point>& points,
                     const std::string& color = "steelblue");
    void drawPolyline(const std::vector<Point>& points,
                      const std::string& color = "steelblue");
    void drawBars(const std::vector<double>& xCenters,
                  const std::vector<double>& heights,
                  double baselineY, double barWidth,
                  const std::string& color = "steelblue");
    bool saveSVG(const std::string& filename) const;

private:
    int width_;
    int height_;
    std::vector<std::string> elements_;
    static std::string escapeXML(const std::string& input);
    static bool finite(double value);
};

} // namespace dataviz
#endif