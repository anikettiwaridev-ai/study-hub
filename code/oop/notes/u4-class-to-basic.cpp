#include <iostream>
using namespace std;
class Meters {
    double m;
public:
    Meters(double v) { m = v; }
    operator double() const { return m; }         // class -> double
    explicit operator int() const { return (int)m; }   // class -> int, only when asked
};
int main() {
    Meters a(12.75);
    double d = a;                    // implicit, uses operator double
    int i = static_cast<int>(a);     // explicit, uses operator int
    cout << d << " " << i << endl;
    return 0;
}
