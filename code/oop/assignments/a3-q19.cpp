#include <iostream>
using namespace std;

// For each element, count it only if this is its FIRST appearance;
// that way no second array is needed to remember what was counted.
void frequencies(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        bool seenBefore = false;
        for (int j = 0; j < i; j++)
            if (arr[j] == arr[i]) { seenBefore = true; break; }
        if (seenBefore) continue;
        int count = 0;
        for (int j = i; j < n; j++)
            if (arr[j] == arr[i]) count++;
        cout << arr[i] << " occurs " << count << " time(s)" << endl;
    }
}

int main() {
    int arr[] = {10, 20, 10, 30, 20, 10, 40};
    frequencies(arr, 7);
    return 0;
}
