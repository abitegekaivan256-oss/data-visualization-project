// ============================================================================
// DATA VISUALIZATION LIBRARY IN C++
//
// MODULE: AXIS SCALING
// ASSIGNED TO: BONIUS
//
// YOUR RESPONSIBILITIES:
// 1. Determine useful data ranges.
// 2. Map data coordinates to plot/screen coordinates.
// 3. Support all three plot types.
// 4. Handle edge cases such as equal minimum and maximum values.
//
// MAIN FILES:
// - include/dataviz/AxisScale.h
// - src/AxisScale.cpp
// - tests/test_scaling.cpp
//
// DEPENDENCIES / COORDINATION:
// - ScatterPlot (Adrian)
// - LinePlot (Sandra)
// - BarPlot (Jeff)
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

// AxisScale is a utility class that provides scaling functionality for data visualization. It maps data values to pixel coordinates based on the specified data range and plot range. This class is designed to be used by various plot types, including scatter plots, line plots, and bar plots.
#ifndef AXIS_SCALE_H
#define AXIS_SCALE_H

#include <vector>
#include <utility>

class AxisScale {
private:
    double dataMin;
    double dataMax;
    double plotMin;
    double plotMax;

public:
    AxisScale(double dMin, double dMax, double pMin, double pMax);

    // Normalize data value to pixel/coordinate space [pMin, pMax]
    double scale(double value) const;

    // Getters
    double getDataMin() const { return dataMin; }
    double getDataMax() const { return dataMax; }
};

#endif // AXIS_SCALE_H