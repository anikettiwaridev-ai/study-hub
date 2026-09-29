#include <iostream>
using namespace std;
void change(int a)    { cout << "int " << a << endl; }
void change(double a) { cout << "double " << a << endl; }
int main() {
    change(10);      // exact match: int
    change('A');     // char -> int is a PROMOTION, beats char -> double
    change(2.5f);    // float -> double is a PROMOTION
    change(3.14);    // exact match: double
    return 0;
}
