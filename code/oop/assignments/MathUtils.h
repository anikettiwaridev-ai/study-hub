#ifndef MATHUTILS_H          // include guard: skip everything if already included
#define MATHUTILS_H

// Functions defined in a header are marked inline, so the header can be
// included in several .cpp files without "multiple definition" errors.

inline bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

inline long long factorial(int n) {
    long long f = 1;
    for (int i = 2; i <= n; i++) f *= i;
    return f;
}

inline int gcd(int a, int b) {
    while (b != 0) { int r = a % b; a = b; b = r; }
    return a;
}

inline long long power(int base, int exp) {
    long long result = 1;
    for (int i = 0; i < exp; i++) result *= base;
    return result;
}

#endif
