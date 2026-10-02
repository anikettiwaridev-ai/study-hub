#include <iostream>
using namespace std;

class node {
public:
    int row;
    int column;
    int value;
    node* next;
    node(int r, int c, int v) {
        row = r;
        column = c;
        value = v;
        next = NULL;
    }
};

// #region answer
void append(node*& head, node*& tail, int r, int c, int v) {
    node* n = new node(r, c, v);
    if (head == NULL) head = tail = n;
    else { tail->next = n; tail = n; }
}

// Like merging two sorted lists: (row, column) decides which node comes first.
node* mat_addition(node* mat1, node* mat2) {
    node *head = NULL, *tail = NULL;
    while (mat1 != NULL && mat2 != NULL) {
        if (mat1->row == mat2->row && mat1->column == mat2->column) {   // same cell: add
            int sum = mat1->value + mat2->value;
            if (sum != 0) append(head, tail, mat1->row, mat1->column, sum);   // 4 + (-4) stores nothing
            mat1 = mat1->next;
            mat2 = mat2->next;
        } else if (mat1->row < mat2->row ||
                   (mat1->row == mat2->row && mat1->column < mat2->column)) {   // mat1's cell first
            append(head, tail, mat1->row, mat1->column, mat1->value);
            mat1 = mat1->next;
        } else {                                                         // mat2's cell first
            append(head, tail, mat2->row, mat2->column, mat2->value);
            mat2 = mat2->next;
        }
    }
    for (; mat1 != NULL; mat1 = mat1->next) append(head, tail, mat1->row, mat1->column, mat1->value);
    for (; mat2 != NULL; mat2 = mat2->next) append(head, tail, mat2->row, mat2->column, mat2->value);
    return head;
}
// #endregion answer

node* fromArray(int r, int c, const int* m) {
    node *h = NULL, *t = NULL;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if (m[i * c + j] != 0) append(h, t, i, j, m[i * c + j]);
    return h;
}
void print(node* t) {
    for (; t; t = t->next) cout << "(" << t->row << "," << t->column << "," << t->value << ") ";
    cout << endl;
}

int main() {
    const int A[3][4] = {{0, 5, 0, 0}, {3, 0, 0, 4}, {0, 0, 7, 0}};
    const int B[3][4] = {{1, 2, 0, 0}, {0, 0, 0, -4}, {0, 6, 0, 0}};
    node *a = fromArray(3, 4, &A[0][0]), *b = fromArray(3, 4, &B[0][0]);
    cout << "mat1: "; print(a);
    cout << "mat2: "; print(b);
    cout << "sum:  "; print(mat_addition(a, b));
    return 0;
}
