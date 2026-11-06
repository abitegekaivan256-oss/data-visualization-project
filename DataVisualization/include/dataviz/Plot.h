#pragma once
#include <string>
#include "dataviz/Renderer.h"

// Common metadata and rendering contract for all plots.
class Plot {
protected:
    std::string title;
    std::string xAxisLabel = "X";
    std::string yAxisLabel = "Y";
public:
    explicit Plot(const std::string& name = "Plot") : title(name) {}
    virtual ~Plot() = default;
    virtual void render(dataviz::Renderer&) const = 0;
    // Compatibility hook. Data export requires a derived override.
    virtual void exportData() const {}
    void setTitle(const std::string& value) { title = value; }
    void setXLabel(const std::string& value) { xAxisLabel = value; }
    void setYLabel(const std::string& value) { yAxisLabel = value; }
    void setAxisLabels(const std::string& x, const std::string& y) {
        setXLabel(x);
        setYLabel(y);
    }
    std::string getTitle() const { return title; }
    std::string getXAxisLabel() const { return xAxisLabel; }
    std::string getYAxisLabel() const { return yAxisLabel; }
};
namespace dataviz { using Plot = ::Plot; }
