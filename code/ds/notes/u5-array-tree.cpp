#include <iostream>
using namespace std;

// The slides' array example: root at 0, children of i at 2i+1 and 2i+2, parent at (i-1)/2.
const int N = 13;
char t[N] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', '-', '-', 'H', 'I', '-', 'J'};   // '-' = empty cell

// #region arrayPreorder
void preorder(int i) {
    if (i >= N || t[i] == '-') return;      // past the array, or an empty cell: no node
    cout << t[i] << " ";
    preorder(2 * i + 1);
    preorder(2 * i + 2);
}
// #endregion arrayPreorder

int main() {
    for (int i = 0; i < N; i++) {
        if (t[i] == '-') continue;
        cout << t[i] << " at " << i << ": parent ";
        if (i == 0) cout << "none"; else cout << t[(i - 1) / 2];
        int l = 2 * i + 1, r = 2 * i + 2;
        cout << ", left " << (l < N && t[l] != '-' ? t[l] : '-');
        cout << ", right " << (r < N && t[r] != '-' ? t[r] : '-') << endl;
    }
    cout << "Preorder from the array: ";
    preorder(0);
    cout << endl;
    return 0;
}
