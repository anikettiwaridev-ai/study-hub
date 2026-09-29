#include <iostream>
using namespace std;

class Student {
    int rollNo;
    int marks;

public:
    Student() {                    // 0 arguments: only this one
        rollNo = 0;
        marks = 0;
    }

    Student(int r) {               // 1 argument: only this one
        rollNo = r;
        marks = 100;
    }

    Student(int r, int m) {        // 2 arguments: only this one (no default any more)
        rollNo = r;
        marks = m;
    }

    void display() {
        cout << "Roll No: " << rollNo << ", Marks: " << marks << endl;
    }
};

int main() {
    Student s1;
    Student s2(101);
    Student s3(102, 80);

    s1.display();
    s2.display();
    s3.display();
    return 0;
}
