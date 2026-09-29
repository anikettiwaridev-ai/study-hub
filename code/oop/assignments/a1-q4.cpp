#include <iostream>
#include <string>
using namespace std;

int main() {
    string name, branch;
    long long rollNo;
    int marks[5];

    cout << "Name: ";              getline(cin, name);    // getline keeps spaces
    cout << "Roll number: ";       cin >> rollNo;
    cout << "Branch: ";            cin >> branch;
    cout << "Marks in 5 subjects: ";
    for (int i = 0; i < 5; i++) cin >> marks[i];

    int total = 0, highest = marks[0], lowest = marks[0];
    for (int i = 0; i < 5; i++) {
        total += marks[i];
        if (marks[i] > highest) highest = marks[i];
        if (marks[i] < lowest) lowest = marks[i];
    }
    double average = total / 5.0;          // 5.0, not 5: otherwise integer division
    double percentage = total / 500.0 * 100;

    cout << endl << name << " (" << rollNo << ", " << branch << ")" << endl;
    cout << "Total:      " << total << " / 500" << endl;
    cout << "Percentage: " << percentage << "%" << endl;
    cout << "Average:    " << average << endl;
    cout << "Highest:    " << highest << endl;
    cout << "Lowest:     " << lowest << endl;
    return 0;
}
