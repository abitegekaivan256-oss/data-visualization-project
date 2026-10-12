// ============================================================================
// DATA VISUALIZATION LIBRARY IN C++
//
// MODULE: DATA LOADING
// ASSIGNED TO: JACKSON
//
// YOUR RESPONSIBILITIES:
// 1. Open and read CSV/data files.
// 2. Parse rows and numeric values.
// 3. Store loaded data in the agreed data structure.
// 4. Handle missing files and basic file errors.
//
// MAIN FILES:
// - include/dataviz/DataLoader.h
// - src/DataLoader.cpp
// - tests/test_data_loading.cpp
//
// DEPENDENCIES / COORDINATION:
// - DataPreprocessor (Gladys)
// - Statistics (Gladys)
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

#ifndef DATAVIZ_DATA_LOADER_H
#define DATAVIZ_DATA_LOADER_H

#include <cstddef>
#include <string>
#include <vector>

namespace dataviz {

// Shared table representation. Missing fields are stored as empty strings.
// Agree on this interface with preprocessing/statistics teammates.
struct DataSet {
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> rows;

    std::size_t rowCount() const noexcept { return rows.size(); }
    std::size_t columnCount() const noexcept { return headers.size(); }
    bool isMissing(std::size_t row, std::size_t column) const;
    double numericValue(std::size_t row, std::size_t column) const;
};

class DataLoader {
public:
    // Loads a CSV with a header row. Supports quoted commas, escaped quotes,
    // CRLF line endings and multiline quoted fields.
    // Throws std::runtime_error for file/CSV errors.
    static DataSet loadCSV(const std::string& filename);
};

} // namespace dataviz
#endif
