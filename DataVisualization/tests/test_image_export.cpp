

// Project headers expose the production classes exercised by this program.
#include "dataviz/ImageExporter.h"
#include "dataviz/Renderer.h"

// Console streams print progress, demonstration results and failure messages.
#include <iostream>
// File streams create CSV fixtures and read the SVG files produced by tests.
#include <fstream>
// Strings hold filenames, labels and expected SVG text.
#include <string>
// Stream iterators read an entire SVG file into a string for content checks.
#include <iterator>
// Compile-time type traits verify the exporter inheritance relationship.
#include <type_traits>

using namespace dataviz;

// Exercise the SVG strategy through its abstract base and verify output/error reporting.
// Return 1 for a rejected expectation and 0 after all export checks succeed.
int main() {
    // INHERITANCE
    // This relationship is checked during compilation rather than at runtime.
    static_assert(std::is_base_of<ExportStrategy, SvgImageExporter>::value,
                  "Inheritance test failed");

    // Create a plot.
    // Populate a real renderer; the exporter only saves these existing SVG elements.
    Renderer renderer(800, 600);

    renderer.clear("white");
    renderer.drawAxes(80, 80, 720, 520);
    renderer.drawText(250, 45, "Image Export Test", 22);

    renderer.drawPoint(150, 420, 6, "red");
    renderer.drawPoint(300, 320, 6, "blue");
    renderer.drawPoint(450, 220, 6, "green");

    // POLYMORPHISM
    SvgImageExporter svgExporter;
    // A base reference invokes the derived exportPlot override at runtime.
    ExportStrategy &exporter = svgExporter;

    // Save directly in the current folder.
    std::string filename = "jackson_plot.svg";

    bool success = exporter.exportPlot(renderer, filename);

    if (!success) {
        std::cerr << svgExporter.lastError() << '\n';
        return 1;
    }

    // Verify file creation.
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Exported file not found\n";
        return 1;
    }

    // Read every written byte and check opening/closing SVG tags, not a screenshot.
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    if (content.find("<svg") == std::string::npos || content.find("</svg>") == std::string::npos) {
        std::cerr << "Invalid SVG output\n";
        return 1;
    }

    // ENCAPSULATION: test error reporting.
    // Invalid names must fail and keep diagnostic text inside SvgImageExporter.
    if (exporter.exportPlot(renderer, "")) {
        std::cerr << "Empty filename was accepted\n";
        return 1;
    }

    if (svgExporter.lastError().empty()) {
        std::cerr << "Error message was not stored\n";
        return 1;
    }

    // Reject unsupported format.
    if (exporter.exportPlot(renderer, "plot.png")) {
        std::cerr << "PNG was incorrectly accepted\n";
        return 1;
    }

    // Test the convenience interface.
    // The convenience static interface should also save the already-rendered canvas.
    if (!ImageExporter::exportSVG(renderer, "jackson_second_plot.svg")) {
        std::cerr << "Convenience export failed\n";
        return 1;
    }

    std::cout << "Inheritance test passed\n";
    std::cout << "Polymorphism test passed\n";
    std::cout << "Encapsulation test passed\n";
    std::cout << "SVG export test passed\n";
    std::cout << "Error handling tests passed\n";
    std::cout << "All tests passed!\n";

    return 0;
}
