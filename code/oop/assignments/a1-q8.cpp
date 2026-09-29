#include <iostream>
using namespace std;

int main() {
    int x;
    x = (10, 20, 30);      // comma operator: evaluates 10, then 20, then 30; value is the LAST
    cout << "x = " << x << endl;

    int y;
    y = 10, 20, 30;        // no brackets: = runs first, so y = 10; 20 and 30 are thrown away
    cout << "y = " << y << endl;

    int i = 0;
    int z = (i++, i++, i * 100);   // the comma is a sequence point: left side fully done first
    cout << "i = " << i << ", z = " << z << endl;
    return 0;
}
