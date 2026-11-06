// Project headers expose the production classes exercised by this program.
#include "dataviz/DataPreprocessor.h"
// assert stops a test when an expected condition is false; CMake keeps these checks enabled.
#include <cassert>
// Standard exception types let tests distinguish validation failures.
#include <stdexcept>
// Check DropRow on missing/nonfinite/nonnumeric pairs and reject an invalid column.
// Both coordinate vectors must stay aligned after an entire row is removed.
int main() {
    // The fixture contains one good pair and NaN, missing and nonnumeric Y/X entries.
    dataviz::DataSet d{{"x", "y"}, {{"1", "2"}, {"nan", "3"}, {"4", ""}, {"5", "bad"}}};
    // Only the first paired row survives DropRow; check its retained Y value.
    auto p = dataviz::DataPreprocessor::numericPairs(d, 0, 1, dataviz::InvalidPolicy::DropRow);
    assert(p.first.size() == 1 && p.second[0] == 2);
    // A column outside the header range must throw out_of_range rather than be silently dropped.
    bool caught = false;
    try {
        dataviz::DataPreprocessor::numericPairs(d, 0, 9);
    } catch (const std::out_of_range &) {
        caught = true;
    }
    assert(caught);
}
