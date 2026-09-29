#include <iostream>
#include <cstring>
using namespace std;
int strlen(const char *s) {
    int n = 0;
    while (s[n] != '\0') n++;
    return n;
}
int main() {
    cout << strlen("hello");
    return 0;
}
