#include <iostream>
using namespace std;
void fun(int a = 10, int b) { cout << a << b; }
int main() { fun(1, 2); return 0; }
