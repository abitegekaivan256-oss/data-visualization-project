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

// AxisScale is a utility class that provides scaling functionality for data visualization. It maps data values to pixel coordinates based on the specified data range and plot range. This class is designed to be used by various plot types, including scatter plots, line plots, and bar plots.
#ifndef AXIS_SCALE_H
#define AXIS_SCALE_H

// stdexcept supplies invalid_argument for unusable ranges; cmath supplies finite-value checks.
#include <stdexcept>
#include <cmath>

namespace dataviz { // <--- [ADDED IN WEEK 2/3] Namespace encapsulation

// Abstract scale contract: store a validated data range, then let a derived class
// choose the output unit. This class cannot be constructed on its own because scale is pure virtual.
// A scale returns a distance; the plot adds margins and handles the inverted SVG Y direction.
class AxisScale {
  private:
    // Private bounds prevent callers from bypassing the validation in setRange.
    double minValue;
    double maxValue;

  public:
    // Validate and store the minimum/maximum. Throws invalid_argument for nonfinite
    // limits or min > max; equal limits are allowed and handled by derived scales.
    AxisScale(double min, double max);
    virtual ~AxisScale() = default; // <--- [ADDED] Safe virtual destructor for polymorphism

    // Read-only accessors return copies of the current bounds without changing them.
    double getMin() const;
    double getMax() const;
    // Replace both bounds only after validating them; rejected input leaves the old range intact.
    void setRange(double min, double max);

    // [ADDED IN WEEK 3] Pure virtual function making this an abstract interface
    // Input: one finite data value. Output: its mapped distance. Derived classes
    // override this operation, enabling calls through an AxisScale pointer/reference.
    virtual double scale(double value) const = 0;
};

// [ADDED IN WEEK 2/3] Concrete derived class for terminal/screen rendering
class LinearScale : public AxisScale {
  private:
    // The available drawing distance, which must be positive and finite.
    // The same class also scales vertical distances despite this historical member name.
    double screenWidth;

  public:
    // Construct the validated base range and store the desired output distance.
    // scale throws for nonfinite input; values outside the range extrapolate rather than clamp.
    LinearScale(double min, double max, double width);
    double scale(double value) const override;
};

// [ADDED IN WEEK 2/3] Concrete derived class for percentage-based scaling
class PercentageScale : public AxisScale {
  public:
    // Reuse base-range validation and express the normalized result in percentage units.
    // A constant range maps to 50; this utility does not draw an axis by itself.
    PercentageScale(double min, double max);
    double scale(double value) const override;
};

} // namespace dataviz

#endif // AXIS_SCALE_H