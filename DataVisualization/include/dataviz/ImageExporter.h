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
#ifndef DATAVIZ_IMAGE_EXPORTER_H
#define DATAVIZ_IMAGE_EXPORTER_H

// string stores filenames and the last diagnostic message.
#include <string>

namespace dataviz {

// A forward declaration is sufficient for references in these declarations.
// The implementation includes Renderer.h when it calls its methods.
class Renderer;

// Abstract export contract. A derived strategy decides how to save a drawing;
// only the SVG strategy is implemented in this project.
class ExportStrategy {
  public:
    // A virtual destructor makes destruction through a base pointer safe. No
    // manual cleanup is needed here because the base owns no resources.
    virtual ~ExportStrategy() = default;

    // renderer is read-only drawing content; filename is the destination path.
    // Return true only on successful export. =0 makes this a pure virtual
    // operation, so ExportStrategy itself cannot be instantiated.
    virtual bool exportPlot(const Renderer &renderer, const std::string &filename) = 0;
};

// Public inheritance permits this concrete object to be used through an
// ExportStrategy reference. override asks the compiler to check the virtual signature.
class SvgImageExporter : public ExportStrategy {
  private:
    // Encapsulation: callers read errors through lastError(), not direct writes.
    std::string lastError_;

  protected:
    // Protected helper validates the name/suffix and records a failure reason.
    // It does not create directories or check all filesystem permissions.
    bool preparePath(const std::string &filename);

  public:
    // Clear old errors, validate the path, and ask Renderer to write its SVG.
    // False reports a failed path/write; standard exceptions become diagnostics.
    bool exportPlot(const Renderer &renderer, const std::string &filename) override;

    // Read without copying or exposing mutation. The returned reference is
    // valid only while this exporter exists, and a new export may change it.
    const std::string &lastError() const;
};

// Convenience utility for callers needing only success/failure. No stored
// state or custom constructor/destructor is required for this static entry point.
class ImageExporter {
  public:
    // Delegate to a temporary SvgImageExporter. For detailed errors, create a
    // named SvgImageExporter and read its lastError() instead.
    static bool exportSVG(const Renderer &renderer, const std::string &filename);
};

} // namespace dataviz

#endif