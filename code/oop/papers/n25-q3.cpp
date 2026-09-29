#include <iostream>
using namespace std;
void modifyValue(int x) {
x = x + 5;
cout << "Inside modifyValue function: x = " << x << endl;
}
void modifyReference(int &y)
{ y = y + 5;
cout << "Inside modifyReference function: y = " << y << endl;
}
int main() {
int a = 10, b = 20;
modifyValue(a);
cout << "After modifyValue function: a = " << a << endl; modifyReference(b);
cout << "After modifyReference function: b = " << b << endl; modifyValue(b);
cout << "After modifyValue with b: b = " << b << endl; modifyReference(a);
cout << "After modifyReference with a: a = " << a << endl; return 0;}
