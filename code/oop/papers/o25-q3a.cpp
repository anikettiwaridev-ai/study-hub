#include <iostream>
using namespace std;

class ComplexNumber {
private:
    int real, imaginary;

public:
    ComplexNumber() { real = 0; imaginary = 0; }            // default

    ComplexNumber(int r, int i) {                           // parameterized
        real = r;
        imaginary = i;
    }

    ComplexNumber(const ComplexNumber &c) {                 // copy constructor
        real = c.real;
        imaginary = c.imaginary;
    }

    void setComplexNumber(int r, int i) {                   // member function to initialise
        real = r;
        imaginary = i;
    }

    void displayComplexNumber() {
        cout << real << " + " << imaginary << "i" << endl;
    }

    // addComplexNumbers is not a member, so it is made a friend to read the private data.
    friend ComplexNumber addComplexNumbers(const ComplexNumber &a,
                                           const ComplexNumber &b,
                                           const ComplexNumber &c);
};

ComplexNumber addComplexNumbers(const ComplexNumber &a,
                                const ComplexNumber &b,
                                const ComplexNumber &c) {
    ComplexNumber sum;
    sum.real = a.real + b.real + c.real;
    sum.imaginary = a.imaginary + b.imaginary + c.imaginary;
    return sum;
}

int main() {
    int r, i;
    cout << "Enter real and imaginary parts of complex1: ";
    cin >> r >> i;                         // values known only at run time:
    ComplexNumber complex1(r, i);          // dynamic initialisation via constructor

    cout << "Enter real and imaginary parts of complex2: ";
    cin >> r >> i;
    ComplexNumber complex2;
    complex2.setComplexNumber(r, i);       // initialised through a member function

    ComplexNumber complex3(complex1);      // copy constructor copies complex1

    cout << endl << "complex1 = "; complex1.displayComplexNumber();
    cout << "complex2 = "; complex2.displayComplexNumber();
    cout << "complex3 = "; complex3.displayComplexNumber();

    ComplexNumber complex4 = addComplexNumbers(complex1, complex2, complex3);
    cout << "complex4 = "; complex4.displayComplexNumber();
    return 0;
}
