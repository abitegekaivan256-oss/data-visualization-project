#include "dataviz/BarPlot.h"

int main() {
    BarPlot salesPlot("Q3 Regional Sales");
    salesPlot.addBar("North", 150.5);
    salesPlot.addBar("South", 85.0);
    salesPlot.addBar("East", 200.0);
    salesPlot.addBar("West", 120.0);

    salesPlot.renderAscii();
    return 0;
}
