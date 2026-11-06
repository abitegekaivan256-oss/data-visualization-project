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
// ============================================================================

#ifndef DATAVIZ_DATA_LOADER_H
#define DATAVIZ_DATA_LOADER_H

// size_t represents nonnegative row/column counts and indexes.
#include <cstddef>
// CSV fields remain strings until a caller explicitly requests a number.
#include <string>
// Vectors store a variable number of headers, rows and fields.
#include <vector>

namespace dataviz {

// Shared table representation. Missing fields are stored as empty strings.
// The loader and numeric preprocessing share this representation. A struct has
// public members by default; callers can inspect the table directly.
struct DataSet {
    // Column names come from the first CSV record.
    std::vector<std::string> headers;
    // Each inner vector is one data record. The loader checks its column count.
    std::vector<std::vector<std::string>> rows;

    // These const/noexcept accessors only inspect container sizes. They neither
    // modify the table nor perform numeric conversion.
    std::size_t rowCount() const noexcept {
        return rows.size();
    }
    std::size_t columnCount() const noexcept {
        return headers.size();
    }
    // Test a trimmed field for emptiness. Bounds-checked access can throw
    // out_of_range for an invalid row or column index.
    bool isMissing(std::size_t row, std::size_t column) const;
    // Convert the complete selected field to double. Missing/non-numeric fields
    // throw invalid_argument; bad indexes throw out_of_range. Conversion may
    // produce NaN/infinity, so DataPreprocessor checks finiteness separately.
    double numericValue(std::size_t row, std::size_t column) const;
};

// Stateless loading utility: static loadCSV can be called without constructing
// a DataLoader object. Its result owns all loaded strings and rows.
class DataLoader {
  public:
    // Loads a CSV with a header row. Supports quoted commas, escaped quotes,
    // CRLF line endings and multiline quoted fields.
    // filename is the input path; the returned DataSet contains headers and rows.
    // Throws std::runtime_error for file/CSV errors.
    // No custom constructor/destructor is needed: standard containers own data.
    static DataSet loadCSV(const std::string &filename);
};

} // namespace dataviz
#endif
