#include <iostream>
using namespace std;
class Complex;
class A {
public:
    int calculate(Complex c1, Complex c2) {
        return c1.real + c2.real;
    }
};
class Complex {
    int real, img;
    friend int A::calculate(Complex, Complex);
};
int main() { return 0; }
