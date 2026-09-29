#include <iostream>
using namespace std;

class Item {
public:
    Item() { cout << "D "; }
    Item(int) { cout << "P "; }
    Item(const Item &) { cout << "C "; }
    Item &operator=(const Item &) { cout << "A "; return *this; }
};

void show(Item i) {}                 // by value: the argument is COPIED in
void look(const Item &i) {}          // by reference: nothing is copied

int main() {
    Item a(5);        // line 1
    Item b = a;       // line 2
    Item c;           // line 3
    c = b;            // line 4
    show(a);          // line 5
    look(a);          // line 6
    Item d = 7;       // line 7
    return 0;
}
