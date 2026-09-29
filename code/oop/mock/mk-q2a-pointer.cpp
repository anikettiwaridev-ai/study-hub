#include <iostream>
using namespace std;
void update(int *p) {
    static int step = 2;
    step *= 2;
    *p += step;
}
int main() {
    int m = 10;
    update(&m);
    cout << "First: m = " << m << endl;
    update(&m);
    cout << "Second: m = " << m << endl;
    return 0;
}
