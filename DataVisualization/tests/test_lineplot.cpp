// Project headers expose the production LinePlot class exercised by this program.
#include "dataviz/LinePlot.hpp"

// Include libraries needed for testing and handling files.
// assert stops a test when an expected condition is false; CMake keeps these checks enabled.
#include <cassert>
// Floating-point helpers support approximate comparisons and finite-value examples.
#include <cmath>
// File streams create CSV fixtures and read the SVG files produced by tests.
#include <fstream>
// Console streams print progress, demonstration results and failure messages.
#include <iostream>
// Stream iterators read the generated SVG into a string for content assertions.
#include <iterator>
// Numeric limits supply NaN and infinity for invalid-input tests.
#include <limits>
// Standard exception types let tests distinguish validation failures.
#include <stdexcept>
// Strings hold filenames, labels and expected SVG text.
#include <string>
// Vectors store related observations and expected coordinate sequences.
#include <vector>

// Allows us to use LinePlot without writing dataviz:: every time.
using dataviz::LinePlot;

// Accept a callable such as a lambda and return true only for invalid_argument.
// Unexpected exception types still escape, preventing a false passing test.
template <typename Operation> bool throwsInvalidArgument(Operation operation) {
    try {
        // Try to perform the operation.
        operation();
    } catch (const std::invalid_argument &) { // Only the expected error counts as success.
        return true;
    }
    // If no error occurs, return false.
    return false;
}

// Check line geometry, invalid input, metadata escaping and empty/singleton/flat cases.
// Exceptions expected by a test are checked explicitly; other exceptions fail execution.
int main() {
    // An empty plot has no points/segments and cannot be exported.
    LinePlot plot; // Create an empty line plot.
    // Check that the new plot has no data points.
    assert(plot.size() == 0);
    // Check that the new plot has no connecting lines.
    assert(plot.segments().empty());
    // Check that an empty graph cannot be saved.
    assert(throwsInvalidArgument([&] { plot.saveSvg("empty.svg"); }));

    // Consecutive observations create one fewer segment than points; preserve their given order.
    // Enter four X values and four Y values.
    plot.setData({0, 1, 2, 3}, {1, 3, 2, 5});

    // Check that four points have been stored.
    assert(plot.size() == 4);

    // Get the lines connecting the points.
    auto lines = plot.segments();

    // Check that four points produce three connecting lines.
    assert(lines.size() == 3);

    // Check the starting position of the first line.
    assert(lines[0].start.x == 0 && lines[0].start.y == 1);

    // Check the ending position of the first line.
    assert(lines[0].end.x == 1 && lines[0].end.y == 3);

    // Check the ending position of the third line.
    assert(lines[2].end.x == 3 && lines[2].end.y == 5);

    // Bad input must throw before replacing the previously valid coordinate vectors.
    // Check that the program rejects unequal X and Y values.
    assert(throwsInvalidArgument([&] { plot.setData({1, 2}, {10}); }));
    // Check that the program rejects NaN (Not a Number).
    assert(throwsInvalidArgument(
        [&] { plot.setData({1, std::numeric_limits<double>::quiet_NaN()}, {2, 3}); }));
    // Check that the program rejects infinity.
    assert(throwsInvalidArgument(
        [&] { plot.setData({1}, {std::numeric_limits<double>::infinity()}); }));
    assert(plot.size() == 4); // Failed input must preserve existing data.

    // Check that the program rejects a graph that is too small.
    assert(throwsInvalidArgument([&] { plot.saveSvg("bad.svg", 100, 100); }));
    // The special characters must appear as XML entities rather than malformed SVG markup.
    plot.setTitle("Revenue & Profit <2026>");

    // Set the horizontal axis label.
    plot.setXLabel("Time");

    // Set the vertical axis label.
    plot.setYLabel("USD");

    // Give the output graph a filename.
    const std::string output = "test_lineplot.svg";

    // Generate and save the graph.
    plot.saveSvg(output);

    // Open the generated SVG file.
    std::ifstream svg(output);

    // Check whether the file opened successfully.
    assert(svg.good());

    // Read the contents of the SVG file into a string.
    std::string content((std::istreambuf_iterator<char>(svg)), std::istreambuf_iterator<char>());

    // Check that the saved graph contains a line.
    assert(content.find("<polyline") != std::string::npos);

    // Check that special characters in the title were handled correctly.
    assert(content.find("Revenue &amp; Profit &lt;2026&gt;") != std::string::npos);

    // Create a graph containing only one point.
    // A singleton has no connecting segment; constant ranges still need a usable midpoint mapping.
    LinePlot single({4}, {9});

    // Check that one point cannot form a connecting line.
    assert(single.segments().empty());

    // Save the graph containing one point.
    single.saveSvg("test_single.svg");

    // Create a graph where all X and Y values are equal.
    LinePlot flat({2, 2, 2}, {7, 7, 7});

    // Save the graph containing equal values.
    flat.saveSvg("test_flat.svg");

    // Display a success message when all tests pass.
    std::cout << "All LinePlot tests passed.\n";
}
