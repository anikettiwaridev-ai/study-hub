#include <iostream>
using namespace std;

class Rupees {
    double amount;
public:
    Rupees(double a = 0) { amount = a; }
    double value() const { return amount; }
};

class Dollars {
    double amount;
public:
    Dollars(double a) { amount = a; }
    // Class to class inside the SOURCE: a conversion operator to Rupees.
    operator Rupees() const { return Rupees(amount * 83.0); }
};

int main() {
    Dollars d(12);
    Rupees r;
    r = d;                         // d.operator Rupees(), then assignment
    cout << "12 dollars = Rs " << r.value() << endl;
    return 0;
}
