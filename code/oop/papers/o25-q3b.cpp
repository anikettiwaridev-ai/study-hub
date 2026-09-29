#include <iostream>
using namespace std;

class ABC {
    int v;
public:
    ABC()                { v = 0;   cout << "default constructor" << endl; }
    ABC(int x)           { v = x;   cout << "parameterized constructor" << endl; }
    ABC(const ABC &o)    { v = o.v; cout << "copy constructor" << endl; }
    ABC &operator=(const ABC &o) {
        v = o.v;
        cout << "assignment operator" << endl;
        return *this;
    }
};

int main() {
    cout << "A: "; ABC A(100);
    cout << "B: "; ABC B(A);
    cout << "C: "; ABC C = A;
    cout << "D: "; ABC D;
    cout << "D = A: "; D = A;
    return 0;
}
