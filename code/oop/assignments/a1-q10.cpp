#include <iostream>
using namespace std;

int main() {
    int a, b;
    cout << "Enter two integers: ";
    cin >> a >> b;
    cout << "a & b  = " << (a & b)  << endl;   // AND: 1 only where both bits are 1
    cout << "a | b  = " << (a | b)  << endl;   // OR:  1 where either bit is 1
    cout << "a ^ b  = " << (a ^ b)  << endl;   // XOR: 1 where the bits differ
    cout << "~a     = " << (~a)     << endl;   // NOT: flips every bit, equals -(a+1)
    cout << "a << 1 = " << (a << 1) << endl;   // left shift: multiply by 2
    cout << "a >> 1 = " << (a >> 1) << endl;   // right shift: divide by 2
    return 0;
}
