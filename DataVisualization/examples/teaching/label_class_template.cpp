// Standalone template/class teaching program, compiled as teaching_template.
// These Label<T> types print coordinates; they are not production SVG Label types.
// Terminal output demonstrates which implementation is selected.
#include <iostream>
// string owns the visible text for each label object.
#include <string>
using namespace std;

// BASE CLASS: Demonstrates templates and encapsulation
// T is the coordinate type chosen at compile time (int or double below).
template <typename T> class Label {
  private:
    // Private members are changed only through constructor/setter operations.
    string text;
    T x, y;

  public:
    // Receive visible text and two coordinates, then initialize object state.
    // Constructor
    Label(string t, T a, T b) {
        text = t;
        x = a;
        y = b;
    }

    // Return a copy of the stored text. This example getter is not const.
    // Getter
    string getText() {
        return text;
    }

    // Replace private text through a public member function.
    // Setter
    void setText(string t) {
        text = t;
    }

    // Runtime polymorphism is separate from the compile-time template choice:
    // a Label<T>* can select the derived display override for the same T.
    // Virtual function for polymorphism
    virtual void display() {
        cout << text << " at (" << x << ", " << y << ")" << endl;
    }

    // Virtual destruction is safe through a base pointer; strings clean themselves.
    virtual ~Label() {
    }
};

// DERIVED CLASS 1: Axis labels
template <typename T> class AxisLabel : public Label<T> {
  public:
    // Initialize the templated base using the same coordinate type T.
    AxisLabel(string t, T x, T y) : Label<T>(t, x, y) {
    }

    // Function overriding
    void display() override {
        cout << "Axis Label: ";
        // Qualify the base call to reuse coordinate printing after the prefix.
        Label<T>::display();
    }
};

// DERIVED CLASS 2: Annotations
template <typename T> class Annotation : public Label<T> {
  public:
    // Reuse the base constructor rather than duplicating its private state.
    Annotation(string t, T x, T y) : Label<T>(t, x, y) {
    }

    void display() override {
        cout << "Annotation: ";
        // Qualify the base call to reuse coordinate printing after the prefix.
        Label<T>::display();
    }
};

// Exercise integer and double instantiations, then demonstrate virtual dispatch.
int main() {

    // Creating objects using templates
    Label<int> title("Student Performance", 100, 20);

    AxisLabel<int> xAxis("Time (seconds)", 50, 200);

    AxisLabel<double> yAxis("Voltage (V)", 20.5, 100.5);

    Annotation<int> peak("Maximum Voltage", 80, 60);

    cout << "DATA VISUALIZATION LIBRARY" << endl;
    cout << "MODULE: LABELS AND ANNOTATIONS" << endl;
    cout << "----------------------------" << endl;

    // Encapsulation: Using setter and getter
    title.setText("Student Results");
    cout << "Title: " << title.getText() << endl;

    // Displaying different label types
    title.display();
    xAxis.display();
    yAxis.display();
    peak.display();

    // Polymorphism: Base pointer to derived object
    // The pointer is non-owning and points to an existing Annotation<int>.
    Label<int> *ptr = &peak;

    cout << "\nPolymorphism Example:" << endl;
    ptr->display();

    return 0;
}