#include <iostream>
using namespace std;
class Student {
    int rollno;
    Student() { rollno = 0; cout << "constructed once" << endl; }   // private
public:
    Student(const Student &) = delete;           // no copies either
    static Student &setter() { static Student s; return s; }
    void set(int r) { rollno = r; }
    void show() { cout << rollno << endl; }
};
int main() {
    Student &a = Student::setter();
    Student &b = Student::setter();
    a.set(7);
    b.show();
    cout << (&a == &b ? "same object" : "different objects") << endl;
    return 0;
}
