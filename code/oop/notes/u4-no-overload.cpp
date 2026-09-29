#include <iostream>
using namespace std;
class A {
    int x;
public:
    int operator.(int) { return x; }
};
int main() { return 0; }
