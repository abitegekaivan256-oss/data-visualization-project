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
#ifndef DATAVIZ_IMAGE_EXPORTER_H
#define DATAVIZ_IMAGE_EXPORTER_H

#include <string>

namespace dataviz {

class Renderer;

class ExportStrategy {
public:
    virtual ~ExportStrategy() = default;

    virtual bool exportPlot(
        const Renderer& renderer,
        const std::string& filename
    ) = 0;
};

class SvgImageExporter : public ExportStrategy {
private:
    std::string lastError_;

protected:
    bool preparePath(const std::string& filename);

public:
    bool exportPlot(
        const Renderer& renderer,
        const std::string& filename
    ) override;

    const std::string& lastError() const;
};

class ImageExporter {
public:
    static bool exportSVG(
        const Renderer& renderer,
        const std::string& filename
    );
};

} // namespace dataviz

#endif