// ============================================================================
// DATA VISUALIZATION LIBRARY IN C++
//
// MODULE: BAR PLOT
// ASSIGNED TO: JEFF
//
// YOUR RESPONSIBILITIES:
// 1. Accept categories/values.
// 2. Determine bar positions, widths and heights.
// 3. Use AxisScale where appropriate.
// 4. Pass drawing requirements to Renderer.
//
// MAIN FILES:
// - include/dataviz/BarPlot.h
// - src/BarPlot.cpp
// - tests/test_bar.cpp
//
// DEPENDENCIES / COORDINATION:
// - AxisScale (Bonius)
// - Renderer (Adrian + Group)
// - Plot (Group)
//
// TEAM RULES:
// - Work mainly in your allocated files.
// - Pull the latest repository before starting work.
// - Discuss changes to shared interfaces before editing them.
// - Compile/test your component before committing.
// - Use a clear commit message describing what changed.
//
// ============================================================================
#ifndef BAR_PLOT_H
#define BAR_PLOT_H

// string stores category/metadata text, vector owns the series, and the project
// headers supply scaling and the common polymorphic Plot interface.
#include <string>
#include <vector>
#include "dataviz/AxisScale.h"
#include "dataviz/Plot.h"

// Category/value plot with signed ASCII and SVG rendering.
class BarPlot : public Plot {
    // Encapsulation keeps the category/value series under this class's control.
    // Elements with the same index describe the same bar.
  private:
    std::vector<std::string> categories;
    std::vector<double> values;

  public:
    // Constructor to initialize the bar plot with a title
    // Initialize inherited metadata. Start empty and use addBar to build the series.
    BarPlot(const std::string &plotTitle);

    // Map values, including zero, into SVG rectangles on an existing Renderer.
    // Overrides Plot::render; empty series or invalid drawing geometry are errors.
    void render(dataviz::Renderer &) const override;
    // Append one category and finite value; reject NaN or infinity with invalid_argument.
    void addBar(const std::string &category, double value);
    // Print a signed character chart with a shared zero column. Width must be positive.
    void renderAscii(int terminalWidth = 50)
        const; // Render a simple ASCII representation of the bar plot in the terminal.

    // Getters for integration
    // Const references avoid copying whole vectors and prevent mutation through these accessors.
    // A returned reference remains valid only while the owning plot remains alive.
    const std::vector<std::string> &getCategories() const {
        return categories;
    }
    const std::vector<double> &getValues() const {
        return values;
    }
};

#endif // BAR_PLOT_H
