#include <iostream>
using namespace std;
int main() {
    int x = 2, y;
    y = (x++, x += 3, x * 2);
    int z = x, w = (y, x);
    cout << x << " " << y << " " << z << " " << w;
    return 0;
}
