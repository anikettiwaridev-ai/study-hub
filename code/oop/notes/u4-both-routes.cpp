#include <iostream>
using namespace std;
class B;
class A {
public:
    int v = 5;
    operator B() const;
};
class B {
public:
    int v = 0;
    B() {}
    B(const A &a) { v = a.v; }
};
A::operator B() const { B b; b.v = v; return b; }
void take(B b) { cout << b.v; }
int main() {
    A a;
    take(a);
    return 0;
}
