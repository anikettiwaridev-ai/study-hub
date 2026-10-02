#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) { data = val; next = NULL; }
};

Node *front = NULL, *rear = NULL;       // front = head (delete here), rear = tail (insert here)

// #region enqueue
void enqueue(int x) {
    Node* n = new Node(x);
    if (rear == NULL) { front = rear = n; return; }   // empty: n is both ends
    rear->next = n;                                   // link after the old rear
    rear = n;                                         // then move rear
}
// #endregion enqueue

// #region dequeue
int dequeue() {
    if (front == NULL) return -1;
    Node* t = front;
    int v = t->data;
    front = front->next;
    if (front == NULL) rear = NULL;                   // removed the last node
    delete t;
    return v;
}
// #endregion dequeue

void print() {
    cout << "queue: ";
    for (Node* t = front; t; t = t->next) cout << t->data << " ";
    cout << (rear == NULL ? "(empty, rear = NULL)" : "") << endl;
}

int main() {
    enqueue(4); print();
    cout << "dequeue " << dequeue() << endl; print();
    cout << "dequeue " << dequeue() << endl;
    enqueue(9); enqueue(5); print();
    cout << "dequeue " << dequeue() << endl; print();
    return 0;
}
