#include <iostream>
using namespace std;

class BankAccount {
private:
    double balance;            // hidden: nobody outside can write balance = -500

public:
    BankAccount() { balance = 0; }

    void deposit(double amount) {          // public method: the only way in
        if (amount <= 0) {
            cout << "Rejected: deposit must be positive" << endl;
            return;
        }
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Rejected: not enough balance" << endl;
            return false;
        }
        balance -= amount;
        return true;
    }

    double getBalance() const { return balance; }   // read access, no write access
};

int main() {
    BankAccount acc;
    acc.deposit(1000);
    acc.deposit(-50);          // the class refuses bad data
    acc.withdraw(5000);        // and impossible operations
    acc.withdraw(300);
    // acc.balance = 999999;   // would not compile: balance is private
    cout << "Balance = " << acc.getBalance() << endl;
    return 0;
}
