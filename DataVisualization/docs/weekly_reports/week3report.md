WEEK 3 PROGRESS REPORT
Implementation of Object-Oriented Programming Concepts

1. Introduction

During Week 2, I reviewed my responsibilities in the Data Preprocessing module and proposed a `DataPreprocessor` class responsible for validating, cleaning, and preparing data for statistical analysis and visualization.

In Week 3, I have extended the proposed class design to demonstrate three important Object-Oriented Programming (OOP) concepts:

1. Encapsulation
2. Inheritance
3. Polymorphism

These concepts are important because they improve code reusability, data protection, flexibility, and maintainability.

The proposed implementation demonstrates how the Data Preprocessing module can apply these principles while maintaining its original responsibility of preparing reliable data for other components.

2. Class Structure
The design consists of three classes:

1. DataPreprocessor (Base Class)
This class stores numerical data and provides basic validation and preprocessing functions.

2. MissingValuePreprocessor (Derived Class)
This class inherits from `DataPreprocessor` and specializes in handling missing values.

3. InvalidValuePreprocessor (Derived Class)
This class inherits from `DataPreprocessor` and specializes in handling invalid numerical values.

The derived classes reuse the common functionality of the parent class while providing their own preprocessing behavior.

3. Implementation of OOP Concepts
3.1 Encapsulation
Encapsulation is the process of combining data and member functions within a class while restricting direct access to internal data.

In the `DataPreprocessor` class, numerical data is declared private.

class DataPreprocessor {
private:
vector<double> data;

public:
void setData(vector<double> values) {
data = values;
}
vector<double> getData() const {
return data;
}
};

The `setData()` function allows data to be updated, while `getData()` provides controlled access to the stored values.

Importance of encapsulation:
Protects internal data.
Prevents unauthorized direct modification.
Improves code organization.
Makes the module easier to maintain.

3.2 Inheritance
Inheritance allows a derived class to acquire accessible properties and functions from a base class.
In this module, `MissingValuePreprocessor` and `InvalidValuePreprocessor` inherit from `DataPreprocessor`.
 
class MissingValuePreprocessor
: public DataPreprocessor {
public:
void preprocessData() override;
};

The inheritance relationship allows specialized preprocessing classes to reuse common data-handling functionality.

Importance of inheritance:
Reduces code duplication.
Encourages code reuse.
Simplifies program extension.
Improves class organization.

3.3 Polymorphism
Polymorphism allows different objects to respond differently to the same function call.
In this module, polymorphism is demonstrated using a virtual function called `preprocessData()`.
The base class declares:

virtual void preprocessData();
The derived classes override this function to perform different preprocessing operations.

For example:

DataPreprocessor processor;
MissingValuePreprocessor missing;
processor = &missing;
processor->preprocessData();

The appropriate preprocessing function is selected according to the actual object type.

Importance of polymorphism:
Allows different preprocessing methods to share one interface.
Improves program flexibility.
Simplifies the addition of new preprocessing methods.
Makes the code easier to extend.

4. Class Layout and Inheritance Relationships
They are provided as jpeg

 