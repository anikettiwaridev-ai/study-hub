#include <iostream>
using namespace std;
class BankAccount {
    const long accountNumber;
    double balance;
public:
    BankAccount(long accNo, double opening) {
        accountNumber = accNo;
        balance = opening;
    }
};
int main() {
    BankAccount acc(123, 1000);
    return 0;
}
