#include <iostream>
using namespace std;

class Triple {
public:
    int row, col, value;
    Triple* next;
    Triple(int r, int c, int v) { row = r; col = c; value = v; next = NULL; }
};

const int R = 4, C = 5;

// #region toList
// Scan row by row (row-major); every nonzero becomes a (row, col, value) node.
Triple* toList(int m[R][C]) {
    Triple *head = NULL, *tail = NULL;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (m[i][j] != 0) {
                Triple* t = new Triple(i + 1, j + 1, m[i][j]);   // 1-based, as on the slides
                if (head == NULL) head = tail = t; else { tail->next = t; tail = t; }
            }
    return head;
}
// #endregion toList

// #region rebuild
void rebuild(Triple* head) {
    Triple* t = head;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (t != NULL && t->row == i && t->col == j) { cout << t->value << " "; t = t->next; }
            else cout << "0 ";
        }
        cout << endl;
    }
}
// #endregion rebuild

int main() {
    int m[R][C] = {{0, 0, 3, 0, 4}, {0, 0, 5, 7, 0}, {0, 0, 0, 0, 0}, {0, 2, 6, 0, 0}};
    Triple* list = toList(m);
    for (Triple* t = list; t; t = t->next) cout << "(" << t->row << ", " << t->col << ", " << t->value << ") ";
    cout << endl;
    rebuild(list);
    while (list) { Triple* t = list; list = list->next; delete t; }
    return 0;
}
