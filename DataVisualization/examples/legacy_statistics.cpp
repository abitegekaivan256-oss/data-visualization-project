#include <iostream>
using namespace std;

// Calculate sum
double sum(double data[], int n) {
    double total = 0;

    for (int i = 0; i < n; i++) {
        total += data[i];
    }

    return total;
}

// Calculate mean
double mean(double data[], int n) {
    return sum(data, n) / n;
}

// Find minimum
double minimum(double data[], int n) {
    double minValue = data[0];

    for (int i = 1; i < n; i++) {
        if (data[i] < minValue) {
            minValue = data[i];
        }
    }

    return minValue;
}

// Find maximum
double maximum(double data[], int n)
{
    double maxValue = data[0];

    for (int i = 1; i < n; i++) {
        if (data[i] > maxValue)
        {
            maxValue = data[i];
        }
    }

    return maxValue;
}

// Main program
int main() {

    double data[] = {10, 20, 30, 40, 50};
    int n = 5;

    cout << "Sum: " << sum(data, n) << endl;
    cout << "Mean: " << mean(data, n) << endl;
    cout << "Minimum: " << minimum(data, n) << endl;
    cout << "Maximum: " << maximum(data, n) << endl;
    cout << "Range: "
         << maximum(data, n) - minimum(data, n)
         << endl;

    return 0;
}
