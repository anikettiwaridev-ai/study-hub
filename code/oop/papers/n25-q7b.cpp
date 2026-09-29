#include <iostream>
#include <cmath>
using namespace std;

// Assumption: one class that computes areas through the overloaded
// function-call operator (). The number of arguments picks the shape:
//   1 argument  -> circle (radius)
//   2 arguments -> rectangle (length, breadth)
//   3 arguments -> triangle (three sides, Heron's formula)
class Area {
public:
    double operator()(double radius) {
        return 3.14159 * radius * radius;
    }
    double operator()(double length, double breadth) {
        return length * breadth;
    }
    double operator()(double a, double b, double c) {
        double s = (a + b + c) / 2;                 // semi-perimeter
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
};

int main() {
    Area area;
    cout << "Area of triangle (3, 4, 5) = " << area(3, 4, 5) << endl;
    cout << "Area of circle (r = 7)      = " << area(7) << endl;
    cout << "Area of rectangle (4 x 6)   = " << area(4, 6) << endl;
    return 0;
}
