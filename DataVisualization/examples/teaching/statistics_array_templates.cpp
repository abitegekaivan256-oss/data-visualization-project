// Preserved standalone template teaching implementation from src/Statistics.cpp.
// CMake builds it as teaching_statistics, outside the production library.
// The reusable production Summary API remains in dataviz/Statistics.h.
// The main below is this example's entry point; its algorithms are unchanged.
#include <iostream>
using namespace std;

// Calculate sum
// T supplies the array element type. data points to n readable elements.
// Return their total as double. The caller must provide a valid array/count;
// this legacy example does not perform the production finite-input checks.
template <typename T> double sum(T data[], int n) {
    double total = 0;

    // Visit each of the first n elements once and accumulate its contribution.
    for (int i = 0; i < n; i++) {
        total += data[i];
    }
    return total;
}

// Calculate mean
// Reuse sum and divide by the number of elements. The demonstration supplies
// n=5; this legacy function does not reject n=0, unlike production summarize.
template <typename T> double mean(T data[], int n) {
    return sum(data, n) / n;
}

// Find minimum
// Begin with the first element and replace it whenever a smaller one appears.
// n must be positive because data[0] is accessed before the loop.
template <typename T> T minimum(T data[], int n) {
    T min = data[0];

    // Start at one: data[0] has already supplied the initial candidate.
    for (int i = 1; i < n; i++) {
        if (data[i] < min)
            min = data[i];
    }
    return min;
}

// Find maximum
// The same search as minimum with the comparison reversed. T preserves the
// array's element type in the returned value. A valid nonempty array is required.
template <typename T> T maximum(T data[], int n) {
    T max = data[0];

    for (int i = 1; i < n; i++) {
        if (data[i] > max)
            max = data[i];
    }
    return max;
}

// Teaching entry point: instantiate the template functions with an int array
// and print their results. It uses no file loading, SVG rendering or exceptions.
// Container/array lifetime is automatic; there is no manual memory allocation.
int main() {
    // Five known values let students verify sum=150, mean=30, min=10, max=50.
    int data[] = {10, 20, 30, 40, 50};
    int n = 5;

    // Calling each function with the int array selects T=int at compile time.
    cout << "Sum: " << sum(data, n) << endl;
    cout << "Mean: " << mean(data, n) << endl;
    cout << "Minimum: " << minimum(data, n) << endl;
    cout << "Maximum: " << maximum(data, n) << endl;

    return 0;
}
