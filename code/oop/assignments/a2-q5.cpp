#include <iostream>
using namespace std;

int main() {
    int a, b;
    cout << "Enter a and b: ";
    cin >> a >> b;
    int found = -1;
    for (int i = 1; i <= 1000; i++) {
        if (i % a == 0 && i % b == 0) {
            found = i;
            break;                   // the first one is enough
        }
    }
    if (found == -1) cout << "None between 1 and 1000" << endl;
    else cout << "First number divisible by both = " << found << endl;
    return 0;
}
