#include <iostream>
using namespace std;

int main() {
    int n = 3, used = 0;
    int *arr = new int[n];
    cout << "Enter numbers (0 to stop): ";

    int x;
    while (cin >> x && x != 0) {
        if (used == n) {                          // full: grow from n to 2n
            int *bigger = new int[2 * n];
            for (int i = 0; i < used; i++)        // copy the old elements
                bigger[i] = arr[i];
            delete[] arr;                         // release the old block
            arr = bigger;                         // point at the new one
            n = 2 * n;
            cout << "\n[grew to " << n << "] ";
        }
        arr[used++] = x;
    }

    cout << "\nStored " << used << " elements in capacity " << n << ": ";
    for (int i = 0; i < used; i++) cout << arr[i] << " ";
    cout << endl;
    delete[] arr;
    return 0;
}
