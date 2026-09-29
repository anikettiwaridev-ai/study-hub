#include <iostream>
using namespace std;
class String {
    int len;
public:
    String(int l) { len = l; }
    friend String operator+(const String &a, const String &b);
    bool operator+(const String &b) const { return len < b.len; }
};
String operator+(const String &a, const String &b) { return String(a.len + b.len); }
int main() {
    String s1(3), s2(5);
    s1 + s2;
    return 0;
}
