#include <iostream>
using namespace std;

class Array {
private:
    int *dynamicArray;
    int arrayLength;

public:
    Array() {                       // for array3, filled later by mergeArrays
        arrayLength = 0;
        dynamicArray = nullptr;
    }

    // Parameterized dynamic constructor. An array parameter decays to a pointer,
    // so the constructor cannot find the length by itself: it is passed in.
    Array(const int arr[], int n) {
        arrayLength = n;                        // I.
        dynamicArray = new int[arrayLength];    // II.  no +1: ints have no terminator
        for (int i = 0; i < n; i++)             // III.
            dynamicArray[i] = arr[i];
    }

    // B. Display.
    void display() {
        for (int i = 0; i < arrayLength; i++)
            cout << dynamicArray[i] << " ";
        cout << "(length " << arrayLength << ")" << endl;
    }

    // C. Merge two arrays into this object.
    void mergeArrays(const Array &a, const Array &b) {
        arrayLength = a.arrayLength + b.arrayLength;   // i.
        delete[] dynamicArray;                         // free any old block
        dynamicArray = new int[arrayLength];           // ii.
        int k = 0;                                     // iii.
        for (int i = 0; i < a.arrayLength; i++) dynamicArray[k++] = a.dynamicArray[i];
        for (int i = 0; i < b.arrayLength; i++) dynamicArray[k++] = b.dynamicArray[i];
    }

    ~Array() { delete[] dynamicArray; }
};

int main() {
    int first[] = {1, 2, 3, 4};
    int second[] = {5, 6, 7, 8};

    // sizeof works HERE, in main, where the arrays are still real arrays.
    Array array1(first, sizeof(first) / sizeof(first[0]));
    Array array2(second, sizeof(second) / sizeof(second[0]));
    array1.display();
    array2.display();

    Array array3;
    array3.mergeArrays(array1, array2);
    array3.display();
    return 0;
}
