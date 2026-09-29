#include <iostream>
using namespace std;

// Second reading of the question: overload a BINARY operator.
// A Length object times a Length object gives an area.
class Length {
    double value;
public:
    Length(double v) { value = v; }
    double operator*(const Length &other) const { return value * other.value; }
};

class Radius {
    double r;
public:
    Radius(double v) { r = v; }
    double operator!() const { return 3.14159 * r * r; }   // unary: "area of" this radius
};

int main() {
    Length l(4), b(6);
    Length base(10), height(5);
    Radius r(7);
    cout << "Rectangle area = " << l * b << endl;
    cout << "Triangle area  = " << 0.5 * (base * height) << endl;
    cout << "Circle area    = " << !r << endl;
    return 0;
}
