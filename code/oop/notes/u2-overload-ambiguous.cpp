#include <iostream>
using namespace std;
void change(float a)  { cout << "float" << endl; }
void change(double a) { cout << "double" << endl; }
int main() {
    change(10);
    return 0;
}
