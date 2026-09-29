#include <iostream>
using namespace std;

class ClassB;                       // forward declaration: ClassA's friend list mentions ClassB

class ClassA {
private:
    int x, y;
public:
    ClassA(int a, int b) { x = a; y = b; }
    int total() const { return x + y; }
    void display() const { cout << "ClassA(" << x << ", " << y << ")"; }
    friend int sumOfBoth(const ClassA &a, const ClassB &b);
};

class ClassB {
private:
    int p, q;
public:
    ClassB(int a, int b) { p = a; q = b; }
    int total() const { return p + q; }
    void display() const { cout << "ClassB(" << p << ", " << q << ")"; }
    friend int sumOfBoth(const ClassA &a, const ClassB &b);
};

// Friend of BOTH classes, so it can read the private members of each.
int sumOfBoth(const ClassA &a, const ClassB &b) {
    return a.x + a.y + b.p + b.q;
}

// ClassA and ClassB are unrelated types, so one function cannot return "either one".
// Assumption: return which object has the larger sum (1 = A, 2 = B, 0 = equal),
// and main displays that object.
int largerObject(const ClassA &a, const ClassB &b) {
    if (a.total() > b.total()) return 1;
    if (b.total() > a.total()) return 2;
    return 0;
}

int main() {
    ClassA objA(10, 20);
    ClassB objB(15, 25);

    cout << "Sum of private members of both = " << sumOfBoth(objA, objB) << endl;

    int winner = largerObject(objA, objB);
    cout << "Object with the larger sum: ";
    if (winner == 1)      { objA.display(); cout << " with sum " << objA.total(); }
    else if (winner == 2) { objB.display(); cout << " with sum " << objB.total(); }
    else                  cout << "both sums are equal";
    cout << endl;
    return 0;
}
