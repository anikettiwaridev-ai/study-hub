#include <iostream>
using namespace std;
class Item {
    int id;
public:
    Item(int i) { id = i; cout << "C" << id << " "; }
    Item(const Item &o) { id = o.id + 10; cout << "K" << id << " "; }
    ~Item() { cout << "D" << id << " "; }
};
void use(Item x) { cout << "use "; }
int main() {
    Item a(1);
    use(a);
    Item *p = new Item(2);
    delete p;
    cout << "end ";
    return 0;
}
