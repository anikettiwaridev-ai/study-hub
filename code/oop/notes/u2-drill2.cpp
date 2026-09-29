#include <iostream>
using namespace std;
int main() {
    int b = 10, a = 5;
    int c = ++a + b-- - --b + a++;
    cout << a << " " << b << " " << c;
    return 0;
}
