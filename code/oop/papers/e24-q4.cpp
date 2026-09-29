#include <iostream>
#include <cstring>
using namespace std;

class String {
    char *stringName;
    int stringLength;

public:
    String() {
        stringLength = 0;
        stringName = new char[1];
        stringName[0] = '\0';
    }

    String(const char *s) {                          // dynamic constructor
        stringLength = strlen(s);
        stringName = new char[stringLength + 1];     // size from the parameter's length
        strcpy(stringName, s);
    }

    String(const String &o) {                        // deep copy: needed because
        stringLength = o.stringLength;               // operator+ returns a String by value
        stringName = new char[stringLength + 1];
        strcpy(stringName, o.stringName);
    }

    String &operator=(const String &o) {             // deep assignment for string3 = ...
        if (this == &o) return *this;
        delete[] stringName;
        stringLength = o.stringLength;
        stringName = new char[stringLength + 1];
        strcpy(stringName, o.stringName);
        return *this;
    }

    ~String() { delete[] stringName; }

    void showOutput() const { cout << stringName << " (length " << stringLength << ")" << endl; }

    // A. Join, as a FRIEND: two parameters, both operands passed in.
    friend String operator+(const String &a, const String &b);

    // B. Compare, as a MEMBER. The paper says '+' again, but a member + and a
    // friend + with the same operand types cannot both exist (the call would be
    // ambiguous). Assumption: the comparison uses '<'.
    bool operator<(const String &other) const {
        return stringLength < other.stringLength;
    }
};

String operator+(const String &a, const String &b) {
    String result;
    delete[] result.stringName;
    result.stringLength = a.stringLength + b.stringLength;   // I.
    result.stringName = new char[result.stringLength + 1];   // II.
    strcpy(result.stringName, a.stringName);                 // III.
    strcat(result.stringName, b.stringName);
    return result;
}

int main() {
    String string1("Object"), string2("Oriented");
    string1.showOutput();
    string2.showOutput();

    String string3 = string1 + string2;       // A.
    cout << "Joined: ";
    string3.showOutput();

    cout << "Smaller string: ";               // B.
    if (string1 < string3) string1.showOutput();
    else string3.showOutput();
    return 0;
}
