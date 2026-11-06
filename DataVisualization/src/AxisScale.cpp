#include <iostream>
#include <stdexcept>
using namespace std;
// BASE CLASS: AxisScale
class AxisScale {
private:
    double minValue;
    double maxValue;

public:
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

    // Setter for data range
    void setRange(double min, double max) {
        if (min > max) {
            throw invalid_argument(
                "Minimum cannot exceed maximum"
            );
        }

        minValue = min;
        maxValue = max;
    }

    // Virtual function for POLYMORPHISM
    virtual double scale(double value) const = 0;

    // Virtual destructor
    virtual ~AxisScale() = default;
};
// DERIVED CLASS 1: LinearScale
class LinearScale : public AxisScale {
private:
    double screenWidth;

public:
    // Constructor
    LinearScale(double min, double max, double width)
        : AxisScale(min, max) {
        screenWidth = width;
    }

    // Override scale() function
    double scale(double value) const override {

        double min = getMin();
        double max = getMax();

        // Handle equal minimum and maximum
        if (min == max) {
            return screenWidth / 2.0;
        }

        // Linear scaling formula
        return ((value - min) / (max - min))
               * screenWidth;
    }
};
// DERIVED CLASS 2: PercentageScale
class PercentageScale : public AxisScale {
public:
    // Constructor
    PercentageScale(double min, double max)
        : AxisScale(min, max) {}

    // Override scale() function
    double scale(double value) const override {

        double min = getMin();
        double max = getMax();

        // Handle equal minimum and maximum
        if (min == max) {
            return 50.0;
        }

        // Percentage scaling formula
        return ((value - min) / (max - min))
               * 100.0;
    }
};
int main() {

    cout << "====================================" << endl;
    cout << " DATA VISUALIZATION LIBRARY IN C++" << endl;
    cout << " AXIS SCALING MODULE - BONIUS" << endl;
    cout << "====================================" << endl;
    cout << "\n--- ENCAPSULATION ---" << endl;

    LinearScale linear(0, 100, 500);

    cout << "Minimum value: "
         << linear.getMin() << endl;

    cout << "Maximum value: "
         << linear.getMax() << endl;
    cout << "\n--- INHERITANCE ---" << endl;

    cout << "Linear scaling of 50: "
         << linear.scale(50) << endl;

    PercentageScale percentage(0, 100);

    cout << "Percentage scaling of 50: "
         << percentage.scale(50) << "%" << endl;

    cout << "\n--- POLYMORPHISM ---" << endl;

    AxisScale* scaler;

    // Base-class pointer to LinearScale
    scaler = &linear;

    cout << "Linear position: "
         << scaler->scale(50) << endl;

    // Same pointer to PercentageScale
    scaler = &percentage;

    cout << "Percentage position: "
         << scaler->scale(50) << "%" << endl;

    cout << "\n--- EDGE CASE TESTING ---" << endl;

    LinearScale equalRange(20, 20, 500);

    cout << "Equal minimum and maximum: "
         << equalRange.scale(20) << endl;

    cout << "\n--- RANGE UPDATE ---" << endl;

 linear.setRange(0, 200);

    cout << "Updated maximum value: "
         << linear.getMax() << endl;

    cout << "New scaled position of 50: "
         << linear.scale(50) << endl;

    cout << "\nProgram executed successfully!" << endl;

    return 0;
}