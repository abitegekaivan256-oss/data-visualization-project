
#include <iostream>
#include <vector>
#include <stdexcept>

#include "dataviz/ScatterPlot.h"
#include "dataviz/Renderer.h"

using namespace std;

int main() {

    cout << "SCATTER PLOT TEST\n";

    // Test 1: Create dataset
    vector<double> x = {1, 2, 3, 4, 5};
    vector<double> y = {2, 4, 6, 8, 10};

    try {
        ScatterPlot plot(x, y, "Scatter Plot");

        cout << "Number of points: "
               << x.size() << endl;

        // Test 2: Draw scatter plot
        dataviz::Renderer renderer(800, 600);

        plot.render(renderer);
        renderer.saveSVG("scatter_demo.svg");

        cout << "Rendering successful!\n";

        // Test 3: Empty dataset
        vector<double> emptyX;
        vector<double> emptyY;

        try {
            ScatterPlot emptyPlot(vector<double>{}, vector<double>{}, string("Empty Scatter Plot"));
            cout << "Empty dataset test failed!\n";
            return 1;
        }
        catch (const invalid_argument&) {
            cout << "Empty dataset test passed!\n";
        }

        // Test 4: Different dataset sizes
        vector<double> x2 = {1, 2, 3};
        vector<double> y2 = {4, 5};

        try {
            ScatterPlot invalidPlot(x2, y2, "Invalid Scatter Plot");
            cout << "Mismatched dataset test failed!\n";
            return 1;
        }
        catch (const invalid_argument&) {
            cout << "Mismatched dataset test passed!\n";
        }

        cout << "All ScatterPlot tests passed!\n";
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

