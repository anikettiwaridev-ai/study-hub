#include <iostream>
using namespace std;

// LEAK: the only pointer to the block dies when the function returns.
int sumLeaky(int n) {
    int *arr = new int[n];
    int sum = 0;
    for (int i = 0; i < n; i++) { arr[i] = i + 1; sum += arr[i]; }
    return sum;             // arr is lost here; the block can never be freed
}

// FIXED: the same work, and the block is released before returning.
int sumFixed(int n, int &maxValue) {
    int *arr = new int[n];
    int sum = 0;
    maxValue = 0;
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
        sum += arr[i];
        if (arr[i] > maxValue) maxValue = arr[i];
    }
    delete[] arr;           // delete[] because the block came from new[]
    return sum;
}

int main() {
    int maxValue;
    cout << "Leaky sum = " << sumLeaky(5) << " (5 ints, 20 bytes, never returned)" << endl;
    cout << "Fixed sum = " << sumFixed(5, maxValue) << ", max = " << maxValue << endl;
    // Calling sumLeaky in a loop a million times would lose about 20 MB.
    return 0;
}
