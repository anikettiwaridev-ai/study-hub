#include <iostream>
#include <stack>
using namespace std;

// #region nextGreater
void nextGreater(int a[], int n, int res[]) {
    stack<int> s;                                 // candidates, scanned right to left
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && s.top() <= a[i]) s.pop();   // not greater: can never be an answer again
        res[i] = s.empty() ? -1 : s.top();
        s.push(a[i]);
    }
}
// #endregion nextGreater

int main() {
    int a[] = {6, 2, 9, 3, 3, 1, 8}, res[7];
    nextGreater(a, 7, res);
    for (int i = 0; i < 7; i++) cout << a[i] << " -> " << res[i] << endl;
    return 0;
}
