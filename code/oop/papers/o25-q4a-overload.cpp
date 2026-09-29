#include <iostream>
#include <cmath>
using namespace std;

// Same name as the library's pow, but a DIFFERENT parameter list (int, int).
// That is function overloading, so both versions exist side by side.
int pow(int base, int exp) {
    cout << "[my pow] ";
    int result = 1;
    for (int i = 0; i < exp; i++) result *= base;
    return result;
}

int main() {
    cout << pow(2, 3) << endl;     // both arguments int: exact match with mine
    cout << pow(2.0, 3) << endl;   // double argument: the library version is chosen
    cout << sqrt(16.0) << endl;    // untouched library function
    return 0;
}
