#include <initializer_list>
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) { data = val; next = NULL; }
};

// #region answer
Node* removeAll(Node* head, int key) {
    while (head != NULL && head->data == key) {     // 1. strip matching nodes from the front
        Node* t = head;
        head = head->next;
        delete t;
    }
    if (head == NULL) return NULL;                  // every node matched
    Node* prev = head;                              // 2. prev->data != key from here on
    while (prev->next != NULL) {
        if (prev->next->data == key) {
            Node* t = prev->next;
            prev->next = t->next;                   // unlink, free, and DON'T advance:
            delete t;                               //    the new prev->next may match too
        } else {
            prev = prev->next;
        }
    }
    return head;
}
// #endregion answer

Node* build(std::initializer_list<int> v) {
    Node *h = NULL, *t = NULL;
    for (int x : v) { Node* n = new Node(x); if (!h) h = t = n; else { t->next = n; t = n; } }
    return h;
}
void print(Node* t) { if (!t) cout << "(empty)"; for (; t; t = t->next) cout << t->data << " "; cout << endl; }

int main() {
    print(removeAll(build({3, 3, 1, 3, 3, 2, 3}), 3));
    print(removeAll(build({7, 7, 7}), 7));
    print(removeAll(build({1, 2, 4}), 9));
    print(removeAll(NULL, 1));
    return 0;
}
