#include <iostream>
using namespace std;

int main() {
    int marks[5], total = 0;
    cout << "Enter marks in five subjects: ";
    for (int i = 0; i < 5; i++) { cin >> marks[i]; total += marks[i]; }

    double percentage = total / 5.0;
    char grade[3];
    if (percentage >= 90)      { grade[0] = 'A'; grade[1] = '+'; grade[2] = '\0'; }
    else if (percentage >= 80) { grade[0] = 'A'; grade[1] = '\0'; }
    else if (percentage >= 70) { grade[0] = 'B'; grade[1] = '\0'; }
    else if (percentage >= 60) { grade[0] = 'C'; grade[1] = '\0'; }
    else if (percentage >= 50) { grade[0] = 'D'; grade[1] = '\0'; }
    else                       { grade[0] = 'F'; grade[1] = '\0'; }

    cout << "Percentage: " << percentage << "%" << endl;
    cout << "Grade: " << grade << endl;
    cout << (percentage >= 50 ? "Result: Passed" : "Result: Failed") << endl;
    return 0;
}
