
#ifndef DATAVIZ_LINEPLOT_HPP
#define DATAVIZ_LINEPLOT_HPP

// Include standard C++ libraries needed by this header.
#include <cstddef>  // Provides std::size_t.
#include <string>   // Provides std::string.
#include <vector>   // Provides std::vector.

// Include the shared Point structure used by LinePlot and Renderer.
#include "dataviz/Point.hpp"

// Groups all classes and structures belonging to our data visualization library.
namespace dataviz {

// Represents a line connecting two points on a graph.
struct LineSegment {
    Point start;  // Starting point of the line.
    Point end;    // Ending point of the line.
};

// Represents a line plot that stores data and generates an SVG graph.
class LinePlot {
public:

    // Default constructor creates an empty line plot.
    LinePlot() = default;

    // Constructor that creates a line plot using X and Y coordinate values.
    LinePlot(const std::vector<double>& x,
             const std::vector<double>& y);

    // Checks and stores the X and Y coordinate values.
    // Both vectors must contain the same number of values.
    void setData(const std::vector<double>& x,
                 const std::vector<double>& y);

    // Sets the title displayed at the top of the graph.
    void setTitle(const std::string& title);

    // Sets the label displayed along the horizontal axis.
    void setXLabel(const std::string& label);

    // Sets the label displayed along the vertical axis.
    void setYLabel(const std::string& label);

    // Returns the number of data points stored in the line plot.
    // noexcept means this function is not expected to throw exceptions.
    std::size_t size() const noexcept;

    // Creates and returns line segments connecting consecutive data points.
    std::vector<LineSegment> segments() const;

    // Generates and saves the line graph as an SVG file.
    // The default graph dimensions are 800 pixels wide and 500 pixels high.
    void saveSvg(const std::string& filename,
                 unsigned width = 800,
                 unsigned height = 500) const;

private:

    // Stores the X-coordinate values of the data points.
    std::vector<double> x_values_;

    // Stores the Y-coordinate values of the data points.
    std::vector<double> y_values_;

    // Stores the graph title. A default title is provided.
    std::string title_ = "Line Plot";

    // Stores the horizontal axis label.
    std::string x_label_ = "X";

    // Stores the vertical axis label.
    std::string y_label_ = "Y";
    
};

} // End of the dataviz namespace.

// Prevents this header file from being included more than once.
#endif // DATAVIZ_LINEPLOT_HPP