#ifndef DATAVIZ_LINEPLOT_HPP
#define DATAVIZ_LINEPLOT_HPP

#include <cstddef>
#include <string>
#include <vector>

namespace dataviz {

struct Point {
    double x;
    double y;
};

struct LineSegment {
    Point start;
    Point end;
};

// Standalone component until the team defines Plot/AxisScale/Renderer interfaces.
class LinePlot {
public:
    LinePlot() = default;
    LinePlot(const std::vector<double>& x, const std::vector<double>& y);

    // Throws std::invalid_argument on mismatched sizes or non-finite values.
    void setData(const std::vector<double>& x, const std::vector<double>& y);
    void setTitle(const std::string& title);
    void setXLabel(const std::string& label);
    void setYLabel(const std::string& label);

    std::size_t size() const noexcept;
    std::vector<LineSegment> segments() const;
    // Saves a genuine SVG line plot; throws std::runtime_error on file errors.
    void saveSvg(const std::string& filename, unsigned width = 800,
                 unsigned height = 500) const;

private:
    std::vector<double> x_values_;
    std::vector<double> y_values_;
    std::string title_ = "Line Plot";
    std::string x_label_ = "X";
    std::string y_label_ = "Y";
};

} // namespace dataviz
#endif
