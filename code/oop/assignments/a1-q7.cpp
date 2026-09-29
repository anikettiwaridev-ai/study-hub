#include <iostream>
using namespace std;

int main() {
    int a, b, c;
    cout << "Enter three numbers: ";
    cin >> a >> b >> c;
    int largest = (a > b) ? (a > c ? a : c) : (b > c ? b : c);   // nested ?: only
    cout << "Largest = " << largest << endl;
    return 0;
}
