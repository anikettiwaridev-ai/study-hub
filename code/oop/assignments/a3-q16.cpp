#include <iostream>
using namespace std;

void addTenByPointer(int *p)   { *p += 10; }   // needs * to reach the value
void doubleByReference(int &r) { r *= 2; }     // r is the variable itself

int main() {
    int value = 5;
    cout << "Start: " << value << endl;
    addTenByPointer(&value);                   // caller passes the address
    cout << "After addTenByPointer:   " << value << endl;
    doubleByReference(value);                  // caller passes the variable
    cout << "After doubleByReference: " << value << endl;
    return 0;
}
