#include <iostream>
using namespace std;
int main() {
    int a = 5, b = 9;
    int max = (a > b) ? a : b;          // condition ? if-true : if-false
    cout << max << endl;
    cout << (a % 2 == 0 ? "even" : "odd") << endl;
    int x = 3;
    int r = x > 2 ? x < 5 ? 1 : 2 : 3;   // ?: groups right to left: x>2 ? (x<5 ? 1 : 2) : 3
    cout << r << endl;
    return 0;
}
