#include <iostream>
using namespace std;

// The quotient comes back through return, the remainder through the reference.
int divide(int a, int b, int &remainder) {
    remainder = a % b;
    return a / b;
}

int main() {
    int r;
    int q = divide(47, 5, r);
    cout << "47 / 5: quotient = " << q << ", remainder = " << r << endl;
    return 0;
}
