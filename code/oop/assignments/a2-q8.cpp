#include <iostream>
using namespace std;

void spaces(int k) { for (int i = 0; i < k; i++) cout << ' '; }

void item(int k, bool letters) {
    if (letters) cout << char('A' + k - 1);   // 1 -> A, 2 -> B ...
    else cout << k;
}

// Row i of a palindromic pyramid: i ... 2 1 2 ... i, separated by spaces.
void palindromeRow(int i, bool letters) {
    for (int k = i; k >= 1; k--) {        // going down: i, i-1, ..., 1
        if (k != i) cout << ' ';
        item(k, letters);
    }
    for (int k = 2; k <= i; k++) {        // coming back up: 2, ..., i
        cout << ' ';
        item(k, letters);
    }
    cout << endl;
}

void palindromicPyramid(int n, bool letters) {
    for (int i = 1; i <= n; i++) {
        spaces(2 * (n - i));
        palindromeRow(i, letters);
    }
}

void hollowPyramid(int n) {
    for (int i = 1; i <= n; i++) {
        spaces(n - i);
        if (i == 1) cout << 1;
        else if (i == n) for (int k = 0; k < 2 * n - 1; k++) cout << 1;
        else { cout << 1; spaces(2 * i - 3); cout << 1; }
        cout << endl;
    }
}

void invertedPyramid(int n) {
    for (int i = 1; i <= n; i++) {
        spaces(2 * (i - 1));
        for (int k = i; k <= n; k++) { cout << k; if (k < n) cout << ' '; }
        cout << endl;
    }
}

void diamond(int n) {
    for (int i = 1; i <= n; i++) { spaces(2 * (n - i)); palindromeRow(i, false); }
    for (int i = n - 1; i >= 1; i--) { spaces(2 * (n - i)); palindromeRow(i, false); }
}

void hollowDiamondRow(int n, int i) {
    spaces(2 * (n - i));
    cout << '*';
    if (i > 1) { spaces(4 * (i - 1) - 1); cout << '*'; }
    cout << endl;
}

void hollowDiamond(int n) {
    for (int i = 1; i <= n; i++) hollowDiamondRow(n, i);
    for (int i = n - 1; i >= 1; i--) hollowDiamondRow(n, i);
}

int main() {
    int choice, n;
    do {
        cout << "\n1. Palindromic number pyramid\n2. Alphabetic palindromic pyramid\n"
             << "3. Hollow number pyramid\n4. Inverted number pyramid\n"
             << "5. Diamond number pattern\n6. Hollow diamond\n7. Exit\nChoice: ";
        cin >> choice;
        if (choice >= 1 && choice <= 6) { cin >> n; cout << "N = " << n << endl; }
        switch (choice) {
            case 1: palindromicPyramid(n, false); break;
            case 2: palindromicPyramid(n, true); break;
            case 3: hollowPyramid(n); break;
            case 4: invertedPyramid(n); break;
            case 5: diamond(n); break;
            case 6: hollowDiamond(n); break;
            case 7: cout << "Bye" << endl; break;
            default: cout << "Invalid choice" << endl;
        }
    } while (choice != 7);
    return 0;
}
