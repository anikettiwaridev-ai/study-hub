#include <iostream>
using namespace std;

void modify(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) *(arr + i) *= 2;   // even index: times 2
        else            *(arr + i) *= 3;   // odd index: times 3
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    modify(arr, 6);                        // the array name is already a pointer to arr[0]
    for (int i = 0; i < 6; i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
}
