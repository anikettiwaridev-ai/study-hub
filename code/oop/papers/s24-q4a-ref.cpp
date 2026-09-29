#include <iostream>
using namespace std;
void modifyValue(int &x) {
    static int counter = 0;
    counter++;
    x += counter;}
int main() {
    int a = 5;
    modifyValue(a);
    cout << "After first call: a = " << a << endl;
    modifyValue(a);
    cout << "After second call: a = " << a << endl;}
