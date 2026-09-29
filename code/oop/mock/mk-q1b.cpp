#include <iostream>
using namespace std;

int total;                         // global: data segment, default 0, whole program

class Ticket {
public:
    static int sold;               // static member: data segment, one copy for all objects
    Ticket() { sold++; }
};
int Ticket::sold = 0;

int nextId() {
    static int id = 100;           // static local: data segment, block scope, keeps value
    return ++id;
}

int main() {
    int local = 5;                 // local: stack, garbage if uninitialised, dies at }
    Ticket t1, t2, t3;
    cout << total << " " << Ticket::sold << " " << nextId() << " " << nextId() << " " << local << endl;
    return 0;
}
