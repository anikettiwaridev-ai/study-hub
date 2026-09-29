#include <iostream>
using namespace std;
class Complex {
    int real;
public:
    Complex(int r) { real = r; }
    Complex(Complex c) { real = c.real; }
};
int main() { Complex a(1); Complex b(a); return 0; }
