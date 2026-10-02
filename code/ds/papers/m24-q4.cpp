#include <iostream>
using namespace std;

struct node {
    int info;
    node* next;
};

node* start = NULL;              // start = top of the stack

// #region push
void push(int x) {
    node* p = new node;          // 1. get a new node
    p->info = x;                 // 2. store the data
    p->next = start;             // 3. point it at the old top
    start = p;                   // 4. it becomes the new top
}
// #endregion push

// #region pop
int pop() {
    if (start == NULL) {         // 1. underflow check
        cout << "Stack underflow" << endl;
        return -1;
    }
    node* p = start;             // 2. remember the top node
    int x = p->info;             // 3. save its data
    start = start->next;         // 4. the next node becomes the top
    delete p;                    // 5. free the old top
    return x;
}
// #endregion pop

int main() {
    push(10); push(20); push(30);
    cout << pop() << " " << pop() << " " << pop() << endl;
    pop();
    return 0;
}
