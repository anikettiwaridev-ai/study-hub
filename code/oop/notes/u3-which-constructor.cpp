#include <iostream>
using namespace std;
class Complex {
public:
    Complex()                   { cout << "D"; }
    Complex(int, int)           { cout << "P"; }
    Complex(const Complex &)    { cout << "C"; }
    Complex &operator=(const Complex &) { cout << "A"; return *this; }
};
int main() {
    Complex c1(4, 6);
    Complex c2(c1);
    Complex c3;
    c3 = c1;
    Complex c4 = c1;
    return 0;
}
