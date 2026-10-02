#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) { data = val; next = NULL; }
};

// A circular list kept by its TAIL: tail->next is the head, so both ends are O(1).
// #region insertEnd
void insertEnd(Node*& tail, int x) {
    Node* n = new Node(x);
    if (tail == NULL) { n->next = n; tail = n; return; }   // one node points to itself
    n->next = tail->next;      // new node points at the head
    tail->next = n;            // old tail points at the new node
    tail = n;                  // the new node is the tail
}
// #endregion insertEnd

// #region printList
void printList(Node* tail) {
    if (tail == NULL) { cout << "List empty" << endl; return; }
    Node* t = tail->next;      // start at the head
    do {
        cout << t->data << " ";
        t = t->next;
    } while (t != tail->next); // stop when we are back at the head
    cout << endl;
}
// #endregion printList

// #region josephus
// Removes every k-th node until one is left. Returns the survivor.
int josephus(Node*& tail, int k) {
    Node* prev = tail;                     // node before the current one
    while (prev->next != prev) {           // more than one node left
        for (int i = 1; i < k; i++) prev = prev->next;
        Node* victim = prev->next;
        cout << "removes " << victim->data << endl;
        prev->next = victim->next;
        if (victim == tail) tail = prev;
        delete victim;
    }
    tail = prev;
    return prev->data;
}
// #endregion josephus

int main() {
    Node* tail = NULL;
    printList(tail);
    for (int i = 1; i <= 7; i++) insertEnd(tail, i);
    printList(tail);
    cout << "head = " << tail->next->data << ", tail = " << tail->data << endl;
    int s = josephus(tail, 3);
    cout << "survivor: " << s << endl;
    delete tail;
    return 0;
}
