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

#include "dataviz/AxisScale.h"

namespace dataviz {

// BASE CLASS
AxisScale::AxisScale(double min, double max) {
    setRange(min, max);
}

double AxisScale::getMin() const { return minValue; }
double AxisScale::getMax() const { return maxValue; }

void AxisScale::setRange(double min, double max) {
    // [ADDED IN WEEK 2/3] Robust error checking and safety validation
    if (!std::isfinite(min) || !std::isfinite(max) || min > max) {
        throw std::invalid_argument("Invalid data range");
    }
    minValue = min;
    maxValue = max;
}

// LINEAR SCALE IMPLEMENTATION
LinearScale::LinearScale(double min, double max, double width)
    : AxisScale(min, max), screenWidth(width) {
    if (!std::isfinite(width) || width <= 0) {
        throw std::invalid_argument("Invalid screen width");
    }
}

double LinearScale::scale(double value) const {
    if (!std::isfinite(value)) throw std::invalid_argument("Invalid value");
    if (getMin() == getMax()) return screenWidth / 2.0;
    
    return ((value - getMin()) / (getMax() - getMin())) * screenWidth;
}

// PERCENTAGE SCALE IMPLEMENTATION
PercentageScale::PercentageScale(double min, double max) : AxisScale(min, max) {}

double PercentageScale::scale(double value) const {
    if (!std::isfinite(value)) throw std::invalid_argument("Invalid value");
    if (getMin() == getMax()) return 50.0;

    return ((value - getMin()) / (getMax() - getMin())) * 100.0;
}

} // namespace dataviz