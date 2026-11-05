
#ifndef DATAVIZ_LINEPLOT_HPP
#define DATAVIZ_LINEPLOT_HPP

#include "dataviz/Plot.h"
#include <cstddef>
#include <string>
#include <vector>

namespace dataviz {



struct LineSegment {
    Point start;
    Point end;
};

// Line graph using shared Plot metadata.
class LinePlot:public Plot {
public:
    LinePlot() : Plot("Line Plot") {}
    void render(Renderer&)const override;

    LinePlot(const std::vector<double>& x,
             const std::vector<double>& y);

    // Validates and stores X and Y values.
    void setData(const std::vector<double>& x,
                 const std::vector<double>& y);





    std::size_t size() const noexcept;

    std::vector<LineSegment> segments() const;

    // Generates an SVG line graph.
    void saveSvg(const std::string& filename,
                 unsigned width = 800,
                 unsigned height = 500) const;

private:
    std::vector<double> x_values_;
    std::vector<double> y_values_;




};

} // namespace dataviz

#endif
