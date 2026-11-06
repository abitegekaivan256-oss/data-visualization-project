// Includes the DataPreprocessor header file
#include "dataviz/DataPreprocessor.h"

#include <cmath>       // Used to check if numbers are finite
#include <stdexcept>   // Used for handling errors and exceptions

namespace dataviz {

// Function to extract valid numeric pairs from two dataset columns
std::pair<std::vector<double>, std::vector<double>>
DataPreprocessor::numericPairs(const DataSet& d, std::size_t x,
                               std::size_t y, InvalidPolicy policy)
{
    // Check whether the selected column indexes exist
    if (x >= d.columnCount() || y >= d.columnCount())
        throw std::out_of_range("Column index");

    // Create two vectors to store the valid numeric values
    std::pair<std::vector<double>, std::vector<double>> result;

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

} // End of dataviz namespace
/* #include "dataviz/DataPreprocessor.h"
#include <cmath>
#include <stdexcept>
namespace dataviz {
std::pair<std::vector<double>,std::vector<double>> DataPreprocessor::numericPairs(const DataSet& d,std::size_t x,std::size_t y,InvalidPolicy policy){
if(x>=d.columnCount()||y>=d.columnCount()) throw std::out_of_range("Column index");
std::pair<std::vector<double>,std::vector<double>> result;
for(std::size_t i=0;i<d.rowCount();++i){
try {
double a=d.numericValue(i,x),b=d.numericValue(i,y);
if(!std::isfinite(a)||!std::isfinite(b)) throw std::invalid_argument("Nonfinite data");
result.first.push_back(a);result.second.push_back(b);
} catch(const std::invalid_argument&){if(policy==InvalidPolicy::Reject) throw;}
}
return result;
}
}

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Base class
class DataPreprocessor {
private:   
vector<double> data;

public:
    void setData(vector<double> values) 
    {
         data = values;
    }

    vector<double> getData() const {
        return data;
    }

    virtual void preprocessData() 
    {
        cout << "General data preprocessing" << endl;
    }

    virtual ~DataPreprocessor() = default;
};

// Derived class 1
class MissingValuePreprocessor : public DataPreprocessor {

public:
    void preprocessData() override
    {
        cout << "Handling missing values..." << endl;

        vector<double> values = getData();

        for (double &x : values)
        {
            if (isnan(x)) 
            {
                x = 0;
            }
        }

        setData(values);
    }
};

// Derived class 2
class InvalidValuePreprocessor : public DataPreprocessor 
{

public:
    void preprocessData() override 
    {
        cout << "Handling invalid values..." << endl;

        vector<double> values = getData();

        for (double &x : values) 
        {
            if (!isfinite(x)) 
            {
                x = 0;
            }
        }

        setData(values);
    }
};

int main() 
{

    MissingValuePreprocessor missing;
    InvalidValuePreprocessor invalid;

    missing.setData({10, NAN, 30});
    invalid.setData({20, INFINITY, 40});

    // Runtime polymorphism
    DataPreprocessor* processor;

    processor = &missing;
    processor->preprocessData();

    processor = &invalid;
    processor->preprocessData();

    cout << "\nCleaned missing-value data: ";
    for (double x : missing.getData()) 
    {
        cout << x << " ";
    }

    cout << "\nCleaned invalid-value data: ";
    for (double x : invalid.getData()) 
    {
        cout << x << " ";
    }

    cout << endl;

    return 0;
}


 */