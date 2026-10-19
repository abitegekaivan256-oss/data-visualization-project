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
// IMPLEMENTATION STATUS: NOT YET IMPLEMENTED
// ============================================================================
#pragma once

#include "dataviz/DataTypes.h"
#include "dataviz/PlotOptions.h"
#include "dataviz/AxisScale.h"
#include "dataviz/Labels.h"
#include "dataviz/Renderer.h"

namespace dataviz {

/**
 * BarPlot draws a category/value series as vertical bars.
 *
 * Integration note:
 * This module follows the workflow's intended dependencies. The group must
 * agree the exact method names/signatures in AxisScale, Labels, Renderer and
 * PlotOptions before merging. The method below uses the shared renderer's
 * primitive operations (begin, line, rectangle, text, finish); see README.md
 * for the proposed contract used by this implementation.
 */
class BarPlot {
public:
    /**
     * Draw a vertical bar chart.
     *
     * @param series One category and one numeric value per bar.
     * @param options Canvas size, margins, title, labels and colours.
     * @param axis Shared value-axis scaler, responsible for value range and
     *             conversion of values to drawing coordinates.
     * @param labels Shared label helper for title, axes and category labels.
     * @param renderer Shared renderer that draws primitives and exports SVG.
     * @return true when the chart is drawn; false for invalid/empty input.
     */
    static bool draw(const CategorySeries& series,
                     const PlotOptions& options,
                     AxisScale& axis,
                     Labels& labels,
                     Renderer& renderer);
};

} // namespace dataviz
