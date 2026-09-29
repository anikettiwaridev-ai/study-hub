#include <iostream>
using namespace std;
int main() {
    int *arr = new int[4];
    for (int i = 0; i < 4; i++) arr[i] = (i + 1) * 10;
    delete[] arr;           // memory released, but arr still holds the old address
    cout << arr[0] << " " << arr[1] << endl;   // dangling: reading freed memory
    return 0;
}
