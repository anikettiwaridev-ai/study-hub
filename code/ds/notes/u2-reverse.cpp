#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) { data = val; next = NULL; }
};

// #region reverse
Node* reverseList(Node* head) {
    Node *prev = NULL, *curr = head;
    while (curr != NULL) {
        Node* nxt = curr->next;   // 1. remember the rest
        curr->next = prev;        // 2. turn this arrow around
        prev = curr;              // 3. step both forward
        curr = nxt;
    }
    return prev;                  // the old last node is the new head
}
// #endregion reverse

// #region printReverse
void printReverse(Node* t) {      // prints AFTER the call, so the last node comes out first
    if (t == NULL) return;
    printReverse(t->next);
    cout << t->data << " ";
}
// #endregion printReverse

void print(Node* t) { for (; t; t = t->next) cout << t->data << " "; cout << endl; }

int main() {
    Node* head = NULL;
    for (int x = 5; x >= 1; x--) { Node* n = new Node(x); n->next = head; head = n; }
    print(head);
    printReverse(head); cout << endl;
    head = reverseList(head);
    print(head);
    while (head) { Node* t = head; head = head->next; delete t; }
    return 0;
}
