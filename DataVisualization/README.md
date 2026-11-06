# Current C++17 library structure and usage

This guide applies to the local `integration-final` version integrating the verified `build-fix` branch with `origin/main`. See the [final integration report](docs/FINAL_INTEGRATION_REPORT.md) for the merged revisions, conflict decisions and current verification results. The [structure repair report](docs/STRUCTURE_REPAIR_REPORT.md) and [commenting report](docs/COMMENTING_REVIEW_REPORT.md) retain the preceding file moves and test evidence; their paths and results describe those earlier states. The original group README is retained below.

The implemented workflow is CSV → paired finite numerical data → statistics and three plots → labels/annotations → SVG export. Export supports SVG; PNG/JPEG export and custom plot-scale injection are not implemented.

## Production code and teaching examples

- `include/dataviz/` contains reusable public `.h` and `.hpp` interfaces. Production preprocessing is declared in `DataPreprocessor.h`; the `Statistics::summarize` template remains in `Statistics.h`, where clients can instantiate it. Production SVG labels are defined inline in `Labels.h`.
- `Point.hpp` contains the single shared `dataviz::Point` definition. Renderer and LinePlot use this same two-coordinate value type. LinePlot continues to use Plot's title and axis-label state through its inherited setters and getters.
- `src/` contains all eleven production translation units. `Labels.cpp` and `Statistics.cpp` include their production headers without defining application entry points.
- `examples/teaching/` contains the eight relocated standalone lessons. Each has its own `main()` and separate executable target. Both historical Labels copies have distinct filenames to preserve their original locations; they do not implement the production SVG label API.
- `examples/` also retains the existing library demonstrations and the distinct double-array `legacy_statistics.cpp` lesson. `examples/main.cpp` is the integrated CSV demonstration.
- `tests/` contains all thirteen original CTest programs. Their assertions are unchanged. Each test links the production library and runs in its own build-directory folder.

The explanatory comments and group contributions are retained. The active build starts at the repository-level `CMakeLists.txt`. The root `Cmakelist.txt` remains an inactive historical proposal; CMake does not select that spelling.

## Configure, build and test

The verification tools are GCC 16.2.0 and CMake 4.4.5. A separate `build/integration-final` directory verifies the integrated sources from a clean configuration. Run these commands in PowerShell:

```powershell
$project = 'C:\Users\GLADYS\Documents\DataVisualization_Final_Integration'
$build = "$project\build\integration-final"
$env:PATH = 'C:\msys64\ucrt64\bin;' + $env:PATH
& 'C:\Program Files\CMake\bin\cmake.exe' -S $project -B $build -G Ninja '-DCMAKE_BUILD_TYPE=Debug' '-DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe' '-DCMAKE_MAKE_PROGRAM=C:/PROGRA~1/MATLAB/R2025b/toolbox/shared/coder/ninja/win64/ninja.exe' '-DCMAKE_EXPORT_COMPILE_COMMANDS=ON'
& 'C:\Program Files\CMake\bin\cmake.exe' --build $build --parallel 4
& 'C:\Program Files\CMake\bin\ctest.exe' --test-dir $build --output-on-failure
```

The compiler runtime directory on `PATH` supplies the GCC runtime DLLs. It does not override Windows Application Control. If Windows prevents an executable from starting, record the native error and report the test as BLOCKED. An administrator must determine the approved policy, signing process or testing environment. Do not disable security or rename programs to evade restrictions. The final integration report gives the actual results for this build; historical test results are retained in the earlier reports.

## Run the CSV-to-SVG demonstration

The demo requires an existing output directory. Use a directory reserved for this demonstration:

```powershell
$demoOutput = "$build\integration-demo"
New-Item -ItemType Directory -Force -Path $demoOutput | Out-Null
& "$build\DataVisualization\csv_demo.exe" "$project\DataVisualization\data\demo.csv" $demoOutput
```

The expected result for `demo.csv` is `Rows: 5 Mean: 2.4 Median: 3 Population variance: 7.44`, with `scatter.svg`, `bar.svg` and `line.svg` exported into that directory. The separate `sample.csv` contains different values. The final integration report records the independently observed output and SVG verification.

Scatter SVG markers are filled blue circles with a dark outline and a configurable radius (default 5 pixels); the configured character is used for ASCII output. Signed bars include a visible, labeled zero baseline. Line plots preserve input order. Production `Plot::exportData()` remains a no-op extension hook, not a data-file exporter.

## Original group README

The text below is retained as group documentation; historical responsibilities, proposed features and previous test statements should be read alongside the current evidence above.

---

 DATA VISUALIZATION LIBRARY IN C++
1. PROJECT NAME AND DESCRIPTION
1.1 Project Name
Data Visualization Library in C++

Description
The Data Visualization Library is a C++ software project designed to provide reusable components for processing, analyzing, and visualizing numerical data. The project aims to simplify the process of converting numerical datasets into graphical representations.
It combines several modules, including data loading, data preprocessing, statistical analysis, graph generation, axis scaling, rendering, labels and annotations, and image export. The library is organized using object-oriented programming principles to improve code organization, reusability, maintainability, and extensibility.
Instead of implementing every operation in a single program, the system separates different responsibilities into independent but interconnected modules. For example, the DataLoader module handles reading data from files, while the Renderer module handles graphical representation. This separation allows individual modules to be developed, tested, and improved independently.

1.2 Problem Being Addressed
Numerical datasets are often difficult to interpret when presented only as tables of values.
Graphs make it easier to identify patterns, trends, comparisons, and relationships between variables.
The Data Visualization Library addresses this problem by providing reusable C++ components for common data processing and visualization operations.
1.4 Intended Users
* Students learning C++ programming.
* Programmers working with numerical datasets.
* Developers building educational applications.
* Users requiring basic statistical analysis and visualization.
* Programmers interested in reusable object-oriented software components.

2. PROJECT OBJECTIVES
2.1 General Objective
To design and implement a reusable C++ library capable of processing numerical data and generating graphical representations while demonstrating important object-oriented programming concepts.
2.2 Specific Objectives

- To implement functionality for loading numerical data from CSV files.
- To develop data preprocessing components for handling invalid or missing numerical values.
- To implement statistical analysis functions.
- To provide different graphical representations, including scatter plots, line plots, and bar plots.
- To implement appropriate axis scaling.
- To support graph titles, labels, and annotations.
- To develop a Renderer for producing graphical output.
- To provide image export functionality.
- To apply C++ concepts such as classes, objects, inheritance, polymorphism, encapsulation, and templates.
- To organize the project into reusable modules.
- To test the major components of the library.
- To demonstrate collaborative software development using Git and GitHub.

3. MAIN FEATURES
The project contains source files corresponding to the following major modules.
3.1 Data Loading
Module: DataLoader
Relevant files:
* include/dataviz/DataLoader.h
* src/DataLoader.cpp
The Data Loading module is responsible for reading numerical datasets from external files.
Its intended responsibilities include opening CSV files, reading rows, extracting numerical values, and handling file-related errors.
C++ concepts involved:
* File handling.
* Input streams.
* Functions.
* Classes and objects.
* Data structures.
* Error handling.

3.2 Data Preprocessing
Module: DataPreprocessor
Relevant files:
* src/DataPreprocessor.cpp
* include/dataviz/DataPreprocessor.cpp
The Data Preprocessing module is intended to prepare numerical data for analysis and visualization.
Data preprocessing may involve identifying invalid values, handling missing values, and producing datasets suitable for further processing.
C++ concepts involved:
* Functions.
* Loops.
* Conditional statements.
* Data structures.
* Classes or structures.
* Data validation.

3.3 Statistical Analysis
Module: Statistics
Relevant files:
* include/dataviz/Statistics.h
* src/Statistics.cpp
The Statistical Analysis module is intended to perform mathematical calculations on numerical datasets.
During development, the group worked on statistical operations including:
* Sum.
* Mean.
* Minimum.
* Maximum.
* Range.
* Variance.
* Standard deviation.
These operations help users summarize and interpret numerical information.
Statistical analysis provides useful information that can complement graphical visualization.
C++ concepts involved:
* Functions.
* Loops.
* Templates.
* Arrays or vectors.
* Return values.
* Numerical calculations.

3.4 Scatter Plot

Module:ScatterPlot
Relevant files:
* include/dataviz/ScatterPlot.h
* src/ScatterPlot.cpp
A scatter plot represents numerical data using points positioned according to their X and Y coordinates.
Scatter plots are useful for examining relationships between two numerical variables.
The ScatterPlot module is responsible for representing the data required to generate this type of graph.
C++ concepts involved:
* Classes and objects.
* Constructors.
* Data structures.
* Member functions.
* Inheritance or polymorphism, were implemented.

3.5 Line Plot
Module: LinePlot
Relevant files:
* include/dataviz/LinePlot.hpp
* src/LinePlot.cpp
A line plot represents numerical data using points connected by lines. Line plots are particularly useful for displaying trends or changes across ordered values.
For example, a line plot can show how temperature changes with time. The LinePlot module provides the functionality needed to represent line-based graphs.

3.6 Bar Plot
Module:Bar Plot
Relevant files:
* include/dataviz/BarPlot.h
* src/BarPlot.cpp
A bar plot represents numerical values using rectangular bars. Bar plots are useful for comparing quantities across categories. For example, a bar plot may compare the number of students enrolled in different courses.
The BarPlot module is intended to organize the values required to construct such graphical representations.

3.7 Axis Scaling
Module: AxisScale
Relevant files:
* include/dataviz/AxisScale.h
* src/AxisScale.cpp
Axis scaling determines how numerical values are represented along graph axes. The purpose of axis scaling is to ensure that plotted data fits within the available graphical area.
For example, a dataset containing values between 10 and 100 requires an appropriate numerical scale.
Axis scaling may involve calculating minimum and maximum values, determining intervals, and mapping data values to graphical positions.

3.8 Renderer
Module: Renderer
Relevant files:
* include/dataviz/Renderer.h
* src/Renderer.cpp
The Renderer is responsible for converting plot information into graphical output. It works with the plot representation to produce the visual elements required for a graph.
The project includes SVG files such as:
* renderer_demo.svg
* scatter _demo.svg
These files provide examples of graphical output associated with project development. The Renderer is an important connection between plot data and the final exported graph.

3.9 Labels and Annotations
Relevant files:
* src/Labels.cpp
* include/dataviz/Labels.cpp
Labels and annotations provide descriptive information about graphs.
They may include:
* Graph titles.
* X-axis labels.
* Y-axis labels.
* Text annotations.
* Information associated with plotted values.
These elements improve the readability and interpretation of graphical results.

3.10 Image Export
Module: ImageExporter
Relevant files:
* include/dataviz/ImageExporter.h
* src/ImageExporter.cpp
The Image Export module is responsible for saving graphical output to files. During development, the group worked with SVG output. SVG stands for Scalable Vector Graphics.
It is an XML-based graphics format that represents shapes, lines, and text.
SVG images can be resized without the same loss of quality associated with enlarging raster images.

 4. PROJECT STRUCTURE

DataVisualization/

- README.md
- .gitignore

include/
 - dataviz
       DataLoader.h
       Statistics.h
       ScatterPlot.h
       LinePlot.hpp
       BarPlot.h
       AxisScale.h
       Renderer.h
       ImageExporter.h
       Plot.h

src/
    DataLoader.cpp
    DataPreprocessor.cpp
    Statistics.cpp
    ScatterPlot.cpp
    LinePlot.cpp
    BarPlot.cpp
    AxisScale.cpp
    Renderer.cpp
    ImageExporter.cpp
    Labels.cpp
    Plot.cpp

 tests/
    test_data_loading.cpp
    test_preprocessing.cpp
    test_statistics.cpp
    test_scatter.cpp
    test_lineplot.cpp
    test_bar.cpp
    test_scaling.cpp
    test_renderer.cpp
    test_labels.cpp
    test_image_export.cpp

 examples/
    main.cpp
    example_barplot.cpp
    example_lineplot.cpp
    example_applying_Polymorphism.cpp
    example_Inheritance&codeReuse.cpp

 docs/
   ├── PROJECT_ARCHITECTURE.md
   ├── TEAM_FILE_OWNERSHIP.md
   ├── TEAM_WORKFLOW.md
   └── weekly_reports/

 data/
    sample.csv
 output/
4.1 Purpose of Each Directory
a) include
Contains the public header files used to access library functionality.
b) src
Contains implementation files defining the behavior of the library's components.
c) tests
Contains programs intended to verify the functionality of individual modules.
d) examples
Contains programs demonstrating C++ concepts and library functionality.
e)docs
Contains project architecture information, team documentation, and development reports.
f) data
g) output

5. REQUIREMENTS AND DEPENDENCIES
5.1 Programming Language
The library is developed using C++.
5.2 Compiler
A C++17-compatible compiler is required for the previously used compilation approach. The group has used the GNU C++ compiler, `g++`.
5.3 Development Environment
The project has been developed using Visual Studio Code. VS Code provides facilities for editing source files, accessing the terminal, and working with Git.

6. INSTALLATION AND BUILD INSTRUCTIONS
6.1 Obtaining the Project
The project is hosted on GitHub under the group's repository.
A user can clone the repository using Git.
git clone https://github.com/abitegekaivan256-oss/data-visualization-project.git

7. HOW TO USE THE LIBRARY
The intended usage process is:
START
  |
Include required header files
  |
Create library objects
  |
Load numerical data
  |
Preprocess the data
  |
Perform statistical analysis
  |
Select a plot type
  |
Configure axes and labels
  |
Render the graph
  |
Export graphical output
7.1 Using Header Files
C++ header files provide declarations that allow other programs to access library functionality.
7.2 Creating Objects
Classes define the structure and behavior of objects. A program may create an object of a library class and use its public member functions to perform operations. The exact constructor arguments and member functions must be taken from the implemented header files.
7.3 Combining Modules
The library is intended to allow data produced by one module to be used by another. For example, numerical values obtained through DataLoader may be passed to statistical analysis or plotting components.
7.4 Reusability
A reusable library allows programmers to use its functionality in different applications without copying the implementation code into every program.
This is achieved through public interfaces, modular design, and a suitable build configuration.
9. HOW TO RUN THE TESTS
Testing verifies whether software behaves as expected.
The project contains test source files for major modules.
9.1 Test Files
test_data_loading.cpp 
 test_preprocessing.cpp 
 test_statistics.cpp    
 test_scatter.cpp       
 test_lineplot.cpp      
 test_line.cpp
 test_bar.cp       
 test_scaling.cpp       
 test_renderer.cpp     
 test_labels.cpp        
 test_image_export.cpp  
9.2 Types of Tests
Normal Input Tests
These verify that a function works correctly when valid data is provided.
Edge Case Tests
These examine unusual but valid situations.
Examples may include:
* Empty datasets.
* Single-element datasets.
* Repeated values.
* Very large or small numerical values.
Invalid Input Tests
These verify how the program responds to incorrect input.
Examples may include:
* Missing files.
* Invalid numerical values.
* Unsupported input formats.
* Invalid output paths.
9.3 Previous Testing Results
Earlier testing of the Image Export module reported:
Inheritance test passed
Polymorphism test passed
Encapsulation test passed
SVG export passed
Error handling passed
All tests passed
10. PROJECT LIMITATIONS
The Data Visualization Library in C++ provides basic functionality for processing, analyzing, and visualizing numerical data. However, the current version has some limitations that could be addressed in future development.
10.1 Limited Input File Formats
The library currently focuses on reading numerical data from CSV files. Support for other file formats, such as Excel (.xlsx) and JSON (.json), has not been implemented.
10.2 Limited Graph Types
The library focuses on three main types of graphs: scatter plots, line plots, and bar plots. More advanced visualizations, such as pie charts, histograms, and three-dimensional graphs, are not currently supported.
10.3 Limited Image Export Formats
The library has been developed to export graphs in SVG (Scalable Vector Graphics) format. Other image formats, such as PNG and JPEG, are not currently supported.
10.4 Future Improvements
Future versions of the library could introduce additional input formats, more graph types, support for PNG and JPEG export, interactive visualization features, and improved performance when processing large datasets.
11. CONTRIBUTIONS BY GROUP MEMBERS
The project was divided into modules to support collaborative development.
The following table records the responsibilities previously assigned within the group.


 Jackson         Data Loading and Image Export               
 Gladys Babirye  Data Preprocessing and Statistical Analysis 
 Adrian          Scatter Plot and Renderer                   
 Ivan            Labels and Annotations                      
 Bonius          Axis Scaling                                
 Sandra          Line Plot                                   
 Jeff            Bar Plot                                    
11.1 Individual Contributions
Each member was responsible for developing and understanding their assigned components. The group also discussed shared responsibilities involving integration, testing, and documentation.
11.2 Contribution Evidence
Individual contributions can be supported by:
* Git commit history.
* Pull requests.
* Source files.
* Test files.
* Weekly progress reports.
* Recorded technical discussions.
12. TEAM COLLABORATION
12.1 Collaboration Approach
The project uses Git and GitHub to support collaborative development.
Git provides version control, while GitHub allows members to share changes through a common repository.
The group has discussed dividing responsibilities into separate modules so that members can work independently while contributing to a common library.
12.2 Branch-Based Development
Branches allow developers to work on changes without immediately modifying the main branch.
A member can develop a feature, test it, commit the changes, and push the branch to GitHub.
12.3 Commits
A commit records a particular state of the project.
Commits are important because they allow developers to track changes and identify contributions.
on description should identify which of these activities actually occurred.
12.4 Collaboration Challenges
During the development of the Data Visualization Library in C++, our group encountered several challenges related to teamwork, code integration, version control, and project organization.

Git and GitHub Challenges
Some group members experienced difficulties working with Git branches, committing changes, pushing code to GitHub, and creating pull requests. We addressed these challenges by improving our understanding of Git commands and coordinating how individual contributions were submitted to the shared repository.

Integration of Different Modules
Since each group member was responsible for developing a particular module, combining the independently developed components presented some challenges. We worked together to understand the relationships between modules and ensure that components such as DataLoader, Statistics, Plot, Renderer, and ImageExporter could work together.

Compilation and Debugging Challenges
During development, compilation errors and compatibility issues arose when working with different C++ files. We addressed these issues by reviewing header files, checking function declarations and definitions, and testing individual components to identify and correct errors.

Project File Organization
Organizing source files, header files, tests, examples, and documentation was another challenge. We worked toward maintaining a structured project directory to make the library easier to understand, maintain, and extend.

Documentation and Progress Reporting
Preparing individual weekly reports and combining documentation from different group members required coordination. We organized project documentation to record completed tasks, challenges encountered, and progress made during development.

Lessons Learned
Through these challenges, our group improved its understanding of collaborative software development, Git and GitHub, modular programming, debugging, and the importance of communication. We also learned that successful software development requires not only writing code but also testing, documentation, integration, and teamwork.
13. OBJECT-ORIENTED PROGRAMMING CONCEPTS USED IN THE PROJECT
13.1 Classes and Objects
A class is a user-defined data type that combines data members and member functions.
An object is an instance of a class.
The project uses class-based components to organize responsibilities such as data loading, plotting, rendering, and image export.
13.2 Encapsulation
Encapsulation involves combining data and related operations within a class while controlling access to its internal state.
In C++, access specifiers include:
* private
* protected
* public
Encapsulation helps prevent inappropriate modification of internal data.
It also allows a class to expose a clear public interface.
13.3 Inheritance
Inheritance allows a derived class to reuse or extend functionality defined in a base class. The project contains a Plot component and specialized plot components.
Inheritance can reduce duplicated code when multiple plot types share common behavior.
13.4 Polymorphism
Polymorphism allows different types to respond to a common interface in different ways.
Runtime polymorphism in C++ is commonly implemented using virtual functions and function overriding.
13.5 Abstraction
Abstraction involves exposing essential functionality while hiding unnecessary implementation details.
Header files provide public declarations that help programmers understand how to use a component without examining every implementation statement.
13.6 Templates
Templates allow programmers to write generic functions or classes that operate on different data types.
During development, the group explored templates for statistical calculations.
For example, a function template can support different numerical types without requiring separate implementations for every type.
13.7 Structures
A structure is a user-defined type that groups related data and functions.
In C++, members of a struct are public by default, while members of a class are private by default.
The group explored structures as a simpler way to demonstrate some programming concepts.
13.8 Constructors
Constructors are special member functions used to initialize objects. They are called when objects are created.
Constructors can help establish valid initial values for a class.
13.9 File Handling
File handling allows programs to read data from and write data to external files.
The DataLoader module involves input operations, while graphical export involves output operations.
13.10 Error Handling
Error handling allows software to respond appropriately when operations cannot be completed.
Examples include missing input files, invalid numerical values, and unsuccessful output operations.
The implementation should be examined to determine whether errors are handled using return values, exceptions, or other mechanisms.
13.11 Code Reusability
Code reusability means that existing functionality can be used in multiple programs or components without unnecessary duplication.
The library's modular design is intended to support this principle.
14. AI-USE DECLARATION — REFERENCE INFORMATION
chat gpt was used specifically to elastrate the usage of classes 

15. CONCLUSION

The Data Visualization Library in C++ is intended to provide reusable components for numerical data processing, statistical analysis, graphical representation, and image export.

The project demonstrates how a larger software system can be divided into smaller modules with clearly defined responsibilities.

It also provides opportunities to apply important C++ concepts, including classes, objects, encapsulation, inheritance, polymorphism, templates, file handling, and modular programming.

The project contains source files, public headers, tests, examples, and documentation covering its major components.

Before final submission, the group must verify successful integration, complete the required build configuration, run the full test suite, and ensure that the README accurately describes the working implementation.

The overall objective is to produce a reusable, understandable, and maintainable C++ library while demonstrating effective collaboration and sound software development practices.

