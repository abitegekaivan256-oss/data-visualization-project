#include "dataviz/LinePlot.hpp"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

using dataviz::LinePlot;

template <typename Operation>
bool throwsInvalidArgument(Operation operation) {
    try { operation(); }
    catch (const std::invalid_argument&) { return true; }
    return false;
}

int main() {
    LinePlot plot;
    assert(plot.size() == 0);
    assert(plot.segments().empty());
    assert(throwsInvalidArgument([&] { plot.saveSvg("empty.svg"); }));

    plot.setData({0, 1, 2, 3}, {1, 3, 2, 5});
    assert(plot.size() == 4);
    auto lines = plot.segments();
    assert(lines.size() == 3);
    assert(lines[0].start.x == 0 && lines[0].start.y == 1);
    assert(lines[0].end.x == 1 && lines[0].end.y == 3);
    assert(lines[2].end.x == 3 && lines[2].end.y == 5);

    assert(throwsInvalidArgument([&] { plot.setData({1, 2}, {10}); }));
    assert(throwsInvalidArgument([&] {
        plot.setData({1, std::numeric_limits<double>::quiet_NaN()}, {2, 3});
    }));
    assert(throwsInvalidArgument([&] {
        plot.setData({1}, {std::numeric_limits<double>::infinity()});
    }));
    assert(plot.size() == 4); // Failed input must preserve existing data.

    assert(throwsInvalidArgument([&] { plot.saveSvg("bad.svg", 100, 100); }));
    plot.setTitle("Revenue & Profit <2026>");
    plot.setXLabel("Time");
    plot.setYLabel("USD");
    const std::string output = "test_lineplot.svg";
    plot.saveSvg(output);
    std::ifstream svg(output);
    assert(svg.good());
    std::string content((std::istreambuf_iterator<char>(svg)), std::istreambuf_iterator<char>());
    assert(content.find("<polyline") != std::string::npos);
    assert(content.find("Revenue &amp; Profit &lt;2026&gt;") != std::string::npos);

    LinePlot single({4}, {9});
    assert(single.segments().empty());
    single.saveSvg("test_single.svg");
    LinePlot flat({2, 2, 2}, {7, 7, 7});
    flat.saveSvg("test_flat.svg");

    std::cout << "All LinePlot tests passed.\n";
}
