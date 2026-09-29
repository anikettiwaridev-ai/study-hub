#include <iostream>
using namespace std;

class OnlyFunctions { int x; public: void a() {} void b() {} static int s; };
int OnlyFunctions::s = 0;

class A {              // the worked example from class
    char a;
    int b;
    int c;
    char d;
    int e;
    int *f;
};

class AcharB {         // same, with int b changed to char b
    char a;
    char b;
    int c;
    char d;
    int e;
    int *f;
};

class AOptimal {       // largest first
    int *f;
    int b;
    int c;
    int e;
    char a;
    char d;
};

class B {              // the second padding exercise (int arr[13])
    char a;
    int b;
    char c;
    int arr[13];
    int a1;
    char c1;
    int *a2;
};

class BPointerFirst {
    int *a2;
    int arr[13];
    int b;
    int a1;
    char a;
    char c;
    char c1;
};

class BArrayFirst {
    int arr[13];
    int *a2;
    int b;
    int a1;
    char a;
    char c;
    char c1;
};

int main() {
    cout << "class with one int and two functions: " << sizeof(OnlyFunctions) << endl;
    cout << "A (char,int,int,char,int,int*):       " << sizeof(A) << endl;
    cout << "A with char b:                        " << sizeof(AcharB) << endl;
    cout << "A largest first:                      " << sizeof(AOptimal) << endl;
    cout << "B as written:                         " << sizeof(B) << endl;
    cout << "B pointer first:                      " << sizeof(BPointerFirst) << endl;
    cout << "B array first:                        " << sizeof(BArrayFirst) << endl;
    return 0;
}
