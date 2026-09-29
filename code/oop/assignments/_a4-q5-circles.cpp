#include <iostream>
#include "Geometry.h"     // the SAME header, included in a second .cpp file
using namespace std;

void reportCircles() {
    cout << "circles.cpp uses Geometry.h too:" << endl;
    cout << "  circle r = 3: area " << circleArea(3) << ", perimeter " << circlePerimeter(3) << endl;
}
