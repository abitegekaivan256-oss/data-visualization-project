FINAL REPORT
# 1. INTRODUCTION
The Data Visualization Library is a C++ programming project developed to process, analyze, and visualize numerical datasets.

The project involves several interconnected modules, including Data Loading, Data Preprocessing, Statistical Analysis, Axis Scaling, Plot Generation, Rendering, Labels and Annotations, and Image Export.

Each module performs a specific task and contributes to the overall functionality of the library.

My assigned responsibilities in this group project were:

1. Data Preprocessing
2. Statistical Analysis

The Data Preprocessing module focuses on identifying and handling invalid numerical values before analysis.

The Statistical Analysis module performs mathematical calculations on numerical datasets to provide useful information about their characteristics.

In developing these modules, I explored fundamental C++ programming concepts, including functions, arrays, vectors, loops, conditional statements, templates, and object-oriented programming.

The purpose of this report is to explain the design, implementation, operation, and intended integration of my assigned modules into the complete Data Visualization Library.

# 2. OBJECTIVES

## 2.1 General Objective

To develop reusable C++ components for preprocessing and statistically analyzing numerical datasets as part of a Data Visualization Library.

## 2.2 Specific Objectives

1. To develop functions for identifying and removing invalid numerical values.
2. To prepare numerical datasets for further processing.
3. To implement statistical functions for calculating the sum, mean, minimum, maximum, range, variance, and standard deviation.
4. To apply C++ templates to support different numerical data types.
5. To demonstrate relevant object-oriented programming principles.
6. To develop modular and understandable C++ code.
7. To test the statistical calculations using sample datasets.
8. To prepare the modules for integration with the other components of the library.

# 3. OVERVIEW OF THE DATA VISUALIZATION LIBRARY

The Data Visualization Library is designed to transform numerical data into graphical representations that are easier to interpret.

The general flow of the system is:

**Data Loading → Data Preprocessing → Statistical Analysis → Plot Generation → Rendering → Image Export**

Data Loading reads numerical values from external sources such as CSV files.

Data Preprocessing checks the data and prepares it for analysis.

Statistical Analysis calculates mathematical properties of the processed dataset.

Plot Generation produces graphical representations such as scatter plots, line graphs, and bar charts.

Rendering converts graphical information into visible plot elements, while Image Export saves the resulting visualization into an appropriate file format.

My modules contribute to the reliability and usefulness of the data before visualization.

# 4. DATA PREPROCESSING MODULE

## 4.1 Introduction

Data preprocessing is the process of examining, cleaning, and preparing raw data before performing mathematical analysis or visualization.

Raw datasets may contain missing values, invalid numbers, or values that cannot be processed correctly.

If these problems are ignored, the resulting statistical calculations and graphs may be inaccurate.

Therefore, preprocessing is an important stage in the Data Visualization Library.

## 4.2 Responsibilities of the Module

- Identifying invalid numerical values.
- Detecting missing data where the input format provides that information.
- Removing or handling invalid entries.
- Preparing clean numerical datasets.
- Providing processed data to other modules.

## 4.3 Implementation Approach

The preprocessing logic can be implemented using C++ vectors, loops, conditional statements, and functions.

For example, a function can examine each numerical value and determine whether it is suitable for statistical analysis.

When an invalid value is detected, the program can exclude it from the cleaned dataset.

The cleaned values can then be passed to the Statistical Analysis module.

The implementation must distinguish between genuinely invalid data and valid values such as zero or negative numbers. Such values should not be removed merely because of their sign.

## 4.4 Importance of Data Preprocessing

Data preprocessing improves the reliability of the library by reducing the risk of invalid numerical operations.

It also makes the Statistical Analysis module easier to use because statistical functions can operate on datasets that have already been checked.

For example, when calculating the mean, the program must use the number of valid observations rather than counting values that have been discarded.

# 5. STATISTICAL ANALYSIS MODULE

## 5.1 Introduction

Statistical analysis is the process of examining, organizing, and interpreting numerical data to obtain meaningful information.

In the Data Visualization Library, the Statistical Analysis module performs calculations that help users understand the characteristics of their datasets.

The module provides statistical functions for determining the sum, mean, minimum, maximum, range, variance, and standard deviation.

These functions are implemented using basic C++ programming concepts such as functions, arrays, loops, and templates.

The use of templates allows the module to analyze different numerical data types without requiring separate implementations for each type.

## 5.2 Statistical Operations

### 5.2.1 Sum

The sum is the total value obtained by adding all the numerical elements in a dataset.

In the Statistical Analysis module, the sum function uses a loop to move through the dataset and add each value to a running total.

This operation is important because it provides the total of the dataset and is also used when calculating other statistical measures, particularly the mean.

### 5.2.2 Mean

The mean is the average value of a dataset. It represents the central value around which the observations are distributed.

In the program, the mean function calculates the total sum of the numerical values and divides it by the number of observations.

The mean helps users understand the general level of the dataset and is also used when calculating variance and standard deviation.

### 5.2.3 Minimum

The minimum is the smallest numerical value present in a dataset.

The minimum function examines each value and compares it with the smallest value identified so far.

Whenever a smaller value is found, the stored minimum is updated.

This operation is useful for identifying the lower boundary of a dataset and can assist in determining appropriate limits when generating graphs.

### 5.2.4 Maximum

The maximum is the largest numerical value present in a dataset.

The maximum function compares the values in the dataset and continuously updates the largest value whenever a greater number is encountered.

The maximum is useful for identifying the upper boundary of a dataset and determining the scale required for graphical representation.

### 5.2.5 Range

The range is a measure of the spread of a dataset, determined by the difference between its largest and smallest values.

In the program, the range function uses the results obtained from the minimum and maximum functions.

It provides a simple indication of how widely the numerical values are distributed.

A larger range generally indicates a wider spread between the extreme values, while a smaller range indicates that the highest and lowest values are closer together.

### 5.2.6 Variance

Variance is a statistical measure that describes how far numerical values are spread around their mean.

It helps determine whether the values in a dataset are closely grouped together or widely dispersed.

In the Statistical Analysis module, the variance function first determines the mean of the dataset.

It then examines how far each value differs from the mean, squares these differences, and calculates their average.

The current implementation calculates population variance.

Variance is important because it provides information about the variability of numerical data and helps users understand the consistency of observations.

### 5.2.7 Standard Deviation

Standard deviation is a statistical measure that describes the typical spread of numerical values around their mean.

It is closely related to variance and is obtained by calculating the square root of the variance.

In the program, the standard deviation function calls the variance function and then uses the C++ square root operation to obtain the final result.

A smaller standard deviation generally indicates that values are concentrated closer to the mean, while a larger standard deviation indicates greater variation.

Standard deviation is useful when comparing the consistency and distribution of different datasets.

## 5.3 Importance of Statistical Analysis in the Project

The Statistical Analysis module contributes to the Data Visualization Library by converting raw numerical values into meaningful statistical information.

It helps users understand important characteristics of their datasets before or alongside graphical representation.

The module also supports other components of the library. For example, minimum and maximum values can assist in determining suitable graph limits, while mean and standard deviation can provide useful information when interpreting numerical trends.

By implementing the statistical functions separately, the library becomes more modular, reusable, and easier to maintain.

# 6. APPLICATION OF C++ TEMPLATES

## 6.1 Introduction to Templates

Templates are a C++ programming feature that allows functions or classes to work with different data types.

Instead of writing separate statistical functions for integers, floats, and doubles, templates allow a single function definition to support these types.

This technique is called generic programming.

## 6.2 Function Template Implementation

A function template is declared using:

`template <typename T>`

The symbol `T` represents a data type that is determined when the function is used.

For example, the statistical sum function can be declared as:

```cpp
template <typename T>
double sum(T data[], int n)
```

This allows the function to process arrays containing integers, floats, or doubles.

## 6.3 Example of Template Usage

Consider the following arrays:
int numbers[] = {10, 20, 30, 40, 50};
double decimals[] = {2.5, 4.5, 6.5, 8.5};


The same statistical function can be called for both arrays:
sum(numbers, 5);
sum(decimals, 4);


For the first call, the compiler uses `int` as the template type.

For the second call, the compiler uses `double`.

The return type remains `double` so that the calculations can accommodate decimal results.

## 6.4 Benefits of Templates

1. **Code reusability:** The same statistical function can process multiple numerical data types.
2. **Reduced code duplication:** Separate functions are not required for every supported data type.
3. **Maintainability:** Changes to a statistical calculation can be made in one function definition.
4. **Flexibility:** The library can support different types of numerical datasets.
5. **Type safety:** The compiler checks whether the supplied types support the operations used in the template.

Templates are particularly useful in a Data Visualization Library because datasets may contain integers or floating-point values.

# 7. APPLICATION OF OBJECT-ORIENTED PROGRAMMING CONCEPTS

Object-oriented programming is an important aspect of CMP2103.

During the development and study of my assigned modules, I considered how object-oriented programming principles could improve the organization and reusability of the library.

## 7.1 Encapsulation

Encapsulation involves grouping data and the functions that operate on that data within a class or struct.

For example, a `Statistics` class could store a dataset and provide member functions for calculating the mean, variance, and standard deviation.

Access modifiers can be used to control access to internal data.

However, the simplified statistical implementation developed for this module uses standalone function templates rather than encapsulating all operations in a class.

## 7.2 Inheritance

Inheritance allows one class to acquire properties and functions from another class.

In a larger version of the library, a general data-processing class could provide common functionality that specialized processing classes reuse.

Inheritance was studied as a possible design approach, but it is not required by the current standalone statistical functions.

## 7.3 Polymorphism

Polymorphism allows different implementations to be used through a common interface.

In C++, runtime polymorphism can be implemented using virtual functions and inheritance.

Function templates also provide compile-time generic behavior, although they are different from runtime polymorphism through virtual functions.

The statistical module primarily demonstrates generic programming using templates.

## 7.4 Structs and Classes

C++ supports both `struct` and `class` for organizing data and functions.

A struct has public members by default, while a class has private members by default.

During development, I explored how structs could be used to group numerical data and related operations.

For the simplified implementation, standalone functions were preferred to make the statistical calculations easier to understand and test.

# 8. MODULE INTEGRATION

The Data Preprocessing and Statistical Analysis modules are intended to operate together.

## 8.1 Integration with Data Loading

The Data Loading module reads numerical information from external files.

The loaded values can then be transferred to the Data Preprocessing module.

## 8.2 Integration with Data Preprocessing

The preprocessing stage examines the values and removes or handles invalid entries according to the selected cleaning rules.

Only valid numerical values are passed to the statistical functions.

## 8.3 Integration with Statistical Analysis

The Statistical Analysis module calculates the sum, mean, minimum, maximum, range, variance, and standard deviation.

These calculations provide useful information about the dataset.

## 8.4 Integration with Plot Generation

The processed numerical data can be passed to the plot-generation components.

Statistical information may also support decisions about graph scaling, labels, and interpretation.

For example, the minimum and maximum values can help determine appropriate plotting limits.

The intended integration flow is:

**CSV File → Data Loader → Data Preprocessor → Statistical Analysis → Plot Generation → Renderer → Image Export**

This describes the proposed relationship between the modules. Full end-to-end integration must be verified using the combined group project.

# 9. TESTING AND EXPECTED RESULTS

Testing is important because it helps determine whether the implemented statistical functions produce correct results.

The statistical module can be tested using known datasets for which the expected answers are easy to calculate manually.

## 9.1 Integer Dataset

The first test dataset is:

`10, 20, 30, 40, 50`

Expected results:

| Statistical Operation | Expected Result |
|---|---|
| Sum | 150 |
| Mean | 30 |
| Minimum | 10 |
| Maximum | 50 |
| Range | 40 |
| Population Variance | 200 |
| Population Standard Deviation | 14.1421 |

## 9.2 Decimal Dataset

The second test dataset is:

`2.5, 4.5, 6.5, 8.5`

Expected results:

| Statistical Operation | Expected Result |
|---|---|
| Sum | 22 |
| Mean | 5.5 |
| Minimum | 2.5 |
| Maximum | 8.5 |
| Range | 6 |
| Population Variance | 5 |
| Population Standard Deviation | 2.23607 |

## 9.3 Empty Dataset Handling

The display function includes a condition to check whether the dataset contains any elements.

When the number of elements is zero or negative, the program displays:

`No data available!`

This prevents the display function from calling statistical operations that require a nonempty dataset.

## 9.4 Additional Testing Requirements

Before final project submission, further testing should verify:

- Correct handling of datasets containing one element.
- Correct processing of negative values.
- Correct handling of repeated values.
- Correct processing of floating-point datasets.
- Safe handling of empty datasets.
- Correct behavior after preprocessing.
- Compatibility with the other modules of the group project.

The tables above represent mathematically verified expected results. Actual compilation, execution, and integration test evidence should be attached separately.

# 10. CHALLENGES AND SOLUTIONS

## 10.1 Supporting Different Data Types

**Challenge:** Statistical functions may need to process integer and decimal datasets.

**Solution:** C++ function templates were introduced to allow one function definition to work with different numerical types.

## 10.2 Avoiding Repeated Code

**Challenge:** Writing separate statistical functions for every data type increases code duplication.

**Solution:** Generic functions were used to reduce repeated implementations.

## 10.3 Understanding Variance and Standard Deviation

**Challenge:** Variance and standard deviation require several mathematical operations.

**Solution:** The calculations were divided into simple steps involving the mean, differences, squared differences, and square roots.

## 10.4 Compiler and Linking Errors

**Challenge:** During testing, the MinGW compiler reported an undefined reference to `WinMain@16`.

**Solution Approach:** The program structure, presence of the `main()` function, saved source-file location, and compilation commands were reviewed.

A standalone executable requires a valid entry point. Reusable library modules may instead be compiled together with a separate test program.

## 10.5 Module Integration

**Challenge:** Data preprocessing and statistical calculations must operate correctly with the other components of the library.

**Solution Approach:** The modules were designed around reusable functions and a clear data-processing sequence.

Complete integration remains subject to testing within the combined group repository.

# 11. SKILLS AND KNOWLEDGE GAINED

Through this project, I developed a better understanding of the following C++ concepts:

1. **Functions:** Dividing a program into smaller reusable operations.
2. **Arrays and vectors:** Storing and processing numerical datasets.
3. **Loops:** Iterating through data elements.
4. **Conditional statements:** Making decisions during data validation and statistical calculations.
5. **Templates:** Creating generic functions for different numerical data types.
6. **Object-oriented programming:** Understanding encapsulation, inheritance, polymorphism, classes, and structs.
7. **Modular programming:** Organizing functionality into separate components.
8. **Debugging:** Investigating compiler and linking errors.
9. **Testing:** Comparing program results against known mathematical answers.
10. **Documentation:** Explaining program design, calculations, and implementation decisions.

The project also demonstrated how mathematical concepts can be implemented using programming techniques to solve practical data-processing problems.

# 12. RECOMMENDATIONS FOR FUTURE IMPROVEMENT

1. Extend the Statistical Analysis module to calculate median and mode.
2. Add sample variance and sample standard deviation as separate operations.
3. Improve preprocessing to support configurable handling of missing values.
4. Add more extensive validation for invalid numerical data.
5. Develop automated unit tests for each statistical function.
6. Integrate the modules fully with the group's Data Loading and Plot Generation components.
7. Improve error handling and diagnostic messages.
8. Organize the reusable statistical functions into suitable header files.
9. Test the complete Data Visualization Library using larger datasets.

These improvements would make the library more reliable, flexible, and suitable for practical applications.

# 13. CONCLUSION

The development of the Data Preprocessing and Statistical Analysis modules contributes to the overall objective of building a reusable Data Visualization Library in C++.

The Data Preprocessing module is intended to improve the quality of numerical datasets by identifying and handling invalid values before further processing.

The Statistical Analysis module provides reusable functions for calculating important descriptive statistics, including sum, mean, minimum, maximum, range, variance, and standard deviation.

The use of C++ templates allows the same statistical functions to process different numerical data types without unnecessary code duplication.

The project also provided an opportunity to explore important programming concepts such as modular programming, functions, arrays, vectors, templates, encapsulation, inheritance, and polymorphism.

Overall, my contribution establishes a foundation for preparing and analyzing numerical datasets before visualization. Further testing and integration with the remaining group modules will be necessary to confirm the reliability of the complete system.

