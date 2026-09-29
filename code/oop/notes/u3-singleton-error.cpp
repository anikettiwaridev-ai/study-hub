#include <iostream>
using namespace std;
class Student {
    Student() {}
public:
    static Student &setter() { static Student s; return s; }
};
int main() {
    Student s1;
    return 0;
}
