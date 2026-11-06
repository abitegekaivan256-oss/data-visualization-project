#include "dataviz/ScatterPlot.h"  // Includes the ScatterPlot class declaration
#include "dataviz/AxisScale.h"    // Includes classes used to scale graph coordinates
#include <algorithm>              // Provides minmax_element() for finding minimum and maximum values
#include <cmath>                   // Provides isfinite() for checking valid numbers
#include <iostream>                // Provides cout for displaying output
#include <stdexcept>               // Provides exceptions for handling invalid inputs

namespace dataviz {  // Begins the dataviz namespace

// Constructor that creates a scatter plot using a name and marker
ScatterPlot::ScatterPlot(const std::string& name, char marker)
    : Plot(name), marker_(marker) {  // Initializes the parent Plot class and the marker

    if (marker < 33 || marker > 126)  // Checks whether the marker is a printable ASCII character
        throw std::invalid_argument("Marker must be printable ASCII");  // Reports an error if the marker is invalid
}

// Constructor that creates a scatter plot using existing x and y coordinates
ScatterPlot::ScatterPlot(const std::vector<double>& x, const std::vector<double>& y,
                         const std::string& name, char marker)
    : ScatterPlot(name, marker) {  // Calls the first constructor to initialize the scatter plot

    if (x.empty() || x.size() != y.size())  // Checks whether the data is empty or the coordinate sizes differ
        throw std::invalid_argument("Nonempty, equally sized coordinates required");  // Reports an error for invalid coordinate data

    for (std::size_t i = 0; i < x.size(); ++i) addPoint(x[i], y[i]);  // Adds each x and y coordinate pair to the plot
}

// Function used to set the radius of the plotted points
void ScatterPlot::setMarkerRadius(double radius) {

    if (!std::isfinite(radius) || radius <= 0)  // Checks whether the radius is finite and greater than zero
        throw std::invalid_argument("Marker radius must be positive and finite");  // Reports an error for an invalid radius

    markerRadius_ = radius;  // Stores the valid radius for drawing points
}

// Function used to add a new point to the scatter plot
void ScatterPlot::addPoint(double x, double y) {

    if (!std::isfinite(x) || !std::isfinite(y))  // Checks whether both coordinates are valid finite numbers
        throw std::invalid_argument("Coordinates must be finite");  // Reports an error if either coordinate is invalid

    xValues.push_back(x);  // Adds the x coordinate to the xValues vector
    yValues.push_back(y);  // Adds the y coordinate to the yValues vector
}

// Function that returns the total number of points in the scatter plot
std::size_t ScatterPlot::pointCount() const { return xValues.size(); }  // Returns the number of stored x coordinates

// Function used to draw the scatter plot using the Renderer class
void ScatterPlot::draw(Renderer& renderer) const {

    if (xValues.empty()) throw std::invalid_argument("Empty scatter plot");  // Prevents drawing when no points exist

    const auto xr = std::minmax_element(xValues.begin(), xValues.end());  // Finds the minimum and maximum x values
    const auto yr = std::minmax_element(yValues.begin(), yValues.end());  // Finds the minimum and maximum y values

    const double left = 80, right = renderer.width() - 60;  // Defines the left and right boundaries of the graph
    const double top = 60, bottom = renderer.height() - 80;  // Defines the top and bottom boundaries of the graph

    LinearScale xs(*xr.first, *xr.second, right - left);  // Creates a scale that converts x values into horizontal positions
    LinearScale ys(*yr.first, *yr.second, bottom - top);  // Creates a scale that converts y values into vertical positions

    renderer.drawAxes(left, top, right, bottom);  // Draws the horizontal and vertical graph axes

    renderer.drawNumericTicks(left, top, right, bottom, *xr.first, *xr.second,
                              *yr.first, *yr.second);  // Draws numerical tick marks and values on both axes

    renderer.drawText(left, 30, title, 22);  // Displays the graph title using font size 22
    renderer.drawText(left, bottom + 55, xAxisLabel);  // Displays the label of the horizontal axis
    renderer.drawText(5, 35, yAxisLabel);  // Displays the label of the vertical axis

    for (std::size_t i = 0; i < xValues.size(); ++i)  // Loops through every point in the dataset
        renderer.drawOutlinedPoint(left + xs.scale(xValues[i]), bottom - ys.scale(yValues[i]), markerRadius_, "#2563eb", "#0f172a", 1.25);  // Draws each point at its scaled position with a blue fill, dark outline, and outline width of 1.25
}

// Function used to display a scatter plot using ASCII characters in the terminal
void ScatterPlot::renderAscii(int width, int height) const {

    if (width <= 0 || height <= 0)  // Checks whether the grid dimensions are positive
        throw std::invalid_argument("Grid dimensions must be positive");  // Reports an error if the dimensions are invalid

    if (xValues.empty()) return;  // Stops the function if there are no points to display

    const auto xr = std::minmax_element(xValues.begin(), xValues.end());  // Finds the minimum and maximum x coordinates
    const auto yr = std::minmax_element(yValues.begin(), yValues.end());  // Finds the minimum and maximum y coordinates

    LinearScale xs(*xr.first, *xr.second, width);  // Converts x coordinates into positions within the ASCII grid
    LinearScale ys(*yr.first, *yr.second, height);  // Converts y coordinates into positions within the ASCII grid

    std::vector<std::string> grid(height + 1, std::string(width + 1, ' '));  // Creates a two-dimensional grid filled with spaces

    for (std::size_t i = 0; i < xValues.size(); ++i)  // Loops through all the points to place them on the grid
        grid[height - static_cast<int>(ys.scale(yValues[i]))]  // Calculates the row position and reverses the vertical direction
            [static_cast<int>(xs.scale(xValues[i]))] = marker_;  // Calculates the column position and places the marker character

    for (const auto& row : grid) std::cout << row << '\n';  // Prints every row of the ASCII scatter plot
}

}  // Ends the dataviz namespace