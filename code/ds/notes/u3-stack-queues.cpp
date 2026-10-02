#include <iostream>
#include <queue>
using namespace std;

// Stack from two queues, push-costly version: q1's front is always the stack's top.
// #region pushCostly
queue<int> q1, q2;
void push(int x) {                       // O(n)
    q2.push(x);                          // the newcomer goes in first...
    while (!q1.empty()) { q2.push(q1.front()); q1.pop(); }   // ...then everyone older behind it
    swap(q1, q2);
}
int pop() {                              // O(1)
    if (q1.empty()) return -1;
    int v = q1.front(); q1.pop();
    return v;
}
// #endregion pushCostly

// Pop-costly version: push is one enqueue; pop moves n-1 elements across.
// #region popCostly
queue<int> a, b;
void push2(int x) { a.push(x); }          // O(1)
int pop2() {                              // O(n)
    if (a.empty()) return -1;
    while (a.size() > 1) { b.push(a.front()); a.pop(); }   // all but the newest
    int v = a.front(); a.pop();           // the newest is the stack's top
    swap(a, b);
    return v;
}
// #endregion popCostly

int main() {
    for (int x : {1, 2, 3, 4}) push(x);
    for (int i = 0; i < 5; i++) cout << pop() << " ";
    cout << endl;
    for (int x : {1, 2, 3, 4}) push2(x);
    for (int i = 0; i < 5; i++) cout << pop2() << " ";
    cout << endl;
    return 0;
}
