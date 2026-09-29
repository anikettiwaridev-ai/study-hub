#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 100; i++) {
        if (i == 75) break;          // stop the whole loop at 75
        if (i % 3 == 0) continue;    // skip just this number
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
