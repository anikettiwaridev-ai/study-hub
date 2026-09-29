#include <iostream>
#include <string>
using namespace std;

class Course {
    const string courseCode;                          // a.
    string title;
    int credits;
public:
    inline static string universityName = "PEC";     // b.
    inline static int coursesCreated = 0;             // c.
    static constexpr int MAX_CREDITS = 5;             // d.

    Course(string code, string t, int c) : courseCode(code), title(t) {
        credits = c > MAX_CREDITS ? MAX_CREDITS : c;
        coursesCreated++;
    }

    void show() const {
        cout << courseCode << " " << title << " (" << credits << " credits)" << endl;
    }
};

int main() {
    Course c1("AIN3002", "Object Oriented Programming", 4);
    Course c2("AIN3001", "Data Structures", 4);
    Course c3("AIN3004", "Maths for AI", 7);          // capped at MAX_CREDITS

    cout << "Individual:" << endl;
    c1.show(); c2.show(); c3.show();
    cout << "Shared: " << Course::universityName << ", "
         << Course::coursesCreated << " courses, max " << Course::MAX_CREDITS << " credits" << endl;
    return 0;
}
