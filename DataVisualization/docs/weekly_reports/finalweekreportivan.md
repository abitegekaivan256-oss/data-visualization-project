ivan report final

# 1. INTRODUCTION

The Data Visualization Library is a group programming project developed in C++ as part of the CMP2103 Object-Oriented Programming course at Makerere University.

The main purpose of the project is to develop a reusable software library capable of processing numerical data and presenting it in graphical form.

The overall system consists of several modules, including Data Loading, Data Preprocessing, Statistical Analysis, Axis Scaling, Plot Generation, Rendering, Labels and Annotations, and Image Export.

Each module performs a specific responsibility and contributes to the functionality of the complete system.

My assigned responsibility is the development of the **Labels and Annotations module**.

This module manages textual information associated with graphical plots, including graph titles, horizontal and vertical axis labels, and annotations used to highlight important observations.

For example, when plotting voltage against time, the graph requires labels such as *Time (seconds)* along the horizontal axis and *Voltage (V)* along the vertical axis.

Annotations may also identify important values, such as the maximum voltage recorded during an experiment.

The module was implemented using C++ and demonstrates important Object-Oriented Programming principles, particularly encapsulation, inheritance, polymorphism, and abstraction.

The current implementation uses a single C++ source file, `ivan_labels.cpp`, containing the class definitions, member functions, and testing procedures.

This approach makes the program straightforward to compile, execute, understand, and demonstrate independently.

# 2. PROJECT OBJECTIVES

## 2.1 Main Objective

The main objective of this work is to design and implement a reusable C++ module for managing labels and annotations in a data visualization system.

## 2.2 Specific Objectives

The specific objectives are:

1. To develop a general class for representing textual labels.
2. To implement specialized classes for axis labels and annotations.
3. To demonstrate encapsulation using private data members and public member functions.
4. To demonstrate inheritance through derived classes.
5. To demonstrate runtime polymorphism using virtual functions and function overriding.
6. To develop a manager class capable of storing multiple labels.
7. To provide functions for modifying label text and positions.
8. To implement error handling for invalid axis labels.
9. To test the functionality of the implemented classes.
10. To establish a foundation for integration with the graphical rendering module.

# 3. OVERVIEW OF THE LABELS AND ANNOTATIONS MODULE

The Labels and Annotations module is responsible for storing and managing information that describes different parts of a graph.

A graph without labels may be difficult to interpret because users cannot easily identify the quantities represented or the meaning of important observations.

The module therefore provides three major categories of textual information.

## 3.1 Plot Titles

A plot title describes the overall information represented by a graph.

For example:

**Student Performance**

The title informs the user that the graph represents information about student performance.

In the program, a general label is created using:

```cpp
Label title("Student Performance", 250, 30);
```

The first argument represents the text displayed by the label.

The second and third arguments represent the horizontal and vertical positions.

## 3.2 Axis Labels

Axis labels identify the quantities represented along the horizontal and vertical axes.

For example:

**X-axis:** Time (seconds)

**Y-axis:** Voltage (V)

The program creates axis labels using:

```cpp
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
```

The final argument identifies whether the label belongs to the X-axis or Y-axis.

## 3.3 Annotations

An annotation provides additional information about a specific observation on a graph.

For example, an annotation may identify the maximum voltage.

The program creates an annotation using:

```cpp
Annotation peak(
    "Maximum Voltage",
    350,
    80,
    300,
    120
);
```

The annotation contains five arguments.

The first argument represents the annotation text.

The second and third arguments represent the position of the annotation text.

The fourth and fifth arguments represent the coordinates of the point being described.

In this example, the annotation text is positioned at `(350, 80)` and refers to the point `(300, 120)`.

# 4. DEVELOPMENT TOOLS AND PROGRAM STRUCTURE

## 4.1 Development Tools

The implementation uses the following tools:

| Tool                 | Purpose                                                |
| -------------------- | ------------------------------------------------------ |
| C++                  | Programming language                                   |
| Visual Studio Code   | Writing and editing source code                        |
| GNU G++ Compiler     | Compiling the program                                  |
| Windows Terminal     | Executing compilation and testing commands             |
| C++ Standard Library | Providing strings, vectors, exceptions, and assertions |

## 4.2 Program Organization

The program is contained in one source file:

`ivan_labels.cpp`

The file contains the following components:

1. Header inclusions.
2. Standard namespace declaration.
3. `Label` base class.
4. `AxisLabel` derived class.
5. `Annotation` derived class.
6. `Labels` manager class.
7. `main()` function.
8. Testing and output statements.

This structure allows the module to operate independently without requiring additional custom header files.

# 5. EXPLANATION OF THE C++ PROGRAM

## 5.1 Header Files and Namespace

The program begins with:

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cassert>

using namespace std;
```

Each header provides specific functionality.

| Header        | Purpose                                 |
| ------------- | --------------------------------------- |
| `<iostream>`  | Enables input and output operations     |
| `<string>`    | Supports textual data                   |
| `<vector>`    | Provides dynamically sized arrays       |
| `<stdexcept>` | Supports standard exceptions            |
| `<cassert>`   | Supports assertions used during testing |

The statement:

```cpp
using namespace std;
```

allows standard library components such as `cout`, `string`, and `vector` to be used without writing the `std::` prefix.

For example:

```cpp
cout << "Hello";
```

can be used instead of:

```cpp
std::cout << "Hello";
```

# 6. IMPLEMENTATION OF THE LABEL BASE CLASS

The `Label` class represents a general textual label.

It is the parent class from which specialized labels inherit.

## 6.1 Class Declaration

```cpp
class Label {
private:
    string text;
    double x;
    double y;
```

The class contains three private data members.

**text:** Stores the textual description of the label.

**x:** Stores the horizontal position.

**y:** Stores the vertical position.

These members are declared private to prevent direct modification from outside the class.

## 6.2 Constructor

The constructor initializes the label object.

```cpp
Label(string text, double x, double y) {
    this->text = text;
    this->x = x;
    this->y = y;
}
```

A constructor is a special member function that executes automatically when an object is created.

The keyword `this` refers to the current object.

For example:

```cpp
this->text = text;
```

assigns the value of the constructor parameter `text` to the object's private data member `text`.

An object is created using:

```cpp
Label title("Student Performance", 250, 30);
```

The constructor initializes:

* `text = "Student Performance"`
* `x = 250`
* `y = 30`

## 6.3 Setter Functions

Setter functions modify private data members.

The program implements:

```cpp
void setText(string newText) {
    text = newText;
}
```

This function changes the label text.

For example:

```cpp
title.setText("Student Results");
```

The original title changes from *Student Performance* to *Student Results*.

The program also implements:

```cpp
void setPosition(double newX, double newY) {
    x = newX;
    y = newY;
}
```

This function changes the label position.

For example:

```cpp
title.setPosition(300, 40);
```

The updated position becomes `(300, 40)`.

## 6.4 Getter Functions

Getter functions retrieve the values of private data members.

The program implements:

```cpp
string getText() const {
    return text;
}
```

```cpp
double getX() const {
    return x;
}
```

```cpp
double getY() const {
    return y;
}
```

The keyword `const` indicates that these functions do not modify the object's data members.

For example:

```cpp
cout << title.getText();
```

displays the current label text.

## 6.5 Virtual Display Function

The base class contains:

cpp
virtual void display() const {
    cout << "Label: " << text
         << " at (" << x << ", " << y << ")"
         << endl;
}


The function displays the label text and position.

The keyword `virtual` allows derived classes to provide their own implementations of the function.

This is important for demonstrating runtime polymorphism.

## 6.6 Virtual Destructor

The class also contains:

cpp
virtual ~Label() = default;


A destructor is a special member function called when an object is destroyed.

The destructor is declared virtual so that derived-class objects can be destroyed correctly through base-class pointers.

The `default` keyword instructs the compiler to generate the standard destructor implementation.

# 7. IMPLEMENTATION OF THE AXISLABEL CLASS

The `AxisLabel` class represents a label associated with either the horizontal or vertical axis.

## 7.1 Inheritance

The class is declared as:

cpp
class AxisLabel : public Label


The expression `public Label` indicates public inheritance.

This means that the `AxisLabel` class inherits the public and protected functionality of the `Label` class.

The inherited functionality includes the getter functions, setter functions, and virtual display interface.

## 7.2 Additional Data Member

The class introduces:
cpp
private:
    string axis;

This variable identifies whether the label belongs to the X-axis or Y-axis.

## 7.3 Constructor

cpp
AxisLabel(string text, double x, double y, string axis)
    : Label(text, x, y) {

    if (axis != "X" && axis != "Y") {
        throw invalid_argument("Axis must be X or Y");
    }

    this->axis = axis;
}


The statement:

cpp
: Label(text, x, y)


calls the constructor of the base class.

This initializes the inherited label properties.

The `if` statement validates the axis designation.

Only `"X"` and `"Y"` are accepted.

If an invalid axis is supplied, the constructor throws an exception.

## 7.4 Function Overriding

The class overrides the display function:

cpp
void display() const override {
    cout << axis << "-Axis Label: "
         << getText()
         << " at (" << getX()
         << ", " << getY() << ")"
         << endl;
}


The keyword `override` indicates that the function replaces a virtual function declared in the base class.

For example, calling:

cpp
xAxis.display();

produces:

text
X-Axis Label: Time (seconds) at (250, 450)


# 8. IMPLEMENTATION OF THE ANNOTATION CLASS

The `Annotation` class represents textual information associated with a particular point on a graph.

## 8.1 Inheritance

The class is declared as:

cpp
class Annotation : public Label


This allows the annotation to reuse the general label functionality.

## 8.2 Additional Data Members

The class introduces:

cpp
private:
    double pointX;
    double pointY;


These variables store the coordinates of the point being described.

They are different from the label's own position.

For example, the annotation text may be positioned at `(350, 80)` while referring to a point at `(300, 120)`.

## 8.3 Constructor
cpp
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


The constructor initializes the inherited label properties and the annotation's target coordinates.

## 8.4 Updating Annotation Coordinates

The class implements:

cpp
void setTarget(double x, double y) {
    pointX = x;
    pointY = y;
}


This function changes the point associated with the annotation.

For example:

cpp
peak.setTarget(320, 110);


updates the target point to `(320, 110)`.

## 8.5 Annotation Display

The annotation overrides the display function.

cpp
void display() const override {
    cout << "Annotation: "
         << getText()
         << " at (" << getX()
         << ", " << getY() << ")"
         << " pointing to ("
         << pointX << ", "
         << pointY << ")" << endl;
}


The expected output is:

text
Annotation: Maximum Voltage at (350, 80) pointing to (320, 110)


This demonstrates how a derived class can provide specialized behavior while reusing functionality from its base class.

# 9. IMPLEMENTATION OF THE LABELS MANAGER CLASS

The `Labels` class manages multiple label objects.

## 9.1 Data Storage

The manager stores labels using:

cpp
vector<Label*> items;

A vector is a dynamically sized container provided by the C++ Standard Library.

The expression `Label*` represents a pointer to a `Label` object.

Because `AxisLabel` and `Annotation` inherit from `Label`, pointers to their objects can also be stored in this vector.

## 9.2 Adding Labels

cpp
void addLabel(Label& label) {
    items.push_back(&label);
}


This function adds the address of a label object to the collection.

For example:

cpp
manager.addLabel(title);
manager.addLabel(xAxis);
manager.addLabel(yAxis);
manager.addLabel(peak);


The manager now contains four label references.

## 9.3 Displaying All Labels

cpp
void displayAll() const {
    for (const Label* item : items) {
        item->display();
    }
}


The function loops through the stored labels and calls the display function for each object.

Because `display()` is virtual, the appropriate implementation is selected according to the actual object type.

Therefore, the manager can display general labels, axis labels, and annotations through the same interface.

## 9.4 Counting Labels

cpp
size_t count() const {
    return items.size();
}


This function returns the number of stored label references.

For example:

cpp
manager.count();


returns `4` after four labels have been added.

## 9.5 Clearing Labels

cpp
void clear() {
    items.clear();
}


This function removes all stored pointers from the vector.

It does not destroy the original label objects because the manager does not own them.

The referenced objects must remain alive while the manager uses them.

# 10. APPLICATION OF OBJECT-ORIENTED PROGRAMMING PRINCIPLES

## 10.1 Encapsulation

Encapsulation is the process of combining data and related functions within a class while restricting direct access to internal data.

In the `Label` class, the text and position variables are private.

cpp
private:
    string text;
    double x;
    double y;


These values are accessed through getter and setter functions.

This demonstrates data hiding and controlled access.

## 10.2 Inheritance

Inheritance allows a derived class to reuse functionality from an existing base class.

The program demonstrates inheritance through:

cpp
class AxisLabel : public Label


and:

cpp
class Annotation : public Label


Both derived classes inherit the general label functionality.

This reduces code duplication and improves maintainability.

## 10.3 Polymorphism

Polymorphism allows the same interface to produce different behaviors depending on the object being used.

The base class declares:

cpp
virtual void display() const;


The derived classes override this function.

Runtime polymorphism is demonstrated using:

cpp
Label* basePointer = &xAxis;

basePointer->display();


Although the pointer is declared as `Label*`, the function executed is `AxisLabel::display()`.

The same principle is used by the `Labels` manager when displaying different label types.

## 10.4 Abstraction

Abstraction involves exposing essential functionality while hiding unnecessary implementation details.

The module provides a common interface for creating, modifying, and displaying labels.

A programmer can use the public member functions without directly accessing the internal data.

The `Label` class provides a general interface, although it is not an abstract class because its `display()` function has an implementation.

# code cpp
//provided

# 12. TESTING AND VALIDATION

The program contains eight test sections.

## 12.1 Test One: Encapsulation

A general label is created:

cpp
Label title("Student Performance", 250, 30);


The getter functions are used to verify its initial properties.

The text and position are then modified.
cpp
title.setText("Student Results");
title.setPosition(300, 40);


Assertions verify that the updated values are correct.

**Expected result:** Encapsulation test passed.

## 12.2 Test Two: Inheritance

Two `AxisLabel` objects are created.

The first represents the X-axis, while the second represents the Y-axis.

The test checks whether the correct axis designation is stored.

**Expected result:** Inheritance test passed.

## 12.3 Test Three: Annotation

An annotation is created to identify a maximum voltage point.

The target coordinates are retrieved and modified.

Assertions verify that the updated coordinates are correct.

**Expected result:** Annotation test passed.

## 12.4 Test Four: Polymorphism

A base-class pointer is assigned the address of an `AxisLabel` object.

cpp
Label* basePointer = &xAxis;


The display function is then called through the pointer.

cpp
basePointer->display();


The expected behavior is that the overridden `AxisLabel::display()` function executes.

**Expected result:** Polymorphism test passed.

## 12.5 Test Five: Label Manager

Four objects are added to the manager.

The count function is used to verify that four references have been stored.

**Expected result:** Label manager test passed.

## 12.6 Test Six: Displaying Labels

The manager displays all stored labels.

The expected output includes the plot title, X-axis label, Y-axis label, and annotation.

This test demonstrates the use of runtime polymorphism within a collection.

## 12.7 Test Seven: Error Handling

The program attempts to create an axis label using an invalid axis designation.

cpp
AxisLabel invalid(
    "Invalid Axis",
    0,
    0,
    "Z"
);

The constructor throws an `invalid_argument` exception.

The exception is caught using a `try-catch` block.

**Expected result:** Invalid axis test passed.

## 12.8 Test Eight: Clearing Labels

The manager's `clear()` function removes the stored references.

An assertion verifies that the collection is empty.

**Expected result:** Clear labels test passed.

# 13. EXPECTED PROGRAM OUTPUT

The following output is expected when the program executes successfully:

====================================
DATA VISUALIZATION LIBRARY
MODULE: LABELS AND ANNOTATIONS
ASSIGNED TO: IVAN
====================================

Encapsulation test passed
Inheritance test passed
Annotation test passed

X-Axis Label: Time (seconds) at (250, 450)
Polymorphism test passed
Label manager test passed

DISPLAYING LABELS
-----------------------------
Label: Student Results at (300, 40)
X-Axis Label: Time (seconds) at (250, 450)
Y-Axis Label: Voltage (V) at (30, 200)
Annotation: Maximum Voltage at (350, 80) pointing to (320, 110)

Invalid axis test passed
Clear labels test passed

====================================
ALL LABELS TESTS PASSED
====================================
These are expected results based on the source code. Actual execution should be verified using the compiler and terminal.

# 14. CONTRIBUTION TO THE OVERALL DATA VISUALIZATION PROJECT

The Labels and Annotations module forms an important part of the Data Visualization Library.

Its responsibility is to manage textual information that helps users understand graphical results.

The complete visualization workflow is intended to operate as follows:

**Data Loading → Data Preprocessing → Statistical Analysis → Plot Generation → Rendering → Labels and Annotations → Image Export**

In practice, some of these modules may interact rather than execute strictly in this order.

The Labels and Annotations module will provide information required for displaying graph titles, axis labels, and annotations.

For example, when the Plot Generation module creates a line graph representing voltage against time, the Labels module can supply:

* The graph title.
* The horizontal axis label.
* The vertical axis label.
* Descriptions of significant data points.

The Renderer module can then use this information to position text on the graph.

The Image Export module can subsequently save the completed visualization.

The current single-file implementation demonstrates the label-management functionality independently.

Direct graphical integration with the Renderer and Image Export modules remains a future development task.

# 15. CHALLENGES AND SOLUTIONS

## 15.1 Managing Different Types of Labels

The module must support general labels, axis labels, and annotations.

**Solution:** A base class was developed to store common properties, while derived classes provide specialized functionality.

## 15.2 Avoiding Code Duplication

Different label types share properties such as text and position.

**Solution:** Inheritance was used to reuse common functions and data structures.

## 15.3 Supporting Different Display Behaviors

Different label types require different output formats.

**Solution:** Virtual functions and function overriding were used to implement runtime polymorphism.

## 15.4 Managing Multiple Label Objects

A single graph may contain several labels and annotations.

**Solution:** The `Labels` manager was developed using a vector of base-class pointers.

## 15.5 Handling Invalid Input

An axis label should only represent a valid axis.

**Solution:** Constructor validation and exception handling were implemented.

# 16. LIMITATIONS OF THE CURRENT IMPLEMENTATION

The current implementation has several limitations.

First, labels are displayed in the console rather than being drawn directly on a graphical plot.

Second, the program does not automatically generate tick labels.

Third, the program does not support text rotation, font customization, or automatic label positioning.

Fourth, the label manager stores non-owning pointers, requiring the referenced objects to remain alive while they are used.

Finally, the single-file implementation is suitable for independent demonstration but will require an appropriate shared interface when integrated into the larger group project.

# 17. FUTURE IMPROVEMENTS

The following improvements are proposed:

1. Integration with the Renderer module.
2. Graphical display of plot titles and axis labels.
3. Automatic generation of tick labels.
4. Support for rotated Y-axis labels.
5. Support for different font sizes and styles.
6. Automatic annotation positioning.
7. Detection of overlapping labels.
8. Integration with SVG image export.
9. Improved object lifetime management.
10. Additional unit tests.

# 18. CONCLUSION

The Labels and Annotations module was designed to provide reusable functionality for managing textual information in the Data Visualization Library.

The implementation consists of four classes: `Label`, `AxisLabel`, `Annotation`, and `Labels`.

The `Label` class provides common functionality for storing and modifying label text and position.

The `AxisLabel` and `Annotation` classes extend the base class through inheritance and function overriding.

The `Labels` manager provides a common interface for storing and displaying different label objects.

The implementation demonstrates encapsulation, inheritance, polymorphism, and abstraction.

The test program is designed to verify the functionality of the module through assertions and expected output.

Although the current implementation displays information in the console, it establishes a foundation for integrating labels and annotations into the graphical rendering and image-export components of the complete Data Visualization Library.

# APPENDIX A: SOURCE CODE

**File name:** `ivan_labels.cpp`

The complete source code contains:

1. Standard library header inclusions.
2. `Label` base class.
3. `AxisLabel` derived class.
4. `Annotation` derived class.
5. `Labels` manager class.
6. `main()` function.
7. Eight testing sections.

The full source code should be attached to the submitted project.

# APPENDIX B: PROGRAM OUTPUT

Insert screenshots showing the terminal output after successful compilation and execution.

The screenshots should demonstrate the test messages and displayed labels.

# APPENDIX C: CLASS DIAGRAM

The class diagram should illustrate:

* The `Label` base class.
* The `AxisLabel` derived class.
* The `Annotation` derived class.
* The `Labels` manager class.
* Public inheritance relationships.
* Private data members.
* Public member functions.
* The manager's association with stored label objects.

