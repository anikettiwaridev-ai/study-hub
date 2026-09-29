#include <iostream>
using namespace std;
class Seat {
    static int booked;
public:
    Seat()  { booked++; }
    ~Seat() { booked--; }
    static int count() { return booked; }
};
int Seat::booked = 0;
int main() {
    Seat a, b;
    {
        Seat c, d;
        cout << Seat::count() << " ";
    }
    Seat e;
    cout << Seat::count();
    return 0;
}
