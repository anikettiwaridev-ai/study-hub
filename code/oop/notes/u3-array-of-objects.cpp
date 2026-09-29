#include <iostream>
using namespace std;
class Student {
    int roll;
public:
    Student() { roll = 0; }                   // needed: every element is default-constructed first
    void set(int r) { roll = r; }
    void show() const { cout << roll << " "; }
};
int main() {
    Student s[5];                             // default constructor runs 5 times
    for (int i = 0; i < 5; i++) s[i].set(101 + i);
    for (int i = 0; i < 5; i++) s[i].show();
    cout << endl;
    Student *batch = new Student[3];          // array of objects on the heap
    delete[] batch;                           // delete[] for arrays
    return 0;
}
