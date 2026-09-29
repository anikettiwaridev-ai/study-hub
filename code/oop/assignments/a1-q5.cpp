#include <iostream>
using namespace std;

int main() {
    int a, b;
    cout << "Enter two integers: ";
    cin >> a >> b;

    cout << "Without casting: " << a / b << endl;                       // int / int = int
    cout << "Implicit (one side made double): " << a / (b * 1.0) << endl;
    cout << "Explicit C-style: " << (float)a / b << endl;               // a becomes float first
    cout << "Explicit C++ style: " << static_cast<double>(a) / b << endl;
    cout << "Too late: " << (double)(a / b) << endl;                    // division already truncated
    return 0;
}
