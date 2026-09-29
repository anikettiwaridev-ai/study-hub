#include <iostream>
using namespace std;
class Level {
    int n;
public:
    Level(int x) { n = x; }
    Level &operator++() { ++n; return *this; }
    int get() { return n; }
};
int main() {
    Level a(5);
    ++(++a);
    cout << a.get();
    return 0;
}
