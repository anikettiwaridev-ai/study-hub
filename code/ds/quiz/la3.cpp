#include <iostream>
#include <vector>
using namespace std;

// Lab Quiz III (2025), every blank filled in.
vector<vector<int>> adj;
vector<bool> visited;

// #region q1
bool dfs(int vertex, int parent) {               // cycle in an UNDIRECTED graph
    visited[vertex] = true;
    for (int adjacent : adj[vertex]) {
        if (!visited[adjacent]) {
            if (dfs(adjacent, vertex))           // blanks 1 and 2
                return true;
        }
        else if (adjacent != parent) {           // blank 3: visited, and not the edge we came by
            return true;
        }
    }
    return false;
}
// #endregion q1

int Rank[10], Rep[10];

// #region q2
bool unionByRank(int x, int y) {                 // x, y are representatives; Rank = set size
    if (x == y) return false;
    if (Rank[x] < Rank[y]) {
        Rep[x] = y;
        Rank[y] += Rank[x];                      // blank 1: y's set absorbs x's
    }
    else {
        Rep[y] = x;
        Rank[x] += Rank[y];                      // blank 2
    }
    return true;
}
// #endregion q2

// #region q3
int find(int v) {
    if (v == Rep[v]) return v;
    return find(Rep[v]);                         // blank
}
// #endregion q3

// #region q4
void heapify(int* a, int n, int i) {             // MIN-heap
    int min = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && a[left] < a[min])
        min = left;                              // blank 1
    if (right < n && a[right] < a[min])
        min = right;                             // blank 2
    if (min != i) {
        swap(a[i], a[min]);
        heapify(a, n, min);                      // blanks 3 and 4: the child that was swapped
    }
}
// #endregion q4

int main() {
    adj = {{1, 2}, {0, 2}, {0, 1}, {4}, {3}};     // triangle 0-1-2 plus edge 3-4
    visited.assign(5, false);
    cout << "cycle from 0: " << dfs(0, -1) << endl;
    adj = {{1}, {0, 2}, {1}};                     // a path: no cycle
    visited.assign(3, false);
    cout << "cycle in a path: " << dfs(0, -1) << endl;

    for (int i = 0; i < 5; i++) { Rep[i] = i; Rank[i] = 1; }
    unionByRank(find(0), find(1));
    unionByRank(find(2), find(1));
    cout << "find(2) = " << find(2) << ", size " << Rank[find(2)] << endl;

    int a[] = {9, 4, 7, 1, 8, 3};
    for (int i = 6 / 2 - 1; i >= 0; i--) heapify(a, 6, i);
    for (int x : a) cout << x << " ";
    cout << endl;
    return 0;
}
