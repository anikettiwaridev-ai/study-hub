#include <iostream>
using namespace std;

// The Unit 3 slides' recursive binary search: it prints a[mid] AFTER the recursive call.
void BS(int a[], int s, int e, int key) {
    if (s > e) return;
    int m = (s + e) / 2;
    if (a[m] == key) {}                 // found: nothing more to do
    else if (a[m] > key) BS(a, s, m - 1, key);
    else BS(a, m + 1, e, key);
    cout << a[m] << " ";
}

// Iterative version that counts comparisons with the key.
int search(int a[], int n, int key, int &comparisons) {
    int s = 0, e = n - 1;
    comparisons = 0;
    while (s <= e) {
        int m = (s + e) / 2;
        comparisons++;
        if (a[m] == key) return m;
        if (a[m] < key) s = m + 1; else e = m - 1;
    }
    return -1;
}

int main() {
    int a[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    BS(a, 0, 9, 45);
    cout << endl;

    int c;
    search(a, 10, 50, c); cout << "find 50: " << c << " comparison(s)" << endl;   // middle element: the minimum
    search(a, 10, 100, c); cout << "find 100: " << c << " comparison(s)" << endl;
    search(a, 10, 5, c); cout << "find 5 (absent): " << c << " comparison(s)" << endl;
    return 0;
}
