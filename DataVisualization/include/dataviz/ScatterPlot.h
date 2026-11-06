// Guard against duplicate declarations when several headers include this file.
#pragma once
// Plot supplies the shared metadata/render contract and the Renderer/Point declarations used for drawing.
#include "dataviz/Plot.h"

namespace dataviz {
// A scatter plot represents each supplied X/Y pair independently. Public inheritance
// makes it usable through Plot while its private coordinates stay inside the class.
class ScatterPlot : public Plot {
    // Class members before public: are private. Matching indices form one observation.
    // vector owns the coordinate storage and releases it automatically on destruction.
    std::vector<double> xValues, yValues;
    char marker_ = '*'; // ASCII only; SVG uses filled circles.
    // SVG circle size in pixels; keep it positive and finite through setMarkerRadius.
    double markerRadius_ = 5.0;

  public:
    // Copy a nonempty, equally sized pair of finite-coordinate vectors.
    // Invalid coordinates, sizes or ASCII marker characters throw invalid_argument.
    ScatterPlot(const std::vector<double> &x, const std::vector<double> &y,
                const std::string &name = "Scatter Plot", char marker = '*');
    // Start an empty plot with metadata and an ASCII marker, then populate it with addPoint.
    // Rendering SVG before adding any point is an error, while ASCII output may be empty.
    explicit ScatterPlot(const std::string &name, char marker = '*');
    // Read the configured terminal character. SVG uses outlined circles instead of this glyph.
    char getMarker() const {
        return marker_;
    }
    // Update circle radius only after validation; rejected input preserves the old radius.
    void setMarkerRadius(double radius);
    // Return a value copy of the current SVG radius without allowing direct mutation.
    double getMarkerRadius() const {
        return markerRadius_;
    }
    // Append one finite X/Y observation. A nonfinite coordinate throws invalid_argument.
    void addPoint(double x, double y);
    // Print a character grid of the requested positive dimensions; no SVG file is written.
    void renderAscii(int width = 40, int height = 15) const;
    // Report the number of stored observations, which is the coordinate-vector length.
    std::size_t pointCount() const;
    // Map data to canvas pixels and send axes, ticks, labels and circles to the renderer.
    // This fills the renderer only; ImageExporter or Renderer::saveSVG writes the file.
    void draw(Renderer &) const;
    // Overriding satisfies Plot's abstract contract. A Plot* call dispatches here at runtime.
    // Forwarding to draw keeps the existing direct-draw API available too.
    void render(Renderer &renderer) const override {
        draw(renderer);
    }
};
}
// Preserve the historical global class name as an alias for the namespaced implementation.
using ScatterPlot = dataviz::ScatterPlot;
