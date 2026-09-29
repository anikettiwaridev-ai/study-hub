#include <iostream>
using namespace std;
class Score {
    int s;
public:
    Score(int v) { s = v; }
    Score operator++()    { ++s; cout << "pre "; return *this; }
    Score operator++(int) { Score old = *this; s += 10; cout << "post "; return old; }
    int get() { return s; }
};
int main() {
    Score a(1);
    Score b = a++;
    Score c = ++a;
    cout << a.get() << " " << b.get() << " " << c.get();
    return 0;
}
