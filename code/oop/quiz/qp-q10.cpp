#include <iostream>
using namespace std;
class M {
    int v;
public:
    M(int x) { v = x; cout << "C"; }
    operator int() { cout << "O"; return v; }
};
int main() {
    M m = 5;
    int k = m + 2;
    cout << k;
    return 0;
}
