#include <iostream>
using namespace std;

// The textbook convention (Horowitz and Sahni, the course text): front sits one cell
// BEFORE the first element, rear ON the last. Empty: front == rear.
// Full: (rear + 1) % N == front, so one cell always stays empty and only N - 1 fit.
const int N = 5;
int Q[N], front = 0, rear = 0;

// #region enqueue
void enqueue(int x) {
    if ((rear + 1) % N == front) { cout << "Enqueue(" << x << "): overflow" << endl; return; }
    rear = (rear + 1) % N;
    Q[rear] = x;
}
// #endregion enqueue

// #region dequeue
int dequeue() {
    if (front == rear) { cout << "Dequeue(): underflow" << endl; return -1; }
    front = (front + 1) % N;
    return Q[front];
}
// #endregion dequeue

void show() {
    cout << "  front = " << front << ", rear = " << rear << ", queue:";
    for (int i = front; i != rear; ) { i = (i + 1) % N; cout << " " << Q[i]; }
    cout << endl;
}

int main() {                                    // Oct 2025 Q3
    for (int x : {10, 20, 30, 40, 50}) enqueue(x);
    show();
    cout << "removed " << dequeue() << endl;
    enqueue(60); show();
    for (int i = 0; i < 5; i++) { int v = dequeue(); if (v != -1) cout << "removed " << v << endl; }
    show();
    enqueue(70); enqueue(80);
    cout << "removed " << dequeue() << endl;
    show();
    return 0;
}
