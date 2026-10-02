#include <iostream>
#include <exception>
using namespace std;

class StackUnderflowException : public exception {
public:
    const char* what() const noexcept override { return "stack underflow: the stack is empty"; }
};

class Node {
public:
    int data;
    Node* next;
    Node(int val) { data = val; next = NULL; }
};

class Stack {
    Node* top = NULL;                 // head of the list = top of the stack
public:
    bool isEmpty() const { return top == NULL; }

    // #region push
    void push(int x) {                // O(1): insert at the head
        Node* n = new Node(x);
        n->next = top;                // link first
        top = n;                      // then move
    }
    // #endregion push

    // #region pop
    int pop() {                       // O(1): delete at the head
        if (top == NULL) throw StackUnderflowException();
        Node* t = top;
        int v = t->data;              // read BEFORE delete
        top = top->next;
        delete t;
        return v;
    }
    // #endregion pop

    int peek() const {
        if (top == NULL) throw StackUnderflowException();
        return top->data;
    }
    ~Stack() { while (top) { Node* t = top; top = top->next; delete t; } }
};

int main() {
    Stack s;
    s.push(1); s.push(2); s.push(3);
    cout << "peek " << s.peek() << endl;
    try {
        for (int i = 0; i < 4; i++) { int v = s.pop(); cout << "popped " << v << endl; }   // the 4th throws
    } catch (const StackUnderflowException& e) {
        cout << "caught: " << e.what() << endl;
    }
    return 0;
}
