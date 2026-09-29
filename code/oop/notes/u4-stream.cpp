#include <iostream>
using namespace std;

class Point {
    int x, y;
public:
    Point(int a = 0, int b = 0) { x = a; y = b; }
    // Friends, because the LEFT operand is cout / cin, not a Point.
    friend ostream &operator<<(ostream &out, const Point &p);
    friend istream &operator>>(istream &in, Point &p);
};

ostream &operator<<(ostream &out, const Point &p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;              // returned by reference so << can be chained
}

istream &operator>>(istream &in, Point &p) {   // p NOT const: we write into it
    in >> p.x >> p.y;
    return in;
}

int main() {
    Point p, q(7, 8);
    cout << "Enter x and y: ";
    cin >> p;
    cout << endl << "p = " << p << ", q = " << q << endl;   // chained
    return 0;
}
