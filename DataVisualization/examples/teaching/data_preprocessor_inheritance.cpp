// Standalone preprocessing teaching program. These stateful global classes
// are separate from production dataviz::DataPreprocessor::numericPairs, whose
// Reject/DropRow policy does not replace invalid entries with zero.
// Terminal output illustrates which virtual implementation runs.
#include <iostream>
// vector<double> owns a resizable numerical sequence for each processor.
#include <vector>
// isnan/isfinite detect missing/nonfinite values; NAN/INFINITY provide examples.
#include <cmath>
using namespace std;

// Base class
class DataPreprocessor {
    // Private storage demonstrates encapsulation. Derived classes use public
    // getData/setData instead of directly accessing the vector.
  private:
    vector<double> data;

  public:
    // Store a copy of the supplied values. This teaching setter does not validate.
    void setData(vector<double> values) {
        data = values;
    }

    // Return a copy so cleaning a local vector does not silently mutate data.
    vector<double> getData() const {
        return data;
    }

    // The concrete base implementation only prints a message. Derived classes
    // override this virtual operation with their own cleaning rules.
    virtual void preprocessData() {
        cout << "General data preprocessing" << endl;
    }

    // Safe virtual destruction; vector automatically releases its storage.
    virtual ~DataPreprocessor() = default;
};

// Derived class 1
class MissingValuePreprocessor : public DataPreprocessor {

  public:
    // Clean the copied vector, then explicitly store the changed copy back.
    // override checks this method against the base virtual declaration.
    void preprocessData() override {
        cout << "Handling missing values..." << endl;

        vector<double> values = getData();

        // A reference lets the loop change the current element of the local copy.
        for (double &x : values) {
            // NaN represents the example's missing value; replace it with zero.
            // Infinity is not NaN and is handled by the other processor below.
            if (isnan(x)) {
                x = 0;
            }
        }

        // Commit the cleaned local copy; changing only values would not update data.
        setData(values);
    }
};

// Derived class 2
class InvalidValuePreprocessor : public DataPreprocessor {

  public:
    // Clean the copied vector, then explicitly store the changed copy back.
    // override checks this method against the base virtual declaration.
    void preprocessData() override {
        cout << "Handling invalid values..." << endl;

        vector<double> values = getData();

        // A reference lets the loop change the current element of the local copy.
        for (double &x : values) {
            // Both infinities and NaN are nonfinite, so this rule replaces either.
            if (!isfinite(x)) {
                x = 0;
            }
        }

        // Commit the cleaned local copy; changing only values would not update data.
        setData(values);
    }
};

// Prepare two small examples and dispatch through one non-owning base pointer.
// Objects live on the stack; no manual allocation or deletion is needed.
int main() {

    MissingValuePreprocessor missing;
    InvalidValuePreprocessor invalid;

    missing.setData({10, NAN, 30});
    invalid.setData({20, INFINITY, 40});

    // Virtual dispatch follows the actual derived object, not the pointer type.
    // Runtime polymorphism
    DataPreprocessor *processor;

    processor = &missing;
    processor->preprocessData();

    processor = &invalid;
    processor->preprocessData();

    cout << "\nCleaned missing-value data: ";
    // Read back the cleaned values for verification by terminal output.
    for (double x : missing.getData()) {
        cout << x << " ";
    }

    cout << "\nCleaned invalid-value data: ";
    // The invalid-value processor has replaced the infinite example with zero.
    for (double x : invalid.getData()) {
        cout << x << " ";
    }

    cout << endl;

    return 0;
}
