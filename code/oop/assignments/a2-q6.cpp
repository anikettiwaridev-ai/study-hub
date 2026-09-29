#include <iostream>
using namespace std;

int main() {
    int x, sum = 0;
    cout << "Enter integers (negative to stop): ";
    while (true) {
        cin >> x;
        if (x < 0) break;       // negative ends input
        if (x == 0) continue;   // zeros are ignored
        sum += x;
    }
    cout << "Sum = " << sum << endl;
    return 0;
}
