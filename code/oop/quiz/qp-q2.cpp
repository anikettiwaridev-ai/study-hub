#include <iostream>
using namespace std;
int main() {
    int a = 1, b = 2;
    int c = (a += b, b += a, a * b);
    cout << a << b << c;
    return 0;
}
