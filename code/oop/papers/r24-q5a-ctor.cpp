#include <iostream>
using namespace std;

class Computer {
    int price;
public:
    Computer(int p) { price = p; }
    int getPrice() const { return price; }   // Mobile needs to read the price
};

class Mobile {
    int price;
public:
    Mobile() { price = 0; }
    // Class to class, done in the DESTINATION class: a one-argument constructor
    // that takes the source object.
    Mobile(const Computer &c) { price = c.getPrice(); }
    void display() { cout << "Mobile price = " << price << endl; }
};

int main() {
    Computer comp(45000);
    Mobile mob;
    mob = comp;       // Mobile(comp) builds a temporary Mobile, then it is assigned
    mob.display();
    return 0;
}
