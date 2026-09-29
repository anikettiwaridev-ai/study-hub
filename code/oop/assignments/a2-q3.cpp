#include <iostream>
using namespace std;

long long factorial(int n) {
    long long f = 1;
    for (int i = 2; i <= n; i++) f *= i;
    return f;
}

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int reverseNumber(int n) {
    int rev = 0;
    while (n > 0) { rev = rev * 10 + n % 10; n /= 10; }
    return rev;
}

bool isArmstrong(int n) {
    int digits = 0;
    for (int t = n; t > 0; t /= 10) digits++;
    int sum = 0;
    for (int t = n; t > 0; t /= 10) {
        int d = t % 10, p = 1;
        for (int k = 0; k < digits; k++) p *= d;
        sum += p;
    }
    return sum == n;
}

bool isPerfect(int n) {
    if (n < 2) return false;
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) sum += n / i;
        }
    }
    return sum == n;
}

int gcd(int a, int b) {
    while (b != 0) { int r = a % b; a = b; b = r; }
    return a;
}

bool isStrong(int n) {
    int sum = 0;
    for (int t = n; t > 0; t /= 10) sum += factorial(t % 10);
    return sum == n;
}

int main() {
    int choice;
    do {
        cout << "\n--- MENU ---\n"
             << "1. Factorial\n2. Prime check\n3. Reverse and palindrome\n"
             << "4. Armstrong\n5. Perfect number\n6. GCD and LCM\n"
             << "7. Sum of primes in a range\n8. Fibonacci series\n"
             << "9. Strong number\n10. Exit\nChoice: ";
        cin >> choice;
        int n, a, b;
        switch (choice) {
            case 1:
                cin >> n;
                cout << n << "! = " << factorial(n) << endl;
                break;
            case 2:
                cin >> n;
                cout << n << (isPrime(n) ? " is prime" : " is not prime") << endl;
                break;
            case 3:
                cin >> n;
                cout << "Reverse = " << reverseNumber(n)
                     << (reverseNumber(n) == n ? ", palindrome" : ", not a palindrome") << endl;
                break;
            case 4:
                cin >> n;
                cout << n << (isArmstrong(n) ? " is an Armstrong number" : " is not an Armstrong number") << endl;
                break;
            case 5:
                cin >> n;
                cout << n << (isPerfect(n) ? " is perfect" : " is not perfect") << endl;
                break;
            case 6:
                cin >> a >> b;
                cout << "GCD = " << gcd(a, b) << ", LCM = " << (long long)a / gcd(a, b) * b << endl;
                break;
            case 7: {
                cin >> a >> b;
                int count = 0; long long sum = 0;
                for (int i = a; i <= b; i++) if (isPrime(i)) { count++; sum += i; }
                cout << count << " primes, sum = " << sum << endl;
                break;
            }
            case 8: {
                cin >> n;
                long long x = 0, y = 1, sum = 0;
                for (int i = 0; i < n; i++) { cout << x << " "; sum += x; long long z = x + y; x = y; y = z; }
                cout << "(sum " << sum << ")" << endl;
                break;
            }
            case 9:
                cin >> n;
                cout << n << (isStrong(n) ? " is a strong number" : " is not a strong number") << endl;
                break;
            case 10:
                cout << "Bye" << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != 10);
    return 0;
}
