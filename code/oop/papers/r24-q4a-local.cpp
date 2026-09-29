#include <iostream>
using namespace std;
void modifyValue(int &x) {
   int counter = 0;
    counter++;
    x += counter;
    cout<<"value of x is"<<x<<endl;
    x=++x + x++ +x++;}
int main() {
    int a = 8;
    modifyValue(a);
    cout << "After first call: a = " << a << endl;
    modifyValue(a);
    cout << "After second call: a = " << a << endl;}
