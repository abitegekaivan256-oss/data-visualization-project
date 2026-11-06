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

#include <stdexcept>
#include <cmath>

namespace dataviz { // <--- [ADDED IN WEEK 2/3] Namespace encapsulation

class AxisScale {
private:
    double minValue;
    double maxValue;

public:
    AxisScale(double min, double max);
    virtual ~AxisScale() = default; // <--- [ADDED] Safe virtual destructor for polymorphism

    double getMin() const;
    double getMax() const;
    void setRange(double min, double max);

    // [ADDED IN WEEK 3] Pure virtual function making this an abstract interface
    virtual double scale(double value) const = 0; 
};

// [ADDED IN WEEK 2/3] Concrete derived class for terminal/screen rendering
class LinearScale : public AxisScale {
private:
    double screenWidth;

public:
    LinearScale(double min, double max, double width);
    double scale(double value) const override;
};

// [ADDED IN WEEK 2/3] Concrete derived class for percentage-based scaling
class PercentageScale : public AxisScale {
public:
    PercentageScale(double min, double max);
    double scale(double value) const override;
};

} // namespace dataviz

#endif // AXIS_SCALE_H