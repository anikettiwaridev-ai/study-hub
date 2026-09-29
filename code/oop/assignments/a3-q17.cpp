#include <iostream>
using namespace std;

// Defaults are filled from the RIGHT: end may be omitted alone, or both.
// end = -1 means "the last element".
int sumBetween(const int arr[], int n, int start = 0, int end = -1) {
    if (end == -1 || end >= n) end = n - 1;
    int sum = 0;
    for (int i = start; i <= end; i++) sum += arr[i];
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    cout << "Whole array:        " << sumBetween(arr, 6) << endl;        // start 0, end last
    cout << "From index 2:       " << sumBetween(arr, 6, 2) << endl;     // end defaults
    cout << "Index 1 to 3:       " << sumBetween(arr, 6, 1, 3) << endl;  // nothing defaulted
    return 0;
}
