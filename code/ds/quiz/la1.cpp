#include <iostream>
using namespace std;

// Lab Quiz I (2025), every blank filled in. Shared class from the paper:
class Node {
public:
    int data;
    Node* next;
    Node(int val) {
        data = val;
        next = NULL;
    }
};

class LinkedList {
public:
    Node* head = NULL;

    // #region q1
    void x(int val, int key) {             // insert val BEFORE the first key
        Node* n = new Node(val);
        if (!head) return;
        if (head->data == key)
            { n->next = head;              // blank 1
              head = n;                    // blank 2
              return; }
        Node* t = head;
        while (t->next && t->next->data != key)   // blank 3: t->next->data
            t = t->next;
        if (!t->next) return;
        n->next = t->next;
        t->next = n;
    }
    // #endregion q1

    // #region q2
    void y() {                             // remove duplicates from a SORTED list
        Node* curr = head;
        while (curr && curr->next) {
            if (curr->data == curr->next->data) {
                Node* tmp = curr->next;           // blank 1
                curr->next = curr->next->next;    // blank 2 (tmp->next also works)
                delete tmp;
            } else curr = curr->next;
        }
    }
    // #endregion q2

    // #region q4
    Node* gamma(Node* h1, Node* h2) {      // recursive merge of two sorted lists
        if (!h1) return h2;
        if (!h2) return h1;
        if (h1->data <= h2->data)          // blank 1: h2->data
            { h1->next = gamma(h1->next, h2); return h1; }
        else { h2->next = gamma(h1, h2->next); return h2; }   // blank 2: h2->next
    }
    // #endregion q4

    void print() { for (Node* t = head; t; t = t->next) cout << t->data << " "; cout << endl; }
};

// #region q3
#define SIZE 5
class CQueue {
    int arr[SIZE], front = -1, rear = -1;
public:
    void z(int val) {
        if ((front == 0 && rear == SIZE - 1) ||       // blank 1: SIZE - 1
            (rear + 1) % SIZE == front) return;       // blank 2: front  (overflow)
        if (front == -1) front = 0;
        rear = (rear + 1) % SIZE;                     // blank 3
        arr[rear] = val;
    }
    // #endregion q3
    void print() {
        if (front == -1) { cout << "empty" << endl; return; }
        for (int i = front; ; i = (i + 1) % SIZE) { cout << arr[i] << " "; if (i == rear) break; }
        cout << endl;
    }
};

int main() {
    LinkedList L;
    for (int v : {40, 30, 30, 20, 10, 10}) { Node* n = new Node(v); n->next = L.head; L.head = n; }
    L.print();
    L.y();          L.print();
    L.x(5, 10);     L.print();   // before the head
    L.x(25, 30);    L.print();   // before a middle node
    L.x(99, 77);    L.print();   // key absent: nothing happens
    LinkedList M;
    Node* a = new Node(1); a->next = new Node(4); a->next->next = new Node(9);
    Node* b = new Node(2); b->next = new Node(3);
    M.head = M.gamma(a, b);
    M.print();
    CQueue q;
    for (int v = 1; v <= 6; v++) q.z(v * 10);   // the 6th is rejected
    q.print();
    return 0;
}
