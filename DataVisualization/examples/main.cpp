// Project headers expose the production classes exercised by this program.
#include "dataviz/DataPreprocessor.h"
#include "dataviz/Statistics.h"
#include "dataviz/ScatterPlot.h"
#include "dataviz/BarPlot.h"
#include "dataviz/LinePlot.hpp"
#include "dataviz/Labels.h"
#include "dataviz/ImageExporter.h"
// Console streams print progress, demonstration results and failure messages.
#include <iostream>
// Strings hold filenames, labels and expected SVG text.
#include <string>
// Run the integrated CSV-to-SVG demonstration. argv[1] is a CSV path and argv[2]
// is an EXISTING output directory; this current implementation does not create directories.
// It prints cleaned-row statistics and writes three graphs, returning 1 on a caught error.
int main(int argc, char **argv) {
    try {
        // argc includes the executable name. Check it before reading the two user-supplied arguments.
        if (argc != 3) {
            std::cerr << "Usage: csv_demo input.csv output_directory\n";
            return 1;
        }
        // Load a string table, then extract columns 0 and 1 with the default Reject policy.
        auto data = dataviz::DataLoader::loadCSV(argv[1]);
        auto xy = dataviz::DataPreprocessor::numericPairs(data, 0, 1);
        // Statistics and plots separately consume the clean data; Summary is not an input to the plots.
        auto stats = dataviz::Statistics::summarize(xy.second);
        // Construct three concrete views of the same observations; bar X values become category strings.
        ScatterPlot scatter(xy.first, xy.second, "CSV Scatter");
        BarPlot bars("CSV Bars");
        for (std::size_t i = 0; i < xy.first.size(); ++i)
            bars.addBar(std::to_string(xy.first[i]), xy.second[i]);
        dataviz::LinePlot line(xy.first, xy.second);
        line.setTitle("CSV Line");
        // This non-owning array makes virtual rendering possible without allocating objects manually.
        Plot *plots[] = {&scatter, &bars, &line};
        const char *names[] = {"scatter.svg", "bar.svg", "line.svg"};
        // Normalize only the joining separator. The caller must create the directory beforehand.
        std::string outputDirectory = argv[2];
        if (!outputDirectory.empty() && outputDirectory.back() != '/' &&
            outputDirectory.back() != '\\')
            outputDirectory += '/';
        // Render each plot into its own canvas, add a note in pixel coordinates and export a matching file.
        for (int i = 0; i < 3; ++i) {
            dataviz::Renderer r;
            plots[i]->render(r);
            // This red annotation point is separate from the plotted data observations.
            dataviz::Annotation("CSV observations").render(r, 500, 40);
            // The exporter returns bool; convert failure into an exception handled by the outer catch.
            if (!dataviz::ImageExporter::exportSVG(r, outputDirectory + names[i]))
                throw std::runtime_error("Export failed");
        }
        // Print selected Summary fields after all exports succeed. Count means retained numeric pairs.
        std::cout << "Rows: " << stats.count << " Mean: " << stats.mean
                  << " Median: " << stats.median << " Population variance: " << stats.variance
                  << "\n";
        // Report validation/file errors on stderr and return 1. Normal completion of main returns 0 implicitly.
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
