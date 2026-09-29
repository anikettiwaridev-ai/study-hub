#include <iostream>
using namespace std;

class Time {
    int hours, minutes;
public:
    Time(int h, int m) { hours = h; minutes = m; }

    // Class to basic: a conversion operator. No return type is written,
    // because the name "int" already says what it returns.
    operator int() const {
        return hours * 60 + minutes;
    }
};

int main() {
    Time t(2, 30);
    int duration;
    duration = t;   // calls t.operator int()
    cout << "Duration = " << duration << " minutes" << endl;
    return 0;
}
