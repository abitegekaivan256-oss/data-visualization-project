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
// ============================================================================

// Include the matching declarations so the compiler checks every definition against its interface.
#include "dataviz/AxisScale.h"

namespace dataviz {

// BASE CLASS
// Initialize the common range by reusing the same validation used for later updates.
// Construction stops with invalid_argument if the supplied range is not usable.
AxisScale::AxisScale(double min, double max) {
    setRange(min, max);
}

// These const getters expose the private bounds without giving the caller writable references.
double AxisScale::getMin() const {
    return minValue;
}
double AxisScale::getMax() const {
    return maxValue;
}

// Input: proposed data limits. Output: no return value; a successful call updates the object.
// Validate first so an exception does not replace previously valid bounds.
void AxisScale::setRange(double min, double max) {
    // [ADDED IN WEEK 2/3] Robust error checking and safety validation
    if (!std::isfinite(min) || !std::isfinite(max) || min > max) {
        throw std::invalid_argument("Invalid data range");
    }
    // Once both limits pass, store them together as the range used by scale().
    minValue = min;
    maxValue = max;
}

// LINEAR SCALE IMPLEMENTATION
// Build the base range first, then the derived output-width member.
// Nonpositive or nonfinite widths cannot represent a usable drawing distance.
LinearScale::LinearScale(double min, double max, double width)
    : AxisScale(min, max), screenWidth(width) {
    if (!std::isfinite(width) || width <= 0) {
        throw std::invalid_argument("Invalid screen width");
    }
}

// Map a finite data value to a distance in the chosen output width.
// This returns a double so plots retain subpixel precision; it does not add a plot margin.
double LinearScale::scale(double value) const {
    if (!std::isfinite(value))
        throw std::invalid_argument("Invalid value");
    // A constant dataset would divide by zero in the general formula. Center it instead.
    if (getMin() == getMax())
        return screenWidth / 2.0;

    // Subtract the data minimum, divide by the range, then multiply by the available width.
    // A negative minimum works naturally. Out-of-range finite values are not clamped.
    return ((value - getMin()) / (getMax() - getMin())) * screenWidth;
}

// PERCENTAGE SCALE IMPLEMENTATION
// Percentage scaling needs no extra state; its constructor delegates range validation to AxisScale.
PercentageScale::PercentageScale(double min, double max) : AxisScale(min, max) {
}

// Use the same normalization in percentage units. Reject nonfinite values,
// and use the midpoint 50 when every observation has the same value.
double PercentageScale::scale(double value) const {
    if (!std::isfinite(value))
        throw std::invalid_argument("Invalid value");
    if (getMin() == getMax())
        return 50.0;

    // Multiplying the normalized fraction by 100 expresses the result as a percentage.
    return ((value - getMin()) / (getMax() - getMin())) * 100.0;
}

} // namespace dataviz