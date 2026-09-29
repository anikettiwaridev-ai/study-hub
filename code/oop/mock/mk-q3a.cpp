#include <iostream>
using namespace std;

class Vector {
private:
    int *elements;
    int size;

public:
    Vector() { size = 0; elements = nullptr; }

    // (i) parameterized dynamic constructor: the length is passed in,
    // because an array parameter is only a pointer.
    Vector(const int arr[], int n) {
        size = n;
        elements = new int[size];
        for (int i = 0; i < size; i++) elements[i] = arr[i];
    }

    // (ii) deep copy constructor
    Vector(const Vector &v) {
        size = v.size;
        elements = size ? new int[size] : nullptr;
        for (int i = 0; i < size; i++) elements[i] = v.elements[i];
    }

    // (vi) deep copy assignment, so v5 = v3 does not share memory
    Vector &operator=(const Vector &v) {
        if (this == &v) return *this;
        delete[] elements;
        size = v.size;
        elements = size ? new int[size] : nullptr;
        for (int i = 0; i < size; i++) elements[i] = v.elements[i];
        return *this;
    }

    // (vii) destructor
    ~Vector() { delete[] elements; }

    // (iii) member +: element-wise sum; size = the larger size, missing elements count as 0
    Vector operator+(const Vector &v) const {
        Vector r;
        r.size = size > v.size ? size : v.size;
        r.elements = new int[r.size];
        for (int i = 0; i < r.size; i++)
            r.elements[i] = (i < size ? elements[i] : 0) + (i < v.size ? v.elements[i] : 0);
        return r;
    }

    // (iv) friend ==: same size and every element equal
    friend bool operator==(const Vector &a, const Vector &b);

    void display() const {
        cout << "[ ";
        for (int i = 0; i < size; i++) cout << elements[i] << " ";
        cout << "] size " << size << endl;
    }

    void set(int i, int value) { if (i >= 0 && i < size) elements[i] = value; }
};

bool operator==(const Vector &a, const Vector &b) {
    if (a.size != b.size) return false;
    for (int i = 0; i < a.size; i++)
        if (a.elements[i] != b.elements[i]) return false;
    return true;
}

int main() {
    int x[] = {1, 2, 3};
    int y[] = {10, 20, 30, 40};
    Vector v1(x, 3), v2(y, 4);
    cout << "v1 = "; v1.display();
    cout << "v2 = "; v2.display();

    Vector v3 = v1 + v2;                      // (iii)
    cout << "v3 = v1 + v2 = "; v3.display();

    Vector v4(v1);                            // (ii) copy constructor
    cout << "v4 (copy of v1) == v1 ? " << (v4 == v1 ? "true" : "false") << endl;
    cout << "v1 == v2 ? " << (v1 == v2 ? "true" : "false") << endl;

    Vector v5;
    v5 = v3;                                  // (vi) assignment
    v5.set(0, 999);                           // (v) proves the copies are independent
    cout << "after changing v5[0]: v3 = "; v3.display();
    cout << "                      v5 = "; v5.display();
    return 0;
}
