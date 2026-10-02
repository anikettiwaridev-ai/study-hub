#include <iostream>
#include <stack>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    Node(int v) { data = v; left = right = NULL; }
};

// #region iterPre
void preorderIter(Node* root) {           // a stack replaces the call stack
    if (root == NULL) return;
    stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        Node* t = s.top(); s.pop();
        cout << t->data << " ";
        if (t->right) s.push(t->right);   // right FIRST, so left is popped first
        if (t->left) s.push(t->left);
    }
}
// #endregion iterPre

// #region iterIn
void inorderIter(Node* root) {
    stack<Node*> s;
    Node* t = root;
    while (t != NULL || !s.empty()) {
        while (t != NULL) { s.push(t); t = t->left; }   // go as far left as possible
        t = s.top(); s.pop();
        cout << t->data << " ";                          // visit
        t = t->right;                                    // then the right subtree
    }
}
// #endregion iterIn

Node* N(int v, Node* l = NULL, Node* r = NULL) { Node* n = new Node(v); n->left = l; n->right = r; return n; }

int main() {
    // The slides' exercise tree (a BST)
    Node* root = N(20, N(17, N(11, N(6), N(16)), N(19, N(18))),
                       N(53, N(23, NULL, N(44)), N(64, N(61), N(66))));
    cout << "Preorder: "; preorderIter(root); cout << endl;
    cout << "Inorder:  "; inorderIter(root); cout << endl;
    return 0;
}
