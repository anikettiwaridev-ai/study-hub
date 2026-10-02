#include <iostream>
using namespace std;

class node {
public:
    int priority;
    int key;
    int value;
    node* next;
    node(int p, int k, int v) {
        priority = p;
        key = k;
        value = v;
        next = NULL;
    }
};

class PQ {
public:
    node* head;
    node* tail;
    PQ() {
        head = NULL;
        tail = NULL;
    }
    void ENQUEUE(int p, int k, int v);
    void DEQUEUE();
    void display();
};

// #region answer
void PQ::ENQUEUE(int p, int k, int v) {
    node* n = new node(p, k, v);
    if (head == NULL) {                        // case 1: empty queue
        head = tail = n;
        return;
    }
    if (p > head->priority) {                  // case 2: higher than everyone: new head
        n->next = head;
        head = n;
        return;
    }
    node* t = head;                            // case 3: walk past every node with priority >= p
    while (t->next != NULL && t->next->priority >= p)
        t = t->next;                           // >= keeps equal priorities first-come first-served
    n->next = t->next;
    t->next = n;
    if (n->next == NULL) tail = n;             // inserted at the end: move tail
}
// #endregion answer

void PQ::DEQUEUE() {                           // the highest priority is always at the head
    if (head == NULL) { cout << "Underflow" << endl; return; }
    node* t = head;
    cout << "dequeued key " << t->key << " (priority " << t->priority << ")" << endl;
    head = head->next;
    if (head == NULL) tail = NULL;
    delete t;
}

void PQ::display() {
    for (node* t = head; t; t = t->next) cout << "[p" << t->priority << " k" << t->key << " v" << t->value << "] ";
    cout << " tail = k" << (tail ? tail->key : -1) << endl;
}

int main() {
    PQ q;
    q.ENQUEUE(3, 1, 100);
    q.ENQUEUE(5, 2, 200);     // new head
    q.ENQUEUE(1, 3, 300);     // new tail
    q.ENQUEUE(3, 4, 400);     // ties with key 1: goes after it
    q.ENQUEUE(4, 5, 500);     // middle
    q.display();
    q.DEQUEUE();
    q.display();
    return 0;
}
