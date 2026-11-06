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
// Include the public declarations whose definitions are supplied in this file.
#include "dataviz/DataLoader.h"

// Character classification, file input, exceptions and container/string helpers.
// utility supplies move, which transfers an already parsed record without copying.
#include <cctype>
#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace dataviz {
namespace {
// These helpers have internal linkage: other translation units use DataLoader
// rather than depending on the parser implementation.
// Return a copy without leading/trailing whitespace. No numeric conversion occurs.
std::string trim(const std::string &value) {
    // Locate the first non-space character. Casting to unsigned char keeps
    // isspace valid even when a plain char contains a negative byte value.
    std::size_t begin = 0;
    while (begin < value.size() && std::isspace(static_cast<unsigned char>(value[begin])))
        ++begin;
    // Walk backward from one past the last character, stopping at begin so an
    // all-whitespace string produces an empty substring rather than underflow.
    std::size_t end = value.size();
    while (end > begin && std::isspace(static_cast<unsigned char>(value[end - 1])))
        --end;
    return value.substr(begin, end - begin);
}

// Parse CSV records from an existing stream. A logical record can span several
// physical lines when a quoted field contains a newline. The returned outer
// vector holds records; malformed quoting or stream failure throws runtime_error.
std::vector<std::vector<std::string>> parseCSV(std::istream &input) {
    // Build one field inside one record, then collect completed records.
    std::vector<std::vector<std::string>> records;
    std::vector<std::string> record;
    std::string field;
    // Parser state decides whether a comma/newline is data or a separator.
    // justClosedQuote restricts what may follow a quoted field. atFieldStart
    // permits an opening quote after optional whitespace. sawAny detects EOF cases.
    bool inQuotes = false;
    bool justClosedQuote = false;
    bool atFieldStart = true;
    bool sawAny = false;
    char ch;

    // A lambda is a small local function. [&] allows it to update the surrounding
    // parser variables. Finish one field and reset the state for the next field.
    // The existing policy trims even quoted field edges, which callers must know.
    auto finishField = [&]() {
        record.push_back(trim(field));
        field.clear();
        justClosedQuote = false;
        atFieldStart = true;
    };
    // Finish the last field, transfer the record into the result, and reuse
    // the now-cleared record container for the next CSV row.
    auto finishRecord = [&]() {
        finishField();
        records.push_back(std::move(record));
        record.clear();
    };

    // Read one character at a time so quoted commas, escaped quotes and
    // multiline fields can be handled without treating each line as a full row.
    while (input.get(ch)) {
        sawAny = true;
        // Within quotes, separators are ordinary field content. A doubled quote
        // means one literal quote; a single quote closes the quoted field.
        if (inQuotes) {
            if (ch == '"') {
                if (input.peek() == '"') {
                    // Consume the second quote so it is not mistaken for a close.
                    input.get(ch);
                    field.push_back('"');
                } else {
                    inQuotes = false;
                    justClosedQuote = true;
                }
            } else {
                field.push_back(ch);
            }
        } else if (justClosedQuote) {
            // After a closing quote, accept only a delimiter, line ending or
            // whitespace. Reject other characters instead of silently losing data.
            if (ch == ',')
                finishField();
            else if (ch == '\n')
                finishRecord();
            else if (ch == '\r') {
                if (input.peek() == '\n')
                    input.get(ch);
                finishRecord();
            } else if (!std::isspace(static_cast<unsigned char>(ch))) {
                throw std::runtime_error("Invalid character after closing CSV quote");
            }
        } else if (ch == '"') {
            // Quotes may open a field, but cannot appear halfway through an
            // already unquoted value such as abc"def.
            if (!atFieldStart && !trim(field).empty())
                throw std::runtime_error("Unexpected quote in unquoted CSV field");
            field.clear();
            inQuotes = true;
            atFieldStart = false;
        } else if (ch == ',') {
            // Outside quotes, a comma ends the current field.
            finishField();
        } else if (ch == '\n') {
            // A line feed outside quotes completes the logical record.
            finishRecord();
        } else if (ch == '\r') {
            // Treat CRLF as one line ending by consuming an optional following LF.
            if (input.peek() == '\n')
                input.get(ch);
            finishRecord();
        } else {
            // Ordinary unquoted content belongs to the current field.
            field.push_back(ch);
            if (!std::isspace(static_cast<unsigned char>(ch)))
                atFieldStart = false;
        }
    }
    // EOF is normal, but a bad stream or an unfinished quoted field is an error.
    if (input.bad())
        throw std::runtime_error("Error while reading CSV file");
    if (inQuotes)
        throw std::runtime_error("Unterminated quoted CSV field");
    // Preserve a final record without a trailing newline, including an empty
    // quoted last field. Do not invent another row after a completed line ending.
    if (sawAny && (!record.empty() || !field.empty() || justClosedQuote))
        finishRecord();
    return records;
}
} // namespace

// Return true for an empty/whitespace-only selected field. at() deliberately
// reports invalid indexes instead of reading outside a vector.
bool DataSet::isMissing(std::size_t row, std::size_t column) const {
    return trim(rows.at(row).at(column)).empty();
}

// Convert one field and require the whole trimmed string to be numeric.
// Parameters are zero-based row/column indexes; return is a double. The caller
// still needs to check finite values before scaling or computing statistics.
double DataSet::numericValue(std::size_t row, std::size_t column) const {
    const std::string value = trim(rows.at(row).at(column));
    if (value.empty())
        throw std::invalid_argument("Missing numeric value");
    // stod writes how many characters it consumed, allowing rejection of 12kg
    // rather than accepting only its numeric prefix.
    std::size_t consumed = 0;
    double number;
    try {
        number = std::stod(value, &consumed);
    } catch (const std::exception &) {
        // Present one consistent conversion error to preprocessing callers.
        // Index errors occur before this try block and are not translated here.
        throw std::invalid_argument("Not a valid number: " + value);
    }
    if (consumed != value.size())
        throw std::invalid_argument("Not a valid number: " + value);
    return number;
}

// Open filename, parse logical CSV records and return an owned DataSet.
// File/CSV structure errors throw runtime_error. The header record establishes
// the required width of every data row for downstream column selection.
DataSet DataLoader::loadCSV(const std::string &filename) {
    // Binary mode leaves CR/LF handling to parseCSV instead of text translation.
    std::ifstream input(filename, std::ios::binary);
    if (!input.is_open())
        throw std::runtime_error("Cannot open CSV file: " + filename);
    auto records = parseCSV(input);
    if (records.empty())
        throw std::runtime_error("CSV file is empty: " + filename);

    // The first logical record contains column names, not a data observation.
    DataSet data;
    data.headers = std::move(records.front());
    if (data.headers.empty())
        throw std::runtime_error("CSV file has no headers");
    for (const auto &header : data.headers)
        if (header.empty())
            throw std::runtime_error("CSV contains an empty column header");

    // Validate every row against the header width. The +1 in error messages
    // describes human-readable CSV record numbers, including the header.
    for (std::size_t i = 1; i < records.size(); ++i) {
        if (records[i].size() != data.headers.size())
            throw std::runtime_error("CSV record " + std::to_string(i + 1) + " has " +
                                     std::to_string(records[i].size()) + " columns; expected " +
                                     std::to_string(data.headers.size()));
        // Transfer each valid record into the result; no plot/scaling work belongs
        // in the loader, so all fields remain strings at this stage.
        data.rows.push_back(std::move(records[i]));
    }
    return data;
}
} // namespace dataviz
