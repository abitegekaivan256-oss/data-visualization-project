// Standalone historical labels teaching program, preserved for the group.
// Its global classes print to cout and are different from dataviz::Label,
// AxisLabel and Annotation in Labels.h. In this version Annotation stores a
// label ID association rather than inheriting Label. Do not confuse the two APIs.
// week three display labels
// iostream sends this teaching example's messages to the terminal.
#include <iostream>
// string owns the label names, colors and annotation text.
#include <string>
using namespace std;
// 1. LABEL CLASS (BASE CLASS)
class Label {
  private:
    // Private identity/text metadata is accessed through public operations.
    int id;
    string name;
    string color;

  public:
    // Initialize the supplied identity, visible name and color for this object.
    // These values are stored; this teaching version does not validate them.
    // Constructor
    Label(int i, string n, string c) {
        id = i;
        name = n;
        color = c;
    }

    // Return a copy of the identity without changing the object (const).
    // Getter for ID
    int getId() const {
        return id;
    }

    // Return a copy of the current name; no mutable reference escapes.
    // Getter for name
    string getName() const {
        return name;
    }

    // Public operations provide controlled access to otherwise private fields.
    // This setter accepts any supplied string without extra validation.
    // Setter for name
    void setName(string n) {
        name = n;
    }

    // Store a color name for the teaching object; display does not render color.
    // Setter for color
    void setColor(string c) {
        color = c;
    }

    // A call through Label* can select a derived display implementation.
    // The default implementation prints the current name only.
    // Virtual function for polymorphism
    virtual void display() const {
        cout << "Label: " << name << endl;
    }

    // A derived object can be destroyed safely through a base pointer.
    // The string members release their own storage.
    // Virtual destructor
    virtual ~Label() = default;
};
// 2. AXIS LABEL CLASS (DERIVED CLASS)
// Demonstrates Inheritance

class AxisLabel : public Label {
  private:
    // Derived-only state tells the overridden display which axis it describes.
    string axis;

  public:
    // Constructor
    // Construct the Label base first, then initialize this derived axis field.
    AxisLabel(int i, string n, string c, string a) : Label(i, n, c) {
        axis = a;
    }

    // override makes the compiler check that this matches a virtual base method.
    // getName reads the private base name through its public interface.
    // Function overriding (Polymorphism)
    void display() const override {
        cout << axis << "-Axis Label: " << getName() << endl;
    }
};
// 3. ANNOTATION CLASS
// Demonstrates Encapsulation

class Annotation {
  private:
    // Private identity/text metadata is accessed through public operations.
    int id;
    string text;
    // This integer associates the note with a label; it is not an owning pointer.
    int labelId;

  public:
    // Constructor
    // Store note identity, text and the associated label ID. This constructor
    // does not look up a Label or check whether that ID exists.
    Annotation(int i, string t, int l) {
        id = i;
        text = t;
        labelId = l;
    }

    // Replace the private annotation text through its public interface.
    // Setter
    void setText(string t) {
        text = t;
    }

    // Return the annotation text by value without changing the note.
    // Getter
    string getText() const {
        return text;
    }

    // Print both pieces of information; this example does not draw SVG text.
    // Display annotation
    void display() const {
        cout << "Annotation: " << text << endl;
        cout << "Associated Label ID: " << labelId << endl;
    }
};
// 4. MAIN FUNCTION
// Demonstrates All Three OOP Concepts

// Construct stack objects, demonstrate state changes and dispatch, then exit.
// Returning zero reports normal completion to the operating system.
int main() {

    cout << "===================================" << endl;
    cout << " DATA VISUALIZATION LIBRARY" << endl;
    cout << " LABELS AND ANNOTATIONS MODULE" << endl;
    cout << "===================================" << endl;
    // ENCAPSULATION
    Label title(1, "Student Results", "Blue");

    // Modify private data using a setter
    title.setName("Student Performance");
    // AxisLabel inherits from Label
    AxisLabel x(2, "Time", "Black", "X");
    AxisLabel y(3, "Marks", "Black", "Y");
    Annotation note(101, "Highest mark recorded", 3);
    // POLYMORPHISM
    // Base-class pointers to different objects
    Label *labels[] = {&title, &x, &y};

    cout << "\n--- PLOT LABELS ---" << endl;

    // Each pointer refers to an existing object, so the loop owns/deletes none.
    // Virtual dispatch selects Label::display or AxisLabel::display as needed.
    for (Label *label : labels) {
        label->display();
    }

    cout << "\n--- ANNOTATION ---" << endl;

    note.display();

    cout << "\nProgram executed successfully!" << endl;

    return 0;
}
