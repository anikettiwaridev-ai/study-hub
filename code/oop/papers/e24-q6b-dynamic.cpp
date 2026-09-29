#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "enter number of elements for first loop: ";
    cin >> n;
    int *arr = new int[n];                  // exactly n slots, decided at run time
    for (int i = 0; i < n; i++) arr[i] = i;
    for (int i = 0; i < n; i++) cout << "the values of first loop are " << arr[i] << endl;
    delete[] arr;                           // give the old block back

    cout << "enter number of elements for second loop: ";
    cin >> n;
    arr = new int[n];                       // a fresh block of the new size
    for (int i = 0; i < n; i++) arr[i] = i;
    for (int i = 0; i < n; i++)             // loop to n, never past the end
        cout << "the values of second loop are " << arr[i] << endl;
    delete[] arr;
    arr = nullptr;                          // no dangling pointer left behind
    return 0;
}
