#include <iostream>
using namespace std;

class BankAccount {
    const long accountNumber;    // fixed for the life of the object
    double balance;
public:
    // A const member can only get its value in the member initializer list,
    // the part after the colon. The constructor body is too late: by then
    // the member already exists and assignment to a const is forbidden.
    BankAccount(long accNo, double opening) : accountNumber(accNo), balance(opening) {}

    void deposit(double amt) { if (amt > 0) balance += amt; }
    bool withdraw(double amt) {
        if (amt > balance) { cout << "Insufficient balance" << endl; return false; }
        balance -= amt;
        return true;
    }
    void show() const { cout << "Account " << accountNumber << ": Rs " << balance << endl; }
    // void change() { accountNumber = 5; }   // would not compile: const member
};

int main() {
    BankAccount acc(1234567890L, 1000);
    acc.show();
    acc.deposit(500);
    acc.withdraw(2000);
    acc.withdraw(300);
    acc.show();
    return 0;
}
