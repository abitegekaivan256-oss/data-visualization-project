// Project headers expose the production classes exercised by this program.
#include "dataviz/BarPlot.h"
#include "dataviz/ScatterPlot.h"
// Demonstrate a single base-pointer render loop for different concrete plot objects.
// Objects live on the stack; the pointer array refers to them without taking ownership.
int main() {
    BarPlot bar("Sales");
    bar.addBar("North", 120);
    ScatterPlot scatter({1, 2}, {3, 4});
    // Pointers refer to existing stack objects. Virtual dispatch chooses the correct plot renderer.
    Plot *plots[] = {&bar, &scatter};
    // Each iteration creates a separate canvas. This example draws in memory and does not export files.
    for (auto *p : plots) {
        dataviz::Renderer r;
        p->render(r);
    }
}
