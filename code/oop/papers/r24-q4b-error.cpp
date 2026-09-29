#include <iostream>
using namespace std;
class Counter {
    int id;
    static int count;
public:
    static int getId() { return id; }
};
int Counter::count = 0;
int main() {
    cout << Counter::getId();
    return 0;
}
