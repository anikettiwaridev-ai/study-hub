#include <iostream>
#include <cstring>
using namespace std;

// c) + j) SHALLOW copy: the copy constructor copies the POINTERS, exactly like
// the compiler's default one would. Both objects then share one heap block.
class Student {
public:
    int rollNo;
    char *name;
    int *marks;
    int n;

    Student(int r, const char *nm, int count) {
        rollNo = r;
        name = new char[strlen(nm) + 1];
        strcpy(name, nm);
        n = count;
        marks = new int[n];
        for (int i = 0; i < n; i++) marks[i] = 60 + i;
    }

    Student(const Student &s) {        // member-by-member: same as the default
        rollNo = s.rollNo;
        name = s.name;                 // copies the address, not the characters
        marks = s.marks;               // copies the address, not the numbers
        n = s.n;
    }

    // No destructor on purpose. With a destructor that deletes name and marks,
    // the SECOND object to die would free the same blocks again: a double free crash.

    void show(const char *label) {
        cout << label << ": roll " << rollNo << ", name " << name << ", marks[0] " << marks[0] << endl;
    }
};

int main() {
    Student s1(1, "Asha", 3);
    Student s2 = s1;                   // shallow copy

    cout << "Same name block?  " << (s1.name == s2.name ? "yes" : "no") << endl;
    cout << "Same marks block? " << (s1.marks == s2.marks ? "yes" : "no") << endl;

    s2.marks[0] = 99;                  // change the COPY...
    s2.name[0] = 'U';
    s2.rollNo = 2;                     // ordinary member: really separate
    s1.show("s1");                     // ...and the ORIGINAL changes too
    s2.show("s2");
    return 0;
}
