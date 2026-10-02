#include <iostream>
using namespace std;

int main() {
    int vals[] = {4, 7, 11};
    int *p = vals;                 // the array's name is the address of vals[0]
    cout << *p << " " << *(p + 2) << " " << p[1] << endl;

    p += 2;                        // moves 2 ints forward, not 2 bytes
    cout << "ints between p and vals: " << p - vals << endl;

    int x = 10;
    const int *pc = &x;            // pointer to const: *pc = 5 is an error, pc = &other is fine
    int *const cp = &x;            // const pointer:    cp = &other is an error, *cp = 5 is fine
    *cp = 20;
    cout << "*pc = " << *pc << endl;   // 20: both point at the same x

    int *d = new int(5);
    int *e = d;                    // two pointers, ONE heap block
    delete d;                      // freed once; delete e now would free it twice
    d = e = nullptr;               // both were dangling: reset both
    cout << "reset: " << (e == nullptr) << endl;
    return 0;
}
