#include <iostream>
using namespace std;

void swapByValue(int a, int b)      { int t = a; a = b; b = t; }     // swaps COPIES
void swapByReference(int &a, int &b){ int t = a; a = b; b = t; }     // swaps the originals
void swapByPointer(int *a, int *b)  { int t = *a; *a = *b; *b = t; } // swaps through addresses

int main() {
    int x = 10, y = 20;
    swapByValue(x, y);
    cout << "After swapByValue:     x = " << x << ", y = " << y << "  (not swapped)" << endl;
    swapByReference(x, y);
    cout << "After swapByReference: x = " << x << ", y = " << y << "  (swapped)" << endl;
    swapByPointer(&x, &y);
    cout << "After swapByPointer:   x = " << x << ", y = " << y << "  (swapped back)" << endl;
    return 0;
}
