// Standalone array-statistics template exercise, compiled as teaching_templates.
// Production statistics use vector-based Statistics::summarize instead. These
// helpers assume a valid array and positive n; display checks n before calling them.

// cout presents results for the two worked arrays in main.
#include <iostream>
// sqrt converts population variance into standard deviation.
#include <cmath>
using namespace std;

// Function to calculate sum
template <typename T>
// Input is the first n array values; return their total as double.
// T permits the same loop to read integer or floating-point arrays.
double sum(T data[], int n) {
    double total = 0;

    // Visit each selected element once and accumulate it in a double total.
    for (int i = 0; i < n; i++) {
        total = total + data[i];
    }

    return total;
}

// Function to calculate mean
template <typename T>
// Reuse sum, then divide by count. The caller must ensure n > 0.
double mean(T data[], int n) {
    return sum(data, n) / n;
}

// Function to find minimum
template <typename T>
// Return the smallest value using T. A first element must exist (n > 0).
T minimum(T data[], int n) {
    T small = data[0];

    // Index zero supplies the initial candidate; compare the remaining values.
    for (int i = 1; i < n; i++) {
        if (data[i] < small) {
            small = data[i];
        }
    }

    return small;
}

// Function to find maximum
template <typename T>
// Return the largest value using T. Begin with an actual element, not zero,
// so an all-negative array is handled correctly.
T maximum(T data[], int n) {
    T large = data[0];

    // Index zero supplies the initial candidate; compare the remaining values.
    for (int i = 1; i < n; i++) {
        if (data[i] > large) {
            large = data[i];
        }
    }

    return large;
}

// Function to calculate range
template <typename T>
// Return the spread between extreme values by reusing both searches.
double range(T data[], int n) {
    return maximum(data, n) - minimum(data, n);
}

// Function to calculate variance
template <typename T>
// Compute population variance: average the squared distances from the mean.
// This teaching function divides by n, not the sample-variance denominator n-1.
double variance(T data[], int n) {
    double average = mean(data, n);
    double total = 0;

    // Squaring makes positive and negative deviations contribute equally.
    for (int i = 0; i < n; i++) {
        double difference = data[i] - average;
        total = total + difference * difference;
    }

    return total / n;
}

// Function to calculate standard deviation
template <typename T>
// Standard deviation has the original data units; it is sqrt(variance).
double standardDeviation(T data[], int n) {
    return sqrt(variance(data, n));
}

// Function to display results
template <typename T>
// Guard the empty/nonpositive count before invoking helpers that index data[0]
// or divide by n, then print the available descriptive statistics.
void display(T data[], int n) {

    // Report absent data instead of calling helpers with invalid preconditions.
    if (n <= 0) {
        cout << "No data available!" << endl;
        return;
    }

    cout << "Sum: " << sum(data, n) << endl;
    cout << "Mean: " << mean(data, n) << endl;
    cout << "Minimum: " << minimum(data, n) << endl;
    cout << "Maximum: " << maximum(data, n) << endl;
    cout << "Range: " << range(data, n) << endl;
    cout << "Variance: " << variance(data, n) << endl;
    cout << "Standard Deviation: " << standardDeviation(data, n) << endl;
}

// Main function
// Compiler instantiates the same function templates for int and double arrays.
// These fixed examples satisfy the helpers' positive-length precondition.
int main() {

    int numbers[] = {10, 20, 30, 40, 50};
    double decimals[] = {2.5, 4.5, 6.5, 8.5};

    cout << "=== INTEGER DATA ===" << endl;
    display(numbers, 5);

    cout << endl;

    cout << "=== DECIMAL DATA ===" << endl;
    display(decimals, 4);

    return 0;
}
