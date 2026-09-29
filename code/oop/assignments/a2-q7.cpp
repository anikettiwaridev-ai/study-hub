#include <iostream>
using namespace std;

int main() {
    int found = 0;
    for (int n = 101; ; n++) {
        bool prime = true;
        for (int i = 2; i * i <= n; i++)
            if (n % i == 0) { prime = false; break; }
        if (!prime) continue;        // not prime: skip to the next n
        cout << n << " ";
        found++;
        if (found == 5) break;       // five primes found: stop
    }
    cout << endl;
    return 0;
}
