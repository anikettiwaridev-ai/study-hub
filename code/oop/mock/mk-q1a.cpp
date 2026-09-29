#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() { cout << "Drawing a shape" << endl; }   // virtual: decided at run time
    virtual ~Shape() {}
};
class Circle : public Shape {
public:
    void draw() override { cout << "Drawing a circle" << endl; }
};
class Square : public Shape {
public:
    void draw() override { cout << "Drawing a square" << endl; }
};

// Compile-time polymorphism: the compiler picks by the arguments.
int add(int a, int b)          { return a + b; }
double add(double a, double b) { return a + b; }

int main() {
    Shape *shapes[2] = { new Circle, new Square };
    for (int i = 0; i < 2; i++) shapes[i]->draw();   // same call, different behaviour
    for (int i = 0; i < 2; i++) delete shapes[i];
    cout << add(2, 3) << " " << add(2.5, 1.5) << endl;
    return 0;
}
