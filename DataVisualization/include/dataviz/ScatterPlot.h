#pragma once
#include "dataviz/Plot.h"

namespace dataviz {
class ScatterPlot : public Plot {
    std::vector<double> xValues, yValues;
    char marker_ = '*'; // ASCII only; SVG uses filled circles.
    double markerRadius_ = 5.0;
public:
    ScatterPlot(const std::vector<double>& x, const std::vector<double>& y,
                const std::string& name = "Scatter Plot", char marker = '*');
    explicit ScatterPlot(const std::string& name, char marker = '*');
    char getMarker() const { return marker_; }
    void setMarkerRadius(double radius);
    double getMarkerRadius() const { return markerRadius_; }
    void addPoint(double x, double y);
    void renderAscii(int width = 40, int height = 15) const;
    std::size_t pointCount() const;
    void draw(Renderer&) const;
    void render(Renderer& renderer) const override { draw(renderer); }
};
}
using ScatterPlot = dataviz::ScatterPlot;
