#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    Node(int v) { data = v; left = right = NULL; }
};

int find(const int a[], int lo, int hi, int x) { for (int i = lo; i <= hi; i++) if (a[i] == x) return i; return -1; }

// #region fromPostIn
// The LAST postorder element is the root; it splits the inorder into left | right.
Node* fromPostIn(const int post[], int ps, int pe, const int in[], int is, int ie) {
    if (ps > pe) return NULL;
    Node* root = new Node(post[pe]);
    int k = find(in, is, ie, post[pe]);
    int leftSize = k - is;
    root->left  = fromPostIn(post, ps, ps + leftSize - 1, in, is, k - 1);
    root->right = fromPostIn(post, ps + leftSize, pe - 1, in, k + 1, ie);
    return root;
}
// #endregion fromPostIn

// #region fromPreIn
// The FIRST preorder element is the root.
Node* fromPreIn(const int pre[], int ps, int pe, const int in[], int is, int ie) {
    if (ps > pe) return NULL;
    Node* root = new Node(pre[ps]);
    int k = find(in, is, ie, pre[ps]);
    int leftSize = k - is;
    root->left  = fromPreIn(pre, ps + 1, ps + leftSize, in, is, k - 1);
    root->right = fromPreIn(pre, ps + leftSize + 1, pe, in, k + 1, ie);
    return root;
}
// #endregion fromPreIn

void preorder(Node* r)  { if (!r) return; cout << r->data << " "; preorder(r->left); preorder(r->right); }
void postorder(Node* r) { if (!r) return; postorder(r->left); postorder(r->right); cout << r->data << " "; }
void bfs(Node* r) {
    queue<Node*> q; q.push(r);
    while (!q.empty()) { Node* t = q.front(); q.pop(); cout << t->data << " ";
        if (t->left) q.push(t->left); if (t->right) q.push(t->right); }
}

int main() {
    // End-semester Dec 2024 Q3(d)
    int post[] = {8, 9, 6, 7, 4, 5, 2, 3, 1}, in1[] = {8, 6, 9, 4, 7, 2, 5, 1, 3};
    Node* t = fromPostIn(post, 0, 8, in1, 0, 8);
    cout << "Dec 2024 Q3d preorder: "; preorder(t); cout << endl;
    cout << "Dec 2024 Q3d BFS:      "; bfs(t); cout << endl;
    // Mock paper Q5 (letters A..I numbered 1..9)
    int pre[] = {1, 2, 4, 7, 8, 5, 3, 6, 9}, in2[] = {7, 4, 8, 2, 5, 1, 6, 9, 3};
    Node* m = fromPreIn(pre, 0, 8, in2, 0, 8);
    cout << "Mock Q5 postorder:     "; postorder(m); cout << endl;
    cout << "Mock Q5 BFS:           "; bfs(m); cout << endl;
    return 0;
}
