#include <iostream>
using namespace std;

// Practice sheet 3, Q6. A count of stored elements tells "empty" (count == 0) from
// "full" (count == CAP), so all CAP cells are usable and front == rear is never ambiguous.
class Queue {
    static const int CAP = 5;
    int arr[CAP];
    int front = 0, rear = -1, count = 0;
public:
    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == CAP; }

    // #region enqueue
    void enqueue(int x) {
        if (isFull()) { cout << "overflow: " << x << endl; return; }
        rear = (rear + 1) % CAP;          // wraps back to 0 after CAP - 1
        arr[rear] = x;
        count++;
    }
    // #endregion enqueue

    // #region dequeue
    int dequeue() {
        if (isEmpty()) { cout << "underflow" << endl; return -1; }
        int v = arr[front];
        front = (front + 1) % CAP;
        count--;
        return v;
    }
    // #endregion dequeue

    void print() const {
        cout << "front = " << front << ", rear = " << rear << ": ";
        for (int i = 0; i < count; i++) cout << arr[(front + i) % CAP] << " ";
        cout << endl;
    }
};

int main() {
    Queue q;
    for (int x = 1; x <= 5; x++) q.enqueue(x * 10);
    q.print();
    q.dequeue(); q.dequeue();
    q.print();
    q.enqueue(60); q.enqueue(70);       // these two wrap into cells 0 and 1
    q.print();
    q.enqueue(80);                      // full
    return 0;
}
