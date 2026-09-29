#include <iostream>
using namespace std;

void greet() { cout << "1. no argument, no return value" << endl; }
int  lucky() { return 7; }                                       // 2. no argument, returns
void show(int n) { cout << "3. argument " << n << ", no return value" << endl; }
int  square(int n) { return n * n; }                             // 4. argument and return

int main() {
    greet();
    cout << "2. no argument, returns " << lucky() << endl;
    show(5);
    cout << "4. argument 6, returns " << square(6) << endl;
    return 0;
}
