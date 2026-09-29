#include <iostream>
using namespace std;

class Money {
    int rupees;
public:
    Money(int r) { rupees = r; }
    Money operator+(int n) const { return Money(rupees + n); }        // Money + int
    friend Money operator+(int n, const Money &m);                    // int + Money
    void show() const { cout << "Rs " << rupees << endl; }
};

// 5 + m cannot be a member: the LEFT operand, 5, is not a Money object.
Money operator+(int n, const Money &m) { return Money(n + m.rupees); }

int main() {
    Money m(100);
    (m + 5).show();
    (5 + m).show();
    return 0;
}
