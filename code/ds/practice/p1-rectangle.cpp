#include <iostream>
using namespace std;

// Practice sheet 1, Q2, Q4 and Q6.
class Rectangle {
    double length, width;
public:
    Rectangle();                               // defaults: 1.0 x 1.0
    Rectangle(double l, double w);
    void setLength(double l);
    void setWidth(double w);
    double getArea() const;
    double getPerimeter() const;
    void display() const;                      // const: promises not to change the object
};

Rectangle::Rectangle() { length = 1.0; width = 1.0; }
Rectangle::Rectangle(double l, double w) { length = l; width = w; }
void Rectangle::setLength(double l) { length = l; }
void Rectangle::setWidth(double w) { width = w; }
double Rectangle::getArea() const { return length * width; }
double Rectangle::getPerimeter() const { return 2 * (length + width); }
void Rectangle::display() const {
    cout << length << " x " << width << ", area " << getArea() << endl;
}

// Q6: a non-member "helper". It only needs the public getArea(), so it need not be a friend.
bool operator==(const Rectangle& a, const Rectangle& b) {
    return a.getArea() == b.getArea();
}

int main() {
    Rectangle r1;                              // Q4.1: a normal local object
    Rectangle* r2 = new Rectangle(3, 4);       // Q4.2: on the heap, through a pointer
    r1.display();
    r2->display();
    cout << "areas: " << r1.getArea() << " and " << r2->getArea() << endl;   // Q4.3: . vs ->
    delete r2;                                 // Q4.4
    r2 = nullptr;

    Rectangle a(2, 6), b(3, 4);                // Q6: different sides, same area
    cout << "a == b: " << (a == b ? "equal" : "not equal") << endl;
    return 0;
}
