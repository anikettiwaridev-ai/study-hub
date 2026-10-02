#include <initializer_list>
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) { data = val; next = NULL; }
};

// #region iterative
// Merges two ascending lists by relinking their nodes (no new nodes). O(m + n).
Node* mergeSorted(Node* a, Node* b) {
    Node dummy(0);                         // a fake first node: no "empty result" special case
    Node* tail = &dummy;
    while (a != NULL && b != NULL) {
        if (a->data <= b->data) { tail->next = a; a = a->next; }
        else                    { tail->next = b; b = b->next; }
        tail = tail->next;
    }
    tail->next = (a != NULL) ? a : b;      // one list is finished: attach the rest of the other
    return dummy.next;
}
// #endregion iterative

// #region recursive
Node* mergeRec(Node* h1, Node* h2) {       // Lab Quiz I (2025) Q4 is this function
    if (h1 == NULL) return h2;
    if (h2 == NULL) return h1;
    if (h1->data <= h2->data) { h1->next = mergeRec(h1->next, h2); return h1; }
    h2->next = mergeRec(h1, h2->next);
    return h2;
}
// #endregion recursive

Node* build(std::initializer_list<int> v) {
    Node *h = NULL, *t = NULL;
    for (int x : v) { Node* n = new Node(x); if (!h) h = t = n; else { t->next = n; t = n; } }
    return h;
}
void print(Node* t) { for (; t; t = t->next) cout << t->data << " "; cout << endl; }

int main() {
    print(mergeSorted(build({1, 4, 7, 9}), build({2, 3, 8, 10, 12})));
    print(mergeRec(build({5, 6}), build({1, 2, 3})));
    print(mergeSorted(NULL, build({4, 5})));
    return 0;
}
