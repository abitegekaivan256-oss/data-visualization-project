#include "dataviz/Renderer.h"
#include <iostream>
#include <vector>

int main() {
    dataviz::Renderer renderer(800, 600);
    renderer.drawAxes(80, 60, 740, 520);
    renderer.drawText(270, 35, "Data Visualization Demo", 22);
    renderer.drawText(350, 570, "X Axis", 16);
    renderer.drawText(15, 45, "Y Axis", 16);
    renderer.drawScatter({{120, 440}, {230, 350}, {340, 400}, {450, 220}}, "red");
    renderer.drawPolyline({{120, 440}, {230, 350}, {340, 400}, {450, 220}}, "blue");
    renderer.drawBars({550, 630, 710}, {100, 180, 130}, 520, 40, "green");
    if (!renderer.saveSVG("renderer_demo.svg")) {
        std::cerr << "Failed to save SVG\n";
        return 1;
    }
    std::cout << "Created renderer_demo.svg\n";
}