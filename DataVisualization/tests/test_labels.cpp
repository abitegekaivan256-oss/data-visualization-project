// Project headers expose the production classes exercised by this program.
#include "dataviz/Labels.h"
// assert stops a test when an expected condition is false; CMake keeps these checks enabled.
#include <cassert>
// File streams create CSV fixtures and read the SVG files produced by tests.
#include <fstream>
// Stream iterators read an entire SVG file into a string for content checks.
#include <iterator>
// Check text mutation, virtual annotation rendering and XML escaping in one SVG.
// The annotation stays a Label through a base reference, but its override draws the point.
int main() {
    // Change the annotation text before drawing, so the getter and rendering share the new value.
    dataviz::Renderer r;
    dataviz::Annotation a("old");
    a.setText("<&>");
    // Calling a virtual method through Label& must still use Annotation::render.
    dataviz::Label &l = a;
    l.render(r, 50, 50);
    assert(a.getText() == "<&>");
    assert(r.saveSVG("labels.svg"));
    // SVG stores escaped XML entities, while getText returns the original human text.
    std::ifstream f("labels.svg");
    std::string s((std::istreambuf_iterator<char>(f)), {});
    assert(s.find("&lt;&amp;&gt;") != s.npos && s.find("<circle") != s.npos);
}
