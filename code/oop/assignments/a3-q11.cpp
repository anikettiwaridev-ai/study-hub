#include <iostream>
using namespace std;

int main() {
    int arr[] = {0, 5, 0, 3, 12, 0, 7};
    int n = 7, pos = 0;
    for (int i = 0; i < n; i++)            // copy every non-zero forward, in order
        if (arr[i] != 0) arr[pos++] = arr[i];
    while (pos < n) arr[pos++] = 0;        // fill the rest with zeros
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
}
