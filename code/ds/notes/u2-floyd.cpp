#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) { data = val; next = NULL; }
};

// #region hasCycle
bool hasCycle(Node* head) {
    Node *slow = head, *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;            // 1 step
        fast = fast->next->next;      // 2 steps
        if (slow == fast) return true; // the fast one lapped the slow one
    }
    return false;                     // fast fell off the end: no loop
}
// #endregion hasCycle

// #region removeCycle
void removeCycle(Node* head) {
    Node *slow = head, *fast = head;
    do {
        if (fast == NULL || fast->next == NULL) return;   // no cycle
        slow = slow->next;
        fast = fast->next->next;
    } while (slow != fast);
    slow = head;                                   // restart one pointer from the head
    if (slow == fast) {                            // loop goes back to the head itself
        while (fast->next != slow) fast = fast->next;
    } else {
        while (slow->next != fast->next) { slow = slow->next; fast = fast->next; }
    }
    fast->next = NULL;                             // fast is the last node of the loop
}
// #endregion removeCycle

int main() {
    Node* nodes[6];
    for (int i = 0; i < 6; i++) nodes[i] = new Node(i + 1);
    for (int i = 0; i < 5; i++) nodes[i]->next = nodes[i + 1];
    cout << "straight list: " << hasCycle(nodes[0]) << endl;
    nodes[5]->next = nodes[2];                     // 6 -> 3 makes a loop
    cout << "after 6 -> 3: " << hasCycle(nodes[0]) << endl;
    removeCycle(nodes[0]);
    cout << "after removeCycle: " << hasCycle(nodes[0]) << endl;
    for (Node* t = nodes[0]; t; t = t->next) cout << t->data << " ";
    cout << endl;
    for (int i = 0; i < 6; i++) delete nodes[i];
    return 0;
}
