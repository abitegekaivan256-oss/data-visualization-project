// Standalone historical axis-scaling teaching program with its own main().
// Its global types differ from the validated production dataviz classes in
// AxisScale.h and src/AxisScale.cpp. CMake builds this as a separate legacy target.
// cout/endl display the worked scaling examples in the terminal.
#include <iostream>
// invalid_argument reports reversed minimum/maximum limits.
#include <stdexcept>
using namespace std;
// BASE CLASS: AxisScale
class AxisScale {
  private:
    // Encapsulation keeps the current data range behind accessors/setRange.
    double minValue;
    double maxValue;

  public:
    // Establish the initial range by reusing the same validation as updates.
    // Constructor
    AxisScale(double min, double max) {
        setRange(min, max);
    }

    // Getter for minimum value
    double getMin() const {
        return minValue;
    }

    // Getter for maximum value
    double getMax() const {
        return maxValue;
    }

    // Accept ordered limits and replace the stored range. This teaching version
    // only rejects reversed limits; production scaling also checks finiteness.
    // Setter for data range
    void setRange(double min, double max) {
        if (min > max) {
            throw invalid_argument("Minimum cannot exceed maximum");
        }

        minValue = min;
        maxValue = max;
    }

    // Pure virtual (=0) makes AxisScale abstract. A derived class decides which
    // output range to use when the caller invokes scale through AxisScale*.
    // Virtual function for POLYMORPHISM
    virtual double scale(double value) const = 0;

    // Enables safe derived destruction through the base interface.
    // Virtual destructor
    virtual ~AxisScale() = default;
};
// DERIVED CLASS 1: LinearScale
class LinearScale : public AxisScale {
  private:
    // Output span used by this linear mapping; this example does not validate it.
    double screenWidth;

  public:
    // Constructor
    LinearScale(double min, double max, double width) : AxisScale(min, max) {
        screenWidth = width;
    }

    // Input: one data value. Output: its normalized distance/percentage.
    // override checks that the derived signature matches the abstract contract.
    // Override scale() function
    double scale(double value) const override {

        double min = getMin();
        double max = getMax();

        // A constant range has no nonzero denominator. Place it at the output
        // midpoint instead of dividing by zero.
        // Handle equal minimum and maximum
        if (min == max) {
            return screenWidth / 2.0;
        }

        // Subtracting min shifts the range to zero, division normalizes it,
        // and multiplication expands the fraction to the desired pixel span.
        // Linear scaling formula
        return ((value - min) / (max - min)) * screenWidth;
    }
};
// DERIVED CLASS 2: PercentageScale
class PercentageScale : public AxisScale {
  public:
    // Constructor
    PercentageScale(double min, double max) : AxisScale(min, max) {
    }

    // Input: one data value. Output: its normalized distance/percentage.
    // override checks that the derived signature matches the abstract contract.
    // Override scale() function
    double scale(double value) const override {

        double min = getMin();
        double max = getMax();

        // A constant range has no nonzero denominator. Place it at the output
        // midpoint instead of dividing by zero.
        // Handle equal minimum and maximum
        if (min == max) {
            return 50.0;
        }

        // The same normalized fraction becomes a percentage by multiplying by 100.
        // This function does not clamp values outside the chosen data range.
        // Percentage scaling formula
        return ((value - min) / (max - min)) * 100.0;
    }
};
// Demonstrate constructors, base-pointer dispatch, a constant range and a range
// update using stack objects. These are printed examples rather than assertions.
int main() {

    cout << "====================================" << endl;
    cout << " DATA VISUALIZATION LIBRARY IN C++" << endl;
    cout << " AXIS SCALING MODULE - BONIUS" << endl;
    cout << "====================================" << endl;
    cout << "\n--- ENCAPSULATION ---" << endl;

    LinearScale linear(0, 100, 500);

    cout << "Minimum value: " << linear.getMin() << endl;

    cout << "Maximum value: " << linear.getMax() << endl;
    cout << "\n--- INHERITANCE ---" << endl;

    cout << "Linear scaling of 50: " << linear.scale(50) << endl;

    PercentageScale percentage(0, 100);

    cout << "Percentage scaling of 50: " << percentage.scale(50) << "%" << endl;

    cout << "\n--- POLYMORPHISM ---" << endl;

    // Non-owning pointer: it refers to existing objects and requires no delete.
    AxisScale *scaler;

    // Base-class pointer to LinearScale
    scaler = &linear;

    cout << "Linear position: " << scaler->scale(50) << endl;

    // Same pointer to PercentageScale
    scaler = &percentage;

    cout << "Percentage position: " << scaler->scale(50) << "%" << endl;

    cout << "\n--- EDGE CASE TESTING ---" << endl;

    LinearScale equalRange(20, 20, 500);

    cout << "Equal minimum and maximum: " << equalRange.scale(20) << endl;

    cout << "\n--- RANGE UPDATE ---" << endl;

    linear.setRange(0, 200);

    cout << "Updated maximum value: " << linear.getMax() << endl;

    cout << "New scaled position of 50: " << linear.scale(50) << endl;

    cout << "\nProgram executed successfully!" << endl;

    return 0;
}