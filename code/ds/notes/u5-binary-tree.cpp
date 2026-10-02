#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

class Node {
public:
    char data;
    Node *left, *right;
    Node(char v) { data = v; left = right = NULL; }
};

// #region traversals
void preorder(Node* r)  { if (r == NULL) return; cout << r->data << " "; preorder(r->left); preorder(r->right); }
void inorder(Node* r)   { if (r == NULL) return; inorder(r->left); cout << r->data << " "; inorder(r->right); }
void postorder(Node* r) { if (r == NULL) return; postorder(r->left); postorder(r->right); cout << r->data << " "; }
// #endregion traversals

// #region bfs
void bfs(Node* root) {
    if (root == NULL) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* t = q.front(); q.pop();
        cout << t->data << " ";
        if (t->left != NULL) q.push(t->left);     // children join the BACK of the queue
        if (t->right != NULL) q.push(t->right);
    }
}
// #endregion bfs

// #region counts
int countNodes(Node* r)  { return r == NULL ? 0 : 1 + countNodes(r->left) + countNodes(r->right); }

int countLeaves(Node* r) {
    if (r == NULL) return 0;
    if (r->left == NULL && r->right == NULL) return 1;      // a leaf
    return countLeaves(r->left) + countLeaves(r->right);
}

int height(Node* r) {                    // edges on the longest root-to-leaf path
    if (r == NULL) return -1;            // so a single node has height 0
    return 1 + max(height(r->left), height(r->right));
}
// #endregion counts

// #region search
bool search(Node* r, char key) {          // a plain binary tree has no order: look everywhere, O(n)
    if (r == NULL) return false;
    return r->data == key || search(r->left, key) || search(r->right, key);
}
// #endregion search

// #region mirror
void mirror(Node* r) {
    if (r == NULL) return;
    swap(r->left, r->right);
    mirror(r->left);
    mirror(r->right);
}
// #endregion mirror

int main() {
    // The slides' tree:        A
    //                       B     C
    //                      D  E   F  G
    //                        H I
    Node* A = new Node('A');
    A->left = new Node('B');            A->right = new Node('C');
    A->left->left = new Node('D');      A->left->right = new Node('E');
    A->left->right->left = new Node('H'); A->left->right->right = new Node('I');
    A->right->left = new Node('F');     A->right->right = new Node('G');

    cout << "BFS:       "; bfs(A); cout << endl;
    cout << "Preorder:  "; preorder(A); cout << endl;
    cout << "Inorder:   "; inorder(A); cout << endl;
    cout << "Postorder: "; postorder(A); cout << endl;
    cout << "nodes " << countNodes(A) << ", leaves " << countLeaves(A) << ", height " << height(A) << endl;
    cout << "search H: " << search(A, 'H') << ", search Z: " << search(A, 'Z') << endl;
    mirror(A);
    cout << "Mirrored inorder: "; inorder(A); cout << endl;
    return 0;
}
