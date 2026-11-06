// Project headers expose the production classes exercised by this program.
#include "dataviz/DataPreprocessor.h"
#include "dataviz/Statistics.h"
#include "dataviz/ScatterPlot.h"
#include "dataviz/BarPlot.h"
#include "dataviz/LinePlot.hpp"
#include "dataviz/Labels.h"
#include "dataviz/ImageExporter.h"
// assert stops a test when an expected condition is false; CMake keeps these checks enabled.
#include <cassert>
// File streams create CSV fixtures and read the SVG files produced by tests.
#include <fstream>
// Stream iterators read an entire SVG file into a string for content checks.
#include <iterator>
// Follow CSV loading, paired-row filtering, statistics, all plot types and SVG export.
// No arguments are required; assertions check cross-module behavior in the CTest working folder.
int main() {
    // Include valid, missing and nonnumeric rows to exercise both preprocessing policies.
    std::ofstream("input.csv") << "x,y\n1,-2\n2,\n3,4\n4,bad\n";
    auto d = dataviz::DataLoader::loadCSV("input.csv");
    // Reject is the default: the first invalid pair must stop extraction.
    bool rejected = false;
    try {
        dataviz::DataPreprocessor::numericPairs(d, 0, 1);
    } catch (const std::invalid_argument &) {
        rejected = true;
    }
    assert(rejected);
    // DropRow keeps only (1,-2) and (3,4), preserving the relationship between X and Y.
    auto xy = dataviz::DataPreprocessor::numericPairs(d, 0, 1, dataviz::InvalidPolicy::DropRow);
    assert(xy.first == std::vector<double>({1, 3}));
    assert(xy.second == std::vector<double>({-2, 4}));
    // For Y={-2,4}, mean and median are 1 and population variance is 9.
    auto s = dataviz::Statistics::summarize(xy.second);
    assert(s.count == 2 && s.mean == 1 && s.median == 1 && s.variance == 9);
    ScatterPlot scatter(xy.first, xy.second);
    BarPlot bar("Bars");
    bar.addBar("Negative", -2);
    bar.addBar("Positive", 4);
    dataviz::LinePlot line(xy.first, xy.second);
    // The three objects satisfy one abstract render contract and are not copied into the array.
    Plot *plots[] = {&scatter, &bar, &line};
    // Give each plot a fresh canvas, draw an annotation through Label&, then inspect saved XML.
    for (int i = 0; i < 3; ++i) {
        dataviz::Renderer r;
        plots[i]->render(r);
        dataviz::Annotation a("A & <B>");
        dataviz::Label &label = a;
        label.render(r, 100, 40);
        std::string path = std::to_string(i) + ".svg";
        assert(dataviz::ImageExporter::exportSVG(r, path));
        std::ifstream f(path);
        std::string svg((std::istreambuf_iterator<char>(f)), {});
        assert(svg.find("A &amp; &lt;B&gt;") != std::string::npos);
        assert(svg.find("</svg>") != std::string::npos);
    }
    // A constant data range must map to the midpoint instead of dividing by zero.
    dataviz::LinearScale scale(2, 2, 100);
    assert(scale.scale(2) == 50);
}
