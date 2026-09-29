#include <iostream>
using namespace std;

class Vehicle {                          // parent (base) class
public:
    void start() { cout << "Vehicle started" << endl; }
};

class Car : public Vehicle {             // child (derived) class
public:
    void playMusic() { cout << "Car plays music" << endl; }   // NEW method of its own
};

int main() {
    Car c;
    c.start();       // reused from Vehicle without any change
    c.playMusic();   // added by Car
    return 0;
}
