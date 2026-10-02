#include <iostream>
#include <stack>
using namespace std;

// #region insertAtBottom
void insertAtBottom(stack<int>& s, int x) {
    if (s.empty()) { s.push(x); return; }
    int t = s.top(); s.pop();
    insertAtBottom(s, x);
    s.push(t);
}
// #endregion insertAtBottom

// #region reverseStack
void reverseStack(stack<int>& s) {
    if (s.empty()) return;
    int t = s.top(); s.pop();
    reverseStack(s);            // reverse the rest FIRST
    insertAtBottom(s, t);       // then the old top goes to the bottom
}
// #endregion reverseStack

// #region sortStack
void sortedInsert(stack<int>& s, int x) {      // keeps the largest on top
    if (s.empty() || s.top() <= x) { s.push(x); return; }
    int t = s.top(); s.pop();
    sortedInsert(s, x);
    s.push(t);
}
void sortStack(stack<int>& s) {
    if (s.empty()) return;
    int t = s.top(); s.pop();
    sortStack(s);
    sortedInsert(s, t);
}
// #endregion sortStack

// #region deleteMiddle
void deleteMiddle(stack<int>& s, int k) {      // call with k = s.size() / 2
    if (k == 0) { s.pop(); return; }
    int t = s.top(); s.pop();
    deleteMiddle(s, k - 1);
    s.push(t);
}
// #endregion deleteMiddle

void show(stack<int> s) {                      // a copy, printed top first
    cout << "top -> ";
    while (!s.empty()) { cout << s.top() << " "; s.pop(); }
    cout << endl;
}

int main() {
    stack<int> s;
    for (int x : {1, 2, 3, 4}) s.push(x);
    show(s);
    reverseStack(s); show(s);
    stack<int> u;
    for (int x : {5, 1, 4, 2, 3}) u.push(x);
    show(u);
    sortStack(u); show(u);
    stack<int> m;
    for (int x : {1, 2, 3, 4, 5}) m.push(x);
    deleteMiddle(m, m.size() / 2); show(m);
    return 0;
}
