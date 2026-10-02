#include <iostream>
using namespace std;

// Lab Quiz II (2025), every blank filled in.
class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;
    Node(int val) {
        data = val;
        left = right = nullptr;
        height = 0;
    }
};
int max(int a, int b) { return (a > b) ? a : b; }
int getHeight(Node* node) {
    if (node == nullptr) return -1;
    return node->height;
}

// #region q1
int countLeaves(Node* root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr)
        return 1;                                             // blank 1
    return countLeaves(root->left) + countLeaves(root->right);   // blanks 2 and 3
}
// #endregion q1

// #region q2
int findHeight(Node* root) {
    if (root == nullptr) return -1;
    else {
        int lHeight = findHeight(root->left);
        int rHeight = findHeight(root->right);
        return 1 + max(lHeight, rHeight);                    // blank
    }
}
// #endregion q2

// #region q3
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* z = x->right;
    x->right = y;                                            // blank 1
    y->left = z;                                             // blank 2
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    return x;                                                // blank 3
}
// #endregion q3

// #region q4
Node* findMin(Node* root) {
    if (root == nullptr) return nullptr;
    while (root->left != nullptr)                            // blank
        root = root->left;
    return root;
}
// #endregion q4

// #region q5
Node* LCA(Node* root, int n1, int n2) {
    if (root == nullptr) return nullptr;
    if (root->data > n1 && root->data > n2)
        return LCA(root->left, n1, n2);                      // blank 1: both are smaller
    if (root->data < n1 && root->data < n2)
        return LCA(root->right, n1, n2);                     // blank 2: both are larger
    return root;                                             // they split here
}
// #endregion q5

Node* insert(Node* r, int v) {
    if (!r) return new Node(v);
    if (v < r->data) r->left = insert(r->left, v); else r->right = insert(r->right, v);
    r->height = 1 + max(getHeight(r->left), getHeight(r->right));
    return r;
}
void inorder(Node* r) { if (!r) return; inorder(r->left); cout << r->data << " "; inorder(r->right); }

int main() {
    Node* root = nullptr;
    for (int v : {50, 30, 70, 20, 40, 60, 80, 10}) root = insert(root, v);
    cout << "leaves " << countLeaves(root) << ", height " << findHeight(root)
         << ", min " << findMin(root)->data << endl;
    cout << "LCA(10, 40) = " << LCA(root, 10, 40)->data << ", LCA(60, 80) = " << LCA(root, 60, 80)->data
         << ", LCA(10, 80) = " << LCA(root, 10, 80)->data << endl;
    Node* c = new Node(30); c->left = new Node(20); c->left->left = new Node(10);   // left-left chain
    c->left->height = 1; c->height = 2;
    Node* r = rightRotate(c);
    cout << "after rightRotate: root " << r->data << ", inorder "; inorder(r); cout << endl;
    return 0;
}
