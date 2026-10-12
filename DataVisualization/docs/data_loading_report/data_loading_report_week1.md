# DATA VISUALIZATION LIBRARY IN C++
## WEEK 1 INDIVIDUAL PROGRESS REPORT

Module: Data Loading  
Contributor: Jackson  
Development Branch: jackson-data-loading  
Project: Design and Implementation of a Data Visualization Library in C++

### 1. Introduction

The Data Loading module is responsible for reading external datasets and preparing them for subsequent processing within the C++ Data Visualization Library.

The module provides a foundation for other components, including Data Preprocessing, Statistical Analysis, Scatter Plots, Line Plots, and Bar Plots.

### 2. Objectives

1. Implement functionality for opening and reading CSV files.
2. Extract column headers and individual data records.
3. Support numeric data conversion.
4. Store the imported data in a reusable data structure.
5. Identify missing values and handle file-related errors.
6. Develop a test program to verify the module's functionality.

### 3. Implementation

The module consists of three primary files.

| File | Purpose |
|---|---|
| `DataLoader.h` | Declares the data-loading interface and associated data structures. |
| `DataLoader.cpp` | Implements CSV reading, parsing, and error handling. |
| `test_data_loading.cpp` | Contains tests for the data-loading functionality. |

The implementation is designed to support CSV files containing both numerical and textual values.

### 4. Testing and Validation

The module was compiled using the GNU C++ compiler with the C++17 standard.

**Compilation command:**

`g++ -std=c++17 -Iinclude src/DataLoader.cpp tests/test_data_loading.cpp -o test_loader.exe`

The compilation completed without errors.

The test program is intended to verify CSV parsing, numerical conversion, missing-value handling, and file-error detection.

**Test execution:** Pending confirmation.

### 5. Integration With Other Modules

The Data Loading module supplies datasets to the Data Preprocessing and Statistics modules assigned to Gladys.

The data structure and interface will be coordinated with the preprocessing developer to ensure compatibility.

### 6. Challenges and Solutions

**Challenge:** Initial compilation failed because the terminal was opened in the parent project directory rather than the nested `DataVisualization` folder.

**Solution:** The correct project directory was identified, and the source and test files were compiled successfully.

### 7. Current Progress

The initial Data Loading implementation has been added to the project and compiled successfully.

Functional test results and GitHub integration are awaiting final verification.

### 8. Next Development Activities

- Complete and document functional testing.
- Coordinate the shared data interface with the preprocessing developer.
- Review CSV parsing against additional sample datasets.
- Integrate the module with other components after interface approval.
- Submit the changes for group review through a GitHub Pull Request.

### 9. Conclusion

The first implementation of the Data Loading module establishes the foundation for importing CSV datasets into the C++ Data Visualization Library. Successful compilation confirms that the source and test files build together. Functional verification and integration with the remaining modules are the next development stages.