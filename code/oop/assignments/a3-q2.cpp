#include <iostream>
#include <climits>
using namespace std;

// One pass, no sorting: keep the largest and the second largest seen so far.
int secondLargest(const int arr[], int n) {
    int first = INT_MIN, second = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (arr[i] > first) {            // new largest: old largest becomes second
            second = first;
            first = arr[i];
        } else if (arr[i] > second && arr[i] != first) {   // "distinct": skip copies of the largest
            second = arr[i];
        }
    }
    return second;                       // INT_MIN means there is no second distinct value
}

int main() {
    int a[] = {12, 35, 1, 35, 10, 34};
    int b[] = {5, 5, 5};
    int r = secondLargest(a, 6);
    cout << "Second largest distinct = " << r << endl;
    r = secondLargest(b, 3);
    if (r == INT_MIN) cout << "No second distinct element" << endl;
    return 0;
}
