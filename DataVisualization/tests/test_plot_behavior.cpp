#include <limits>
#include "dataviz/LinePlot.hpp"
#include "dataviz/ScatterPlot.h"
#include "dataviz/BarPlot.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>

std::string read(const std::string& path) {
    std::ifstream file(path);
    assert(file);
    return {std::istreambuf_iterator<char>(file), {}};
}
template<class Action> std::string capture(Action action) {
    std::ostringstream stream;
    auto* old = std::cout.rdbuf(stream.rdbuf());
    try { action(); } catch (...) { std::cout.rdbuf(old); throw; }
    std::cout.rdbuf(old);
    return stream.str();
}
int main() {
    dataviz::LinePlot line({1, 2}, {-2, 6});
    Plot& base = line;
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
    for (const auto& path : {"shared.svg", "standalone.svg"}) {
        const auto svg = read(path);
        assert(svg.find("Shared &amp; title") != svg.npos);
        assert(svg.find("Updated X") != svg.npos);
        assert(svg.find("Value label") != svg.npos);
    }
    assert(read("shared.svg").find(">-2</text>") != std::string::npos);
    assert(read("shared.svg").find(">6</text>") != std::string::npos);

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
    const auto markerSvg = read("markers.svg");
    assert(markerSvg.find("<circle cx=\"80\" cy=\"520\" r=\"5\"") != markerSvg.npos);
    assert(markerSvg.find("fill=\"#2563eb\" stroke=\"#0f172a\" stroke-width=\"1.25\"") != markerSvg.npos);
    assert(markerSvg.find("<circle cx=\"740\" cy=\"60\" r=\"5\"") != markerSvg.npos);
    scatter.setMarkerRadius(8);
    assert(scatter.getMarkerRadius() == 8);
    for (double invalid : {0.0, -1.0, std::numeric_limits<double>::infinity(),
                            std::numeric_limits<double>::quiet_NaN()}) {
        bool rejected = false;
        try { scatter.setMarkerRadius(invalid); }
        catch (const std::invalid_argument&) { rejected = true; }
        assert(rejected && scatter.getMarkerRadius() == 8);
    }
    dataviz::Renderer enlarged;
    scatter.render(enlarged);
    assert(enlarged.saveSVG("enlarged.svg"));
    assert(read("enlarged.svg").find("r=\"8\"") != std::string::npos);
    ScatterPlot signedPoints({-2, 0, 2}, {-4, 0, 4});
    dataviz::Renderer signedPointsRenderer;
    signedPoints.render(signedPointsRenderer);
    assert(signedPointsRenderer.saveSVG("signed_points.svg"));
    const auto signedSvg = read("signed_points.svg");
    assert(signedSvg.find("<circle cx=\"80\" cy=\"520\"") != signedSvg.npos);
    assert(signedSvg.find("<circle cx=\"410\" cy=\"290\"") != signedSvg.npos);
    assert(signedSvg.find("<circle cx=\"740\" cy=\"60\"") != signedSvg.npos);

    ScatterPlot escaped({1}, {2}, "Escaped", '&');
    dataviz::Renderer escapedRenderer;
    escaped.render(escapedRenderer);
    assert(escapedRenderer.saveSVG("escaped.svg"));
    assert(capture([&] { escaped.renderAscii(4, 2); }).find('&') != std::string::npos);
    assert(read("escaped.svg").find("<circle") != std::string::npos);

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
    const auto svg = read("signed.svg");
    assert(svg.find("x1=\"80\" y1=\"290\" x2=\"760\" y2=\"290\"") != svg.npos);
    assert(svg.find(">0 (zero)</text>") != svg.npos);
    assert(svg.find(">-2</text>") != svg.npos);
    assert(svg.find(">2</text>") != svg.npos);
    BarPlot negative("Negative only");
    negative.addBar("n", -3);
    assert(capture([&] { negative.renderAscii(4); }).find("####|") != std::string::npos);
    BarPlot zeros("Zeros");
    zeros.addBar("z", 0);
    assert(capture([&] { zeros.renderAscii(4); }).find("  |  ") != std::string::npos);
}
