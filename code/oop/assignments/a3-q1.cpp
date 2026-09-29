#include <iostream>
using namespace std;

// Returns the index of the first occurrence of key, or -1.
int search(const int arr[], int size, int key) {
    for (int i = 0; i < size; i++)
        if (arr[i] == key) return i;     // first match: stop immediately
    return -1;
}

int main() {
    int arr[] = {7, 3, 9, 3, 5};
    int size = sizeof(arr) / sizeof(arr[0]);   // works here, in main, not inside search
    cout << "search 3 -> " << search(arr, size, 3) << endl;
    cout << "search 5 -> " << search(arr, size, 5) << endl;
    cout << "search 8 -> " << search(arr, size, 8) << endl;
    return 0;
}
