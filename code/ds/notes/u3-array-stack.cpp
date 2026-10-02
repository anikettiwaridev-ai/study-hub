#include <iostream>
using namespace std;

class Stack {
    int* arr;
    int capacity, top;
public:
    Stack(int cap) { capacity = cap; arr = new int[cap]; top = -1; }
    ~Stack() { delete[] arr; }

    bool isEmpty() const { return top == -1; }
    bool isFull() const { return top == capacity - 1; }

    // #region push
    void push(int x) {
        if (isFull()) { cout << "Overflow: " << x << " not pushed" << endl; return; }
        arr[++top] = x;              // increment first, then write
    }
    // #endregion push

    // #region pop
    int pop() {
        if (isEmpty()) { cout << "Underflow" << endl; return -1; }
        return arr[top--];           // read first, then decrement
    }
    // #endregion pop

    int peek() const { return isEmpty() ? -1 : arr[top]; }

    void print() const {             // bottom to top
        for (int i = 0; i <= top; i++) cout << arr[i] << " ";
        cout << "(top = " << top << ")" << endl;
    }
};

int main() {
    Stack s(5);
    for (int x = 10; x <= 60; x += 10) s.push(x);   // the 6th push overflows
    s.print();
    for (int i = 0; i < 3; i++) cout << "popped " << s.pop() << endl;
    cout << "peek " << s.peek() << endl;
    s.print();
    s.pop(); s.pop();
    s.pop();                                          // underflow
    return 0;
}
