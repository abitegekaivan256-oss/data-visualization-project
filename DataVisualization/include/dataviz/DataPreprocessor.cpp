#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Base class
class DataPreprocessor {
private:   vector<double> data;

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
class InvalidValuePreprocessor : public DataPreprocessor {

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

