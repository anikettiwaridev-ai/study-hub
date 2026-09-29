#include <iostream>
#include <string>
using namespace std;

class Employee {
public:
    int id;
    double basicSalary;
    int rating;          // 1 to 5
    Employee(int i, double s, int r) { id = i; basicSalary = s; rating = r; }
    void show() const { cout << "Employee " << id << ": salary " << basicSalary << ", rating " << rating << endl; }
};

// By reference: the function changes the caller's object, and no copy is made.
void reviseSalary(Employee &e) {
    double raise = 0;
    if (e.rating == 5) raise = 0.20;
    else if (e.rating == 4) raise = 0.10;
    else if (e.rating == 3) raise = 0.05;
    e.basicSalary += e.basicSalary * raise;
}

int main() {
    Employee e(7, 50000, 4);
    cout << "Before: "; e.show();
    reviseSalary(e);
    cout << "After:  "; e.show();
    return 0;
}
