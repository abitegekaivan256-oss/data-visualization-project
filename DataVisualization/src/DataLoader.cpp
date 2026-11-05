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
#include "dataviz/DataLoader.h"

#include <cctype>
#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace dataviz {
namespace {
std::string trim(const std::string& value) {
    std::size_t begin = 0;
    while (begin < value.size() && std::isspace(static_cast<unsigned char>(value[begin]))) ++begin;
    std::size_t end = value.size();
    while (end > begin && std::isspace(static_cast<unsigned char>(value[end - 1]))) --end;
    return value.substr(begin, end - begin);
}

std::vector<std::vector<std::string>> parseCSV(std::istream& input) {
    std::vector<std::vector<std::string>> records;
    std::vector<std::string> record;
    std::string field;
    bool inQuotes = false;
    bool justClosedQuote = false;
    bool atFieldStart = true;
    bool sawAny = false;
    char ch;

    auto finishField = [&]() {
        record.push_back(trim(field));
        field.clear();
        justClosedQuote = false;
        atFieldStart = true;
    };
    auto finishRecord = [&]() {
        finishField();
        records.push_back(std::move(record));
        record.clear();
    };

    while (input.get(ch)) {
        sawAny = true;
        if (inQuotes) {
            if (ch == '"') {
                if (input.peek() == '"') {
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
            if (ch == ',') finishField();
            else if (ch == '\n') finishRecord();
            else if (ch == '\r') {
                if (input.peek() == '\n') input.get(ch);
                finishRecord();
            } else if (!std::isspace(static_cast<unsigned char>(ch))) {
                throw std::runtime_error("Invalid character after closing CSV quote");
            }
        } else if (ch == '"') {
            if (!atFieldStart && !trim(field).empty())
                throw std::runtime_error("Unexpected quote in unquoted CSV field");
            field.clear();
            inQuotes = true;
            atFieldStart = false;
        } else if (ch == ',') {
            finishField();
        } else if (ch == '\n') {
            finishRecord();
        } else if (ch == '\r') {
            if (input.peek() == '\n') input.get(ch);
            finishRecord();
        } else {
            field.push_back(ch);
            if (!std::isspace(static_cast<unsigned char>(ch))) atFieldStart = false;
        }
    }
    if (input.bad()) throw std::runtime_error("Error while reading CSV file");
    if (inQuotes) throw std::runtime_error("Unterminated quoted CSV field");
    if (sawAny && (!record.empty() || !field.empty() || justClosedQuote)) finishRecord();
    return records;
}
} // namespace

bool DataSet::isMissing(std::size_t row, std::size_t column) const {
    return trim(rows.at(row).at(column)).empty();
}

double DataSet::numericValue(std::size_t row, std::size_t column) const {
    const std::string value = trim(rows.at(row).at(column));
    if (value.empty()) throw std::invalid_argument("Missing numeric value");
    std::size_t consumed = 0;
    double number;
    try {
        number = std::stod(value, &consumed);
    } catch (const std::exception&) {
        throw std::invalid_argument("Not a valid number: " + value);
    }
    if (consumed != value.size()) throw std::invalid_argument("Not a valid number: " + value);
    return number;
}

DataSet DataLoader::loadCSV(const std::string& filename) {
    std::ifstream input(filename, std::ios::binary);
    if (!input.is_open()) throw std::runtime_error("Cannot open CSV file: " + filename);
    auto records = parseCSV(input);
    if (records.empty()) throw std::runtime_error("CSV file is empty: " + filename);

    DataSet data;
    data.headers = std::move(records.front());
    if (data.headers.empty()) throw std::runtime_error("CSV file has no headers");
    for (const auto& header : data.headers)
        if (header.empty()) throw std::runtime_error("CSV contains an empty column header");

    for (std::size_t i = 1; i < records.size(); ++i) {
        if (records[i].size() != data.headers.size())
            throw std::runtime_error("CSV record " + std::to_string(i + 1) +
                                     " has " + std::to_string(records[i].size()) +
                                     " columns; expected " + std::to_string(data.headers.size()));
        data.rows.push_back(std::move(records[i]));
    }
    return data;
}
} // namespace dataviz
