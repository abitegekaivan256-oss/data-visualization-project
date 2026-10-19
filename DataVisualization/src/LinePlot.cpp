// ============================================================================
// DATA VISUALIZATION LIBRARY IN C++
//
// MODULE: LINE PLOT
// ASSIGNED TO: SANDRA
//
// YOUR RESPONSIBILITIES:
// 1. Accept ordered x and y datasets.
// 2. Use AxisScale to map data to plot coordinates.
// 3. Connect consecutive points.
// 4. Pass drawing requirements to Renderer.
//
// MAIN FILES:
// - include/dataviz/LinePlot.h
// - src/LinePlot.cpp
// - tests/test_line.cpp
//
// DEPENDENCIES / COORDINATION:
// - AxisScale (Bonius)
// - Renderer (Adrian + Group)
// - Plot (Group)
//
// TEAM RULES:
// - Work mainly in your allocated files.
// - Pull the latest repository before starting work.
// - Discuss changes to shared interfaces before editing them.
// - Compile/test your component before committing.
// - Use a clear commit message describing what changed.
//
// IMPLEMENTATION STATUS: NOT YET IMPLEMENTED
// ============================================================================



#include "LinePlot.hpp"

// Constructor
LinePlot::LinePlot(vector<double> x, vector<double> y) {
    xData = x;
    yData = y;
}

// Set graph title
void LinePlot::setTitle(string t) {
    title = t;
}

// Set X-axis label
void LinePlot::setXLabel(string label) {
    xLabel = label;
}

// Set Y-axis label
void LinePlot::setYLabel(string label) {
    yLabel = label;
}

// Display data
void LinePlot::showData() {
    if (xData.size() != yData.size()) {
        cout << "Error: X and Y must have the same number of values."
             << endl;
        return;
    }

    cout << "\n" << title << endl;
    cout << xLabel << "\t" << yLabel << endl;

    for (size_t i = 0; i < xData.size(); i++) {
        cout << xData[i] << "\t" << yData[i] << endl;
    }
}

// Plot the graph
void LinePlot::plot() {
    if (xData.size() != yData.size()) {
        cout << "Cannot plot: X and Y have different sizes."
             << endl;
        return;
    }

    cout << "\nDrawing line plot..." << endl;

    // Actual graph rendering must be implemented here
}
