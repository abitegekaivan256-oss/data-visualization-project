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
#ifndef DATAVIZ_RENDERER_H
#define DATAVIZ_RENDERER_H

// string stores SVG fragments, labels and color values.
#include <string>
// vector keeps drawing elements in their original drawing order.
#include <vector>

namespace dataviz {

// A simple value type for an X/Y coordinate. Public fields make geometry
// easy to pass between plots and the renderer; this type owns no resources.
struct Point {
    double x;
    double y;
};

// Concrete SVG drawing service. Plots calculate pixel positions and call
// these public primitives. Private canvas dimensions and SVG strings are
// encapsulated so callers cannot bypass the drawing methods. No file is
// created until saveSVG is called. Coordinates use SVG pixels: X grows right
// and Y grows down from the canvas top-left corner.
class Renderer {
  public:
    // Construct a blank canvas. Throws invalid_argument for nonpositive sizes.
    // Standard containers clean themselves up, so no custom destructor is needed.
    Renderer(int width = 800, int height = 600);

    // Read-only dimension access lets each plot choose its available drawing area.
    int width() const {
        return width_;
    }
    int height() const {
        return height_;
    }
    // Discard previous drawing elements and add a full-canvas background.
    void clear(const std::string &background = "white");
    // Add a line between two finite pixel positions. Width must be positive;
    // invalid geometry throws invalid_argument. Drawing methods return no value.
    void drawLine(double x1, double y1, double x2, double y2, const std::string &color = "black",
                  double strokeWidth = 2.0);
    // Add a filled circle centered at (x,y); radius must be positive and finite.
    void drawPoint(double x, double y, double radius = 4.0, const std::string &color = "steelblue");
    // Add a filled circle with a contrasting stroke. Both radius and outline
    // width must be positive and finite; colors are escaped as XML attributes.
    void drawOutlinedPoint(double x, double y, double radius, const std::string &fill,
                           const std::string &outline, double outlineWidth);
    // Add a rectangle at its upper-left corner. Zero dimensions are accepted
    // for zero-height bars; negative or nonfinite dimensions are rejected.
    void drawRectangle(double x, double y, double width, double height,
                       const std::string &fill = "steelblue");
    // Add visible text at a pixel position. XML-special characters are escaped
    // so the supplied text cannot accidentally become SVG markup.
    void drawText(double x, double y, const std::string &text, int fontSize = 14,
                  const std::string &color = "black");
    // Draw bottom and left axes for an ordered rectangular plot area.
    void drawAxes(double left, double top, double right, double bottom);
    // Draw one ordinary filled point for every supplied pixel coordinate.
    void drawScatter(const std::vector<Point> &points, const std::string &color = "steelblue");
    // Connect consecutive pixel points in caller-provided order.
    void drawPolyline(const std::vector<Point> &points, const std::string &color = "steelblue");
    // Draw signed pixel heights around baselineY. Positive heights extend up,
    // negative heights down; center/height vectors must have equal lengths.
    void drawBars(const std::vector<double> &xCenters, const std::vector<double> &heights,
                  double baselineY, double barWidth, const std::string &color = "steelblue");
    // Label varying data ranges with six ticks, or a constant range with one
    // centered tick. includeX=false leaves X labeling to categorical bar plots.
    void drawNumericTicks(double left, double top, double right, double bottom, double xmin,
                          double xmax, double ymin, double ymax, bool includeX = true);
    // Write the accumulated elements to filename. Returns false if the output
    // stream cannot open or reports a write failure; does not create directories.
    bool saveSVG(const std::string &filename) const;

  private:
    // Encapsulated canvas size; it remains fixed after successful construction.
    int width_;
    int height_;
    // Each string is one SVG element. Later elements appear over earlier ones.
    std::vector<std::string> elements_;
    // Internal helpers do not depend on one Renderer instance (static).
    // escapeXML returns safe XML text; finite rejects NaN and infinities.
    static std::string escapeXML(const std::string &input);
    static bool finite(double value);
};

} // namespace dataviz
#endif