#include <iostream>
#include <cmath>       // sqrt() and pow() live here
using namespace std;

int main() {
    double num;
    cout << "Enter a number: ";
    cin >> num;

    if (num < 0) {
        cout << "Square root of a negative number is not real" << endl;
    } else {
        cout << "Square root of " << num << " = " << sqrt(num) << endl;
    }
    cout << "Cube of " << num << " = " << pow(num, 3) << endl;
    return 0;
}
