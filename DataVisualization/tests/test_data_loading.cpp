// ============================================================================
// COMPONENT TEST
// MODULE: DATA LOADING
// ASSIGNED TO: JACKSON
//
// The checks below exercise the integrated module.
// Do not place the production implementation in this file.
// STATUS: Implemented tests; assertions and explicit error returns determine success.
// ============================================================================
// Project headers expose the production classes exercised by this program.
#include "dataviz/DataLoader.h"
// assert stops a test when an expected condition is false; CMake keeps these checks enabled.
#include <cassert>
// Floating-point helpers support approximate comparisons and finite-value examples.
#include <cmath>
// File streams create CSV fixtures and read the SVG files produced by tests.
#include <fstream>
// Console streams print progress, demonstration results and failure messages.
#include <iostream>
// Standard exception types let tests distinguish validation failures.
#include <stdexcept>
// Strings hold filenames, labels and expected SVG text.
#include <string>

// Write a small CSV fixture, load it and check parsing/conversion and missing-file errors.
// Run through CTest so its data working directory exists. Failed checks abort or return 1.
int main() {
    using dataviz::DataLoader;
    // The fixture deliberately includes a missing age, a quoted comma and escaped quotes.
    const std::string path = "data/loading_test.csv";
    {
        std::ofstream output(path);
        if (!output) {
            std::cerr << "Create the data folder first\n";
            return 1;
        }
        output << "Name,Age,Score,Notes\n"
               << "Jackson,22,89.5,Good\n"
               << "Gladys,,91,\"Very good, excellent\"\n"
               << "Adrian,21,78,\"Said \"\"hello\"\"\"\n";
    }
    // Read the fixture through the production parser, then check table shape and values.
    const auto data = DataLoader::loadCSV(path);
    assert(data.columnCount() == 4);
    assert(data.rowCount() == 3);
    assert(data.headers.at(0) == "Name");
    assert(data.rows.at(0).at(0) == "Jackson");
    assert(std::abs(data.numericValue(0, 2) - 89.5) < 1e-9);
    assert(data.isMissing(1, 1));
    assert(data.rows.at(1).at(3) == "Very good, excellent");
    assert(data.rows.at(2).at(3) == "Said \"hello\"");

    // A missing file must throw runtime_error; merely continuing would be a false success.
    bool missingFileHandled = false;
    try {
        DataLoader::loadCSV("data/does_not_exist.csv");
    } catch (const std::runtime_error &) {
        missingFileHandled = true;
    }
    assert(missingFileHandled);

    std::cout << "All data loading tests passed!\n"
              << "Rows: " << data.rowCount() << ", Columns: " << data.columnCount() << '\n';
}
