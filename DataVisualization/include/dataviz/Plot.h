// Include this shared interface only once per translation unit.
#pragma once
// string stores the title and axis-label text; Renderer declares the drawing service used by render.
#include <string>
#include "dataviz/Renderer.h"

// Common metadata and rendering contract for all plots.
class Plot {
    // Protected metadata is shared with derived plot implementations. Ordinary callers
    // use the public setters/getters instead of writing these fields directly.
  protected:
    std::string title;
    std::string xAxisLabel = "X";
    std::string yAxisLabel = "Y";
    // Public operations form the common interface used by examples and application code.
  public:
    // Copy the initial title without changing the caller's string. This constructor
    // initializes the base part of a derived object; Plot itself remains abstract.
    explicit Plot(const std::string &name = "Plot") : title(name) {
    }
    // A virtual destructor permits correct destruction through a base-class pointer.
    // Default cleanup is sufficient because string members manage their own memory.
    virtual ~Plot() = default;
    // Draw into an existing renderer without modifying this plot. The pure virtual
    // declaration is abstraction: each concrete plot must supply its own implementation.
    virtual void render(dataviz::Renderer &) const = 0;
    // Compatibility hook. Data export requires a derived override.
    virtual void exportData() const {
    }
    // Copy caller-provided metadata into the one shared state used by all plot types.
    // These functions do not render or export a file, and they do not validate text length.
    void setTitle(const std::string &value) {
        title = value;
    }
    void setXLabel(const std::string &value) {
        xAxisLabel = value;
    }
    void setYLabel(const std::string &value) {
        yAxisLabel = value;
    }
    // Convenience operation: update both labels through the same individual setters.
    void setAxisLabels(const std::string &x, const std::string &y) {
        setXLabel(x);
        setYLabel(y);
    }
    // Return string copies so callers can inspect labels without modifying stored state.
    // The const qualification promises not to change this plot while reading metadata.
    std::string getTitle() const {
        return title;
    }
    std::string getXAxisLabel() const {
        return xAxisLabel;
    }
    std::string getYAxisLabel() const {
        return yAxisLabel;
    }
};
// This alias makes the existing global Plot usable as dataviz::Plot. It is another
// name for the same type, not a second class or an additional inheritance relationship.
namespace dataviz {
using Plot = ::Plot;
}
