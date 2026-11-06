// Project headers expose the production classes exercised by this program.
#include "dataviz/Renderer.h"
// Console streams print progress, demonstration results and failure messages.
#include <iostream>
// Vectors store related observations and expected coordinate sequences.
#include <vector>

// Smoke-test the drawing primitives on a canvas and write renderer_demo.svg.
// This checks file-write success, not every pixel or primitive attribute; failure returns 1.
int main() {
    // Canvas coordinates are pixels, not unscaled dataset values.
    dataviz::Renderer renderer(800, 600);
    renderer.drawAxes(80, 60, 740, 520);
    renderer.drawText(270, 35, "Data Visualization Demo", 22);
    renderer.drawText(350, 570, "X Axis", 16);
    renderer.drawText(15, 45, "Y Axis", 16);
    // Reuse drawing primitives for points, a connected sequence and bars on one canvas.
    renderer.drawScatter({{120, 440}, {230, 350}, {340, 400}, {450, 220}}, "red");
    renderer.drawPolyline({{120, 440}, {230, 350}, {340, 400}, {450, 220}}, "blue");
    renderer.drawBars({550, 630, 710}, {100, 180, 130}, 520, 40, "green");
    // Saving returns a boolean; translate failure into a nonzero process exit for CTest.
    if (!renderer.saveSVG("renderer_demo.svg")) {
        std::cerr << "Failed to save SVG\n";
        return 1;
    }
    std::cout << "Created renderer_demo.svg\n";
}