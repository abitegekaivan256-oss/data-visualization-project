
#include <iostream>
#include "dataviz/AxisScale.h"

using namespace std;
using namespace dataviz;

int main() {

    cout << "AXIS SCALING TEST\n";
    cout << "====================\n";

    // Test 1: Linear scaling
    LinearScale linear(0, 100, 500);

    cout << "Scaled value of 50: "
         << linear.scale(50) << endl;

    // Test 2: Percentage scaling
    PercentageScale percentage(0, 100);

    cout << "Percentage of 50: "
         << percentage.scale(50) << "%" << endl;

    // Test 3: Polymorphism
    AxisScale* scale = &linear;

    cout << "Polymorphism - Linear: "
         << scale->scale(50) << endl;

    scale = &percentage;

    cout << "Polymorphism - Percentage: "
         << scale->scale(50) << endl;

    // Test 4: Equal minimum and maximum
    LinearScale equalScale(10, 10, 500);

    cout << "Equal range result: "
         << equalScale.scale(10) << endl;

    // Test 5: Update scaling width
    LinearScale smallerScale(0, 100, 250);

    cout << "Scaled value with width 250: "
         << smallerScale.scale(50) << endl;

    cout << "\nAll AxisScale examples completed!\n";

    return 0;
}
