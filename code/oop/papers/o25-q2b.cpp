#include <iostream>
using namespace std;
void calculate(int n) {
  static int s = n;
    int a = n;
    s += 2;
    a += 2;
    cout << "n = " << n << ", s = " << s << ", a = " << a << endl;}
int main() {
    calculate(5);
    calculate(10);
    calculate(15);
    return 0;}
