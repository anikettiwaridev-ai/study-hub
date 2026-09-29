#include <iostream>
using namespace std;

// x ^ x = 0 and x ^ 0 = x, so every value that appears an even number
// of times cancels itself out. Only the odd one survives.
int oddOccurrence(const int arr[], int n) {
    int result = 0;
    for (int i = 0; i < n; i++) result ^= arr[i];
    return result;
}

int main() {
    int arr[] = {4, 3, 6, 2, 6, 4, 2, 3, 3};
    cout << "Element occurring an odd number of times: " << oddOccurrence(arr, 9) << endl;
    return 0;
}
