/* #pragma once
#include "dataviz/Renderer.h"
namespace dataviz
{
class Label
{
std::string text_;
public:
explicit Label(std::string text):text_(text){}
virtual ~Label()=default;
const std::string& getText()const
{
    return text_;
}
void setText(std::string text)
{
    text_=text;
}
virtual void render(Renderer& r,double x,double y)const
{
    r.drawText(x,y,text_);
}
};
class AxisLabel:public Label 
{
    public:using Label::Label;
};
class Annotation:public Label
{
public:using Label::Label;
void render(Renderer& r,double x,double y)const override{r.drawPoint(x,y,3,"red");r.drawText(x+8,y-8,getText());}
};
}
 */
#pragma once  // Prevents the header file from being included more than once

#include "dataviz/Renderer.h"  // Includes the Renderer class used for drawing

namespace dataviz
{

// BASE CLASS: Label
// Represents a general text label used in data visualization
class Label
{
    // Private data member: stores the label text
    std::string text_;

public:
    // Constructor: initializes the label with text
    explicit Label(std::string text) : text_(text) {}

    // Virtual destructor: allows safe destruction of derived objects
    virtual ~Label() = default;

    // Getter: returns the text stored in the label
    const std::string& getText() const
    {
        return text_;
    }

    // Setter: updates the label text
    void setText(std::string text)
    {
        text_ = text;
    }

    // Virtual function: draws the label at position (x, y)
    // Can be overridden by derived classes (polymorphism)
    virtual void render(Renderer& r, double x, double y) const
    {
        r.drawText(x, y, text_);
    }
};


// DERIVED CLASS: AxisLabel
// Inherits from Label and is used for labeling graph axes
class AxisLabel : public Label
{
public:
    // Inherits the constructor from the Label class
    using Label::Label;
};


// DERIVED CLASS: Annotation
// Inherits from Label and adds a marked point with descriptive text
class Annotation : public Label
{
public:
    // Inherits the constructor from the Label class
    using Label::Label;

    // Overrides the render() function from the base class
    void render(Renderer& r, double x, double y) const override
    {
        // Draws a red point at the specified coordinates
        r.drawPoint(x, y, 3, "red");

        // Draws annotation text slightly away from the point
        r.drawText(x + 8, y - 8, getText());
    }
};

} // End of dataviz namespace