// Project headers expose the production classes exercised by this program.
#include "dataviz/LinePlot.hpp"
// assert stops a test when an expected condition is false; CMake keeps these checks enabled.
#include <cassert>
// Render a concrete LinePlot through a Plot reference, exercising the shared interface.
// Saving must succeed; assert reports a failure to CTest.
int main() {
    dataviz::LinePlot l({1, 2}, {3, 4});
    // This base reference tests runtime polymorphism; it must select LinePlot::render.
    Plot &p = l;
    dataviz::Renderer r;
    p.render(r);
    assert(r.saveSVG("polymorphic_line.svg"));
}
