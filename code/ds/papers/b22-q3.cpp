#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) { data = val; next = NULL; }
};

// #region answer
void stretch(Node* head) {
    int k = 1;                                 // k = position of the current ORIGINAL node
    Node* t = head;
    while (t != NULL) {
        Node* after = t->next;                 // remember the next original node
        for (int i = 0; i < k; i++) {          // k extra copies, each inserted right after t
            Node* copy = new Node(t->data);
            copy->next = t->next;
            t->next = copy;
        }
        t = after;                             // jump over the copies
        k++;
    }
}
// #endregion answer

void print(Node* t) { for (; t; t = t->next) cout << t->data << (t->next ? " -> " : ""); cout << endl; }

int main() {
    Node* head = NULL;
    for (int x : {1, 5, 1, 4, 3}) { Node* n = new Node(x); n->next = head; head = n; }   // 3 4 1 5 1
    print(head);
    stretch(head);
    print(head);
    return 0;
}
