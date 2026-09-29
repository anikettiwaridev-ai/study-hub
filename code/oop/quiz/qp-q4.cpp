#include <iostream>
using namespace std;
class Wallet {
    int *cash;
public:
    Wallet(int c) { cash = new int(c); }
    Wallet(const Wallet &w) { cash = new int(*w.cash); }
    ~Wallet() { delete cash; }
    void spend(int x) { *cash -= x; }
    int left() { return *cash; }
};
int main() {
    Wallet w1(500);
    Wallet w2 = w1;
    w2.spend(200);
    cout << w1.left() << " " << w2.left();
    return 0;
}
