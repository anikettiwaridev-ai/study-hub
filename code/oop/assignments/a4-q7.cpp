#include <iostream>
using namespace std;

class SmartMeter {
    const int meterID;                                  // per object, never changes
public:
    inline static double ratePerUnit = 6.5;             // shared by all meters, can change
    static constexpr int MAX_UNITS = 500;               // compile-time limits
    static constexpr int PENALTY_THRESHOLD = 300;
    static constexpr double PENALTY_RATE = 1.5;         // extra per unit above the threshold

    SmartMeter(int id) : meterID(id) {}

    double bill(int units) const {
        if (units > MAX_UNITS) units = MAX_UNITS;       // cap readings at the limit
        double amount = units * ratePerUnit;
        if (units > PENALTY_THRESHOLD)
            amount += (units - PENALTY_THRESHOLD) * PENALTY_RATE;
        return amount;
    }

    void report(int units) const {
        cout << "Meter " << meterID << ": " << units << " units -> Rs " << bill(units) << endl;
    }
};

int main() {
    SmartMeter m1(101), m2(102), m3(103);
    m1.report(120);
    m2.report(350);
    m3.report(800);                                     // capped at 500
    SmartMeter::ratePerUnit = 7.0;                      // one change reaches every meter
    cout << "After the rate change:" << endl;
    m1.report(120);
    m2.report(350);
    return 0;
}
