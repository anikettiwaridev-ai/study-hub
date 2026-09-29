#include <iostream>
using namespace std;

class abc {
    int x;
public:
    abc(int a) { x = a; }
    friend abc &operator++(abc &a);        // prefix: one parameter, by reference
    friend abc operator++(abc &a, int);    // postfix: the object FIRST, dummy int SECOND
    int get() const { return x; }
};

abc &operator++(abc &a) {                  // no 'this' in a friend: use the parameter
    ++a.x;
    return a;
}

abc operator++(abc &a, int) {
    abc old = a;
    ++a.x;
    return old;
}

int main() {
    abc a1(30);
    abc a2 = ++a1;
    abc a3 = a1++;
    cout << "a1 = " << a1.get() << ", a2 = " << a2.get() << ", a3 = " << a3.get() << endl;
    return 0;
}
