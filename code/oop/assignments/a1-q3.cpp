#include <iostream>
#include <climits>     // INT_MIN, INT_MAX ...
#include <cfloat>      // FLT_MAX, DBL_MAX
using namespace std;

int main() {
    cout << "char:      " << CHAR_MIN  << " to " << CHAR_MAX  << endl;
    cout << "short:     " << SHRT_MIN  << " to " << SHRT_MAX  << endl;
    cout << "int:       " << INT_MIN   << " to " << INT_MAX   << endl;
    cout << "long:      " << LONG_MIN  << " to " << LONG_MAX  << endl;
    cout << "long long: " << LLONG_MIN << " to " << LLONG_MAX << endl;
    cout << "unsigned int: 0 to " << UINT_MAX << endl;
    cout << "float max:  " << FLT_MAX << endl;
    cout << "double max: " << DBL_MAX << endl;
    return 0;
}
