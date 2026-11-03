#include <iostream>
#include <string>
using namespace std;

// A struct makes its members public by default.
template <typename T>
struct Label {
    string text;
    T x, y;

    Label(string t, T a, T b) : text(t), x(a), y(b) {}

    virtual void display() const {
        cout << text << " at (" << x << ", " << y << ")\n";
    }

    virtual ~Label() = default;
};

template <typename T>
struct AxisLabel : Label<T> {
    AxisLabel(string t, T x, T y) : Label<T>(t, x, y) {}

    void display() const override {
        cout << "Axis Label: ";
        Label<T>::display();
    }
};

template <typename T>
struct Annotation : Label<T> {
    Annotation(string t, T x, T y) : Label<T>(t, x, y) {}

    void display() const override {
        cout << "Annotation: ";
        Label<T>::display();
    }
};

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

    Label<int>* ptr = &peak;
    cout << "\nPolymorphism Example:\n";
    ptr->display();
    return 0;
}
