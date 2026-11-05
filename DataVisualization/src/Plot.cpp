#include "dataviz/Plot.h"

Plot::Plot(const std::string& plotTitle)
    : title(plotTitle),
      xAxisLabel("X Axis"),
      yAxisLabel("Y Axis"),
      xScale(0.0, 1.0, 0.0, 100.0),
      yScale(0.0, 1.0, 0.0, 100.0) {}

void Plot::setAxisLabels(const std::string& xLabel, const std::string& yLabel) {
    xAxisLabel = xLabel;
    yAxisLabel = yLabel;
}

// NOTE: You do NOT write a Plot::render() function here in Plot.cpp 
// because it is pure virtual (= 0)!