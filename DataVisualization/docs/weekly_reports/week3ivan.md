# DATA VISUALIZATION LIBRARY IN C++

WEEKLY REPORT: LABELS AND ANNOTATIONS MODULE
22/10/2026
25/U/0819

1. Introduction

The Labels and Annotations module manages descriptive information associated with graphical plots, including plot titles, axis labels, and annotations.
For example, when visualizing student performance, the module can provide the title "Student Performance", an X-axis label "Time", a Y-axis label "Marks", and annotations highlighting important observations.

This applies three fundamental Object-Oriented Programming (OOP) principles:

1.Encapsulation: Protecting label and annotation data from uncontrolled access.
2.Inheritance: Allowing specialized labels to reuse properties and functions from a general label class.
3.Polymorphism: Allowing different types of labels to respond differently to the same function call.

//These concepts make the module organized, reusable, and easier to integrate with other components of the project.

2. Classes Used in the Program

The proposed implementation consists of three main classes:

* Label
* AxisLabel
* Annotation

Each class has a specific responsibility.

a) Label Class

The Label class represents general information about a label used in the visualization.

It is the base class from which specialized labels can inherit.

Private data members:

* id : A unique identifier for the label.
* name: The text displayed by the label.
* color: The color used to display the label.

Public member functions:

* Label(): Initializes the label.
* getId(): Returns the label identifier.
* getName(): Returns the label name.
* setName(): Updates the label name.
* setColor(): Updates the label color.
* display(): Displays the label information.

The "display()" function is declared virtual to support runtime polymorphism.

C++ code:

class Label {
private:
    int id;
    string name;
    string color;

public:
    Label(int i, string n, string c)
        : id(i), name(n), color(c) {}

    int getId() const {
        return id;
    }

    string getName() const
    {
        return name;
    }

    void setName(string n)
     {
        name = n;
     }

    void setColor(string c) 
    {
        color = c;
    }

    virtual void display() const
    {
        cout << "Label: " << name << endl;
    }

    virtual ~Label() = default;
};

The class demonstrates encapsulation because its data members are private and can only be accessed through the appropriate public functions.

2.2 AxisLabel Class
The AxisLabel class represents labels attached to the horizontal or vertical axes of a graph. And unlike an ordinary label, an axis label must identify the axis to which it belongs.

Instead of creating a completely independent class, AxisLabel inherits from Label.

This demonstrates inheritance.

Private data member:

* axis: Identifies the X-axis or Y-axis.

* Public member functions:

* AxisLabel(): Initializes the axis label.
* display(): Displays the axis and its corresponding label.

C++ implementation:
class AxisLabel : public Label {
private:
    string axis;

public:
    AxisLabel(int id, string name, string color, string a)
        : Label(id, name, color), axis(a) {}

    void display() const override
    {
        cout << axis << "-Axis Label: "<< getName() << endl;
    }
};


The statement:
class AxisLabel : public Label means that AxisLabel publicly inherits from Label.

As a result, it can reuse the accessible member functions of the parent class, such as getName() and setName().

The display() function is overridden to provide behavior specific to axis labels.

2.3 Annotation Class

The Annotation class represents additional information or comments associated with a particular label.

For example, an annotation can highlight the highest mark on a student performance graph.

Private data members:

* id: Unique annotation identifier.
* text: Descriptive information.
* labelId: Identifier of the associated label.

Public member functions:

* Annotation(): Initializes the annotation.
* setText(): Updates the annotation.
* getText(): Retrieves the annotation text.
* display(): Displays annotation information.

C++ implementation:
class Annotation {
private:
    int id;
    string text;
    int labelId;

public:
    Annotation(int i, string t, int l)
        : id(i), text(t), labelId(l) {}

    void setText(string t)
    {
        text = t;
    }

    string getText() const
    {
        return text;
    }

    void display() const
    {
        cout << "Annotation: " << text << endl;
        cout << "Associated Label ID: " << labelId << endl;
    }
};
The Annotation class does not inherit from Label.

Instead, it maintains an association with a label through the labelId variable.

This is appropriate because an annotation provides additional information about a label rather than being a specialized type of label.

3. Implementation of Object-Oriented Programming Concepts

3.1 Encapsulation

Encapsulation is the process of combining data and the functions that operate on that data within a class while restricting direct access to internal information.
In this project, encapsulation is demonstrated in all three classes.
For example, the Label class declares its data members as private:

private:
    int id;
    string name;
    string color;

These variables cannot be accessed directly from outside the class.Instead, public member functions are used:
void setName(string n) 
{
    name = n;
}

string getName() const 
{
    return name;
}

Example:
Label title(1, "Results", "Blue");

title.setName("Student Results");

cout << title.getName() << endl;

Importance of encapsulation:
* Protects internal class data.
* Provides controlled access to variables.
* Improves program security and reliability.
* Makes code easier to modify and maintain.
3.2 Inheritance
Inheritance is an OOP mechanism through which a derived class acquires accessible properties and functions from an existing base class.
In my implementation:

Base class: Label
Derived class: AxisLabel

The inheritance relationship is established using:
class AxisLabel : public Label
For example:
AxisLabel x(2, "Time", "Black", "X");

cout << x.getName() << endl;

Although getName() is defined in the Label class, it can be called using an AxisLabel object because of public inheritance.

**Importance of inheritance:**

* Encourages code reusability.
* Reduces code duplication.
* Allows specialization of existing classes.
* Makes the project easier to extend.
3.3 Polymorphism

Polymorphism is the ability of objects belonging to different classes to respond differently to the same function call.
In this project, runtime polymorphism is demonstrated using the virtual function display().

The parent class declares:
virtual void display() const 
{
    cout << "Label: " << name << endl;
}
The child class overrides the function:
void display() const override
{
    cout << axis << "-Axis Label: " << getName() << endl;
}
Example:
Label title(1, "Student Results", "Blue");

AxisLabel x(2, "Time", "Black", "X");

Label* labels[] = {&title, &x};

for (Label* label : labels) 
{
    label->display();
}

Although both objects are accessed through pointers of type Label*, the appropriate version of display() is executed.

This demonstrates runtime polymorphism.
Importance of polymorphism:

* Allows different objects to share a common interface.
* Improves program flexibility.
* Reduces the need for repeated conditional statements.
* Simplifies integration with other modules.

 4. How the Classes Work Together

The three classes perform different but related responsibilities.

The Label class stores general label information, including its identifier, name, and color.

The AxisLabel class extends Label to represent labels associated with graph axes.

The Annotation class stores descriptive information and identifies the label to which it belongs.

For example, consider a graph showing student performance.

The program can create:

* A general label containing the graph title.
* An X-axis label representing time.
* A Y-axis label representing marks.
* An annotation describing an important observation.

The Renderer module can eventually use this information to display titles, axis labels, and annotations on the graph.

The current implementation prints label information to the console. Actual graphical rendering will require integration with the Renderer module.

5. Program Testing

The following test program demonstrates how the three classes work together.
int main() {

    // General label
    Label title(1, "Student Results", "Blue");

    // Encapsulation
    title.setName("Student Performance");

    // Inheritance
    AxisLabel x(2, "Time", "Black", "X");
    AxisLabel y(3, "Marks", "Black", "Y");

    // Annotation
    Annotation note(101, "Highest mark recorded",3);

    // Runtime polymorphism
    Label* labels[] = {&title, &x, &y};

    for (Label* label : labels)
    {
        label->display();
    }

    // Display annotation
    note.display();

    return 0;
}

6. Class Layouts and Relationships

The class diagrams illustrate the organization of the module.
they are provided as jpeg files

Access-specifier notation:

* "+" represents public members.
* "-" represents private members.
* "#" represents protected members.
7. Integration with Other Project Modules

The Labels and Annotations module is designed to coordinate with two other components.
Renderer Module

The Renderer is responsible for drawing graphical elements. The Labels module will supply the information needed to display plot titles, axis labels, and annotations.
