#include <iostream>
using namespace std;

class Sample {
private:
    int a, b;

public:
    Sample(int x = 0, int y = 0) { a = x; b = y; }

    // i. Member function, so one parameter: abj1 is *this, abj2 is 'other'.
    // ii. Returns a Sample object.
    Sample operator+(const Sample &other) {
        Sample result;
        result.a = a + other.a;
        result.b = b + other.b;
        return result;
    }

    void display() { cout << "a = " << a << ", b = " << b << endl; }
};

int main() {
    Sample abj1(2, 3), abj2(4, 5), abj3;
    abj1.display();
    abj2.display();

    abj3 = abj1 + abj2;   // abj1.operator+(abj2)
    abj3.display();
    return 0;
}
