#include <iostream>
#include <stack>
#include <queue>
using namespace std;

long ops;                                   // counts pushes and pops

// (a) reverse a stack with recursion, using only push/pop
void insertAtBottom(stack<int>& s, int x) {
    if (s.empty()) { s.push(x); ops++; return; }
    int t = s.top(); s.pop(); ops++;
    insertAtBottom(s, x);
    s.push(t); ops++;
}
void reverseStack(stack<int>& s) {
    if (s.empty()) return;
    int t = s.top(); s.pop(); ops++;
    reverseStack(s);
    insertAtBottom(s, t);
}

// (c) reverse a queue using one other queue and nothing else
void reverseWithQueue(queue<int>& q) {
    queue<int> r;
    while (!q.empty()) {
        for (size_t i = 1; i < q.size(); i++) { q.push(q.front()); q.pop(); ops += 2; }   // bring the last to the front
        r.push(q.front()); q.pop(); ops += 2;                                             // move it across
    }
    swap(q, r);
}

int main() {
    for (int n : {4, 8, 16, 32}) {
        stack<int> s; queue<int> q;
        for (int i = 1; i <= n; i++) { s.push(i); q.push(i); }
        ops = 0; reverseStack(s);     long a = ops;
        ops = 0; reverseWithQueue(q); long c = ops;
        cout << "n = " << n << ": stack reverse " << a << " ops, queue reverse " << c
             << " ops, front of queue now " << q.front() << ", top of stack now " << s.top() << endl;
    }
    return 0;
}
