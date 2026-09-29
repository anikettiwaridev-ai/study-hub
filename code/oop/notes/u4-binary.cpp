#include <iostream>
using namespace std;

class Complex {
    int real, img;
public:
    Complex(int r = 0, int i = 0) { real = r; img = i; }

    // MEMBER: one parameter. c1 + c2 becomes c1.operator+(c2).
    Complex operator+(const Complex &c) const {
        return Complex(real + c.real, img + c.img);
    }

    // FRIEND: two parameters. c1 * c2 becomes operator*(c1, c2).
    friend Complex operator*(const Complex &a, const Complex &b);

    void show() const { cout << real << (img < 0 ? " - " : " + ") << (img < 0 ? -img : img) << "i" << endl; }
};

// (a + bi)(c + di) = (ac - bd) + (ad + bc)i
Complex operator*(const Complex &a, const Complex &b) {
    return Complex(a.real * b.real - a.img * b.img,
                   a.real * b.img + a.img * b.real);
}

int main() {
    Complex c1(10, 40), c2(20, 50);
    Complex c3 = c1 + c2;
    Complex c4 = c1 * c2;
    Complex c5 = c1 + c2 * c1;     // * first, as with numbers: precedence is kept
    cout << "c1 + c2 = "; c3.show();
    cout << "c1 * c2 = "; c4.show();
    cout << "c1 + c2 * c1 = "; c5.show();
    return 0;
}
