#include <iostream>
using namespace std;

class Array {
private:
    int *dynamicArray;
    int arrayLength;

public:
    Array() { arrayLength = 0; dynamicArray = nullptr; }

    // Parameterized dynamic constructor (length passed in: an array parameter is a pointer).
    Array(const int arr[], int n) {
        arrayLength = n;                         // a)
        dynamicArray = new int[arrayLength];     // b)
        for (int i = 0; i < n; i++)              // c)
            dynamicArray[i] = arr[i];
    }

    // Deep copy constructor: array4 below is a copy of whichever array is larger.
    Array(const Array &o) {
        arrayLength = o.arrayLength;
        dynamicArray = new int[arrayLength];
        for (int i = 0; i < arrayLength; i++) dynamicArray[i] = o.dynamicArray[i];
    }

    Array &operator=(const Array &o) {           // deep assignment for array3 = ...
        if (this == &o) return *this;
        delete[] dynamicArray;
        arrayLength = o.arrayLength;
        dynamicArray = new int[arrayLength];
        for (int i = 0; i < arrayLength; i++) dynamicArray[i] = o.dynamicArray[i];
        return *this;
    }

    ~Array() { delete[] dynamicArray; }

    void display() const {                       // II.
        for (int i = 0; i < arrayLength; i++) cout << dynamicArray[i] << " ";
        cout << "(length " << arrayLength << ")" << endl;
    }

    // III. Minus as a MEMBER: one parameter, the left operand is *this.
    Array operator-(const Array &other) const {
        Array result;
        result.arrayLength = arrayLength > other.arrayLength ? arrayLength : other.arrayLength; // a)
        result.dynamicArray = new int[result.arrayLength];                                      // b)
        for (int i = 0; i < result.arrayLength; i++) {                                          // c)
            int a = i < arrayLength ? dynamicArray[i] : 0;          // assumption: a missing
            int b = i < other.arrayLength ? other.dynamicArray[i] : 0; // element counts as 0
            result.dynamicArray[i] = a - b;
        }
        return result;
    }

    // IV. Greater-than as a FRIEND: two parameters, compares lengths.
    friend bool operator>(const Array &a, const Array &b);
};

bool operator>(const Array &a, const Array &b) {
    return a.arrayLength > b.arrayLength;
}

int main() {
    int first[] = {10, 20, 30, 40, 50};
    int second[] = {1, 2, 3};

    Array array1(first, 5), array2(second, 3);
    cout << "array1: "; array1.display();
    cout << "array2: "; array2.display();

    Array array3 = array1 - array2;              // array1.operator-(array2)
    cout << "array3 = array1 - array2: "; array3.display();

    // IV. The paper mixes array3 into part (a); part (b) compares array1 and array2,
    // so that is what is compared here. array4 holds a copy of the larger one.
    Array array4 = (array1 > array2) ? array1 : array2;
    cout << "array1 > array2 ? " << ((array1 > array2) ? "true" : "false") << endl;
    cout << "Larger array (array4): "; array4.display();
    return 0;
}
