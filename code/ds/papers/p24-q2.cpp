#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

// #region answer
void candy_crush(int candies, int req[], int n) {
    queue<pair<int, int>> q;                       // (child number, candies still wanted)
    for (int i = 0; i < n; i++) q.push({i + 1, req[i]});

    while (!q.empty() && candies > 0) {
        pair<int, int> c = q.front(); q.pop();
        int take = min(5, min(c.second, candies)); // at most 5 per turn, and only what is left
        candies -= take;
        c.second -= take;
        cout << "  child " << c.first << " takes " << take << ", machine has " << candies << endl;
        if (c.second > 0) q.push(c);               // still wants more: back of the queue
    }

    if (q.empty())
        cout << "All requests fulfilled. Candies left: " << candies << endl;
    else {
        cout << "Candies ran out. Remaining requests:";
        while (!q.empty()) {
            cout << " child " << q.front().first << " (" << q.front().second << ")";
            q.pop();
        }
        cout << endl;
    }
}
// #endregion answer

int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int candies, n, req[100];
        cin >> candies >> n;
        for (int i = 0; i < n; i++) cin >> req[i];
        cout << candies << " candies, " << n << " children" << endl;
        candy_crush(candies, req, n);
    }
    return 0;
}
