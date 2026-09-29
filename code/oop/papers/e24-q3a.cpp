#include <iostream>
using namespace std;

class Numbers {
    int a, b;
public:
    // Use 1 of 'this': separate the member a from the parameter a.
    // Use 2: return *this (the object itself) so calls can be chained.
    Numbers &setA(int a) { this->a = a; return *this; }
    Numbers &setB(int b) { this->b = b; return *this; }

    void display() {
        cout << "a = " << this->a << ", b = " << this->b << endl;
    }
    friend int sum(const Numbers &n);   // not a member, but may read a and b
};

int sum(const Numbers &n) {             // no 'this' here: friends are not members
    return n.a + n.b;
}

int main() {
    Numbers n;
    n.setA(12).setB(30);                // chained through the returned *this
    n.display();
    cout << "Sum = " << sum(n) << endl;
    return 0;
}
