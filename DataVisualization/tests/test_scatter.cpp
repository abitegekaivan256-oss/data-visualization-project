
// Console streams print progress, demonstration results and failure messages.
#include <iostream>
// Vectors store related observations and expected coordinate sequences.
#include <vector>
// Standard exception types let tests distinguish validation failures.
#include <stdexcept>

// Project headers expose the production classes exercised by this program.
#include "dataviz/ScatterPlot.h"
#include "dataviz/Renderer.h"

using namespace std;

// Render a valid scatter dataset and require exceptions for empty/mismatched input.
// Explicit nonzero returns report unexpected acceptance or another exception to CTest.
int main() {

    cout << "SCATTER PLOT TEST\n";

    // Test 1: Create dataset
    // Each x[i] pairs with y[i]; the sample has finite, equally sized vectors.
    vector<double> x = {1, 2, 3, 4, 5};
    vector<double> y = {2, 4, 6, 8, 10};

    try {
        ScatterPlot plot(x, y, "Scatter Plot");

        cout << "Number of points: " << x.size() << endl;

        // Test 2: Draw scatter plot
        dataviz::Renderer renderer(800, 600);

        plot.render(renderer);
        // This smoke test requests saving; stronger SVG-content assertions live in plot_behavior.
        renderer.saveSVG("scatter_demo.svg");

        cout << "Rendering successful!\n";

        // Test 3: Empty dataset
        vector<double> emptyX;
        vector<double> emptyY;

        // An accepted empty dataset would be a failure, so the normal path explicitly returns 1.
        try {
            ScatterPlot emptyPlot(vector<double>{}, vector<double>{}, string("Empty Scatter Plot"));
            cout << "Empty dataset test failed!\n";
            return 1;
        } catch (const invalid_argument &) {
            cout << "Empty dataset test passed!\n";
        }

        // Test 4: Different dataset sizes
        // Different vector lengths cannot describe complete X/Y observation pairs.
        vector<double> x2 = {1, 2, 3};
        vector<double> y2 = {4, 5};

        try {
            ScatterPlot invalidPlot(x2, y2, "Invalid Scatter Plot");
            cout << "Mismatched dataset test failed!\n";
            return 1;
        } catch (const invalid_argument &) {
            cout << "Mismatched dataset test passed!\n";
        }

        cout << "All ScatterPlot tests passed!\n";
        // Unexpected errors fail the executable instead of printing a misleading passing result.
    } catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
