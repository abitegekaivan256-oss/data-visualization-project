// Project headers expose the production classes exercised by this program.
#include "dataviz/LinePlot.hpp"

// assert stops a test when an expected condition is false; CMake keeps these checks enabled.
#include <cassert>
// Floating-point helpers support approximate comparisons and finite-value examples.
#include <cmath>
// File streams create CSV fixtures and read the SVG files produced by tests.
#include <fstream>
// Console streams print progress, demonstration results and failure messages.
#include <iostream>
// Numeric limits supply NaN and infinity for invalid-input tests.
#include <limits>
// Standard exception types let tests distinguish validation failures.
#include <stdexcept>
// Strings hold filenames, labels and expected SVG text.
#include <string>
// Vectors store related observations and expected coordinate sequences.
#include <vector>

using dataviz::LinePlot;

// Accept a callable such as a lambda and return true only for invalid_argument.
// Unexpected exception types still escape, preventing a false passing test.
template <typename Operation> bool throwsInvalidArgument(Operation operation) {
    try {
        operation();
    } catch (const std::invalid_argument &) {
        return true;
    }
    return false;
}

// Check line geometry, invalid input, metadata escaping and empty/singleton/flat cases.
// Exceptions expected by a test are checked explicitly; other exceptions fail execution.
int main() {
    // An empty plot has no points/segments and cannot be exported.
    LinePlot plot;
    assert(plot.size() == 0);
    assert(plot.segments().empty());
    assert(throwsInvalidArgument([&] { plot.saveSvg("empty.svg"); }));

    // Consecutive observations create one fewer segment than points; preserve their given order.
    plot.setData({0, 1, 2, 3}, {1, 3, 2, 5});
    assert(plot.size() == 4);
    auto lines = plot.segments();
    assert(lines.size() == 3);
    assert(lines[0].start.x == 0 && lines[0].start.y == 1);
    assert(lines[0].end.x == 1 && lines[0].end.y == 3);
    assert(lines[2].end.x == 3 && lines[2].end.y == 5);

    // Bad input must throw before replacing the previously valid coordinate vectors.
    assert(throwsInvalidArgument([&] { plot.setData({1, 2}, {10}); }));
    assert(throwsInvalidArgument(
        [&] { plot.setData({1, std::numeric_limits<double>::quiet_NaN()}, {2, 3}); }));
    assert(throwsInvalidArgument(
        [&] { plot.setData({1}, {std::numeric_limits<double>::infinity()}); }));
    assert(plot.size() == 4); // Failed input must preserve existing data.

    assert(throwsInvalidArgument([&] { plot.saveSvg("bad.svg", 100, 100); }));
    // The special characters must appear as XML entities rather than malformed SVG markup.
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

    // A singleton has no connecting segment; constant ranges still need a usable midpoint mapping.
    LinePlot single({4}, {9});
    assert(single.segments().empty());
    single.saveSvg("test_single.svg");
    LinePlot flat({2, 2, 2}, {7, 7, 7});
    flat.saveSvg("test_flat.svg");

    std::cout << "All LinePlot tests passed.\n";
}
