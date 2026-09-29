#include <iostream>
using namespace std;
class Student {
    int rollno;
    inline static int count = 0;
public:
    Student() { rollno = 0; count++; cout << "const" << count << " "; }
    ~Student(){ cout << "dest" << count << " "; count--; }
};
int main() {
    Student s1, s2;
    {
        Student s3;
    }
    Student s4;
    return 0;
}
