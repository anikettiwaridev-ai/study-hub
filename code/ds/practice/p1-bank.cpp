#include <iostream>
using namespace std;

// Practice sheet 1, Q3 and Q10.
class BankAccount {
    double balance;
public:
    class InvalidBalance {};                   // nested classes used as exception types
    class InsufficientFunds {};

    BankAccount(double start) {
        if (start < 0) throw InvalidBalance();  // the invariant: never negative
        balance = start;
    }
    void deposit(double amount) { balance += amount; }
    void withdraw(double amount) {
        if (amount > balance) throw InsufficientFunds();
        balance -= amount;
    }
    double getBalance() const { return balance; }
};

int main() {
    try {
        BankAccount bad(-50);
    } catch (BankAccount::InvalidBalance&) {
        cout << "InvalidBalance caught" << endl;
    }
    try {
        BankAccount acc(100);
        acc.withdraw(30);
        cout << "balance " << acc.getBalance() << endl;
        acc.withdraw(500);
    } catch (BankAccount::InsufficientFunds&) {
        cout << "InsufficientFunds caught" << endl;
    }

    BankAccount* accounts[3];                  // Q10: an array of 3 pointers
    double starts[] = {100, 250, 0};
    for (int i = 0; i < 3; i++) accounts[i] = new BankAccount(starts[i]);
    for (int i = 0; i < 3; i++) accounts[i]->deposit(50);
    for (int i = 0; i < 3; i++) cout << "account " << i << ": " << accounts[i]->getBalance() << endl;
    for (int i = 0; i < 3; i++) { delete accounts[i]; accounts[i] = nullptr; }
    return 0;
}
