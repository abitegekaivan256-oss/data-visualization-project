// ============================================================================
// DATA VISUALIZATION LIBRARY IN C++
//
// MODULE: IMAGE EXPORT
// ASSIGNED TO: JACKSON + GROUP
//
// YOUR RESPONSIBILITIES:
// 1. Save the rendered plot to the agreed image format.
// 2. Handle output filenames/paths.
// 3. Coordinate with Renderer before changing shared interfaces.
//
// MAIN FILES:
// - include/dataviz/ImageExporter.h
// - src/ImageExporter.cpp
//
// DEPENDENCIES / COORDINATION:
// - Renderer (Adrian + Group)
//
// TEAM RULES:
// - Work mainly in your allocated files.
// - Pull the latest repository before starting work.
// - Discuss changes to shared interfaces before editing them.
// - Compile/test your component before committing.
// - Use a clear commit message describing what changed.
//
// IMPLEMENTATION STATUS: NOT YET IMPLEMENTED
// ============================================================================


#include "dataviz/ImageExporter.h"
#include "dataviz/Renderer.h"

#include <string>
#include <exception>

namespace dataviz {

// Validate the output filename.
bool SvgImageExporter::preparePath(
    const std::string& filename
) {
    if (filename.empty()) {
        lastError_ = "Filename cannot be empty";
        return false;
    }

    // Check whether filename ends with .svg
    if (filename.length() < 5 ||
        filename.substr(filename.length() - 4) != ".svg") {
        lastError_ = "Only SVG files are supported";
        return false;
    }

    return true;
}

// Runtime polymorphism through overriding.
bool SvgImageExporter::exportPlot(
    const Renderer& renderer,
    const std::string& filename
) {
    lastError_.clear();

    try {
        if (!preparePath(filename)) {
            return false;
        }

        // Use Adrian's existing rendering function.
        if (!renderer.saveSVG(filename)) {
            lastError_ = "Failed to save SVG file. Check the output path.";
            return false;
        }

        return true;

    } catch (const std::exception& e) {
        lastError_ = e.what();
        return false;
    }
}

// Encapsulation: controlled access to private data.
const std::string& SvgImageExporter::lastError() const {
    return lastError_;
}

// Convenient interface for the rest of the project.
bool ImageExporter::exportSVG(
    const Renderer& renderer,
    const std::string& filename
) {
    SvgImageExporter exporter;
    return exporter.exportPlot(renderer, filename);
}

} // namespace dataviz
