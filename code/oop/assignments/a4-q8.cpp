#include <iostream>
#include <string>
using namespace std;

class Student {
    const int rollNo;                           // a. per-object immutable value
    string name;
public:
    inline static string universityName = "PEC";   // b. shared, modifiable
    static constexpr int MAX_CREDITS = 26;          // c. compile-time limit

    static constexpr int creditsFor(int courses) {  // d. constexpr utility function
        return courses * 4;
    }

    Student(int r, string n) : rollNo(r), name(n) {}

    void show() const {
        cout << rollNo << " " << name << " @ " << universityName
             << " (limit " << MAX_CREDITS << " credits)" << endl;
    }
};

int main() {
    // creditsFor(5) is worked out by the COMPILER, so it can size an array.
    int weeklySlots[Student::creditsFor(5)];
    cout << "Array sized at compile time: " << sizeof(weeklySlots) / sizeof(int) << " slots" << endl;

    Student a(1, "Asha"), b(2, "Ravi");
    a.show();
    b.show();

    Student::universityName = "Punjab Engineering College";   // shared: both objects see it
    a.show();
    b.show();
    // a.rollNo = 5;              // const: not allowed
    // Student::MAX_CREDITS = 30; // constexpr: not allowed
    return 0;
}
