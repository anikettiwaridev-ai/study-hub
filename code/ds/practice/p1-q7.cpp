#include <iostream>
using namespace std;

// Practice sheet 1, Q7. The address changes from run to run.
int main() {
    int x = 42;
    int* p = &x;
    cout << "value " << x << ", address " << p << ", *p " << *p << endl;
    *p = 99;                         // change x through the pointer
    cout << "x is now " << x << endl;
    return 0;
}
