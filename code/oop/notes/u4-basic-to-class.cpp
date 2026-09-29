#include <iostream>
using namespace std;
class Meters {
    double m;
public:
    Meters() { m = 0; }
    Meters(double v) { m = v; }            // basic -> class
    void show() const { cout << m << " m" << endl; }
};
int main() {
    Meters a = 5.5;       // implicit
    Meters b;
    b = 12;               // implicit: int -> double -> Meters(12.0)
    Meters c(3.0);        // explicit call
    Meters d = Meters(7); // explicit, functional style
    a.show(); b.show(); c.show(); d.show();
    return 0;
}
