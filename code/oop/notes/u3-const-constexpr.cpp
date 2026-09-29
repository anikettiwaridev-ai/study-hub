#include <iostream>
using namespace std;

int readLimit() { return 40; }             // a value known only when the program RUNS

class Config {
public:
    const int id;                            // const member: set once, per object, in the init list
    static const int fixedAtCompile = 10;    // static const int with a literal: allowed inside
    inline static const int fromRuntime = readLimit();   // non-constant initialiser: needs inline
    static constexpr int MAX = 100;          // must be a compile-time constant
    inline static int shared = 0;            // shared AND changeable
    Config(int i) : id(i) {}
};

constexpr int square(int n) { return n * n; }   // can be evaluated by the compiler

int main() {
    Config a(1), b(2);
    int grid[square(3)];                    // square(3) = 9, computed at compile time
    Config::shared = 5;
    cout << a.id << " " << b.id << " " << Config::fixedAtCompile << " "
         << Config::fromRuntime << " " << Config::MAX << " " << Config::shared << " "
         << sizeof(grid) / sizeof(int) << endl;
    return 0;
}
