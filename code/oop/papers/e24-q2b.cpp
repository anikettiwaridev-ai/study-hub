#include <iostream>
using namespace std;

int main() {
    // A nested if inside a nested for: print the pairs (i, j) where
    // i is less than j AND their sum is even.
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            if (i < j) {
                if ((i + j) % 2 == 0) {
                    cout << "(" << i << ", " << j << ") ";
                }
            }
        }
    }
    cout << endl;
    return 0;
}
