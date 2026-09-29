#include <iostream>
using namespace std;
class Box {
    int *p;
public:
    Box(int v) { p = new int(v); }
    Box(const Box &b) { p = new int(*b.p); }     // deep: a NEW block, the VALUE copied
    ~Box() { delete p; }
    void set(int v) { *p = v; }
    void show() { cout << *p << endl; }
};
int main() {
    Box b1(5);
    Box b2 = b1;
    b2.set(9);
    b1.show();      // still 5: the copy has its own block
    b2.show();
    return 0;
}
