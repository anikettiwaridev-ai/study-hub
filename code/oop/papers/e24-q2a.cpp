#include <iostream>
using namespace std;

int main() {
    int arr[10];
    cout << "Enter 10 elements: ";
    for (int i = 0; i < 10; i++) cin >> arr[i];

    // Positions counted from 1: position 1 and 2 swap, 3 and 4 swap, and so on.
    // In index terms that is arr[0] with arr[1], arr[2] with arr[3] ...
    for (int i = 0; i + 1 < 10; i += 2) {
        int temp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = temp;
    }

    cout << "After swapping: ";
    for (int i = 0; i < 10; i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
}
