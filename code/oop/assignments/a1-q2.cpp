#include <iostream>
using namespace std;

int main() {
    char c; int i; float f; double d; bool b; short s; long l; long long ll;
    cout << "char:      " << sizeof(c)  << " byte" << endl;
    cout << "int:       " << sizeof(i)  << " bytes" << endl;
    cout << "float:     " << sizeof(f)  << " bytes" << endl;
    cout << "double:    " << sizeof(d)  << " bytes" << endl;
    cout << "bool:      " << sizeof(b)  << " byte" << endl;
    cout << "short:     " << sizeof(s)  << " bytes" << endl;
    cout << "long:      " << sizeof(l)  << " bytes (4 on Windows, 8 on Linux)" << endl;
    cout << "long long: " << sizeof(ll) << " bytes" << endl;
    return 0;
}
