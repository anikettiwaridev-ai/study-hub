#include <iostream>
using namespace std;

class Fruit {
    int shape, colour;                  // per object
    static int count;                   // traditional: declared here...
    inline static int created = 0;      // modern C++17: defined right here
public:
    void setData(int s, int c) {        // non-static: may use both kinds
        shape = s; colour = c;
        count++;
    }
    void display() { cout << shape << " " << colour << " (count " << count << ")" << endl; }
    static void displayCount() { cout << "count = " << count << endl; }   // only statics
    static void showOne(const Fruit &f) { cout << "shape via parameter = " << f.shape << endl; }
    Fruit() { created++; }
    static int howMany() { return created; }
};

int Fruit::count = 0;                   // ...and defined once, here

int main() {
    Fruit f1, f2;
    f1.setData(10, 14);
    f2.setData(12, 20);
    f1.display();
    f2.display();
    Fruit::displayCount();              // called through the class
    Fruit::showOne(f2);
    cout << "objects created = " << Fruit::howMany() << endl;
    return 0;
}
