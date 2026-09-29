#include <iostream>
using namespace std;
int main() {
    int a = 8, b;
    b = (a++, ++a, a >> 2);
    cout << a << " " << b;
    return 0;
}
