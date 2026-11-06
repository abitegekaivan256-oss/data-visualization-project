#include <iostream>
using namespace std;

// Calculate sum
template <typename T>
double sum(T data[], int n) {
    double total = 0;

    for (int i = 0; i < n; i++) {
        total += data[i];
    }
    return total;
}

// Calculate mean
template <typename T>
double mean(T data[], int n) {
    return sum(data, n) / n;
}

// Find minimum
template <typename T>
T minimum(T data[], int n) {
    T min = data[0];

    for (int i = 1; i < n; i++) {
        if (data[i] < min)
            min = data[i];
    }
    return min;
}

// Find maximum
template <typename T>
T maximum(T data[], int n) {
    T max = data[0];

    for (int i = 1; i < n; i++) {
        if (data[i] > max)
            max = data[i];
    }
    return max;
}

int main() {
    int data[] = {10, 20, 30, 40, 50};
    int n = 5;

    cout << "Sum: " << sum(data, n) << endl;
    cout << "Mean: " << mean(data, n) << endl;
    cout << "Minimum: " << minimum(data, n) << endl;
    cout << "Maximum: " << maximum(data, n) << endl;

    return 0;
}
