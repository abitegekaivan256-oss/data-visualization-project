#include <cassert>
// ============================================================================
// COMPONENT TEST PLACEHOLDER
// MODULE: BAR PLOT
// ASSIGNED TO: JEFF
//
// Add tests here as the module is implemented.
// Do not place the production implementation in this file.
// STATUS: NOT YET IMPLEMENTED
// ============================================================================

#include "dataviz/BarPlot.h"        

int main() {
    // 1. Test BarPlot Inheritance
    BarPlot regionalSales("Q3 Regional Revenue");
    regionalSales.addBar("North", 150.0);
    regionalSales.addBar("South", 95.0);
    regionalSales.addBar("East", 210.0);
    regionalSales.renderAscii();

    assert(regionalSales.getValues().size() == 3);
    assert(regionalSales.getValues()[2] == 210.0);
    return 0;
}