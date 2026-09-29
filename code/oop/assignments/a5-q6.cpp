#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    int empID;                                   // a) ordinary members: one copy per object
    string name;
    double monthlySalary;

    static int count;                            // b) declared here, DEFINED outside the class
    static double totalSalary;                   //    (helper for the average, h)

public:
    inline static string companyName = "PEC Softworks";   // c) initialised INSIDE (C++17 inline)
    inline static int retirementAge = 60;
    static constexpr double MAX_SALARY = 200000.0;         // d) compile-time constant

    Employee(int id, string n, double salary) {
        empID = id;
        name = n;
        monthlySalary = salary > MAX_SALARY ? MAX_SALARY : salary;   // never above the cap
        count++;                                                     // b) automatic count
        totalSalary += monthlySalary;
    }

    double calculateAnnualSalary() const {                           // e)
        return monthlySalary * 12;
    }

    int calculateRetirementYears(int currentAge) const {             // f)
        int left = retirementAge - currentAge;
        return left > 0 ? left : 0;
    }

    double calculateSalaryPercentage() const {                       // g)
        return monthlySalary / MAX_SALARY * 100;
    }

    static void calculateAverageSalary() {                           // h)
        if (count == 0) { cout << "No employees" << endl; return; }
        cout << "Average monthly salary = " << totalSalary / count << endl;
    }

    static void displayCompanyDetails() {                            // i)
        cout << "Company: " << companyName
             << ", retirement age: " << retirementAge
             << ", max salary: " << MAX_SALARY << endl;
    }

    static int getCount() { return count; }

    void display(int age) const {
        cout << empID << "  " << name
             << " | annual " << (long long)calculateAnnualSalary()
             << " | years to retire " << calculateRetirementYears(age)
             << " | " << calculateSalaryPercentage() << "% of max" << endl;
    }
};

int Employee::count = 0;          // b) the one definition, outside the class
double Employee::totalSalary = 0;

/* k) Why count is initialised outside but the others inside:
   - A plain `static int count;` inside the class is only a DECLARATION. The class
     body is a blueprint, so no storage exists yet. `int Employee::count = 0;`
     outside creates that storage exactly once.
   - `inline static` (C++17) tells the linker "this definition may appear in many
     files; keep one copy". That is what lets companyName and retirementAge be
     defined and initialised right inside the class.
   - `static constexpr` is a compile-time constant and is implicitly inline, so it
     is also defined inside the class.

   inline static vs static constexpr:
   - inline static: ONE shared copy, CAN be changed at run time
     (Employee::retirementAge = 62; is legal).
   - static constexpr: ONE shared copy, fixed at COMPILE time, can never change,
     and its initialiser must itself be a constant expression.                   */

int main() {
    Employee::displayCompanyDetails();

    Employee e1(101, "Asha", 85000);
    Employee e2(102, "Ravi", 120000);
    Employee e3(103, "Meera", 250000);   // capped at MAX_SALARY

    e1.display(30);
    e2.display(45);
    e3.display(58);

    cout << "Total employees = " << Employee::getCount() << endl;
    Employee::calculateAverageSalary();

    Employee::retirementAge = 62;        // inline static: shared AND changeable
    cout << "After policy change: ";
    e1.display(30);
    // Employee::MAX_SALARY = 1;         // would not compile: constexpr is fixed
    return 0;
}
