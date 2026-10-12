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
#include "dataviz/BarPlot.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <string>

namespace dataviz {

bool BarPlot::draw(const CategorySeries& series,
                   const PlotOptions& options,
                   AxisScale& axis,
                   Labels& labels,
                   Renderer& renderer)
{
    const std::size_t count = series.categories.size();

    // A bar chart requires matching category/value entries and finite values.
    if (count == 0 || series.values.size() != count) {
        return false;
    }

    for (double value : series.values) {
        if (!std::isfinite(value)) {
            return false;
        }
    }

    /*
     * Proposed shared contract used here:
     *   options.width, options.height
     *   options.marginLeft, options.marginRight,
     *   options.marginTop, options.marginBottom
     *   options.title, options.xLabel, options.yLabel
     *   options.backgroundColour, options.barColour,
     *   options.axisColour, options.textColour
     *
     * AxisScale:
     *   axis.configure(minValue, maxValue, pixelTop, pixelBottom)
     *   axis.toPixel(value)
     *
     * Labels:
     *   labels.drawTitle(renderer, text, x, y, colour)
     *   labels.drawAxisLabel(renderer, text, x, y, colour)
     *   labels.drawCategory(renderer, text, x, y, colour)
     *
     * Renderer:
     *   begin(width, height, background); line(...); rectangle(...);
     *   text(...); finish()
     *
     * Confirm these names with the team and adapt them to the final shared
     * headers if their agreed API differs.
     */
    const double width = static_cast<double>(options.width);
    const double height = static_cast<double>(options.height);
    const double left = options.marginLeft;
    const double right = width - options.marginRight;
    const double top = options.marginTop;
    const double bottom = height - options.marginBottom;

    if (width <= 0 || height <= 0 || right <= left || bottom <= top) {
        return false;
    }

    const auto limits = std::minmax_element(series.values.begin(),
                                            series.values.end());
    double minValue = std::min(0.0, *limits.first);
    double maxValue = std::max(0.0, *limits.second);

    // Avoid a zero-height value range when every value is zero.
    if (std::abs(maxValue - minValue) < 1e-12) {
        maxValue = 1.0;
    }

    axis.configure(minValue, maxValue, top, bottom);

    renderer.begin(options.width, options.height, options.backgroundColour);

    // Main axes. The value zero is the baseline, including for negative bars.
    const double zeroY = axis.toPixel(0.0);
    renderer.line(left, top, left, bottom, options.axisColour, 1.0);
    renderer.line(left, zeroY, right, zeroY, options.axisColour, 1.0);

    const double plotWidth = right - left;
    const double slotWidth = plotWidth / static_cast<double>(count);
    const double barWidth = slotWidth * 0.65;

    for (std::size_t i = 0; i < count; ++i) {
        const double centerX = left + (static_cast<double>(i) + 0.5) * slotWidth;
        const double valueY = axis.toPixel(series.values[i]);
        const double barTop = std::min(valueY, zeroY);
        const double barHeight = std::abs(zeroY - valueY);

        renderer.rectangle(centerX - barWidth / 2.0,
                           barTop,
                           barWidth,
                           barHeight,
                           options.barColour,
                           options.barColour);

        labels.drawCategory(renderer,
                            series.categories[i],
                            centerX,
                            bottom + 18.0,
                            options.textColour);
    }

    labels.drawTitle(renderer,
                     options.title,
                     (left + right) / 2.0,
                     options.marginTop / 2.0,
                     options.textColour);

    labels.drawAxisLabel(renderer,
                         options.xLabel,
                         (left + right) / 2.0,
                         height - 8.0,
                         options.textColour);

    // Place the y-axis label near the left margin; rotation may be added by
    // the shared Labels implementation if it supports rotated text.
    labels.drawAxisLabel(renderer,
                         options.yLabel,
                         options.marginLeft / 2.0,
                         (top + bottom) / 2.0,
                         options.textColour);

    renderer.finish();
    return true;
}

} // namespace dataviz
