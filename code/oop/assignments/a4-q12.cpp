#include <iostream>
using namespace std;

class Account {
public:
    long number;
    double balance;
    Account(long n, double b) { number = n; balance = b; }
    void show() const { cout << "  " << number << ": Rs " << balance << endl; }
};

// Pointers can be null, so check them BEFORE touching anything.
// Everything is validated first; only then are both accounts changed.
bool transfer(Account *from, Account *to, double amount) {
    if (from == nullptr || to == nullptr) { cout << "Failed: null account" << endl; return false; }
    if (from == to)                       { cout << "Failed: same account" << endl; return false; }
    if (amount <= 0)                      { cout << "Failed: invalid amount" << endl; return false; }
    if (from->balance < amount)           { cout << "Failed: insufficient balance" << endl; return false; }
    from->balance -= amount;
    to->balance += amount;
    cout << "Transferred Rs " << amount << endl;
    return true;
}

int main() {
    Account a(1001, 5000), b(1002, 1000);
    transfer(&a, &b, 1500);
    transfer(&a, nullptr, 100);
    transfer(&b, &a, 9000);
    transfer(&a, &b, -5);
    a.show();
    b.show();
    return 0;
}
