#include <iostream>
#include <climits>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) { data = val; next = NULL; }
};

// #region answer
int findSmallest(Node* head) {
    if (head == NULL) {                       // empty list: there is no smallest element
        cout << "List is empty" << endl;
        return INT_MAX;
    }
    int smallest = head->data;                // start with the first node, not with 0
    for (Node* t = head->next; t != NULL; t = t->next)
        if (t->data < smallest) smallest = t->data;
    return smallest;
}
// #endregion answer

int main() {
    Node* head = NULL;
    for (int x : {14, -3, 27, 8, -3, 9}) { Node* n = new Node(x); n->next = head; head = n; }
    cout << "smallest = " << findSmallest(head) << endl;
    findSmallest(NULL);
    return 0;
}
