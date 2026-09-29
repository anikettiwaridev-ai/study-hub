#include <iostream>
using namespace std;

class A {
    int *b;
public:
    A(int v) { b = new int(v); }
    A(const A &o) { b = new int(*o.b); }             // deep copy constructor
    ~A() { delete b; }

    A &operator=(const A &o) {                        // deep copy assignment
        if (this == &o) return *this;                 // 1. self-assignment guard: a = a
        delete b;                                     // 2. free what we hold (no leak)
        b = new int(*o.b);                            // 3. our own block, copied value
        return *this;                                 // 4. by reference: allows a1 = a2 = a3
    }

    void set(int v) { *b = v; }
    int get() const { return *b; }
};

int main() {
    A o1(40), o2(50), o3(60);
    o1 = o2 = o3;                    // right to left: o2 = o3 first, then o1 = (that result)
    cout << o1.get() << " " << o2.get() << " " << o3.get() << endl;
    o2.set(99);                      // isolation: changing o2 leaves o1 and o3 alone
    cout << o1.get() << " " << o2.get() << " " << o3.get() << endl;
    o1 = o1;                         // survives thanks to the guard
    cout << o1.get() << endl;
    return 0;
}
