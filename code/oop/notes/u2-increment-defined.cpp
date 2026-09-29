#include <iostream>
using namespace std;
int main() {
    int a = 5;
    int c = ++a;      // a becomes 6 first, c gets 6
    int d = a++;      // d gets 6, then a becomes 7
    cout << "a = " << a << ", c = " << c << ", d = " << d << endl;
    int b = (a++, ++a);   // the comma is a sequence point: fully defined
    cout << "a = " << a << ", b = " << b << endl;
    return 0;
}
