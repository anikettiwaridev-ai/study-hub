#include <iostream>
#include <cmath>
using namespace std;

class Circle;   // forward declaration: Point's friend list mentions Circle

class Point {
    double x, y;
public:
    Point(double a, double b) { x = a; y = b; }
    friend bool isInside(const Point &p, const Circle &c);
    friend bool intersect(const Circle &a, const Circle &b);
    friend class Circle;
};

class Circle {
    Point centre;
    double radius;
public:
    Circle(double cx, double cy, double r) : centre(cx, cy) {
        if (r <= 0) {                       // validate before any calculation
            cout << "Invalid radius " << r << ", using 1" << endl;
            r = 1;
        }
        radius = r;
    }
    friend bool isInside(const Point &p, const Circle &c);
    friend bool intersect(const Circle &a, const Circle &b);
};

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// Friend of BOTH classes: needs Point's x, y and Circle's centre and radius.
bool isInside(const Point &p, const Circle &c) {
    return dist(p.x, p.y, c.centre.x, c.centre.y) <= c.radius;
}

// Two circles meet when the distance between centres is at most r1 + r2
// and at least |r1 - r2| (otherwise one sits inside the other without touching).
bool intersect(const Circle &a, const Circle &b) {
    double d = dist(a.centre.x, a.centre.y, b.centre.x, b.centre.y);
    return d <= a.radius + b.radius && d >= fabs(a.radius - b.radius);
}

int main() {
    Circle c1(0, 0, 5), c2(8, 0, 4), c3(20, 20, 2), bad(1, 1, -3);
    Point p(3, 4), q(6, 1);
    cout << "(3,4) inside c1? " << (isInside(p, c1) ? "yes" : "no") << endl;
    cout << "(6,1) inside c1? " << (isInside(q, c1) ? "yes" : "no") << endl;
    cout << "c1 and c2 intersect? " << (intersect(c1, c2) ? "yes" : "no") << endl;
    cout << "c1 and c3 intersect? " << (intersect(c1, c3) ? "yes" : "no") << endl;
    return 0;
}
