#include <iostream>
using namespace std;

bool isEven(int num) {
    return num % 2 == 0;       // remainder 0 when divided by 2 means even
}

int main() {
    int n;
    cout << "Enter an integer: ";
    cin >> n;
    if (isEven(n))
        cout << n << " is even" << endl;
    else
        cout << n << " is odd" << endl;
    return 0;
}
