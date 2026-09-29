#include <iostream>
using namespace std;
int main() {
    int a;
    a = (cout << "abc", 2);
    cout << a;
    return 0;
}
