#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    if (n < 0) {
        cout << "Factorial is not defined for negative numbers" << endl;
        return 0;
    }

    long long fact = 1;          // 0! = 1, so starting at 1 also handles n = 0
    for (int i = 2; i <= n; i++)
        fact *= i;

    cout << n << "! = " << fact << endl;
    return 0;
}
