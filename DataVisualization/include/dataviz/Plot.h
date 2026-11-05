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

#ifndef PLOT_H
#define PLOT_H

#include <string>
#include "dataviz/AxisScale.h"

class Plot {
protected:
    std::string title;
    std::string xAxisLabel;
    std::string yAxisLabel;
    AxisScale xScale;
    AxisScale yScale;

public:
    Plot(const std::string& plotTitle);
    virtual ~Plot() = default;

    // Common member functions inherited by all plot subclasses
    void setAxisLabels(const std::string& xLabel, const std::string& yLabel);
    void setXScale(double dMin, double dMax, double pMin, double pMax);
    void setYScale(double dMin, double dMax, double pMin, double pMax);

    std::string getTitle() const { return title; }
    std::string getXAxisLabel() const { return xAxisLabel; }
    std::string getYAxisLabel() const { return yAxisLabel; }
};

#endif // PLOT_H