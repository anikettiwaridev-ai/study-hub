#include <iostream>
using namespace std;

int main() {
    int a[] = {13, 16, 11, 4, 12, 6, 7, 90, 67, 5, 20};
    int n = 11;
    for (int pass = 1; pass < n; pass++) {
        int swaps = 0;
        for (int j = 0; j < n - pass; j++)
            if (a[j] > a[j + 1]) { int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t; swaps++; }
        cout << "pass " << pass << ":";
        for (int i = 0; i < n; i++) cout << " " << a[i];
        cout << "  (" << swaps << " swaps)" << endl;
        if (swaps == 0) break;               // no swap in a whole pass: already sorted
    }
    return 0;
}
