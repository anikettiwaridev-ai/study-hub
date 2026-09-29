#include <iostream>
using namespace std;

class Student {
private:                      // obscured from the user: only the class can touch it
    int marks;
    bool valid(int m) { return m >= 0 && m <= 100; }   // private helper too

public:                       // offered to the user: the interface
    Student() { marks = 0; }
    void setMarks(int m) {
        if (valid(m)) marks = m;
        else cout << "Invalid marks ignored" << endl;
    }
    int getMarks() { return marks; }
};

int main() {
    Student s;
    s.setMarks(87);
    s.setMarks(250);
    // s.marks = 250;      // compile error: 'marks' is private
    // s.valid(10);        // compile error: 'valid' is private
    cout << "Marks = " << s.getMarks() << endl;
    return 0;
}
