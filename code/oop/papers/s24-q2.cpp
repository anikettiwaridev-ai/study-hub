#include <iostream>
#include <cstring>
using namespace std;

class String {
private:
    char *stringName;
    int stringLength;

public:
    // Default constructor, used for name3 before it is filled by joinStrings.
    String() {
        stringLength = 0;
        stringName = new char[1];
        stringName[0] = '\0';
    }

    // Parameterized dynamic constructor.
    String(const char *s) {
        stringLength = strlen(s);                  // I.   length of the argument
        stringName = new char[stringLength + 1];   // II.  one extra byte for '\0'
        strcpy(stringName, s);                     // III. copy the characters
    }

    // B. Display.
    void display() {
        cout << stringName << " (length " << stringLength << ")" << endl;
    }

    // C. Join two strings into this object.
    void joinStrings(const String &a, const String &b) {
        stringLength = a.stringLength + b.stringLength;   // i.
        delete[] stringName;                              // free the old block first
        stringName = new char[stringLength + 1];          // ii.
        strcpy(stringName, a.stringName);                 // iii. first string...
        strcat(stringName, b.stringName);                 //      ...then append the second
    }

    ~String() { delete[] stringName; }
};

int main() {
    String name1("Hello"), name2("World");
    name1.display();
    name2.display();

    String name3;
    name3.joinStrings(name1, name2);
    name3.display();
    return 0;
}
