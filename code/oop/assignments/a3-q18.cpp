#include <iostream>
using namespace std;

double bill(int units, double fixedCharge = 50.0, double rate = 6.5) {
    return fixedCharge + units * rate;
}

int main() {
    int units;
    cout << "Units consumed: ";
    cin >> units;
    cout << endl;
    cout << "Default charge and rate:   " << bill(units) << endl;
    cout << "Own fixed charge (100):    " << bill(units, 100) << endl;
    cout << "Own charge and rate (8.0): " << bill(units, 100, 8.0) << endl;
    return 0;
}
