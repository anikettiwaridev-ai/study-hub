#include <iostream>
using namespace std;
int main() {
    int a = 3, b = 5;
    int x = (a++, b++, (++b, a + b));
    cout<<x;
    return 0;}
