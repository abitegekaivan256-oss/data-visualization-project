// Includes the DataPreprocessor header file
#include "dataviz/DataPreprocessor.h"

#include <cmath>       // Used to check if numbers are finite
#include <stdexcept>   // Used for handling errors and exceptions

namespace dataviz {

// Function to extract valid numeric pairs from two dataset columns
std::pair< std::vector<double>, std::vector<double>>

DataPreprocessor::numericPairs
(
    const DataSet& d, 
    std::size_t x,
                               
    std::size_t y, 
    InvalidPolicy policy
)
{
    // Check whether the selected column indexes exist
    if (x >= d.columnCount() || y >= d.columnCount())

        throw std::out_of_range("Column index");

    // Create two vectors to store the valid numeric values
    std::pair< std::vector<double>, std::vector<double>> result;

    // Loop through all rows in the dataset
    for (std::size_t i = 0; i < d.rowCount(); ++i)
    {
        try
        {
            // Read numeric values from columns x and y
            double a = d.numericValue(i, x);
            double b = d.numericValue(i, y);

            // Check for invalid values such as infinity or NaN
            if (!std::isfinite(a) || !std::isfinite(b))
                throw std::invalid_argument("Nonfinite data");

            // Store valid values in their respective vectors
            result.first.push_back(a);
            result.second.push_back(b);
        }

        // Handle invalid numeric values
        catch (const std::invalid_argument&)
        {
            // Reject policy: stop processing and report the error
            // Otherwise, skip the invalid row and continue
            if (policy == InvalidPolicy::Reject)
                throw;
        }
    }

    // Return the two vectors containing valid numeric pairs
    return result;
}

}
