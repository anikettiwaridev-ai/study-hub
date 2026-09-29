#include <iostream>
using namespace std;

// Does value already appear in arr[0 .. n-1]?
bool exists(const int arr[], int n, int value) {
    for (int i = 0; i < n; i++)
        if (arr[i] == value) return true;
    return false;
}

// Keeps the first copy of each value. Returns the new size.
int removeDuplicates(int arr[], int n) {
    int newSize = 0;
    for (int i = 0; i < n; i++) {
        if (!exists(arr, newSize, arr[i]))   // not in the kept part yet
            arr[newSize++] = arr[i];
    }
    return newSize;
}

void display(const int arr[], int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int n;
    cout << "How many elements? ";
    cin >> n;
    int arr[100];
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << endl << "Original: ";
    display(arr, n);
    n = removeDuplicates(arr, n);
    cout << "Without duplicates: ";
    display(arr, n);
    return 0;
}
