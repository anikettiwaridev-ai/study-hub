#include <iostream>
#include <string>
using namespace std;

// Lab Quiz 1 (2026), every blank filled in.
class Node {
public:
    int data;
    Node* next;
    Node(int val) {
        data = val;
        next = NULL;
    }
};

// #region q1
// Prints every binary string of length n whose value is divisible by 3, in descending order.
// rmdr = value of curr mod 3. Appending a bit doubles the value and adds the bit.
void fun(int n, string curr = "", int rmdr = 0) {
    if ((int) curr.length() == n) {
        if (rmdr == 0) {                                   // blank 1
            cout << curr << endl;
        }
        return;
    }
    fun(n, curr + '1', (rmdr * 2 + 1) % 3);                // '1' first: descending
    fun(n, curr + '0', (rmdr * 2) % 3);                    // blanks 2 and 3
}
// #endregion q1

// #region q2
// Remove the node p points to (not the last node) without access to head:
// copy the NEXT node into p, then delete the next node.
void erase(Node* p) {
    Node* temp = p->next;                                  // blank 1
    p->data = temp->data;                                  // blank 2
    p->next = temp->next;                                  // blank 3
    delete temp;
}
// #endregion q2

// #region q3
Node* secondLargest(Node* head) {
    Node* F = nullptr;          // largest so far
    Node* S = nullptr;          // second largest so far
    Node* T;
    for (T = head; T; T = T->next) {
        if (!F || T->data > F->data) {
            S = F;                                         // blank 1: old first becomes second
            F = T;                                         // blank 2
        }
        else if ((T->data < F->data) &&
                 (!S || T->data > S->data)) {              // blank 3: S->data
            S = T;                                         // blank 4
        }
    }
    return S;
}
// #endregion q3

int main() {
    fun(4);
    Node* head = NULL;
    for (int v : {4, 9, 7, 9, 2}) { Node* n = new Node(v); n->next = head; head = n; }   // 2 9 7 9 4
    cout << "second largest: " << secondLargest(head)->data << endl;
    erase(head->next);                                      // removes the first 9
    for (Node* t = head; t; t = t->next) cout << t->data << " ";
    cout << endl;
    return 0;
}
