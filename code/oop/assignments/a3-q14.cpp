#include <iostream>
using namespace std;

// Two answers are needed, and a function returns only one value,
// so both are written through pointers.
void largestSmallest(int a, int b, int c, int *largest, int *smallest) {
    *largest = a;
    if (b > *largest) *largest = b;
    if (c > *largest) *largest = c;
    *smallest = a;
    if (b < *smallest) *smallest = b;
    if (c < *smallest) *smallest = c;
}

int main() {
    int big, small;
    largestSmallest(17, 4, 29, &big, &small);
    cout << "Largest = " << big << ", smallest = " << small << endl;
    return 0;
}
