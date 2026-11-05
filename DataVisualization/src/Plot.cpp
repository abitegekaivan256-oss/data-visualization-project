// ============================================================================
// DATA VISUALIZATION LIBRARY IN C++
//
// MODULE: COMMON PLOT DESIGN / INTEGRATION
// ASSIGNED TO: GROUP
//
// YOUR RESPONSIBILITIES:
// 1. Define common plot information shared by plot types.
// 2. Keep interfaces compatible across ScatterPlot, LinePlot and BarPlot.
// 3. Coordinate changes before editing this shared module.
//
// MAIN FILES:
// - include/dataviz/Plot.h
// - src/Plot.cpp
//
// DEPENDENCIES / COORDINATION:
// - All plotting modules
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

#include "dataviz/Plot.h"

Plot::Plot(const std::string& plotTitle)
    : title(plotTitle),
      xAxisLabel("X Axis"),
      yAxisLabel("Y Axis"),
      xScale(0.0, 1.0, 0.0, 100.0),// Default scale from 0 to 1 mapped to 0 to 100 pixels
      yScale(0.0, 1.0, 0.0, 100.0) {}

void Plot::setAxisLabels(const std::string& xLabel, const std::string& yLabel) {
    xAxisLabel = xLabel;
    yAxisLabel = yLabel;
}

void Plot::setXScale(double dMin, double dMax, double pMin, double pMax) {
    xScale = AxisScale(dMin, dMax, pMin, pMax);
}

void Plot::setYScale(double dMin, double dMax, double pMin, double pMax) {
    yScale = AxisScale(dMin, dMax, pMin, pMax);
}