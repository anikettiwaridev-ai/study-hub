#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "How many numbers? ";
    cin >> n;

    int positive = 0, negative = 0, zeros = 0;
    long long sumPositive = 0, sumNegative = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x > 0)      { positive++; sumPositive += x; }
        else if (x < 0) { negative++; sumNegative += x; }
        else            zeros++;
    }
    cout << endl << "Positive: " << positive << " (sum " << sumPositive << ")" << endl;
    cout << "Negative: " << negative << " (sum " << sumNegative << ")" << endl;
    cout << "Zeros:    " << zeros << endl;
    return 0;
}
