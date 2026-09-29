#include <iostream>
using namespace std;

class A {
    int v;
public:
    A(int x = 0) { v = x; }
    A(const A &o) { v = o.v; cout << "(copy) "; }
    A operator=(const A &o) { v = o.v; return *this; }   // returns by VALUE
    int get() const { return v; }
};

int main() {
    A a1(1), a2(2), a3(3);
    a1 = a2 = a3;                    // still works: every value ends up 3 (with extra copies)
    cout << endl << a1.get() << a2.get() << a3.get() << endl;
    (a1 = a2) = A(7);                // assigns 7 to a TEMPORARY copy, not to a1
    cout << endl << "a1 = " << a1.get() << " (not 7)" << endl;
    return 0;
}
