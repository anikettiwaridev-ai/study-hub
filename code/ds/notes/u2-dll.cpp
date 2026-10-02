#include <iostream>
using namespace std;

class DNode {
public:
    int data;
    DNode *prev, *next;
    DNode(int v) { data = v; prev = next = NULL; }
};

class DoublyLinkedList {
    DNode *head, *tail;
public:
    DoublyLinkedList() { head = tail = NULL; }

    // #region insertFront
    void insertFront(int x) {
        DNode* n = new DNode(x);
        n->next = head;
        if (head != NULL) head->prev = n; else tail = n;   // empty list: n is also the tail
        head = n;
    }
    // #endregion insertFront

    // #region insertEnd
    void insertEnd(int x) {
        DNode* n = new DNode(x);
        n->prev = tail;
        if (tail != NULL) tail->next = n; else head = n;
        tail = n;
    }
    // #endregion insertEnd

    // #region deleteNode
    void deleteNode(int key) {
        DNode* t = head;
        while (t != NULL && t->data != key) t = t->next;
        if (t == NULL) return;                          // not found
        if (t->prev != NULL) t->prev->next = t->next;   // left neighbour skips t
        else head = t->next;                            // t was the first node
        if (t->next != NULL) t->next->prev = t->prev;   // right neighbour points back past t
        else tail = t->prev;                            // t was the last node
        delete t;
    }
    // #endregion deleteNode

    // #region reverse
    void reverse() {                     // swap prev and next in every node: O(n)
        DNode* t = head;
        while (t != NULL) {
            DNode* tmp = t->next;
            t->next = t->prev;
            t->prev = tmp;
            t = tmp;                     // tmp is the old next
        }
        DNode* old = head; head = tail; tail = old;
    }
    // #endregion reverse

    void printForward() {
        for (DNode* t = head; t; t = t->next) cout << t->data << " ";
        cout << endl;
    }
    void printBackward() {
        for (DNode* t = tail; t; t = t->prev) cout << t->data << " ";
        cout << endl;
    }
    ~DoublyLinkedList() { while (head) { DNode* t = head; head = head->next; delete t; } }
};

int main() {
    DoublyLinkedList d;
    for (int x : {30, 40, 50}) d.insertEnd(x);
    d.insertFront(20);
    d.insertFront(10);
    d.printForward();
    d.printBackward();
    d.deleteNode(10);  d.printForward();   // first node
    d.deleteNode(50);  d.printForward();   // last node
    d.deleteNode(30);  d.printForward();   // middle
    d.insertEnd(60);
    d.reverse();
    d.printForward();
    d.printBackward();
    return 0;
}
