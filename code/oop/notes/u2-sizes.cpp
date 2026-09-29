#include <iostream>
using namespace std;

void inside(int arr[]) {                 // really: int *arr
    cout << "sizeof inside the function = " << sizeof(arr) << " (a pointer)" << endl;
}
void bounded(int (&arr)[4]) {            // reference to an array of exactly 4
    cout << "sizeof through int (&arr)[4] = " << sizeof(arr) << endl;
}

int main() {
    int arr[4] = {1, 2, 3, 4};
    int *p = arr;                        // the array name decays to &arr[0]
    cout << "sizeof(arr) in main = " << sizeof(arr) << " (the whole array)" << endl;
    cout << "sizeof(p) = " << sizeof(p) << " (a pointer)" << endl;
    inside(arr);
    bounded(arr);
    cout << "length = " << sizeof(arr) / sizeof(arr[0]) << endl;
    return 0;
}
