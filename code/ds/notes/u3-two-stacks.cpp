#include <iostream>
using namespace std;

const int SIZE = 5;
int arr[SIZE], top1 = -1, top2 = SIZE;    // stack 1 grows right, stack 2 grows left

// #region twostacks
void push1(int x) {
    if (top1 == top2 - 1) { cout << "Overflow pushing " << x << endl; return; }
    arr[++top1] = x;
}
void push2(int x) {
    if (top1 == top2 - 1) { cout << "Overflow pushing " << x << endl; return; }
    arr[--top2] = x;
}
int pop1() { return top1 == -1 ? -1 : arr[top1--]; }
int pop2() { return top2 == SIZE ? -1 : arr[top2++]; }
// #endregion twostacks

int main() {
    push1(1); push1(2);
    push2(9); push2(8); push2(7);         // all 5 cells now used
    push1(3);                             // overflow, though stack 1 holds only 2
    cout << "pop2 " << pop2() << ", pop1 " << pop1() << endl;
    push1(3);                             // fits now
    cout << "top1 = " << top1 << ", top2 = " << top2 << endl;
    return 0;
}
