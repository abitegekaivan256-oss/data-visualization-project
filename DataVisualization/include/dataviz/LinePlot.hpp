
#ifndef DATAVIZ_LINEPLOT_HPP
#define DATAVIZ_LINEPLOT_HPP

// Plot provides inherited metadata and the shared Point/Renderer types.
// cstddef names size_t; string stores filenames/text; vector owns coordinates and returned segments.
#include "dataviz/Plot.h"
#include <cstddef>
#include <string>
#include <vector>

namespace dataviz {

// A simple public value type: each segment stores two data-coordinate points.
// It does not own a renderer or perform scaling by itself.
struct LineSegment {
    Point start;
    Point end;
};

// Line graph using shared Plot metadata.
// Public inheritance lets an application render a LinePlot through Plot*.
// The metadata lives only in Plot; this class adds its coordinate series and line behavior.
class LinePlot : public Plot {
  public:
    // Default construction creates an empty series with the inherited title.
    // Containers need no custom destructor, and Plot's destructor is already virtual.
    LinePlot() : Plot("Line Plot") {
    }
    // Draw into the supplied canvas through the shared Plot contract; reject empty data.
    void render(Renderer &) const override;

    // Construct from paired values by calling setData; invalid sizes/numbers throw invalid_argument.
    LinePlot(const std::vector<double> &x, const std::vector<double> &y);

    // Validates and stores X and Y values.
    // Equal empty vectors are allowed as stored data, but rendering/export rejects emptiness.
    // Validation occurs before assignment, preserving the old series for validation failures.
    void setData(const std::vector<double> &x, const std::vector<double> &y);

    // Return the number of observations without changing state or throwing an exception.
    std::size_t size() const noexcept;

    // Return consecutive pairs in caller-supplied order. Fewer than two points yield no segments.
    std::vector<LineSegment> segments() const;

    // Generates an SVG line graph.
    // Standalone SVG export retains its own grid/tick layout and uses shared metadata.
    // Reject empty data or a canvas smaller than 200x160; throw runtime_error for file errors.
    void saveSvg(const std::string &filename, unsigned width = 800, unsigned height = 500) const;

    // Encapsulated coordinate vectors own their storage. Matching positions form one point;
    // no sorting is performed here because input order defines the connected path.
  private:
    std::vector<double> x_values_;
    std::vector<double> y_values_;
};

} // namespace dataviz

#endif
