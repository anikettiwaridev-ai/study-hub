#include <iostream>
using namespace std;

int main() {
    char grade = 'A';
    int rollNo = 25110002;
    float cgpa = 8.75f;             // f suffix: a float literal, not a double
    double pi = 3.14159265358979;
    bool passed = true;
    short year = 2;
    long population = 1400000000L;
    long long bigNumber = 9000000000000000000LL;

    cout << "char:      " << grade << endl;
    cout << "int:       " << rollNo << endl;
    cout << "float:     " << cgpa << endl;
    cout << "double:    " << pi << endl;         // cout shows 6 significant digits by default
    cout << "bool:      " << passed << endl;     // true prints as 1
    cout << "boolalpha: " << boolalpha << passed << endl;
    cout << "short:     " << year << endl;
    cout << "long:      " << population << endl;
    cout << "long long: " << bigNumber << endl;
    return 0;
}
