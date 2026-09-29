#include <iostream>
using namespace std;

class Engine {
public:
    Engine() { cout << "Engine built" << endl; }
};

class Driver {
public:
    const char *name;
    Driver(const char *n) { name = n; }
};

class Car {
    Engine engine;       // COMPOSITION: the Car owns its Engine; it is born and dies with the Car
    Driver *driver;      // AGGREGATION: the Car only points to a Driver that exists on its own
public:
    Car(Driver *d) { driver = d; }
    void show() { cout << "Car driven by " << driver->name << endl; }
};

// Overloading (compile time): same name, different parameters, same class.
void print(int x)    { cout << "int " << x << endl; }
void print(double x) { cout << "double " << x << endl; }

// Overriding (run time): a derived class redefines a virtual function of its base.
class Shape {
public:
    virtual void draw() { cout << "Shape::draw" << endl; }
    virtual ~Shape() {}
};
class Circle : public Shape {
public:
    void draw() override { cout << "Circle::draw" << endl; }
};

int main() {
    Driver d("Ravi");
    {
        Car c(&d);
        c.show();
    }                                   // Car and its Engine are gone...
    cout << "Driver still exists: " << d.name << endl;   // ...the Driver is not

    print(5);
    print(2.5);

    Shape *s = new Circle;
    s->draw();                          // decided at run time: Circle::draw
    delete s;
    return 0;
}
