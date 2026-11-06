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
// ============================================================================

// Declarations plus the complete Renderer definition needed for saveSVG calls.
#include "dataviz/ImageExporter.h"
#include "dataviz/Renderer.h"

// string handles paths/messages; exception lets failures become diagnostics.
#include <string>
#include <exception>

namespace dataviz {

// Validate the output filename. filename is supplied by the caller.
// Return true if its spelling is accepted, otherwise store a useful diagnostic.
// This validates format only; Renderer detects actual open/write failures.
bool SvgImageExporter::preparePath(const std::string &filename) {
    // Avoid attempting an unnamed destination and explain the failure.
    if (filename.empty()) {
        lastError_ = "Filename cannot be empty";
        return false;
    }

    // Check whether filename ends with .svg. The length check makes the
    // substring position valid; the comparison is deliberately case-sensitive.
    if (filename.length() < 5 || filename.substr(filename.length() - 4) != ".svg") {
        lastError_ = "Only SVG files are supported";
        return false;
    }

    return true;
}

// Runtime polymorphism through overriding. This implementation accepts the
// same Renderer/filename contract as ExportStrategy and returns bool, allowing
// calls through a base reference. It owns neither the Renderer nor its data.
bool SvgImageExporter::exportPlot(const Renderer &renderer, const std::string &filename) {
    // Each attempt starts fresh: a successful export should not expose an old
    // failure message left by an earlier attempt on this same object.
    lastError_.clear();

    try {
        // Stop before file output when the name/suffix is unsupported.
        if (!preparePath(filename)) {
            return false;
        }

        // Use Adrian's existing rendering function. Plot geometry is already
        // stored in Renderer; exporting does not calculate data ranges again.
        // Missing parent directories are not created here.
        if (!renderer.saveSVG(filename)) {
            lastError_ = "Failed to save SVG file. Check the output path.";
            return false;
        }

        return true;

    } catch (const std::exception &e) {
        // Translate standard exceptions into this strategy's bool/error contract.
        // Callers can inspect lastError rather than losing the diagnostic.
        lastError_ = e.what();
        return false;
    }
}

// Encapsulation: controlled read-only access to private error state.
// This const getter returns a reference to this object's stored string.
const std::string &SvgImageExporter::lastError() const {
    return lastError_;
}

// Convenient static interface for the rest of the project. The temporary
// strategy delegates the actual save and is destroyed automatically on return.
// Only success/failure survives; callers needing lastError use a named strategy.
bool ImageExporter::exportSVG(const Renderer &renderer, const std::string &filename) {
    SvgImageExporter exporter;
    return exporter.exportPlot(renderer, filename);
}

} // namespace dataviz
