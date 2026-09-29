#include <iostream>
using namespace std;
class Employee {
    int code;
public:
    Employee() { code = 0; }
    explicit Employee(int c) { code = c; }
};
int main() {
    int Ecode = 1024;
    Employee emp;
    emp = Ecode;
    return 0;
}
