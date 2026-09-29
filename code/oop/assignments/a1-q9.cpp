#include <iostream>
using namespace std;
int main() {
    int a, b, c;
    a = (b = 5, c = 10, b + c);
    int x = 10;
    x = (x += 5, x *= 2, x -= 4);
    cout<<a<<x;
    return 0;
}
