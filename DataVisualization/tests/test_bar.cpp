// assert stops a test when an expected condition is false; CMake keeps these checks enabled.
#include <cassert>
// ============================================================================
// COMPONENT TEST
// MODULE: BAR PLOT
// ASSIGNED TO: JEFF
//
// The checks below exercise the integrated module.
// Do not place the production implementation in this file.
// STATUS: Implemented tests; assertions and explicit error returns determine success.
// ============================================================================

// Project headers expose the production classes exercised by this program.
#include "dataviz/BarPlot.h"

// Check stored bar values and exercise ASCII rendering. No command-line input is needed.
// Assertions report incorrect storage; rendering errors propagate as exceptions.
int main() {
    // 1. Test BarPlot Inheritance
    // Construct a derived plot, append known values and exercise its terminal representation.
    BarPlot regionalSales("Q3 Regional Revenue");
    regionalSales.addBar("North", 150.0);
    regionalSales.addBar("South", 95.0);
    regionalSales.addBar("East", 210.0);
    regionalSales.renderAscii();

    // Check data storage independently of the printed bar lengths.
    assert(regionalSales.getValues().size() == 3);
    assert(regionalSales.getValues()[2] == 210.0);
    return 0;
}