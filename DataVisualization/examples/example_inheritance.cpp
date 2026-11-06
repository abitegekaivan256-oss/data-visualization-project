
// Project headers expose the production classes exercised by this program.
#include "dataviz/BarPlot.h"
#include "dataviz/ScatterPlot.h"

// Show inherited metadata methods together with bar/scatter ASCII rendering.
// Each derived plot owns its own data while reusing the common Plot interface.
int main() {
    // 1. Test BarPlot Inheritance
    BarPlot regionalSales("Q3 Regional Revenue");
    // This metadata operation is inherited from Plot rather than reimplemented by BarPlot.
    regionalSales.setAxisLabels("Region", "Revenue ($k)");
    regionalSales.addBar("North", 150.0);
    regionalSales.addBar("South", 95.0);
    regionalSales.addBar("East", 210.0);
    regionalSales.renderAscii();

    // 2. Test ScatterPlot Inheritance
    // The second constructor argument chooses the ASCII marker; points are added individually.
    ScatterPlot distribution("Height vs Weight", 'O');
    distribution.setAxisLabels("Height (cm)", "Weight (kg)");
    distribution.addPoint(160, 55);
    distribution.addPoint(175, 70);
    distribution.addPoint(180, 85);
    // The requested grid dimensions control the terminal layout, not SVG canvas size.
    distribution.renderAscii(30, 8);

    return 0;
}