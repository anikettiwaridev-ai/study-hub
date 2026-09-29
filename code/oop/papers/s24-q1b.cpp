#include <iostream>
using namespace std;

int globalCount;          // global: default value 0, data segment
extern int shared;        // extern: only declares; the definition is below (or in another file)

void counter() {
    int a = 0;            // automatic (plain local): stack, lives until the function returns
    static int s = 0;     // static local: data segment, keeps its value between calls
    a++;
    s++;
    cout << "local a = " << a << ", static s = " << s << endl;
}

int shared = 42;          // the one real definition of the extern variable

int main() {
    counter();
    counter();
    counter();
    cout << "global default = " << globalCount << endl;
    cout << "extern shared = " << shared << endl;
    return 0;
}
