#include <iostream>
using namespace std;
int main() {
    int i = 7;
    double d = i;                 // implicit: int -> double, safe
    int t = 9.99;                 // implicit: double -> int, fraction CUT, not rounded
    char c = 65;                  // implicit: int -> char
    cout << d << " " << t << " " << c << endl;
    cout << 7 / 2 << " " << 7 / 2.0 << " " << (double)7 / 2 << " " << static_cast<int>(3.9) << endl;
    cout << 'A' + 1 << " " << char('A' + 1) << endl;   // char promoted to int in arithmetic
    return 0;
}
