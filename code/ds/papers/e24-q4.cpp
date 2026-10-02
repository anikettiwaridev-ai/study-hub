#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int pr;
    Node *left, *right;
    Node(int p) { pr = p; left = right = NULL; }
};

// #region bst
Node* insert(Node* root, int p) {
    if (root == NULL) return new Node(p);
    if (p < root->pr) root->left = insert(root->left, p);
    else root->right = insert(root->right, p);       // equal priorities go right: served after the earlier one
    return root;
}

// The highest priority is the SMALLEST number: the leftmost node.
Node* removeMin(Node* root, int& minVal) {
    if (root->left == NULL) {
        minVal = root->pr;
        Node* r = root->right;                        // its right subtree takes its place
        delete root;
        return r;
    }
    root->left = removeMin(root->left, minVal);
    return root;
}

void inorder(Node* r) {                               // ascending = priority order
    if (r == NULL) return;
    inorder(r->left);
    cout << r->pr << " ";
    inorder(r->right);
}
// #endregion bst

int main() {
    int capacity, n, p;
    cin >> capacity >> n;
    Node* root = NULL;
    for (int i = 0; i < n && i < 100; i++) { cin >> p; root = insert(root, p); }
    cout << "All tasks in priority order: "; inorder(root); cout << endl;
    int todo = min(capacity, n);
    for (int i = 0; i < todo; i++) {
        int m;
        root = removeMin(root, m);
        cout << "Processed the task with priority " << m << endl;
    }
    if (n > capacity) cout << "Capacity " << capacity << " exceeded: not all tasks can be processed." << endl;
    cout << "Remaining tasks: ";
    if (root == NULL) cout << "none";
    inorder(root);
    cout << endl;
    return 0;
}
