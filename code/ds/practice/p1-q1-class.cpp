#include <iostream>
using namespace std;

class Point {                          // class: members are PRIVATE by default
    int x, y;
    void print() { cout << "(" << x << ", " << y << ")" << endl; }
};

int main() {
    Point p;
    p.x = 5;                           // error: 'int Point::x' is private
    p.y = 7;                           // error
    p.print();                         // error: print() is private too
    return 0;
}
