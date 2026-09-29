#include <iostream>
using namespace std;
class P1 { char a; double b; char c; };
class P2 { double b; char a; char c; };
int main() {
    cout << sizeof(P1) << " " << sizeof(P2);
    return 0;
}
