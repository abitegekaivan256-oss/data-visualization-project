# Class Structure: Labels and Annotations

## 1. Introduction

This section explains how the program organizes labels and annotations using classes. Classes group related data and functions together, making the program easier to understand, maintain, and extend.

## 2. Classes Used in the Program

### 2.1 `Label` Class

Purpose: Represents a label attached to an object, image, or data item.

Example data members:

- `id` — a unique identifier for the label.
- `name` — the label's name.
- `color` — the color used to display the label, if applicable.

Example member functions:

- `getName()` — returns the label's name.
- `getId()` — returns the label's identifier.
- `setName()` — changes the label's name.
- `setColor()` — changes the label's display color.

Access modifiers:

- Private: Data members such as `id`, `name`, and `color` can be private so other parts of the program cannot change them directly.
- Public: Member functions such as `getName()` and `setName()` can be public so the rest of the program can access or update the label in a controlled way.

### 2.2 `Annotation` Class

Purpose: Represents additional information, comments, or markings associated with an item or label.

Example data members:

- `id` — a unique identifier for the annotation.
- `text` — the annotation's descriptive text.
- `labelId` — the identifier of the label associated with the annotation.

Example member functions:

- `setText()` — updates the annotation text.
- `getText()` — returns the annotation text.
- `display()` — displays the annotation information.

Access modifiers:

- Private: Members such as `id`, `text`, and `labelId` can be private to protect the annotation's internal data.
- **Public:Functions such as `getText()` and `display()` can be public so other parts of the program can retrieve or display annotation information.

## 3. Why Are Some Members Private and Others Public?

Private members support **encapsulation**. They prevent other parts of the program from directly changing internal data in ways the class does not expect.

Public member functions provide a controlled interface for working with that data. For example, a public setter can validate a new label name before storing it, while a getter can return the current value.

This separation helps keep the data consistent and makes the code easier to maintain.

## 4. How the Classes Work Together

The `Label` class stores information about a label. The `Annotation` class stores descriptive information and may refer to its associated label using a label ID. If a `LabelManager` class exists, it can coordinate the creation, storage, retrieval, and removal of labels and annotations.

## 5. Example in C++

The following simplified example demonstrates the idea. It is illustrative and may need to be adapted to the language and structure of the actual project.

#include <iostream>
#include <string>
using namespace std;

class Label {
private:
    int id;
    string name;

public:
    Label(int labelId, string labelName)
        : id(labelId), name(labelName) {}

    string getName() const {
        return name;
    }

    int getId() const {
        return id;
    }
};

class Annotation {
private:
    int id;
    string text;
    int labelId;

public:
    Annotation(int annotationId, string annotationText, int associatedLabelId)
        : id(annotationId),
          text(annotationText),
          labelId(associatedLabelId) {}

    void display() const {
        cout << "Annotation: " << text << '\\n';
        cout << "Associated Label ID: " << labelId << '\\n';
    }
};

int main() {
    Label label1(1, "Important");
    Annotation annotation1(101, "Review this item", 1);

    cout << "Label: " << label1.getName() << '\\n';
    annotation1.display();

    return 0;
}


In this example:

- `Label` stores a label's ID and name.
- `Annotation` stores its ID, text, and associated label ID.
- The constructors initialize each object's data.
- `getName()` and `getId()` provide public access to label information.
- `display()` prints annotation information.
- The data members are private, while the functions used by `main()` are public.

## 6. Conclusion

The program uses classes to group the data and functions related to labels and annotations. The `Label` class represents label information, while the `Annotation` class represents additional information associated with an item or label. A manager class may be used to coordinate these objects if it is part of the implementation.

Private members protect internal data, and public member functions provide controlled access to that data. This organization supports encapsulation, code reuse, and maintainability.
