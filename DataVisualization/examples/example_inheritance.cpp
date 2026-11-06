
#include "dataviz/BarPlot.h"        
#include "dataviz/ScatterPlot.h"

int main() {
    // 1. Test BarPlot Inheritance
    BarPlot regionalSales("Q3 Regional Revenue");
    regionalSales.setAxisLabels("Region", "Revenue ($k)");
    regionalSales.addBar("North", 150.0);
    regionalSales.addBar("South", 95.0);
    regionalSales.addBar("East", 210.0);
    regionalSales.renderAscii();

    // 2. Test ScatterPlot Inheritance
    ScatterPlot distribution("Height vs Weight", 'O');
    distribution.setAxisLabels("Height (cm)", "Weight (kg)");
    distribution.addPoint(160, 55);
    distribution.addPoint(175, 70);
    distribution.addPoint(180, 85);
    distribution.renderAscii(30, 8);

    return 0;
}