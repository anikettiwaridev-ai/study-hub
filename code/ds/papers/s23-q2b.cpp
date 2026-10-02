#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int dt) { data = dt; next = NULL; }
};

void fun(Node* start) {                        // exactly as printed (Null read as NULL)
    if (start == NULL) return;
    cout << start->data;
    if (start->next != NULL)
        fun(start->next->next);
    cout << start->data;
}

void funSpaced(Node* start) {                  // the same, with a space after each number
    if (start == NULL) return;
    cout << start->data << " ";
    if (start->next != NULL)
        funSpaced(start->next->next);
    cout << start->data << " ";
}

int main() {
    Node* head = NULL;
    int vals[] = {49, 40, 37, 34, 12, 9};      // builds 9->12->34->37->40->49
    for (int x : vals) { Node* n = new Node(x); n->next = head; head = n; }
    fun(head);       cout << endl;
    funSpaced(head); cout << endl;
    return 0;
}
