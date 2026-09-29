#include <iostream>
using namespace std;

class Student {
    int rollNo;
    int marks;

public:
    Student() {
        rollNo = 0;
        marks = 0;
    }

    Student(int r, int m = 50) {
        rollNo = r;
        marks = m;
    }

    Student(int r) {
        rollNo = r;
        marks = 100;
    }

    void display() {
        cout << "Roll No: " << rollNo
             << ", Marks: " << marks << endl;
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
