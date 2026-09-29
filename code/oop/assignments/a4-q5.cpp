#include <iostream>
#include "Geometry.h"
using namespace std;

void reportCircles();    // lives in the second module, _a4-q5-circles.cpp

int main() {
    cout << "main.cpp uses Geometry.h:" << endl;
    cout << "  rectangle 4 x 6: area " << rectangleArea(4, 6)
         << ", perimeter " << rectanglePerimeter(4, 6) << endl;
    cout << "  square 5: area " << squareArea(5) << ", perimeter " << squarePerimeter(5) << endl;
    reportCircles();
    return 0;
}
