#include <iostream>
using namespace std;
void fun(int n) {
    if (n <= 0) return;
    cout << n;
    fun(n - 2);
    cout << n + 1;
    fun(n - 1);
    cout << n * 2;
}
int main() { fun(4); return 0; }
