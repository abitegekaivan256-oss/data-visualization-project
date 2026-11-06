// Production paired-column preprocessing interface. This static utility differs
// from examples/teaching/data_preprocessor_inheritance.cpp, a standalone lesson.
// Keep the production and teaching interfaces distinct during oral defense.
#pragma once
// DataSet supplies the table and bounds-checked numeric field conversion.
#include "dataviz/DataLoader.h"
// pair packages the aligned X and Y vectors into one returned value.
#include <utility>
namespace dataviz {
// Reject reports the first invalid observation; DropRow skips both coordinates
// of an invalid row so later X and Y positions remain aligned.
enum class InvalidPolicy { Reject, DropRow };
// Stateless utility: no stored data or custom constructor/destructor is needed.
class DataPreprocessor {
  public:
    // Read two zero-based columns from the input DataSet. The return pair holds
    // X values in first and Y values in second. Reject is the default policy.
    // Invalid column indexes throw out_of_range; invalid numeric data throws
    // invalid_argument in Reject mode. No imputation or normalization is performed.
    static std::pair<std::vector<double>, std::vector<double>>
    numericPairs(const DataSet &, std::size_t, std::size_t, InvalidPolicy = InvalidPolicy::Reject);
};
}
