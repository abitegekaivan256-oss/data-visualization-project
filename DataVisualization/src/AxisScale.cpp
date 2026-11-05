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


//axis scaling implementation
#include "dataviz/AxisScale.h"
#include <stdexcept>

AxisScale::AxisScale(double dMin, double dMax, double pMin, double pMax) 
    : dataMin(dMin), dataMax(dMax), plotMin(pMin), plotMax(pMax) {
    if (dMin == dMax) {
        this->dataMax += 1.0; // Prevent division by zero
    }
}

double AxisScale::scale(double value) const {
    if (value < dataMin) value = dataMin;
    if (value > dataMax) value = dataMax;
    
    return plotMin + (value - dataMin) * (plotMax - plotMin) / (dataMax - dataMin);
}