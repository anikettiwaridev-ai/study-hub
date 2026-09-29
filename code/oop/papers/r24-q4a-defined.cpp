#include <iostream>
using namespace std;

// The same logic with x = ++x + x++ + x++ split into separate statements,
// so every step happens in a fixed order. This is the "textbook" reading.
void modifyValue(int &x, bool useStatic) {
    static int staticCounter = 0;
    int localCounter = 0;
    int &counter = useStatic ? staticCounter : localCounter;
    counter++;
    x += counter;
    cout << "value of x is" << x << endl;

    int t1 = ++x;   // x goes up by 1, t1 gets the new value
    int t2 = x++;   // t2 gets x, then x goes up by 1
    int t3 = x++;   // t3 gets x, then x goes up by 1
    x = t1 + t2 + t3;
}

int main() {
    cout << "Local counter:" << endl;
    int a = 8;
    modifyValue(a, false);
    cout << "After first call: a = " << a << endl;
    modifyValue(a, false);
    cout << "After second call: a = " << a << endl;

    cout << "Static counter:" << endl;
    int b = 8;
    modifyValue(b, true);
    cout << "After first call: a = " << b << endl;
    modifyValue(b, true);
    cout << "After second call: a = " << b << endl;
    return 0;
}
