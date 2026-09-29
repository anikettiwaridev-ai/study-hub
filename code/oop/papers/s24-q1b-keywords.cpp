#include <iostream>
using namespace std;
int main() {
    auto int a = 5;       // C++98 storage-class syntax
    register int r = 7;   // removed in C++17
    cout << a << r;
    return 0;
}
