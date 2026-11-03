#include "dataviz/LinePlot.hpp"

#include <iostream>
#include <vector>

int main() {
    try {
        // Each (x, y) pair represents one point in sequence.
        const std::vector<double> days = {1, 2, 3, 4, 5, 6, 7};
        const std::vector<double> temperature = {23, 25, 24, 28, 30, 27, 29};

        dataviz::LinePlot plot(days, temperature);
        plot.setTitle("Temperature Over Seven Days");
        plot.setXLabel("Day");
        plot.setYLabel("Temperature (C)");
        plot.saveSvg("example_lineplot.svg", 900, 520);

        std::cout << "Saved example_lineplot.svg with " << plot.size()
                  << " points and " << plot.segments().size() << " connected segments.\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Line plot error: " << error.what() << '\n';
        return 1;
    }
}
