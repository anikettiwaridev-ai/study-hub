#include <iostream>
using namespace std;

// When a duplicate of arr[i] is found at j, shift everything after j one
// place left and shrink the size. Returns the new size.
int removeDuplicates(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; ) {
            if (arr[j] == arr[i]) {
                for (int k = j; k < n - 1; k++) arr[k] = arr[k + 1];
                n--;                         // one element fewer; do not move j
            } else {
                j++;
            }
        }
    }
    return n;
}

int main() {
    int n, arr[100];
    cout << "How many elements? ";
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];
    n = removeDuplicates(arr, n);
    cout << endl << "Modified array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl << "New size: " << n << endl;
    return 0;
}
