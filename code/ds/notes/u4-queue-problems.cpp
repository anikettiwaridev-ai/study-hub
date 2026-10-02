#include <iostream>
#include <queue>
#include <stack>
using namespace std;

// #region reverseQueue
void reverseQueue(queue<int>& q) {
    if (q.empty()) return;
    int x = q.front(); q.pop();         // pop() returns void: read front() first
    reverseQueue(q);
    q.push(x);
}
// #endregion reverseQueue

// #region reverseFirstK
void reverseFirstK(queue<int>& q, int k) {
    stack<int> s;
    for (int i = 0; i < k; i++) { s.push(q.front()); q.pop(); }
    while (!s.empty()) { q.push(s.top()); s.pop(); }
    int rest = q.size() - k;
    for (int i = 0; i < rest; i++) { q.push(q.front()); q.pop(); }   // cycle the others behind
}
// #endregion reverseFirstK

// #region twoStackQueue
stack<int> s1, s2;                      // s1 = inbox, s2 = outbox
void enqueue(int x) { s1.push(x); }
int dequeue() {
    if (s2.empty())                     // refill only when the outbox is empty
        while (!s1.empty()) { s2.push(s1.top()); s1.pop(); }
    if (s2.empty()) return -1;
    int v = s2.top(); s2.pop();
    return v;
}
// #endregion twoStackQueue

void show(queue<int> q) {
    while (!q.empty()) { cout << q.front() << " "; q.pop(); }
    cout << endl;
}

int main() {
    queue<int> q;
    for (int x : {1, 2, 3, 4, 5}) q.push(x);
    reverseQueue(q); show(q);
    queue<int> r;
    for (int x : {10, 20, 30, 40, 50, 60}) r.push(x);
    reverseFirstK(r, 4); show(r);
    enqueue(1); enqueue(2);
    cout << dequeue() << " ";
    enqueue(3);
    cout << dequeue() << " " << dequeue() << " " << dequeue() << endl;
    return 0;
}
