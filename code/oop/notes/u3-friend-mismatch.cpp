#include <iostream>
using namespace std;
class Complex {
    int real, img;
public:
    Complex(int r, int i) { real = r; img = i; }
    friend Complex add(Complex c1, Complex c2);
};
Complex add(const Complex &c1, const Complex &c2) {
    return Complex(c1.real + c2.real, c1.img + c2.img);
}
int main() {
    Complex a(1, 2), b(3, 4);
    Complex c = add(a, b);
    return 0;
}
