#include <iostream>
using namespace std;

// Lab Quiz 2 (2026) Q2: every node stores its value AND the maximum of everything
// at or below it, so the maximum is always at the top.
class Node {
public:
    int key;     // the maximum so far
    int val;     // the data
    Node* next;
    Node(int k, int v) { key = k; val = v; next = NULL; }
};

// #region push
Node* push(Node* head, int data) {
    Node* newNode;
    if (head == NULL) {
        newNode = new Node(data, data);
        return newNode;
    }
    if (head->key > data)
        newNode = new Node(head->key, data);   // old maximum still wins
    else
        newNode = new Node(data, data);        // the new value is the maximum
    newNode->next = head;
    return newNode;
}
// #endregion push

// #region pop
Node* pop(Node* head) {                        // the node below already knows ITS maximum
    if (head == NULL) return NULL;
    Node* rest = head->next;
    delete head;
    return rest;
}
// #endregion pop

int maxElement(Node* head) { return head == NULL ? -1 : head->key; }

int main() {
    Node* s = NULL;
    for (int x : {3, 7, 2, 9, 4}) {
        s = push(s, x);
        cout << "push " << x << " -> max " << maxElement(s) << endl;
    }
    while (s != NULL) {
        cout << "pop " << s->val;
        s = pop(s);
        cout << " -> max " << maxElement(s) << endl;
    }
    return 0;
}
