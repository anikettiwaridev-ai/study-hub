#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) { data = val; next = NULL; }
};

// #region insertFront
void insertFront(Node*& head, int x) {     // Node*& : the function can change main's head
    Node* n = new Node(x);
    n->next = head;                        // link first
    head = n;                              // then move head
}
// #endregion insertFront

// #region insertEnd
void insertEnd(Node*& head, int x) {
    Node* n = new Node(x);
    if (head == NULL) { head = n; return; }    // empty list: the new node IS the list
    Node* t = head;
    while (t->next != NULL) t = t->next;       // stop ON the last node
    t->next = n;
}
// #endregion insertEnd

// #region insertAtPosition
// 1-based position. pos = length + 1 appends; anything larger is invalid.
void insertAtPosition(Node*& head, int x, int pos) {
    if (pos < 1) { cout << "Invalid position " << pos << endl; return; }
    if (pos == 1) { insertFront(head, x); return; }
    Node* t = head;
    for (int i = 1; i < pos - 1 && t != NULL; i++) t = t->next;   // walk to node pos-1
    if (t == NULL) { cout << "Invalid position " << pos << endl; return; }
    Node* n = new Node(x);
    n->next = t->next;
    t->next = n;
}
// #endregion insertAtPosition

// #region deleteValue
// Removes the FIRST node holding key. Returns false if key is absent.
bool deleteValue(Node*& head, int key) {
    if (head == NULL) return false;
    if (head->data == key) {                   // deleting the head is the special case
        Node* t = head;
        head = head->next;
        delete t;
        return true;
    }
    Node* prev = head;
    while (prev->next != NULL && prev->next->data != key) prev = prev->next;
    if (prev->next == NULL) return false;      // walked off the end: not found
    Node* t = prev->next;
    prev->next = t->next;                      // bypass, then free
    delete t;
    return true;
}
// #endregion deleteValue

// #region search
Node* search(Node* head, int key) {
    Node* t = head;
    while (t != NULL && t->data != key) t = t->next;   // check NULL first, then data
    return t;                                          // NULL if not found
}
// #endregion search

// #region printList
void printList(Node* head) {
    if (head == NULL) { cout << "List empty" << endl; return; }
    for (Node* t = head; t != NULL; t = t->next) cout << t->data << " ";
    cout << endl;
}
// #endregion printList

void freeList(Node*& head) {
    while (head != NULL) { Node* t = head; head = head->next; delete t; }
}

int main() {
    Node* head = NULL;
    printList(head);
    for (int x : {20, 30, 40}) insertEnd(head, x);
    insertFront(head, 10);
    printList(head);
    insertAtPosition(head, 25, 3);
    insertAtPosition(head, 50, 6);     // length + 1: appends
    insertAtPosition(head, 99, 9);     // beyond the end
    printList(head);
    deleteValue(head, 10);             // front
    deleteValue(head, 30);             // middle
    deleteValue(head, 50);             // end
    cout << "delete 77: " << (deleteValue(head, 77) ? "done" : "not found") << endl;
    printList(head);
    cout << "search 40: " << (search(head, 40) ? "found" : "not found") << endl;
    freeList(head);
    printList(head);
    return 0;
}
