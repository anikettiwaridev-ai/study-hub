#include <iostream>
using namespace std;

void toBinary(int n) {             // print AFTER the call: runs while the stack unwinds
    if (n == 0) return;
    toBinary(n / 2);
    cout << n % 2;
}

void g(int n) {                    // print before AND after the call
    if (n <= 0) return;
    cout << n << " ";
    g(n - 2);
    cout << n << " ";
}

int fun(int n) {                   // Oct 2022 Q1b: McCarthy's 91 function
    if (n > 100) return n - 10;
    return fun(fun(n + 11));
}

int main() {
    toBinary(13); cout << endl;
    g(5); cout << endl;
    cout << fun(99) << " " << fun(50) << " " << fun(105) << endl;
    return 0;
}
