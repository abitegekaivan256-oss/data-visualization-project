
#include <iostream>
#include <cmath>
using namespace std;

// Function to calculate sum
template <typename T>
double sum(T data[], int n) {
    double total = 0;

    for (int i = 0; i < n; i++) {
        total = total + data[i];
    }

    return total;
}

// Function to calculate mean
template <typename T>
double mean(T data[], int n) {
    return sum(data, n) / n;
}

// Function to find minimum
template <typename T>
T minimum(T data[], int n) {
    T small = data[0];

    for (int i = 1; i < n; i++) {
        if (data[i] < small) {
            small = data[i];
        }
    }

    return small;
}

// Function to find maximum
template <typename T>
T maximum(T data[], int n) {
    T large = data[0];

    for (int i = 1; i < n; i++) {
        if (data[i] > large) {
            large = data[i];
        }
    }

    return large;
}

// Function to calculate range
template <typename T>
double range(T data[], int n) {
    return maximum(data, n) - minimum(data, n);
}

// Function to calculate variance
template <typename T>
double variance(T data[], int n) {
    double average = mean(data, n);
    double total = 0;

    for (int i = 0; i < n; i++) {
        double difference = data[i] - average;
        total = total + difference * difference;
    }

    return total / n;
}

// Function to calculate standard deviation
template <typename T>
double standardDeviation(T data[], int n) {
    return sqrt(variance(data, n));
}

// Function to display results
template <typename T>
void display(T data[], int n) {

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
    cout << "Standard Deviation: "
         << standardDeviation(data, n) << endl;
}

// Main function
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
