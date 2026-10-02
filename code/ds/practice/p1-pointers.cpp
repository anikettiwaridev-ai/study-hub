#include <iostream>
using namespace std;

// Practice sheet 1, Q8 and Q9.
void swapValues(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int main() {
    int m = 3, n = 8;
    cout << "before: " << m << " " << n << endl;
    swapValues(&m, &n);                       // pass the ADDRESSES
    cout << "after:  " << m << " " << n << endl;

    int scores[] = {55, 68, 72, 90, 81};
    int* sPtr = scores;
    for (int i = 0; i < 5; i++) cout << *(sPtr + i) << " ";   // no [] anywhere
    cout << endl;
    cout << "scores[2] = " << scores[2] << ", *(sPtr + 2) = " << *(sPtr + 2) << endl;
    cout << "&scores[4] - &scores[0] = " << &scores[4] - &scores[0] << endl;   // elements, not bytes
    return 0;
}
