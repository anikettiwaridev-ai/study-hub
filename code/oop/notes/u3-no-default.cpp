#include <iostream>
using namespace std;
class Complex {
    int real, img;
public:
    Complex(int r, int i) { real = r; img = i; }
};
int main() {
    Complex c1(5, 9);
    Complex c3;
    return 0;
}
