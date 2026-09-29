#include <iostream>
using namespace std;

class Counter {
    int id;                    // non-static: one per object
    static int count;          // static: one shared copy
public:
    Counter() { count++; id = count; }

    static int getCount() {    // static member function
        return count;          // fine: static member
        // return id;          // ERROR: id of WHICH object? There is no 'this'.
    }

    static void showId(const Counter &c) {   // the way round it: pass an object in
        cout << "id = " << c.id << endl;
    }
};

int Counter::count = 0;        // static data member defined once, outside the class

int main() {
    cout << "Before any object: " << Counter::getCount() << endl;   // no object needed
    Counter c1, c2, c3;
    cout << "After three: " << Counter::getCount() << endl;         // ClassName::function()
    cout << "Through an object also works: " << c1.getCount() << endl;
    Counter::showId(c2);
    return 0;
}
