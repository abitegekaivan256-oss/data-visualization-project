// Separate struct-template teaching example, compiled as teaching_templatestruct.
// It contrasts public struct members with private state in label_class_template.cpp.
// These types are not the production dataviz Label/AxisLabel/Annotation API.
// cout displays the values and virtual dispatch demonstration.
#include <iostream>
// string owns the label text.
#include <string>
using namespace std;

// A struct makes its members public by default.
template <typename T> struct Label {
    // Public fields permit direct caller changes, as main demonstrates below.
    string text;
    T x, y;

    // The initializer list initializes text and coordinates before the body runs.
    Label(string t, T a, T b) : text(t), x(a), y(b) {
    }

    // Print the current state without modifying it. A derived override can
    // change the presentation when called through a Label<T> pointer.
    virtual void display() const {
        cout << text << " at (" << x << ", " << y << ")\n";
    }

    // Virtual cleanup supports polymorphic use; owned strings clean themselves.
    virtual ~Label() = default;
};

template <typename T> struct AxisLabel : Label<T> {
    // A struct inherits publicly by default; initialize its Label<T> base first.
    AxisLabel(string t, T x, T y) : Label<T>(t, x, y) {
    }

    // Match the const virtual base method, add a prefix and reuse its display.
    void display() const override {
        cout << "Axis Label: ";
        Label<T>::display();
    }
};

template <typename T> struct Annotation : Label<T> {
    // Reuse base initialization for the same compile-time coordinate type.
    Annotation(string t, T x, T y) : Label<T>(t, x, y) {
    }

    // Match the const virtual base method, add a prefix and reuse its display.
    void display() const override {
        cout << "Annotation: ";
        Label<T>::display();
    }
};

// Create int/double objects, change public fields, and dispatch through a base
// pointer to show that templates and virtual methods solve different problems.
int main() {
    Label<int> title("Student Performance", 100, 20);
    AxisLabel<int> xAxis("Time (seconds)", 50, 200);
    AxisLabel<double> yAxis("Voltage (V)", 20.5, 100.5);
    Annotation<int> peak("Maximum Voltage", 80, 60);

    // Public members can be accessed directly in a struct.
    title.text = "Student Results";
    title.x = 120;

    cout << "DATA VISUALIZATION LIBRARY\n";
    cout << "MODULE: LABELS AND ANNOTATIONS (STRUCT VERSION)\n";
    cout << "---------------------------------------------\n";
    title.display();
    xAxis.display();
    yAxis.display();
    peak.display();

    // Non-owning pointer: peak remains a stack object with automatic cleanup.
    Label<int> *ptr = &peak;
    cout << "\nPolymorphism Example:\n";
    ptr->display();
    return 0;
}
