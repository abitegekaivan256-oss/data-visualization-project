// Match the production declaration; this file does not implement the legacy
// MissingValuePreprocessor/InvalidValuePreprocessor teaching hierarchy.
#include "dataviz/DataPreprocessor.h"
// isfinite rejects NaN/infinity before statistics or coordinate mapping.
#include <cmath>
// Standard exceptions distinguish invalid data from invalid column indexes.
#include <stdexcept>
namespace dataviz {
// Extract aligned numeric vectors from table d using columns x and y. policy
// decides whether conversion errors stop processing or cause a whole row to be
// skipped. Returning a new pair leaves the original DataSet unchanged.
std::pair<std::vector<double>, std::vector<double>>
DataPreprocessor::numericPairs(const DataSet &d, std::size_t x, std::size_t y,
                               InvalidPolicy policy) {
    // Reject bad column choices before iterating, even if the table has no rows.
    if (x >= d.columnCount() || y >= d.columnCount())
        throw std::out_of_range("Column index");
    // first stores X, second stores Y; append only after both values are valid.
    std::pair<std::vector<double>, std::vector<double>> result;
    // Each iteration represents one observation, not one independent coordinate.
    for (std::size_t i = 0; i < d.rowCount(); ++i) {
        try {
            // numericValue rejects missing/non-numeric text and requires full conversion.
            double a = d.numericValue(i, x), b = d.numericValue(i, y);
            // Conversion can accept strings such as nan/inf; finite checks reject those.
            if (!std::isfinite(a) || !std::isfinite(b))
                throw std::invalid_argument("Nonfinite data");
            // Keep the two vector indexes paired by appending the validated coordinates.
            result.first.push_back(a);
            result.second.push_back(b);
        } catch (const std::invalid_argument &) {
            // Rethrow the same error in Reject mode. In DropRow mode, append neither
            // coordinate and continue with the next row. Bounds errors are not caught.
            if (policy == InvalidPolicy::Reject)
                throw;
        }
    }
    // Empty/all-dropped input legitimately returns two empty vectors; plot or
    // statistics operations apply their own nonempty-data requirements later.
    return result;
}
}
