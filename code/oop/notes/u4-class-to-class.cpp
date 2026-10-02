#include <iostream>
using namespace std;

class Fahrenheit {
    double f;
public:
    Fahrenheit(double v = 0) { f = v; }
    double value() const { return f; }
};

class Celsius {
    double c;
public:
    Celsius(double v) { c = v; }
    // Route 1: conversion operator in the SOURCE class.
    operator Fahrenheit() const { return Fahrenheit(c * 9 / 5 + 32); }
};

class Kelvin {
    double k;
public:
    // Route 2: one-argument constructor in the DESTINATION class.
    Kelvin(const Fahrenheit &fh) { k = (fh.value() - 32) * 5 / 9 + 273.15; }
    double value() const { return k; }
};

int main() {
    Celsius c(100);
    Fahrenheit f = c;       // Celsius::operator Fahrenheit()
    Kelvin k = f;           // Kelvin(const Fahrenheit&)
    cout << f.value() << " F, " << k.value() << " K" << endl;
    return 0;
}
