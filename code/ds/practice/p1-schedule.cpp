#include <iostream>
#include <string>
using namespace std;

// Practice sheet 1, Q5.
enum class Day { mon, tue, wed, thu, fri, sat, sun };

class Schedule {
    Day day;
    string activity;
public:
    Schedule(Day d, string a) { day = d; activity = a; }
    bool isWeekend() const { return day == Day::sat || day == Day::sun; }   // Day:: is required
    string getActivity() const { return activity; }
};

int main() {
    Schedule a(Day::wed, "DS lab"), b(Day::sun, "Football");
    for (const Schedule& s : {a, b})
        cout << s.getActivity() << ": " << (s.isWeekend() ? "weekend" : "weekday") << endl;
    return 0;
}
