#include <iostream>
#include <cstring>
using namespace std;

class Student {
    int rollNo;                 // ordinary data members: live inside the object
    int marksTotal;
    char *name;                 // pointer member: the characters live on the heap
    int subjects[5];            // static array member: inside the object
    int *marks;                 // dynamic array: on the heap
    int n;

public:
    Student() {                 // default: needed for "Student s4;" in part g)
        rollNo = 0; marksTotal = 0; n = 0;
        name = new char[1]; name[0] = '\0';
        marks = nullptr;
        for (int i = 0; i < 5; i++) subjects[i] = 0;
        cout << "  [default constructor]" << endl;
    }

    Student(int r, const char *nm, int count) {        // b) parameterized
        rollNo = r;
        name = new char[strlen(nm) + 1];
        strcpy(name, nm);
        n = count;
        marks = new int[n];
        marksTotal = 0;
        for (int i = 0; i < n; i++) { marks[i] = 70 + 5 * i; marksTotal += marks[i]; }
        for (int i = 0; i < 5; i++) subjects[i] = 100 + i;   // subject codes
        cout << "  [parameterized constructor for " << name << "]" << endl;
    }

    Student(const Student &s) {                        // d) DEEP copy constructor
        rollNo = s.rollNo;
        marksTotal = s.marksTotal;
        n = s.n;
        name = new char[strlen(s.name) + 1];           // new block...
        strcpy(name, s.name);                          // ...then copy the characters
        marks = n ? new int[n] : nullptr;
        for (int i = 0; i < n; i++) marks[i] = s.marks[i];
        for (int i = 0; i < 5; i++) subjects[i] = s.subjects[i];
        cout << "  [copy constructor]" << endl;
    }

    Student &operator=(const Student &s) {             // h) DEEP copy assignment
        cout << "  [copy assignment operator]" << endl;
        if (this == &s) return *this;                  // s4 = s4 must not destroy itself
        delete[] name;                                 // free what this object held
        delete[] marks;
        rollNo = s.rollNo;
        marksTotal = s.marksTotal;
        n = s.n;
        name = new char[strlen(s.name) + 1];
        strcpy(name, s.name);
        marks = n ? new int[n] : nullptr;
        for (int i = 0; i < n; i++) marks[i] = s.marks[i];
        for (int i = 0; i < 5; i++) subjects[i] = s.subjects[i];
        return *this;                                  // allows a = b = c
    }

    ~Student() {                                       // l) release every heap block
        cout << "  [destructor for " << (name[0] ? name : "empty") << "]" << endl;
        delete[] name;
        delete[] marks;
    }

    void setFirstMark(int m) { if (n) marks[0] = m; }
    void rename(const char *nm) {
        delete[] name;
        name = new char[strlen(nm) + 1];
        strcpy(name, nm);
    }
    void show(const char *label) const {
        cout << label << ": roll " << rollNo << ", " << name
             << ", marks[0] = " << (n ? marks[0] : 0) << endl;
    }
};

int main() {
    cout << "s1:" << endl;
    Student s1(1, "Asha", 3);

    cout << "e) Student s2 = s1;" << endl;
    Student s2 = s1;              // copy initialisation -> copy constructor

    cout << "f) Student s3(s1);" << endl;
    Student s3(s1);               // direct initialisation -> copy constructor too

    cout << "g) Student s4; s4 = s1;" << endl;
    Student s4;                   // default constructor
    s4 = s1;                      // object already exists -> copy ASSIGNMENT, not the copy constructor

    cout << "k) change the copies, check the original:" << endl;
    s2.setFirstMark(99);
    s4.rename("Changed");
    s1.show("s1");
    s2.show("s2");
    s4.show("s4");

    cout << "i) three kinds of object:" << endl;
    Student local(5, "Local", 2);                  // automatic object on the stack
    Student *dynamicStudent = new Student(6, "Heap", 2);   // object itself on the heap
    // Every Student is also 'hybrid': rollNo/subjects live in the object,
    // name/marks live on the heap through the pointers.
    dynamicStudent->show("dynamic");
    delete dynamicStudent;                         // a heap object is destroyed ONLY by delete

    cout << "end of main: automatic objects die in reverse order" << endl;
    return 0;
}
