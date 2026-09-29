#include <iostream>
#include "GeometryNoInline.h"
using namespace std;
void other();
int main() {
    cout << squareArea(3);
    other();
    return 0;
}
