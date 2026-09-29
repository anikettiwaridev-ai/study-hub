#include <iostream>
using namespace std;
int readLimit() { return 40; }
class Config {
public:
    static constexpr int MAX = readLimit();
};
int main() { return 0; }
