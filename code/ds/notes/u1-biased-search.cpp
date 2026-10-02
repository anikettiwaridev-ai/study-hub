#include <iostream>
using namespace std;

// #region answer
// Biased search: binary search with mid = (2s + e) / 3, one third of the way in.
int biasedSearch(const char a[], int n, char key) {
    int s = 0, e = n - 1;
    while (s <= e) {
        int mid = (2 * s + e) / 3;
        cout << "  s = " << s << ", e = " << e << ", mid = " << mid << ", a[mid] = " << a[mid] << endl;
        if (a[mid] == key) return mid;
        if (key > a[mid]) s = mid + 1;     // key is right of mid
        else e = mid - 1;                  // key is left of mid
    }
    return -1;                             // not present
}
// #endregion answer

int main() {
    const char sep23[] = "PQRSTUVWXYZ";       // Sep 2023 Q4
    const char oct25[] = "NOPQRSTUVWXYZ";     // Oct 2025 Q4
    cout << "Sep 2023, search X:" << endl;
    int i = biasedSearch(sep23, 11, 'X');
    cout << "found at index " << i << endl;
    cout << "Oct 2025, search X:" << endl;
    i = biasedSearch(oct25, 13, 'X');
    cout << "found at index " << i << endl;
    cout << "Oct 2025, search A (absent):" << endl;
    i = biasedSearch(oct25, 13, 'A');
    cout << "returns " << i << endl;
    return 0;
}
