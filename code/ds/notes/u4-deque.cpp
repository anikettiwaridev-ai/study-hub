#include <iostream>
using namespace std;

// A circular deque stored as front + cnt.
const int SIZE = 6;
int arr[SIZE], front = 0, cnt = 0;    // cnt = how many are stored

// #region deque
void insertFront(int x) {
    if (cnt == SIZE) { cout << "overflow" << endl; return; }
    front = (front - 1 + SIZE) % SIZE;      // + SIZE: in C++ (0 - 1) % 6 is -1
    arr[front] = x; cnt++;
}
void insertRear(int x) {
    if (cnt == SIZE) { cout << "overflow" << endl; return; }
    arr[(front + cnt) % SIZE] = x; cnt++;
}
int deleteFront() {
    if (cnt == 0) { cout << "underflow" << endl; return -1; }
    int v = arr[front];
    front = (front + 1) % SIZE; cnt--;
    return v;
}
int deleteRear() {
    if (cnt == 0) { cout << "underflow" << endl; return -1; }
    cnt--;
    return arr[(front + cnt) % SIZE];     // the old last element
}
// #endregion deque

void display() {
    for (int i = 0; i < cnt; i++) cout << arr[(front + i) % SIZE] << " ";
    cout << endl;
}

int main() {                                // Oct 2022 (Paper A) Q7
    insertFront(10); insertFront(20); insertRear(30);
    deleteFront();
    insertRear(40); insertRear(10);
    deleteRear();
    insertRear(15);
    display();
    return 0;
}
