#include <iostream>
using namespace std;

class Term {
public:
    int coeff, pow;
    Term* next;
    Term(int c, int p) { coeff = c; pow = p; next = NULL; }
};

void append(Term*& head, Term*& tail, int c, int p) {
    if (c == 0) return;                          // a zero coefficient is not a term
    Term* t = new Term(c, p);
    if (head == NULL) head = tail = t; else { tail->next = t; tail = t; }
}

// #region polyAdd
// Both lists are sorted by DESCENDING power. Like merging two sorted lists.
Term* polyAdd(Term* a, Term* b) {
    Term *head = NULL, *tail = NULL;
    while (a != NULL && b != NULL) {
        if (a->pow > b->pow)      { append(head, tail, a->coeff, a->pow); a = a->next; }
        else if (a->pow < b->pow) { append(head, tail, b->coeff, b->pow); b = b->next; }
        else {                                   // same power: add the coefficients
            append(head, tail, a->coeff + b->coeff, a->pow);
            a = a->next; b = b->next;
        }
    }
    for (; a != NULL; a = a->next) append(head, tail, a->coeff, a->pow);   // leftovers
    for (; b != NULL; b = b->next) append(head, tail, b->coeff, b->pow);
    return head;
}
// #endregion polyAdd

// #region polySub
Term* polySub(Term* a, Term* b) {               // a - b = a + (-b)
    Term *nh = NULL, *nt = NULL;
    for (; b != NULL; b = b->next) append(nh, nt, -b->coeff, b->pow);
    return polyAdd(a, nh);                      // (the negated copy leaks here; fine for a demo)
}
// #endregion polySub

void print(Term* t) {
    if (t == NULL) { cout << "0" << endl; return; }
    bool first = true;
    for (; t; t = t->next) {
        int c = t->coeff;
        if (!first) cout << (c < 0 ? " - " : " + "); else if (c < 0) cout << "-";
        int m = c < 0 ? -c : c;
        if (m != 1 || t->pow == 0) cout << m;
        if (t->pow > 0) cout << "x";
        if (t->pow > 1) cout << "^" << t->pow;
        first = false;
    }
    cout << endl;
}

Term* make(int n, const int cp[][2]) {
    Term *h = NULL, *t = NULL;
    for (int i = 0; i < n; i++) append(h, t, cp[i][0], cp[i][1]);
    return h;
}

int main() {
    const int p1[][2] = {{5, 12}, {2, 9}, {-1, 3}};            // 5x^12 + 2x^9 - x^3
    const int p2[][2] = {{5, 11}, {-4, 9}, {2, 3}, {-1, 1}};   // 5x^11 - 4x^9 + 2x^3 - x
    Term *a = make(3, p1), *b = make(4, p2);
    cout << "A     = "; print(a);
    cout << "B     = "; print(b);
    cout << "A + B = "; print(polyAdd(a, b));
    cout << "A - B = "; print(polySub(a, b));
    return 0;
}
