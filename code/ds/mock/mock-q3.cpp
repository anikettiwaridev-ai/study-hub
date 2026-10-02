#include <iostream>
using namespace std;

// Mock Q3: textbook convention, N = 6, so at most 5 elements.
const int N = 6;
int Q[N], front = 0, rear = 0;

void enqueue(int x) {
    if ((rear + 1) % N == front) { cout << "Enqueue(" << x << "): overflow" << endl; return; }
    rear = (rear + 1) % N; Q[rear] = x;
    cout << "Enqueue(" << x << "): rear = " << rear << endl;
}
void dequeue() {
    if (front == rear) { cout << "Dequeue(): underflow" << endl; return; }
    front = (front + 1) % N;
    cout << "Dequeue(): removes " << Q[front] << ", front = " << front << endl;
}

int main() {
    enqueue(5); enqueue(15); enqueue(25);
    dequeue(); dequeue();
    enqueue(35); enqueue(45); enqueue(55); enqueue(65); enqueue(75);
    dequeue();
    enqueue(85);
    cout << "front = " << front << ", rear = " << rear << ", queue:";
    for (int i = front; i != rear; ) { i = (i + 1) % N; cout << " " << Q[i]; }
    cout << endl;
    return 0;
}
