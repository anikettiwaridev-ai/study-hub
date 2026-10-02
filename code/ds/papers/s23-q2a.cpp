#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int dt) {
        data = dt;
        next = NULL;
    }
};

class LL {
public:
    Node* head;
    LL() { head = NULL; }

    // #region answer
    void insertM(int key) {
        Node* n = new Node(key);
        if (head == NULL) { head = n; return; }        // empty list: the new node is the list
        int len = 0;
        for (Node* t = head; t != NULL; t = t->next) len++;
        int pos = (len + 1) / 2;                        // 4 nodes -> after 2nd, 5 nodes -> after 3rd
        Node* t = head;
        for (int i = 1; i < pos; i++) t = t->next;      // stop ON node number pos
        n->next = t->next;                              // link the new node to the rest first
        t->next = n;
    }
    // #endregion answer

    void insertEnd(int x) {
        Node* n = new Node(x);
        if (head == NULL) { head = n; return; }
        Node* t = head;
        while (t->next != NULL) t = t->next;
        t->next = n;
    }
    void print() {
        for (Node* t = head; t; t = t->next) cout << t->data << " ";
        cout << endl;
    }
};

int main() {
    LL a, b, c, d;
    for (int x : {1, 2, 3, 4}) a.insertEnd(x);
    a.insertM(99); a.print();
    for (int x : {1, 2, 3, 4, 5}) b.insertEnd(x);
    b.insertM(99); b.print();
    c.insertEnd(1);
    c.insertM(99); c.print();
    d.insertM(99); d.print();
    return 0;
}
