#include <iostream>
using namespace std;

class Mobile {
    int price;
public:
    Mobile() { price = 0; }
    Mobile(int p) { price = p; }
    void display() { cout << "Mobile price = " << price << endl; }
};

class Computer {
    int price;
public:
    Computer(int p) { price = p; }
    // Class to class, done in the SOURCE class: a conversion operator.
    operator Mobile() const {
        return Mobile(price);
    }
};

int main() {
    Computer comp(45000);
    Mobile mob;
    mob = comp;       // comp.operator Mobile() builds a Mobile, then it is assigned
    mob.display();
    return 0;
}
