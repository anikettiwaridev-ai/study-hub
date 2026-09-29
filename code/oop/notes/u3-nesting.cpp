#include <iostream>
using namespace std;

class Student {
    int age;
    void displayAge() { cout << "age " << age << endl; }   // PRIVATE member function
public:
    int rollNo;
    void set(int a, int r) { age = a; rollNo = r; }
    void display() {
        cout << "roll " << rollNo << ", ";
        displayAge();          // nesting: one member function calling another, no object needed
    }
};

int main() {
    Student s;
    s.set(19, 42);
    s.display();               // public entry point
    // s.displayAge();         // error: private
    return 0;
}
