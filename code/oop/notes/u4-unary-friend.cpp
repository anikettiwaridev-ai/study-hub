#include <iostream>
using namespace std;

class abc {
    int x, y;
public:
    abc(int a, int b) { x = a; y = b; }
    friend abc operator-(const abc &a);   // friend, unary: ONE parameter (no 'this')
    void show() const { cout << "(" << x << ", " << y << ")" << endl; }
};

abc operator-(const abc &a) {             // same signature as the declaration
    return abc(-a.x, -a.y);
}

int main() {
    abc a1(40, 30);
    abc a2 = -a1;          // operator-(a1)
    cout << "a1 = "; a1.show();
    cout << "a2 = "; a2.show();
    return 0;
}
