#include <iostream>
using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

// Copies the DISTINCT primes of arr into primes[]; returns how many.
int findPrimes(const int arr[], int n, int primes[]) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (!isPrime(arr[i])) continue;
        bool seen = false;
        for (int j = 0; j < count; j++) if (primes[j] == arr[i]) seen = true;
        if (!seen) primes[count++] = arr[i];
    }
    return count;
}

// How many times does value occur in arr?
int countOccurrences(const int arr[], int n, int value) {
    int c = 0;
    for (int i = 0; i < n; i++) if (arr[i] == value) c++;
    return c;
}

// Fills freq[] for each distinct prime and returns the most frequent one.
int mostFrequentPrime(const int arr[], int n, const int primes[], int freq[], int count) {
    int best = -1, bestFreq = 0;
    for (int i = 0; i < count; i++) {
        freq[i] = countOccurrences(arr, n, primes[i]);
        if (freq[i] > bestFreq) { bestFreq = freq[i]; best = primes[i]; }
    }
    return best;
}

// Sorts primes by frequency, smallest first (ties: smaller prime first).
void sortByFrequency(int primes[], int freq[], int count) {
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - 1 - i; j++) {
            bool swapNeeded = freq[j] > freq[j + 1] ||
                              (freq[j] == freq[j + 1] && primes[j] > primes[j + 1]);
            if (swapNeeded) {
                int t = freq[j];   freq[j] = freq[j + 1];     freq[j + 1] = t;
                t = primes[j];     primes[j] = primes[j + 1]; primes[j + 1] = t;
            }
        }
}

// The one function that calls the others and shows the results.
void report(const int arr[], int n) {
    int primes[100], freq[100];
    int count = findPrimes(arr, n, primes);
    if (count == 0) { cout << "No primes" << endl; return; }
    int best = mostFrequentPrime(arr, n, primes, freq, count);
    cout << "Most frequent prime: " << best << endl;
    sortByFrequency(primes, freq, count);
    cout << "Primes in ascending order of frequency:" << endl;
    for (int i = 0; i < count; i++)
        cout << "  " << primes[i] << " appears " << freq[i] << " time(s)" << endl;
}

int main() {
    int n, arr[100];
    cout << "How many numbers? ";
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];
    cout << endl;
    report(arr, n);
    return 0;
}
