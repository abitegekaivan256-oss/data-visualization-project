#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cassert>

using namespace std;

// =====================================================
// BASE CLASS: Label
// Demonstrates ENCAPSULATION
// =====================================================

class Label {
private:
    string text;
    double x;
    double y;

public:
    // Constructor
    Label(string text, double x, double y) {
        this->text = text;
        this->x = x;
        this->y = y;
    }

    // Setter functions
    void setText(string newText) {
        text = newText;
    }

    void setPosition(double newX, double newY) {
        x = newX;
        y = newY;
    }

    // Getter functions
    string getText() const {
        return text;
    }

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    // Virtual function for POLYMORPHISM
    virtual void display() const {
        cout << "Label: " << text
             << " at (" << x << ", " << y << ")" << endl;
    }

    virtual ~Label() = default;
};


// =====================================================
// DERIVED CLASS 1: AxisLabel
// Demonstrates INHERITANCE
// =====================================================

class AxisLabel : public Label {
private:
    string axis;

public:
    // Constructor
    AxisLabel(string text, double x, double y, string axis)
        : Label(text, x, y) {

        if (axis != "X" && axis != "Y") {
            throw invalid_argument("Axis must be X or Y");
        }

        this->axis = axis;
    }

    string getAxis() const {
        return axis;
    }

    // Function overriding
    void display() const override {
        cout << axis << "-Axis Label: "
             << getText()
             << " at (" << getX()
             << ", " << getY() << ")" << endl;
    }
};


// =====================================================
// DERIVED CLASS 2: Annotation
// Demonstrates INHERITANCE and POLYMORPHISM
// =====================================================

class Annotation : public Label {
private:
    double pointX;
    double pointY;

public:
    // Constructor
    Annotation(
        string text,
        double x,
        double y,
        double pointX,
        double pointY
    ) : Label(text, x, y) {

        this->pointX = pointX;
        this->pointY = pointY;
    }

    void setTarget(double x, double y) {
        pointX = x;
        pointY = y;
    }

    double getPointX() const {
        return pointX;
    }

    double getPointY() const {
        return pointY;
    }

    // Function overriding
    void display() const override {
        cout << "Annotation: "
             << getText()
             << " at (" << getX()
             << ", " << getY() << ")"
             << " pointing to ("
             << pointX << ", "
             << pointY << ")" << endl;
    }
};


// =====================================================
// LABELS MANAGER CLASS
// Manages multiple labels
// =====================================================

class Labels {
private:
    vector<Label*> items;

public:
    // Add a label
    void addLabel(Label& label) {
        items.push_back(&label);
    }

    // Display all labels
    void displayAll() const {
        for (const Label* item : items) {
            item->display();
        }
    }

    // Clear all stored references
    void clear() {
        items.clear();
    }

    // Count labels
    size_t count() const {
        return items.size();
    }
};


// =====================================================
// MAIN FUNCTION
// TESTING ALL OOP CONCEPTS
// =====================================================

int main() {

    cout << "====================================" << endl;
    cout << "DATA VISUALIZATION LIBRARY" << endl;
    cout << "MODULE: LABELS AND ANNOTATIONS" << endl;
    cout << "ASSIGNED TO: IVAN" << endl;
    cout << "====================================" << endl;


    // TEST 1: ENCAPSULATION

    Label title("Student Performance", 250, 30);

    assert(title.getText() == "Student Performance");
    assert(title.getX() == 250);
    assert(title.getY() == 30);

    title.setText("Student Results");
    title.setPosition(300, 40);

    assert(title.getText() == "Student Results");
    assert(title.getX() == 300);
    assert(title.getY() == 40);

    cout << "\nEncapsulation test passed" << endl;


    // TEST 2: INHERITANCE

    AxisLabel xAxis(
        "Time (seconds)",
        250,
        450,
        "X"
    );

    AxisLabel yAxis(
        "Voltage (V)",
        30,
        200,
        "Y"
    );

    assert(xAxis.getAxis() == "X");
    assert(yAxis.getAxis() == "Y");

    cout << "Inheritance test passed" << endl;


    // TEST 3: ANNOTATIONS

    Annotation peak(
        "Maximum Voltage",
        350,
        80,
        300,
        120
    );

    assert(peak.getPointX() == 300);
    assert(peak.getPointY() == 120);

    peak.setTarget(320, 110);

    assert(peak.getPointX() == 320);
    assert(peak.getPointY() == 110);

    cout << "Annotation test passed" << endl;


    // TEST 4: POLYMORPHISM

    Label* basePointer = &xAxis;

    basePointer->display();

    cout << "Polymorphism test passed" << endl;


    // TEST 5: LABEL MANAGER

    Labels manager;

    manager.addLabel(title);
    manager.addLabel(xAxis);
    manager.addLabel(yAxis);
    manager.addLabel(peak);

    assert(manager.count() == 4);

    cout << "Label manager test passed" << endl;


    // TEST 6: DISPLAY ALL LABELS

    cout << "\nDISPLAYING LABELS" << endl;
    cout << "-----------------------------" << endl;

    manager.displayAll();


    // TEST 7: INVALID AXIS

    bool exceptionCaught = false;

    try {
        AxisLabel invalid(
            "Invalid Axis",
            0,
            0,
            "Z"
        );
    }
    catch (const invalid_argument&) {
        exceptionCaught = true;
    }

    assert(exceptionCaught);

    cout << "\nInvalid axis test passed" << endl;


    // TEST 8: CLEAR LABELS

    manager.clear();

    assert(manager.count() == 0);

    cout << "Clear labels test passed" << endl;


    cout << "\n====================================" << endl;
    cout << "ALL LABELS TESTS PASSED" << endl;
    cout << "====================================" << endl;

    return 0;
}