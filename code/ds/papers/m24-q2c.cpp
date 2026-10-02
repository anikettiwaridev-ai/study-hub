#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) { data = val; next = NULL; }
};

// #region answer
void removeDuplicates(Node* START) {
    for (Node* p = START; p != NULL; p = p->next) {
        Node* q = p;                              // q->next is the node being checked
        while (q->next != NULL) {
            if (q->next->data == p->data) {       // a duplicate of p: unlink and free it
                Node* dup = q->next;
                q->next = dup->next;
                delete dup;
            } else {
                q = q->next;                      // advance only when nothing was removed
            }
        }
    }
}
// #endregion answer

void print(Node* t) { for (; t; t = t->next) cout << t->data << " "; cout << endl; }

int main() {
    Node* L = NULL;
    for (int x : {1, 5, 3, 2, 5, 3, 5}) { Node* n = new Node(x); n->next = L; L = n; }   // 5 3 5 2 3 5 1
    print(L);
    removeDuplicates(L);
    print(L);
    return 0;
}
