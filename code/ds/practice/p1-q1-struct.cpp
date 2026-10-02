#include <iostream>
using namespace std;

struct Point {                         // struct: members are PUBLIC by default
    int x, y;
    void print() { cout << "(" << x << ", " << y << ")" << endl; }
};

int main() {
    Point p;
    p.x = 5;                           // compiles
    p.y = 7;                           // compiles
    p.print();
    return 0;
}
