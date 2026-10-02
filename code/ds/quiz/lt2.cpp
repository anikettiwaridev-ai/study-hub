#include <iostream>
using namespace std;

// Lab Quiz 2 (2026), every blank filled in.
class Node {
public:
    int key;
    int val;
    Node* next;
    Node(int k, int v) {
        key = k;
        val = v;
        next = NULL;
    }
};

// #region q1
// Priority queue as a list sorted by DESCENDING priority (key); FIFO among equals.
Node* ENQUEUE(Node* head, int priority, int data) {
    Node* newNode = new Node(priority, data);
    Node* temp = head;
    if (temp == NULL)
        return newNode;                                    // blank 1 (vii)
    if (temp->key < priority) {
        newNode->next = temp;                              // blank 2 (iv, or i: head)
        return newNode;                                    // blank 3 (vii)
    }
    while ((temp->next != NULL) && (temp->next->key >= priority))
        temp = temp->next;
    newNode->next = temp->next;                            // blank 4 (viii) = temp->next
    temp->next = newNode;                                  // blank 5 (vii)
    return head;                                           // blank 6 (i)
}
// #endregion q1

// #region q2
// Max-stack: key = maximum so far, val = data.
Node* push(Node* head, int data) {
    Node* newNode;
    if (head == NULL) {
        newNode = new Node(data, data);
        return newNode;
    }
    if (head->key > data)
        newNode = new Node(head->key, data);
    else
        newNode = new Node(data, data);                    // blanks 1 and 2 (vii, vii)
    newNode->next = head;                                  // blank 3 (i)
    return newNode;                                        // blank 4 (iv)
}
// #endregion q2

int main() {
    Node* pq = NULL;
    int ins[][2] = {{2, 20}, {5, 50}, {2, 21}, {1, 10}, {5, 51}};
    for (auto& p : ins) pq = ENQUEUE(pq, p[0], p[1]);
    for (Node* t = pq; t; t = t->next) cout << "(" << t->key << "," << t->val << ") ";
    cout << endl;
    Node* s = NULL;
    for (int x : {3, 8, 5, 10, 1}) { s = push(s, x); cout << "push " << x << ": max " << s->key << endl; }
    return 0;
}
