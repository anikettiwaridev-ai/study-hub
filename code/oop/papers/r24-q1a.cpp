#include <iostream>
using namespace std;

// Same name, different parameter lists: function overloading.
int area(int side)               { return side * side; }              // square
int area(int length, int width)  { return length * width; }           // rectangle
double area(double radius)       { return 3.14159 * radius * radius; } // circle

int main() {
    cout << "Square:    " << area(4) << endl;       // exact match: area(int)
    cout << "Rectangle: " << area(4, 5) << endl;    // two ints: area(int, int)
    cout << "Circle:    " << area(2.0) << endl;     // double: area(double)
    return 0;
}
