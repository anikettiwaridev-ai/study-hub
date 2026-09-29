#include <iostream>
using namespace std;
class Circle {
    double r;
public:
    Circle(double x) { r = x; }
    double area();                    // declared inside
    double perimeter() { return 2 * 3.14159 * r; }   // defined inside: implicitly inline
};
inline double Circle::area() {        // defined outside, made inline with the keyword
    return 3.14159 * r * r;
}
int main() {
    Circle c(2);
    cout << c.area() << " " << c.perimeter() << endl;
    return 0;
}
