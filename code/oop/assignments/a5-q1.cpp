#include <iostream>
#include <cmath>
using namespace std;

class Point;                 // forward declaration: calculate mentions Point before Point is complete

// II. A class whose MEMBER function will be a friend of Point.
class calculate {
public:
    Point midPoint(const Point &p1, const Point &p2);   // only declared here: Point is incomplete
};

// III. calculate1 gets access to ALL of Point's privates (friend class).
class calculate1 {
public:
    int dotProduct(const Point &p1, const Point &p2);
    int crossProduct2DMagnitude(const Point &p1, const Point &p2);
    bool equalityOrIdentityCheck(const Point &p1, const Point &p2);
};

class Point {
private:
    int x, y;
public:
    Point(int a = 0, int b = 0) { x = a; y = b; }
    void display() const { cout << "(" << x << ", " << y << ")"; }

    friend double distance(const Point &p1, const Point &p2);              // I.  non-member friend
    friend Point calculate::midPoint(const Point &p1, const Point &p2);    // II. member of another class
    friend class calculate1;                                               // III. whole class
};

// I. Not a member of any class, yet reads x and y: a friend function.
double distance(const Point &p1, const Point &p2) {
    int dx = p2.x - p1.x, dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

// II. Defined AFTER Point is complete, so p1.x and p2.x are known.
Point calculate::midPoint(const Point &p1, const Point &p2) {
    return Point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
}

// III. Every member of calculate1 may read Point's privates.
int calculate1::dotProduct(const Point &p1, const Point &p2) {
    return p1.x * p2.x + p1.y * p2.y;
}
int calculate1::crossProduct2DMagnitude(const Point &p1, const Point &p2) {
    return p1.x * p2.y - p1.y * p2.x;
}
bool calculate1::equalityOrIdentityCheck(const Point &p1, const Point &p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

int main() {
    Point p1(2, 3), p2(6, 6);
    cout << "P1 = "; p1.display(); cout << ", P2 = "; p2.display(); cout << endl;

    cout << "Euclidean distance = " << distance(p1, p2) << endl;

    calculate c;
    cout << "Mid point = "; c.midPoint(p1, p2).display(); cout << endl;

    calculate1 c1;
    cout << "Dot product = " << c1.dotProduct(p1, p2) << endl;
    cout << "2D cross product magnitude = " << c1.crossProduct2DMagnitude(p1, p2) << endl;
    cout << "P1 equal to P2? " << (c1.equalityOrIdentityCheck(p1, p2) ? "true" : "false") << endl;
    cout << "P1 equal to P1? " << (c1.equalityOrIdentityCheck(p1, p1) ? "true" : "false") << endl;
    return 0;
}
