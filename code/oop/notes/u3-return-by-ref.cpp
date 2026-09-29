#include <iostream>
using namespace std;

class Counter {
    int value;
public:
    Counter(int v = 0) { value = v; }
    Counter(const Counter &c) { value = c.value; cout << "  (copy made)" << endl; }
    Counter  addCopy(int n) { value += n; return *this; }   // returns a COPY of the object
    Counter &addRef(int n)  { value += n; return *this; }   // returns the object ITSELF
    void show() const { cout << "value = " << value << endl; }
};

void byValue(Counter c)            { c.show(); }   // copy made on the way in
void byConstRef(const Counter &c)  { c.show(); }   // no copy, cannot modify

int main() {
    Counter c;
    cout << "chain by reference:" << endl;
    c.addRef(1).addRef(2).addRef(3);        // all three change c
    c.show();
    cout << "chain by copy:" << endl;
    c.addCopy(10).addCopy(20);              // the second call changes a temporary copy
    c.show();                               // so c only got +10
    cout << "pass by value:" << endl;
    byValue(c);
    cout << "pass by const reference:" << endl;
    byConstRef(c);
    return 0;
}
