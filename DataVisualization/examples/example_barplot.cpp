// Project headers expose the production classes exercised by this program.
#include "dataviz/BarPlot.h"

// Create category/value pairs and show a bar plot in the terminal.
// No file is exported here: renderAscii writes directly to standard output.
int main() {
    // Store four category/value observations in one concrete plot.
    BarPlot salesPlot("Q3 Regional Sales");
    salesPlot.addBar("North", 150.5);
    salesPlot.addBar("South", 85.0);
    salesPlot.addBar("East", 200.0);
    salesPlot.addBar("West", 120.0);

    // Turn the stored values into terminal bars; the default output is standard cout.
    salesPlot.renderAscii();
    return 0;
}
