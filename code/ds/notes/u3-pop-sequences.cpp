#include <iostream>
#include <stack>
using namespace std;

// #region possible
// 1..n are pushed in order with pops allowed at any time. Can `out` be the pop order?
bool possible(const int out[], int n) {
    stack<int> s;
    int next = 1;                                    // next number waiting to be pushed
    for (int i = 0; i < n; i++) {
        while (next <= out[i]) s.push(next++);       // push until out[i] has been pushed
        if (s.top() != out[i]) return false;         // it is buried: impossible
        s.pop();
    }
    return true;
}
// #endregion possible

int main() {
    int tests[][5] = {{2, 1, 5, 4, 3}, {3, 4, 2, 1, 5}, {4, 5, 3, 1, 2}, {1, 3, 2, 5, 4},
                      {3, 5, 4, 1, 2}, {1, 3, 5, 4, 2}, {4, 2, 3, 1, 5}};
    for (auto& t : tests) {
        for (int x : t) cout << x << " ";
        cout << "-> " << (possible(t, 5) ? "possible" : "impossible") << endl;
    }
    return 0;
}
