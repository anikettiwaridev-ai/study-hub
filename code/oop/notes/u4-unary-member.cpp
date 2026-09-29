#include <iostream>
using namespace std;

class abc {
    int x, y;
public:
    abc(int a, int b) { x = a; y = b; }
    // Member, unary: NO parameter. The operand is *this.
    // Build a NEW object; do not change the operand itself.
    abc operator-() const {
        return abc(-x, -y);
    }
    void show() const { cout << "(" << x << ", " << y << ")" << endl; }
};

int main() {
    abc a1(40, 30);
    abc a2 = -a1;          // a1.operator-()
    cout << "a1 = "; a1.show();   // unchanged
    cout << "a2 = "; a2.show();
    return 0;
}
