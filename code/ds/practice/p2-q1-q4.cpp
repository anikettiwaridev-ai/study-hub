#include <iostream>
using namespace std;

// Practice sheet 2, Q1 and Q4.
class Node {
public:
    int data;
    Node* next;
    Node() { data = 0; next = NULL; }
    Node(int d) { data = d; next = NULL; }
};

class Linkedlist {
    Node* head;
public:
    Linkedlist() { head = NULL; }
    void insertNode(int data) {                // at the end
        Node* n = new Node(data);
        if (head == NULL) { head = n; return; }
        Node* t = head;
        while (t->next != NULL) t = t->next;
        t->next = n;
    }
    void printList() {
        if (head == NULL) { cout << "List empty" << endl; return; }
        for (Node* t = head; t; t = t->next) cout << t->data << " ";
        cout << endl;
    }
    // #region deleteNode
    void deleteNode(int data) {                // by VALUE (the slides' version deletes by position)
        if (head == NULL) return;
        Node* t = head;
        if (t->data == data) { head = t->next; delete t; return; }
        while (t->next != NULL && t->next->data != data) t = t->next;
        if (t->next == NULL) return;           // not found
        Node* gone = t->next;
        t->next = gone->next;
        delete gone;
    }
    // #endregion deleteNode
    ~Linkedlist() { while (head) { Node* t = head; head = head->next; delete t; } }
};

int main() {
    Linkedlist L;
    for (int x : {10, 20, 30, 40, 50}) L.insertNode(x);
    L.printList();
    L.deleteNode(10); L.printList();           // front
    L.deleteNode(30); L.printList();           // middle
    L.deleteNode(50); L.printList();           // end

    // Q4: three nodes built by hand, without the class
    Node* a = new Node(1);
    Node* b = new Node(2);
    Node* c = new Node(3);
    a->next = b; b->next = c;
    for (Node* t = a; t; t = t->next) cout << t->data << " ";
    cout << endl;
    // Delete one at a time. Each pointer is set to nullptr at once, so no later line can
    // touch freed memory through it (a dangling pointer) or delete it twice.
    delete a; a = nullptr;
    delete b; b = nullptr;
    delete c; c = nullptr;
    cout << "freed: " << (a == nullptr && b == nullptr && c == nullptr) << endl;
    return 0;
}
