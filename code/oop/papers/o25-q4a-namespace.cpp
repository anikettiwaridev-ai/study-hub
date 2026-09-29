#include <iostream>
#include <cstring>
using namespace std;

// The safe way to reuse a library name: put yours in your own namespace.
namespace mine {
    int strlen(const char *s) {
        int n = 0;
        while (s[n] != '\0') n++;
        return n * 100;    // deliberately different, to prove which one runs
    }
}

int main() {
    cout << "library: " << strlen("hello") << endl;
    cout << "mine:    " << mine::strlen("hello") << endl;
    return 0;
}
