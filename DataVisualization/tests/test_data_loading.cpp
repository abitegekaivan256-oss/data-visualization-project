// ============================================================================
// COMPONENT TEST PLACEHOLDER
// MODULE: DATA LOADING
// ASSIGNED TO: JACKSON
//
// Add tests here as the module is implemented.
// Do not place the production implementation in this file.
// STATUS: NOT YET IMPLEMENTED
// ============================================================================
#include "dataviz/DataLoader.h"
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

int main() {
    using dataviz::DataLoader;
    const std::string path = "data/loading_test.csv";
    {
        std::ofstream output(path);
        if (!output) { std::cerr << "Create the data folder first\n"; return 1; }
        output << "Name,Age,Score,Notes\n"
               << "Jackson,22,89.5,Good\n"
               << "Gladys,,91,\"Very good, excellent\"\n"
               << "Adrian,21,78,\"Said \"\"hello\"\"\"\n";
    }
    const auto data = DataLoader::loadCSV(path);
    assert(data.columnCount() == 4);
    assert(data.rowCount() == 3);
    assert(data.headers.at(0) == "Name");
    assert(data.rows.at(0).at(0) == "Jackson");
    assert(std::abs(data.numericValue(0, 2) - 89.5) < 1e-9);
    assert(data.isMissing(1, 1));
    assert(data.rows.at(1).at(3) == "Very good, excellent");
    assert(data.rows.at(2).at(3) == "Said \"hello\"");

    bool missingFileHandled = false;
    try { DataLoader::loadCSV("data/does_not_exist.csv"); }
    catch (const std::runtime_error&) { missingFileHandled = true; }
    assert(missingFileHandled);

    std::cout << "All data loading tests passed!\n"
              << "Rows: " << data.rowCount() << ", Columns: " << data.columnCount() << '\n';
}
