#include <iostream>
#include "MathUtils.h"      // quotes: look in THIS folder first, then the system folders
using namespace std;

int main() {
    cout << "isPrime(29)   = " << (isPrime(29) ? "true" : "false") << endl;
    cout << "factorial(10) = " << factorial(10) << endl;
    cout << "gcd(84, 36)   = " << gcd(84, 36) << endl;
    cout << "power(2, 10)  = " << power(2, 10) << endl;
    return 0;
}
