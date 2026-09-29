#include <iostream>
using namespace std;
int main() {
    int a = 5;
    int b = a++ + ++a;
    cout << a << " " << b;
    return 0;
}
