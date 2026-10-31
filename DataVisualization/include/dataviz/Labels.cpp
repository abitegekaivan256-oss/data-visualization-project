// week three display labels
#include <iostream>
#include <string>
using namespace std;
// 1. LABEL CLASS (BASE CLASS)
class Label 
{
private:
    int id;
    string name;
    string color;

public:
    // Constructor
    Label(int i, string n, string c)
 {
        id = i;
        name = n;
        color = c;
    }

    // Getter for ID
    int getId() const
    {
        return id;
    }

    // Getter for name
    string getName() const 
    {
        return name;
    }

    // Setter for name
    void setName(string n) 
    {
        name = n;
    }

    // Setter for color
    void setColor(string c) 
    {
        color = c;
    }

    // Virtual function for polymorphism
    virtual void display() const 
    {
        cout << "Label: " << name << endl;
    }

    // Virtual destructor
    virtual ~Label() = default;
};
// 2. AXIS LABEL CLASS (DERIVED CLASS)
// Demonstrates Inheritance

class AxisLabel : public Label
{
private:
    string axis;

public:
    // Constructor
    AxisLabel(int i, string n, string c, string a) : Label(i, n, c)
    {
        axis = a;
    }

    // Function overriding (Polymorphism)
    void display() const override 
    {
        cout << axis << "-Axis Label: "
             << getName() << endl;
    }
};
// 3. ANNOTATION CLASS
// Demonstrates Encapsulation

class Annotation {
private:
    int id;
    string text;
    int labelId;

public:
    // Constructor
    Annotation(int i, string t, int l) 
    {
        id = i;
        text = t;
        labelId = l;
    }

    // Setter
    void setText(string t) 
    {
        text = t;
    }

    // Getter
    string getText() const 
    {
        return text;
    }

    // Display annotation
    void display() const 
    {
        cout << "Annotation: " << text << endl;
        cout << "Associated Label ID: " << labelId << endl;
    }
};
// 4. MAIN FUNCTION
// Demonstrates All Three OOP Concepts

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
    Label* labels[] = {&title, &x, &y};

    cout << "\n--- PLOT LABELS ---" << endl;

    for (Label* label : labels)
    {
        label->display();
    }

    cout << "\n--- ANNOTATION ---" << endl;

    note.display();

    cout << "\nProgram executed successfully!" << endl;

    return 0;
}
