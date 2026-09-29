#include <iostream>
using namespace std;

// Builds a NEW array of size n1 + n2 on the heap and returns it.
int *concatenate(const int *a, int n1, const int *b, int n2) {
    int *c = new int[n1 + n2];            // size computed from the two inputs
    for (int i = 0; i < n1; i++) c[i] = a[i];
    for (int i = 0; i < n2; i++) c[n1 + i] = b[i];
    return c;
}

int main() {
    int n1 = 3, n2 = 4;
    int *a = new int[n1] {1, 2, 3};
    int *b = new int[n2] {40, 50, 60, 70};

    int *c = concatenate(a, n1, b, n2);
    cout << "Concatenated (" << n1 + n2 << " elements): ";
    for (int i = 0; i < n1 + n2; i++) cout << c[i] << " ";
    cout << endl;

    delete[] a;                            // three new[] calls, three delete[] calls
    delete[] b;
    delete[] c;
    return 0;
}
