#include <iostream>
using namespace std;

// Unary * (dereference) CAN be overloaded; smart pointers do exactly this.
class IntBox {
    int *p;
public:
    IntBox(int v) { p = new int(v); }
    ~IntBox() { delete p; }
    IntBox(const IntBox &) = delete;
    int &operator*() { return *p; }
};

int main() {
    IntBox box(5);
    *box = 42;                  // box.operator*() returns a reference into the box
    cout << *box << endl;
    return 0;
}
