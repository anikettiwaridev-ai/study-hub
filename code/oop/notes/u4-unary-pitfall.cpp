#include <iostream>
using namespace std;
class abc {
    int x, y;
public:
    abc(int a, int b) { x = a; y = b; }
    abc operator-() { x = -x; y = -y; return *this; }   // changes the operand itself
    void show() const { cout << "(" << x << ", " << y << ")" << endl; }
};
int main() {
    abc a1(40, 30);
    abc a2 = -a1;
    cout << "a1 = "; a1.show();
    cout << "a2 = "; a2.show();
    return 0;
}
