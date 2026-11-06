// Project headers expose the production classes exercised by this program.
#include "dataviz/LinePlot.hpp"

// Console streams print progress, demonstration results and failure messages.
#include <iostream>
// Vectors store related observations and expected coordinate sequences.
#include <vector>

// Build a seven-day line example and export it through LinePlot::saveSvg.
// The outer catch prints an error and returns 1 when validation or writing fails.
int main() {
    try {
        // Each (x, y) pair represents one point in sequence.
        const std::vector<double> days = {1, 2, 3, 4, 5, 6, 7};
        const std::vector<double> temperature = {23, 25, 24, 28, 30, 27, 29};

        // Keep input order to connect the seven day/temperature observations.
        dataviz::LinePlot plot(days, temperature);
        plot.setTitle("Temperature Over Seven Days");
        plot.setXLabel("Day");
        plot.setYLabel("Temperature (C)");
        // This invokes the standalone SVG path with a 900 by 520 canvas, not a Renderer object.
        plot.saveSvg("example_lineplot.svg", 900, 520);

        std::cout << "Saved example_lineplot.svg with " << plot.size() << " points and "
                  << plot.segments().size() << " connected segments.\n";
        return 0;
        // Turn an exception into a clear diagnostic and nonzero result for this command-line example.
    } catch (const std::exception &error) {
        std::cerr << "Line plot error: " << error.what() << '\n';
        return 1;
    }
}
