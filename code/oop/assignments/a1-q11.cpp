#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter an integer: ";
    cin >> n;
    // The last binary bit of an odd number is always 1. n & 1 keeps only that bit.
    if (n & 1) cout << n << " is odd" << endl;
    else       cout << n << " is even" << endl;
    return 0;
}
