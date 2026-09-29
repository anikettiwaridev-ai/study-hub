#include <iostream>
using namespace std;

class Employee {
    int code;
public:
    Employee() { code = 0; }

    // Basic to class: a constructor taking ONE argument of the basic type.
    Employee(int c) {
        code = c;
        cout << "Converting int " << c << " to Employee" << endl;
    }

    void display() { cout << "Employee code = " << code << endl; }
};

int main() {
    int Ecode = 1024;
    Employee emp;
    emp = Ecode;          // implicit: Employee(Ecode) is built, then assigned to emp
    emp.display();

    Employee emp2 = 2048; // implicit, at the point of creation
    emp2.display();

    Employee emp3(4096);  // explicit call of the same constructor
    emp3.display();
    return 0;
}
