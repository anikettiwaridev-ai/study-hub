#include <iostream>
using namespace std;
int a = 0, b = 0;
void printA() {
    static int a = 2;
    int b = 1;
    a += ++b;
    cout << a << " " << b << endl;
}
int main() {
    static int a = 1;
    printA();
    a = a + 1;
    printA();
    cout << a << " " << b << endl;
    return 0;
}
