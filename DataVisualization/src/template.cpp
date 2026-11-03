#include <iostream>
#include <string>
using namespace std;

// BASE CLASS: Demonstrates templates and encapsulation
template <typename T>
class Label {
private:
    string text;
    T x, y;

public:
    // Constructor
    Label(string t, T a, T b) {
        text = t;
        x = a;
        y = b;
    }

    // Getter
    string getText() {
        return text;
    }

    // Setter
    void setText(string t) {
        text = t;
    }

    // Virtual function for polymorphism
    virtual void display() {
        cout << text << " at (" << x << ", " << y << ")" << endl;
    }

    virtual ~Label() {}
};

// DERIVED CLASS 1: Axis labels
template <typename T>
class AxisLabel : public Label<T> {
public:
    AxisLabel(string t, T x, T y) : Label<T>(t, x, y) {}

    // Function overriding
    void display() override {
        cout << "Axis Label: ";
        Label<T>::display();
    }
};

// DERIVED CLASS 2: Annotations
template <typename T>
class Annotation : public Label<T> {
public:
    Annotation(string t, T x, T y) : Label<T>(t, x, y) {}

    void display() override {
        cout << "Annotation: ";
        Label<T>::display();
    }
};

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
    Label<int>* ptr = &peak;

    cout << "\nPolymorphism Example:" << endl;
    ptr->display();

    return 0;
}