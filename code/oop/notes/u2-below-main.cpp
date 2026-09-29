#include <iostream>
using namespace std;

int add(int a, int b);        // declaration (prototype) ABOVE main

int main() {
    cout << add(2, 3) << endl;  // fine: the compiler already knows add's signature
    return 0;
}

int add(int a, int b) {       // definition BELOW main
    return a + b;
}
