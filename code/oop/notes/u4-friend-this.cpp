#include <iostream>
using namespace std;
class abc {
    int x;
public:
    abc(int a) { x = a; }
    friend abc operator++(abc &a);
};
abc operator++(abc &a) {
    ++a.x;
    return *this;
}
int main() { abc a(1); ++a; return 0; }
