// Production SVG label interface. The separate terminal teaching programs are
// examples/teaching/labels_include_demo.cpp and labels_src_demo.cpp.
#pragma once // Prevents this header from being included more than once.
// Renderer supplies string and SVG drawing operations used by inline methods.
#include "dataviz/Renderer.h"
namespace dataviz {
// Base class for general text labels in data visualization.
// Encapsulate reusable text with a virtual drawing operation. This class is
// concrete: its default render draws plain text at caller-supplied pixels.
class Label {
    // Class members are private until public: appears. Derived classes read
    // this string through getText rather than changing it directly.
    std::string text_;

  public:
    // Construct with initial text. explicit prevents accidental conversion
    // of an unrelated string expression into a Label object.
    explicit Label(std::string text) : text_(text) {
    }

    // Virtual destruction is safe when a derived label is used via Label*.
    // The string cleans itself up, so the default destructor needs no body.
    virtual ~Label() = default;

    // Return a read-only reference without copying the stored string. The
    // caller must not keep the reference after this Label has been destroyed.
    const std::string &getText() const {
        return text_;
    }

    // Replace the text; no length or empty-string restriction is imposed here.
    void setText(std::string text) {
        text_ = text;
    }

    // Add text to an existing Renderer and return nothing. Coordinates are
    // canvas pixels. Renderer validates them and escapes XML characters.
    // const means this drawing request does not modify the Label object.
    virtual void render(Renderer &r, double x, double y) const {
        r.drawText(x, y, text_);
    }
};
// Derived class for labeling graph axes. Public inheritance reuses Label's
// interface and ordinary text rendering.
// It does not automatically position or rotate axis text. using reuses the
// base constructors instead of duplicating their initialization code.
class AxisLabel : public Label {
  public:
    using Label::Label;
};
// A specialized Label adds a point and nearby explanatory text. A Label&
// referring to an Annotation uses this override through runtime polymorphism.
class Annotation : public Label {
  public:
    // Inherit the base class constructors to initialize the annotation text.
    using Label::Label;
    // Draw a radius-three red point at (x,y), then position the annotation
    // eight pixels right and eight pixels up. override checks the signature
    // against Label::render. Renderer may throw for invalid coordinates.
    void render(Renderer &r, double x, double y) const override {
        r.drawPoint(x, y, 3, "red");
        r.drawText(x + 8, y - 8, getText());
    }
};
}
