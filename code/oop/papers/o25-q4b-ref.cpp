#include <iostream>
using namespace std;
void modifyValue(int &x) {
    int counter = 5;
    counter++;
    x += counter;}
int main() {
    int a = 15;
    modifyValue(a);
    cout << "After first call: a = " << a << endl;
    modifyValue(a);
    cout << "After second call: a = " << a << endl;}
