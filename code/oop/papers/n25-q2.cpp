#include <iostream>
using namespace std;

class Counter {
    int id;                          // non-static: every object has its own
    static int created;              // static: ONE copy shared by all objects
    static int destroyed;

public:
    Counter() {
        created++;
        id = created;
        cout << "Object " << id << " created" << endl;
    }
    ~Counter() {
        destroyed++;
        cout << "Object " << id << " destroyed" << endl;
    }

    void show() {                    // non-static: has 'this', can use both kinds
        cout << "I am object " << id << " of " << created << endl;
    }

    static void report() {           // static: no 'this', only static members
        cout << "Created = " << created << ", destroyed = " << destroyed
             << ", alive = " << created - destroyed << endl;
    }
};

int Counter::created = 0;            // defined and initialised once, outside the class
int Counter::destroyed = 0;

int main() {
    Counter::report();               // callable with no object at all
    Counter c1, c2;
    c2.show();
    {
        Counter c3;                  // lives only inside this block
        Counter::report();
    }                                // c3 destroyed here
    Counter::report();
    return 0;
}                                    // c2, then c1 destroyed here
