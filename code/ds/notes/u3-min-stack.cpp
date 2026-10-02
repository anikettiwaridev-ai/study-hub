#include <iostream>
#include <stack>
using namespace std;

stack<int> s, mn;                     // mn.top() is always the current minimum

// #region minstack
void push(int x) {
    s.push(x);
    if (mn.empty() || x <= mn.top()) mn.push(x);   // <= so duplicates of the minimum are kept
}
void pop() {
    if (s.empty()) return;
    if (s.top() == mn.top()) mn.pop();
    s.pop();
}
int getMin() { return mn.empty() ? -1 : mn.top(); }
// #endregion minstack

int main() {
    for (int x : {5, 3, 7, 3}) push(x);
    cout << "min " << getMin() << endl;
    pop(); cout << "after pop: min " << getMin() << endl;
    pop(); pop(); cout << "after two more pops: min " << getMin() << endl;
    return 0;
}
