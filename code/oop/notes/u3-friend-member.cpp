#include <iostream>
using namespace std;

class Complex;                          // 1. forward declaration: "Complex is a class"

class A {
public:
    int calculate(const Complex &c1, const Complex &c2);   // 2. DECLARE only: Complex is incomplete
};

class Complex {
    int real, img;
public:
    Complex(int r, int i) { real = r; img = i; }
    friend int A::calculate(const Complex &c1, const Complex &c2);   // 3. one member of A is a friend
};

// 4. DEFINE after Complex is complete, so c1.real is known.
int A::calculate(const Complex &c1, const Complex &c2) {
    return c1.real + c2.real;
}

int main() {
    Complex c1(10, 20), c2(10, 30);
    A a;
    cout << "Sum of real parts = " << a.calculate(c1, c2) << endl;
    return 0;
}
