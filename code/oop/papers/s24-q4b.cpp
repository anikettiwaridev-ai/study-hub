#include <iostream>
using namespace std;

void byReference(int &r) { r = r + 10; }   // r IS the caller's variable (an alias)

void byPointer(int *p) {
    if (p == nullptr) return;              // a pointer can be null, so check it
    *p = *p + 10;                          // reach the variable through the address
}

int main() {
    int a = 5, b = 5;
    byReference(a);    // call looks like pass by value
    byPointer(&b);     // caller must pass the address explicitly
    byPointer(nullptr);
    cout << "a = " << a << ", b = " << b << endl;
    return 0;
}
