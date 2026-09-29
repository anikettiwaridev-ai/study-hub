#include <iostream>
using namespace std;

int main() {
    int a, b, c, d, e, f, g, h;
    cout << "Enter a b c d e f g h: ";
    cin >> a >> b >> c >> d >> e >> f >> g >> h;

    bool result = (a + b * c) > d && (e != f || g <= h);

    cout << "result = " << result << endl;
    // Order of work:
    // 1. ()  parentheses first
    // 2. *   b * c                  (L to R)
    // 3. +   a + (b*c)              (L to R)
    // 4. >   compare with d         (relational, L to R)
    // 5. != and <=  inside the second brackets
    // 6. ||  e != f  OR  g <= h      (L to R)
    // 7. &&  left part AND right part (L to R, && is above ||)
    // 8. =   store into result      (R to L, lowest here)
    return 0;
}
