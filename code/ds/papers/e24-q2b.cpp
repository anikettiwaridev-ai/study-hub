#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) { data = val; next = NULL; }
};

// #region answer
void kthFromMiddle(Node* head, int k) {
    int n = 0;
    for (Node* t = head; t != NULL; t = t->next) n++;     // pass 1: length
    int pos = n / 2 + 1 - k;                              // middle is node n/2 + 1 (1-based)
    if (n == 0 || k < 0 || pos < 1) {                     // walked past the head
        cout << -1 << endl;
        return;
    }
    Node* t = head;                                       // pass 2: walk to node pos
    for (int i = 1; i < pos; i++) t = t->next;
    cout << t->data << endl;
}
// #endregion answer

int main() {
    Node* head = NULL;
    for (int x = 70; x >= 10; x -= 10) { Node* n = new Node(x); n->next = head; head = n; }   // 10..70
    for (int k : {0, 1, 3, 4}) { cout << "n = 7, k = " << k << ": "; kthFromMiddle(head, k); }
    Node* h6 = NULL;
    for (int x = 6; x >= 1; x--) { Node* n = new Node(x); n->next = h6; h6 = n; }             // 1..6
    for (int k : {0, 2, 4}) { cout << "n = 6, k = " << k << ": "; kthFromMiddle(h6, k); }
    return 0;
}
