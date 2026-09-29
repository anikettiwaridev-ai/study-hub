#include <iostream>
using namespace std;

class abc {
    int x;
public:
    abc(int a) { x = a; }

    abc &operator++() {          // PREFIX ++a: no dummy int
        ++x;
        return *this;            // the object itself, already incremented
    }

    abc operator++(int) {        // POSTFIX a++: the dummy int only tells them apart
        abc old = *this;         // remember the old value
        ++x;
        return old;              // hand back the OLD value
    }

    int get() const { return x; }
};

int main() {
    abc a1(30);
    abc a2 = ++a1;               // a1 becomes 31, a2 gets 31
    cout << "after a2 = ++a1: a1 = " << a1.get() << ", a2 = " << a2.get() << endl;
    abc a3 = a1++;               // a3 gets 31, then a1 becomes 32
    cout << "after a3 = a1++: a1 = " << a1.get() << ", a3 = " << a3.get() << endl;
    return 0;
}
