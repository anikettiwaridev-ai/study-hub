#include <iostream>
using namespace std;
void change(int a)            { cout << "one" << endl; }
void change(int a, int b = 10){ cout << "two" << endl; }
int main() {
    change(10);
    return 0;
}
