#include <iostream>
using namespace std;

// Message passing: one object asks another to do something by calling its method.
class Printer {
public:
    void print(const char *text) { cout << "Printing: " << text << endl; }
};

class Student {
    const char *name;
public:
    Student(const char *n) { name = n; }
    void sendReport(Printer &p) { p.print(name); }   // Student sends a message to Printer
};

// Inheritance: Topper reuses everything in Student without rewriting it.
class Topper : public Student {
public:
    Topper(const char *n) : Student(n) {}
    void celebrate() { cout << "Topper celebrates" << endl; }
};

int main() {
    Printer p;
    Topper t("Asha");
    t.sendReport(p);   // inherited from Student
    t.celebrate();     // added by Topper
    return 0;
}
