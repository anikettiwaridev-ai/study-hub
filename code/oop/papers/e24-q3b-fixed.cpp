#include <iostream>
using namespace std;

class A {
public:
    int x;
    float y;
    A() { x = 0; y = 0; }             // user-written default constructor
    A(int a, float b) { x = a; y = b; } // parameterized, for chosen values
};

int main() {
    A obj;
    A obj2(5, 2.5);
    cout << "A constructor x,y value ::" << obj.x << ", " << obj.y << endl;
    cout << "A constructor x,y value ::" << obj2.x << ", " << obj2.y << endl;
    return 0;
}
