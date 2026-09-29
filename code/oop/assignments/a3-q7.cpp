#include <iostream>
using namespace std;

int *allocate(int n) { return new int[n]; }                    // i.

void readArray(int *arr, int n) { for (int i = 0; i < n; i++) cin >> arr[i]; }
void display(const int *arr, int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

void release(int *&arr) {           // reference to the pointer, so we can null it
    delete[] arr;                   // iii. give the memory back
    arr = nullptr;                  // v.   no dangling pointer left
}

int main() {
    int n;
    cout << "n = ";
    cin >> n;
    int *arr = allocate(n);
    cout << "Elements: ";
    readArray(arr, n);              // ii.
    cout << endl << "Array: ";
    display(arr, n);

    release(arr);

    // iv. Using the pointer after delete[] is undefined behaviour (see the
    // separate dangling-pointer program). With nullptr we can CHECK first:
    if (arr == nullptr)
        cout << "Pointer is null: the program knows the memory is gone" << endl;
    else
        display(arr, n);
    return 0;
}
