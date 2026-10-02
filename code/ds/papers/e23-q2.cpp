#include <iostream>
using namespace std;

class Node {
public:
    int data;
    int maxSoFar;          // the largest value in this node and every node below it
    Node* next;
    Node(int d) { data = d; maxSoFar = d; next = NULL; }
};

class MaxStack {
    Node* top = NULL;
public:
    // #region push
    void push(int x) {                                  // O(1)
        Node* n = new Node(x);
        if (top != NULL && top->maxSoFar > x) n->maxSoFar = top->maxSoFar;
        n->next = top;
        top = n;
    }
    // #endregion push

    // #region pop
    int pop() {                                         // O(1); -1 when empty
        if (top == NULL) return -1;
        Node* t = top;
        int v = t->data;
        top = top->next;                                // the next node already knows its own maximum
        delete t;
        return v;
    }
    // #endregion pop

    // #region max
    int max() const {                                   // O(1): no traversal
        return top == NULL ? -1 : top->maxSoFar;
    }
    // #endregion max
};

int main() {
    MaxStack s;
    cout << "max of empty: " << s.max() << ", pop of empty: " << s.pop() << endl;
    for (int x : {4, 2, 9, 9, 1}) { s.push(x); cout << "push " << x << " -> max " << s.max() << endl; }
    for (int i = 0; i < 5; i++) { int v = s.pop(); cout << "pop " << v << " -> max " << s.max() << endl; }
    return 0;
}
