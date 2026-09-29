#include <iostream>
using namespace std;

class Student {
    int age, rollNo;
public:
    void setWrong(int age, int rollNo) {
        age = age;             // parameter assigned to ITSELF: the member is untouched
        rollNo = rollNo;
    }
    void setRight(int age, int rollNo) {
        this->age = age;       // this->age is the member, age is the parameter
        this->rollNo = rollNo;
    }
    void show() { cout << "age " << age << ", roll " << rollNo << endl; }
    Student() { age = 0; rollNo = 0; }
};

int main() {
    Student s;
    s.setWrong(19, 42);
    s.show();
    s.setRight(19, 42);
    s.show();
    return 0;
}
