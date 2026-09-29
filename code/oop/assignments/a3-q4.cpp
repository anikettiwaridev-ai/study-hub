#include <iostream>
using namespace std;

void display(const int arr[], int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

// Right rotation by k: the element at index i moves to index (i + k) % n.
void rotateRight(int arr[], int n, int k) {
    k = k % n;                  // rotating by n (or 2n ...) changes nothing
    int temp[100];
    for (int i = 0; i < n; i++)
        temp[(i + k) % n] = arr[i];
    for (int i = 0; i < n; i++)
        arr[i] = temp[i];
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int n = 5, k;
    cout << "Enter K: ";
    cin >> k;
    cout << endl << "Before: ";
    display(arr, n);
    rotateRight(arr, n, k);
    cout << "After:  ";
    display(arr, n);
    return 0;
}
