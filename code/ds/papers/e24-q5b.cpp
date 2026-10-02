#include <iostream>
using namespace std;

// #region answer
bool isMaxHeap(int a[], int n) {
    for (int i = 0; i <= (n - 2) / 2; i++) {               // only nodes that have a child
        int l = 2 * i + 1, r = 2 * i + 2;
        if (l < n && a[i] < a[l]) return false;             // parent smaller than a child
        if (r < n && a[i] < a[r]) return false;
    }
    return true;
}
// #endregion answer

int main() {
    int a[] = {90, 15, 10, 7, 12, 2}, b[] = {9, 15, 10, 7, 12, 11}, c[] = {5};
    cout << isMaxHeap(a, 6) << " " << isMaxHeap(b, 6) << " " << isMaxHeap(c, 1) << endl;
    return 0;
}
