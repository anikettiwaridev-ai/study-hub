#include <iostream>
using namespace std;

class ABC {
private:
    int x, y;

public:
    ABC(int a = 0, int b = 0) { x = a; y = b; }

    // i. Member function: the left operand (obj1) is *this, so only ONE parameter.
    // ii. Returns a new ABC object.
    ABC operator-(const ABC &other) {
        ABC result;
        result.x = x - other.x;
        result.y = y - other.y;
        return result;
    }

    void display() { cout << "x = " << x << ", y = " << y << endl; }
};

int main() {
    ABC obj1(10, 20), obj2(4, 5), obj3;
    obj1.display();
    obj2.display();

    obj3 = obj1 - obj2;   // compiler turns this into obj1.operator-(obj2)
    obj3.display();
    return 0;
}
