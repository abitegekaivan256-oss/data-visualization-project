// Numeric limits supply NaN and infinity for invalid-input tests.
#include <limits>
// Project headers expose the production classes exercised by this program.
#include "dataviz/LinePlot.hpp"
#include "dataviz/ScatterPlot.h"
#include "dataviz/BarPlot.h"
// assert stops a test when an expected condition is false; CMake keeps these checks enabled.
#include <cassert>
// File streams create CSV fixtures and read the SVG files produced by tests.
#include <fstream>
// Console streams print progress, demonstration results and failure messages.
#include <iostream>
// String streams collect terminal output so ASCII rendering can be asserted.
#include <sstream>
// Stream iterators read an entire SVG file into a string for content checks.
#include <iterator>

// Read an SVG into a string. The input path must be readable; assert fails otherwise.
// The stream closes automatically when this helper returns.
std::string read(const std::string &path) {
    std::ifstream file(path);
    assert(file);
    return {std::istreambuf_iterator<char>(file), {}};
}
// Capture cout while the callable runs, then return the captured characters.
// Restore its original stream buffer on success AND exceptions, then rethrow any error.
template <class Action> std::string capture(Action action) {
    std::ostringstream stream;
    auto *old = std::cout.rdbuf(stream.rdbuf());
    try {
        action();
    } catch (...) {
        std::cout.rdbuf(old);
        throw;
    }
    std::cout.rdbuf(old);
    return stream.str();
}
// Check observable plot contracts shared across the modules, not just compilation.
// Assertions cover metadata, markers, signed data, numerical ticks and zero baselines.
int main() {
    // Use base setters and derived getters to catch duplicated/unsynchronized metadata state.
    dataviz::LinePlot line({1, 2}, {-2, 6});
    Plot &base = line;
    base.setTitle("Shared & title");
    base.setAxisLabels("Time label", "Value label");
    assert(line.getTitle() == "Shared & title");
    assert(line.getXAxisLabel() == "Time label");
    assert(line.getYAxisLabel() == "Value label");
    line.setXLabel("Updated X");
    assert(base.getXAxisLabel() == "Updated X");
    base.exportData(); // Source-compatible extension hook.
    dataviz::Renderer renderer;
    base.render(renderer);
    assert(renderer.saveSVG("shared.svg"));
    line.saveSvg("standalone.svg");
    // Both rendering paths must show the same escaped title and current axis labels.
    for (const auto &path : {"shared.svg", "standalone.svg"}) {
        const auto svg = read(path);
        assert(svg.find("Shared &amp; title") != svg.npos);
        assert(svg.find("Updated X") != svg.npos);
        assert(svg.find("Value label") != svg.npos);
    }
    assert(read("shared.svg").find(">-2</text>") != std::string::npos);
    assert(read("shared.svg").find(">6</text>") != std::string::npos);

    // The configured character belongs to ASCII output; SVG uses visible circular markers.
    ScatterPlot scatter("Markers", 'X');
    scatter.addPoint(1, 2);
    scatter.addPoint(2, 3);
    assert(scatter.getMarker() == 'X');
    const auto ascii = capture([&] { scatter.renderAscii(4, 2); });
    assert(ascii == "    X\n     \nX    \n");
    dataviz::Renderer markers;
    scatter.render(markers);
    assert(markers.saveSVG("markers.svg"));
    assert(scatter.getMarkerRadius() == 5.0);
    // Check exact center coordinates, default radius, blue fill and contrasting outline.
    const auto markerSvg = read("markers.svg");
    assert(markerSvg.find("<circle cx=\"80\" cy=\"520\" r=\"5\"") != markerSvg.npos);
    assert(markerSvg.find("fill=\"#2563eb\" stroke=\"#0f172a\" stroke-width=\"1.25\"") !=
           markerSvg.npos);
    assert(markerSvg.find("<circle cx=\"740\" cy=\"60\" r=\"5\"") != markerSvg.npos);
    scatter.setMarkerRadius(8);
    assert(scatter.getMarkerRadius() == 8);
    // Zero, negative, infinite and NaN radii must throw without changing the stored radius.
    for (double invalid : {0.0, -1.0, std::numeric_limits<double>::infinity(),
                           std::numeric_limits<double>::quiet_NaN()}) {
        bool rejected = false;
        try {
            scatter.setMarkerRadius(invalid);
        } catch (const std::invalid_argument &) {
            rejected = true;
        }
        assert(rejected && scatter.getMarkerRadius() == 8);
    }
    dataviz::Renderer enlarged;
    scatter.render(enlarged);
    assert(enlarged.saveSVG("enlarged.svg"));
    assert(read("enlarged.svg").find("r=\"8\"") != std::string::npos);
    // Signed coordinates should map to the same screen endpoints and midpoint after scaling.
    ScatterPlot signedPoints({-2, 0, 2}, {-4, 0, 4});
    dataviz::Renderer signedPointsRenderer;
    signedPoints.render(signedPointsRenderer);
    assert(signedPointsRenderer.saveSVG("signed_points.svg"));
    const auto signedSvg = read("signed_points.svg");
    assert(signedSvg.find("<circle cx=\"80\" cy=\"520\"") != signedSvg.npos);
    assert(signedSvg.find("<circle cx=\"410\" cy=\"290\"") != signedSvg.npos);
    assert(signedSvg.find("<circle cx=\"740\" cy=\"60\"") != signedSvg.npos);

    // A printable special character remains valid for ASCII, while SVG remains circle-based.
    ScatterPlot escaped({1}, {2}, "Escaped", '&');
    dataviz::Renderer escapedRenderer;
    escaped.render(escapedRenderer);
    assert(escapedRenderer.saveSVG("escaped.svg"));
    assert(capture([&] { escaped.renderAscii(4, 2); }).find('&') != std::string::npos);
    assert(read("escaped.svg").find("<circle") != std::string::npos);

    // Negative, positive and zero observations must share one terminal zero column.
    BarPlot bars("Signed");
    bars.addBar("negative", -2);
    bars.addBar("positive", 2);
    bars.addBar("zero", 0);
    const auto barText = capture([&] { bars.renderAscii(8); });
    assert(barText.find("####|    ") != barText.npos);
    assert(barText.find("    |####") != barText.npos);
    assert(barText.find("    |    ") != barText.npos);
    dataviz::Renderer signedRenderer;
    bars.render(signedRenderer);
    assert(signedRenderer.saveSVG("signed.svg"));
    // For the symmetric range [-2,2], the zero line lies halfway between pixel Y=60 and 520.
    const auto svg = read("signed.svg");
    assert(svg.find("x1=\"80\" y1=\"290\" x2=\"760\" y2=\"290\"") != svg.npos);
    assert(svg.find(">0 (zero)</text>") != svg.npos);
    assert(svg.find(">-2</text>") != svg.npos);
    assert(svg.find(">2</text>") != svg.npos);
    // Exercise a negative-only range and an all-zero range, not only mixed-sign data.
    BarPlot negative("Negative only");
    negative.addBar("n", -3);
    assert(capture([&] { negative.renderAscii(4); }).find("####|") != std::string::npos);
    BarPlot zeros("Zeros");
    zeros.addBar("z", 0);
    assert(capture([&] { zeros.renderAscii(4); }).find("  |  ") != std::string::npos);
}
