// Preserved standalone double-array statistics example. CMake builds it as
// legacy_statistics, separately from the vector-based production Statistics API.
// Helpers require a valid array with n > 0; main supplies a fixed valid example.
// cout and endl display the worked numerical results.
#include <iostream>
using namespace std;

// Calculate sum
// Read the first n elements and return their total. No ownership is transferred.
double sum(double data[], int n) {
    double total = 0;

    // Each selected value contributes once to the sum.
    for (int i = 0; i < n; i++) {
        total += data[i];
    }

    return total;
}

// Calculate mean
// Divide the total by the positive count; no empty-array guard is supplied here.
double mean(double data[], int n) {
    return sum(data, n) / n;
}

// Find minimum
// Return the smallest array value; data[0] requires a nonempty valid array.
double minimum(double data[], int n) {
    double minValue = data[0];

    // Compare all values after the first candidate and replace it when needed.
    for (int i = 1; i < n; i++) {
        if (data[i] < minValue) {
            minValue = data[i];
        }
    }

    return minValue;
}

// Find maximum
// Return the largest value. Starting with data[0] also handles negative data.
double maximum(double data[], int n) {
    double maxValue = data[0];

    // Compare all values after the first candidate and replace it when needed.
    for (int i = 1; i < n; i++) {
        if (data[i] > maxValue) {
            maxValue = data[i];
        }
    }

    return maxValue;
}

// Main program
// Demonstrate the helpers with five known values and print their range.
// Returning zero reports normal completion; the example writes no SVG files.
int main() {

    double data[] = {10, 20, 30, 40, 50};
    int n = 5;

    cout << "Sum: " << sum(data, n) << endl;
    cout << "Mean: " << mean(data, n) << endl;
    cout << "Minimum: " << minimum(data, n) << endl;
    cout << "Maximum: " << maximum(data, n) << endl;
    cout << "Range: " << maximum(data, n) - minimum(data, n) << endl;

    return 0;
}
