#include <iostream>
using namespace std;

class DNode {
public:
    int data;
    DNode *prev, *next;
    DNode(int v) { data = v; prev = next = NULL; }
};

// #region answer
void sortedInsert(DNode*& START, int q) {
    DNode* n = new DNode(q);
    if (START == NULL) { START = n; return; }                  // case 1: empty list
    if (q <= START->data) {                                    // case 2: new first node
        n->next = START;
        START->prev = n;
        START = n;
        return;
    }
    DNode* t = START;                                          // case 3: middle or end
    while (t->next != NULL && t->next->data < q) t = t->next;  // t = last node smaller than q
    n->next = t->next;                                         // (1) new -> successor
    n->prev = t;                                               // (2) new <- t
    if (t->next != NULL) t->next->prev = n;                    // (3) successor <- new (not at the end)
    t->next = n;                                               // (4) t -> new
}
// #endregion answer

void show(DNode* s) {
    DNode* last = NULL;
    cout << "forward: ";
    for (DNode* t = s; t; t = t->next) { cout << t->data << " "; last = t; }
    cout << "| backward: ";
    for (DNode* t = last; t; t = t->prev) cout << t->data << " ";
    cout << endl;
}

int main() {
    DNode* L = NULL;
    for (int x : {30, 10, 40, 20}) sortedInsert(L, x);
    show(L);
    sortedInsert(L, 25);    // middle
    sortedInsert(L, 5);     // front
    sortedInsert(L, 50);    // end
    show(L);
    return 0;
}
