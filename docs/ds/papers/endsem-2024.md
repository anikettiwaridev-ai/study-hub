---
title: End-semester, December 2024
---

# End-semester, December 2024

<PaperHeader :rows="[
  ['Programme', 'B.Tech, 2nd year (2024), 3rd semester'],
  ['Course code', 'CSN3001 / AIN3001 (your course code)'],
  ['Maximum marks', '80'],
  ['Time allowed', '3 hours'],
  ['Note on the paper', 'All questions are compulsory. Assume suitably and state additional data required, if any.'],
]" />

::: info What to do with this paper before the mid-semester
Questions marked **in your mid-sem syllabus** are worth doing now: recurrences (Q2a), a list function (Q2b), postfix evaluation (Q2c), SJF with a queue (Q3a), array vs list queues (Q3b), and the tree questions (Q3c, Q3d), since trees are new to your mid-sem. The rest (Dijkstra, Kirchhoff, BST, hashing, heaps) is Units 6–8, solved here for the end-semester.
:::

<Q id="E24.Q1a">

Consider the following weighted graph Fig 1a. Find the shortest path to every vertex starting from A using Dijkstra's Algorithm. Show the steps and also the cost/distance table. Also mention the order in which the vertices are visited/relaxed.

Edges (undirected) read from Fig 1(a): A–B 1, A–C 3, A–F 10, B–G 2, G–D 12, B–D 7, B–C 1, B–E 5, C–D 9, C–E 3, D–E 2, D–F 1, E–F 2.

::::: details Solution (Unit 7, end-semester only)

Each row: pick the unvisited vertex with the smallest distance (✓ = finalised), then relax its edges. Entries are distance (predecessor).

| Visit | A | B | C | D | E | F | G |
|---|---|---|---|---|---|---|---|
| start | 0 | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ |
| A | ✓0 | 1 (A) | 3 (A) | ∞ | ∞ | 10 (A) | ∞ |
| B | ✓0 | ✓1 | **2 (B)** | 8 (B) | 6 (B) | 10 (A) | 3 (B) |
| C | ✓0 | ✓1 | ✓2 | 8 (B) | **5 (C)** | 10 (A) | 3 (B) |
| G | ✓0 | ✓1 | ✓2 | 8 (B) | 5 (C) | 10 (A) | ✓3 |
| E | ✓0 | ✓1 | ✓2 | **7 (E)** | ✓5 | **7 (E)** | ✓3 |
| D | ✓0 | ✓1 | ✓2 | ✓7 | ✓5 | 7 (E) | ✓3 |
| F | ✓0 | ✓1 | ✓2 | ✓7 | ✓5 | ✓7 | ✓3 |

**Order visited:** A, B, C, G, E, D, F (D and F tie at 7; either may go first).

| Vertex | Distance | Path |
|---|---|---|
| B | 1 | A → B |
| C | 2 | A → B → C (cheaper than the direct edge of 3) |
| G | 3 | A → B → G |
| E | 5 | A → B → C → E |
| D | 7 | A → B → C → E → D |
| F | 7 | A → B → C → E → F (not the direct edge of 10) |

Computed by a checker running Dijkstra on the edge list above.

:::::

</Q>

<Q id="E24.Q1b">

Find the number of spanning trees for the given graph Fig 1b using Kirchhoff's theorem. Show all the steps.

Edges read from Fig 1(b): 1–2, 1–3, 2–3, 2–4, 3–5, 4–5.

::::: details Solution (Unit 7, end-semester only)

**Kirchhoff's theorem:** the number of spanning trees = any cofactor of the Laplacian L = D − A (degree matrix minus adjacency matrix).

Degrees: deg(1) = 2, deg(2) = 3, deg(3) = 3, deg(4) = 2, deg(5) = 2.

```text
        1   2   3   4   5
L = [   2  −1  −1   0   0 ]   1
    [  −1   3  −1  −1   0 ]   2
    [  −1  −1   3   0  −1 ]   3
    [   0  −1   0   2  −1 ]   4
    [   0   0  −1  −1   2 ]   5
```

Delete row 1 and column 1:

```text
M = [  3  −1  −1   0 ]
    [ −1   3   0  −1 ]
    [ −1   0   2  −1 ]
    [  0  −1  −1   2 ]
```

Expand along the first row (signs + − + −):

- M₁₁ = det[[3, 0, −1], [0, 2, −1], [−1, −1, 2]] = 3(4 − 1) − 0 + (−1)(0 + 2) = **7**
- M₁₂ = det[[−1, 0, −1], [−1, 2, −1], [0, −1, 2]] = −1(4 − 1) − 0 + (−1)(1 − 0) = **−4**
- M₁₃ = det[[−1, 3, −1], [−1, 0, −1], [0, −1, 2]] = −1(0 − 1) − 3(−2 − 0) + (−1)(1 − 0) = **6**

det M = 3(7) − (−1)(−4) + (−1)(6) − 0 = 21 − 4 − 6 = **11**.

**The graph has 11 spanning trees.** Confirmed by brute force: of the 15 ways to choose 4 of the 6 edges, exactly 11 contain no cycle.

:::::

</Q>

<Q id="E24.Q2a">

For the given recurrence relation give the time complexity by solving using substitution method.

(i) T(n) = 2T(n − 1) + c for n > 1, T(1) = 1  (ii) T(n) = T(n/2) + 1 for n > 1, T(1) = 1

::::: details Solution (in your mid-sem syllabus)

**(i)**

```text
T(n) = 2T(n−1) + c
     = 2[2T(n−2) + c] + c   = 4T(n−2) + 2c + c
     = 4[2T(n−3) + c] + 3c  = 8T(n−3) + 4c + 2c + c
after k steps:  2^k T(n−k) + c(2^(k−1) + ... + 2 + 1) = 2^k T(n−k) + c(2^k − 1)
base: n − k = 1  ⇒  k = n − 1
T(n) = 2^(n−1)·1 + c(2^(n−1) − 1)
```

**T(n) = 2ⁿ⁻¹(1 + c) − c = O(2ⁿ).** (Checked numerically for c = 3: 1, 5, 13, 29, 61.)

**(ii)**

```text
T(n) = T(n/2) + 1
     = T(n/4) + 2
     = T(n/8) + 3
after k steps:  T(n/2^k) + k
base: n/2^k = 1  ⇒  k = log₂n
T(n) = T(1) + log₂n = 1 + log₂n
```

**T(n) = O(log n)**, the binary-search recurrence.

:::::

</Q>

<Q id="E24.Q2b">

Given a Linked List with n nodes and a number K. Write a runnable function to print the value of the K-th node from the middle (node (n/2)+1) towards the beginning of the List. If no such element exists, then print "−1".

::::: details Solution (in your mid-sem syllabus)

The middle is node **n/2 + 1** (1-based, integer division). Moving K nodes towards the head lands on node **pos = n/2 + 1 − K**. If pos &lt; 1 there is no such node: print −1.

Two passes: count n, then walk to node pos. (K = 0 gives the middle itself; a negative K is treated as invalid.)

::: code-group
<<< @/../code/ds/papers/e24-q2b.cpp#answer [Answer to write]
<<< @/../code/ds/papers/e24-q2b.cpp [Full program]
<<< @/../code/ds/papers/e24-q2b.out{txt} [Output]
:::

For 10 … 70 (n = 7) the middle is node 4 (40): K = 1 → 30, K = 3 → 10, K = 4 → −1. For 1 … 6 the middle is node 4 (value 4). O(n) time, O(1) space.

:::::

</Q>

<Q id="E24.Q2c">

Evaluate the following Postfix Expression using Stack: **100 5 9 + 2 ∗ 15 3 / − 4 2 ^ + ∗**

::::: details Solution (in your mid-sem syllabus)

| Token | Operation (op2 = first pop) | Stack (bottom → top) |
|---|---|---|
| 100, 5, 9 | push | 100 5 9 |
| + | 5 + 9 = 14 | 100 14 |
| 2 | push | 100 14 2 |
| ∗ | 14 × 2 = 28 | 100 28 |
| 15, 3 | push | 100 28 15 3 |
| / | 15 / 3 = 5 | 100 28 5 |
| − | 28 − 5 = 23 | 100 23 |
| 4, 2 | push | 100 23 4 2 |
| ^ | 4² = 16 | 100 23 16 |
| + | 23 + 16 = 39 | 100 39 |
| ∗ | 100 × 39 = 3900 | 3900 |

**Result: 3900.** The 100 waits at the bottom of the stack until the very last operator.

:::::

</Q>

<Q id="E24.Q3a">

A server processes tasks using Shortest Job First (SJF) scheduling, where tasks with the shortest processing time are completed first. If two tasks have the same processing time, they're processed in arrival order. Write a runnable function with proper syntax named sjf_scheduling(tasks) that takes a list of tasks as input, where each task is a tuple (task_id, processing_time). The function should return a list of task IDs in the order they will be processed.

::::: details Solution (in your mid-sem syllabus: Unit 4, scheduling)

Sort by processing time with a **stable** sort, so equal times keep arrival order. Insertion sort is stable when it shifts only strictly larger elements (`>`, not `>=`). In C++ the "list of tuples" becomes `vector<pair<int, int>>`.

::: code-group
<<< @/../code/ds/papers/e24-q3a.cpp#answer [Answer to write]
<<< @/../code/ds/papers/e24-q3a.cpp [Full program]
<<< @/../code/ds/papers/e24-q3a.out{txt} [Output]
:::

Tasks (1, 6), (2, 2), (3, 8), (4, 2), (5, 4) → **2 4 5 1 3**: tasks 2 and 4 both take 2, and 2 arrived first. O(n²) with insertion sort; `stable_sort` would be O(n log n).

:::::

</Q>

<Q id="E24.Q3b">

Briefly differentiate between array based queues and linked list based queues.

::::: details Solution (in your mid-sem syllabus)

| | Array-based queue | Linked-list queue |
|---|---|---|
| Size | fixed capacity chosen in advance; can overflow | grows and shrinks at run time; overflows only when memory runs out |
| Memory | contiguous block; unused cells are reserved (and a linear queue wastes freed cells unless it is circular) | a node per element plus a pointer each; no unused space |
| Enqueue / dequeue | O(1) (circular, using `% N`) | O(1) with front = head and rear = tail |
| Full / empty test | needs a convention: a count, `front = -1`, or one empty cell | empty when `front == NULL`; never full |
| Access the k-th element | O(1) by index | O(k) by walking |
| Cache behaviour | good (contiguous) | poorer (nodes scattered) |

:::::

</Q>

<Q id="E24.Q3c">

Consider a complete binary tree with 7 nodes. Let A denote the set of first 3 elements obtained by performing Breadth-First Search (BFS) starting from the root. Let B denote the set of first 3 elements obtained by performing Depth-First Search (DFS) starting from the root. What is the value of |A − B|? Give suitable justification for the answer.

::::: details Solution (Unit 5: in your mid-sem syllabus this year)

A complete tree with 7 nodes is perfect, of height 2:

```text
         1
       /   \
      2     3
     / \   / \
    4   5 6   7
```

- **BFS** visits level by level: A = {1, 2, 3}.
- **DFS from the root** (preorder, going left first): 1, 2, 4, … so B = {1, 2, 4}.

A − B = {3}, so **|A − B| = 1**. Justification: both start at the root and then its left child; BFS next takes the root's other child (3), while DFS goes deeper into the left subtree (4).

(If DFS were taken as inorder, the first three would be 4, 2, 5, giving A − B = {1, 3} and the answer 2. The usual reading of "DFS starting from the root" is preorder: state it.)

:::::

</Q>

<Q id="E24.Q3d">

The postorder traversal of a binary tree is 8, 9, 6, 7, 4, 5, 2, 3, 1. The inorder traversal of the same tree is 8, 6, 9, 4, 7, 2, 5, 1, 3. Construct the binary tree and give its preorder traversal.

::::: details Solution (Unit 5: in your mid-sem syllabus this year)

The **last** postorder element is the root; it splits the inorder into left | root | right. Recurse with the matching parts of the postorder.

| Step | Root | Inorder split | Postorder parts |
|---|---|---|---|
| 1 | 1 | [8 6 9 4 7 2 5] · 1 · [3] | left: 8 9 6 7 4 5 2; right: 3 |
| 2 | 2 | [8 6 9 4 7] · 2 · [5] | left: 8 9 6 7 4; right: 5 |
| 3 | 4 | [8 6 9] · 4 · [7] | left: 8 9 6; right: 7 |
| 4 | 6 | [8] · 6 · [9] | 8 is its left child, 9 its right |

```text
            1
          /   \
         2     3
        / \
       4   5
      / \
     6   7
    / \
   8   9
```

**Preorder: 1, 2, 4, 6, 8, 9, 7, 5, 3.**

::: code-group
<<< @/../code/ds/notes/u5-build-tree.cpp#fromPostIn [Builder]
<<< @/../code/ds/notes/u5-build-tree.out{txt} [Output]
:::

:::::

</Q>

<Q id="E24.Q4">

A factory robot processes tasks based on their priority levels, where lower numerical values indicate higher priority (e.g., a priority of 1 is more urgent than 5). Write a runnable program using a BST (binary search tree) to manage the tasks efficiently. The program should allow the user to input the maximum number of tasks the robot can handle and a list of task priorities (up to 100 tasks). Implement functions to insert tasks into the BST, remove and display the highest-priority task, and show the remaining tasks in order of their priority after processing. If the total number of tasks exceeds the robot's capacity, indicate that not all tasks can be processed and display the remaining tasks.

::::: details Solution (Unit 6, end-semester only)

The highest priority is the **smallest** number, which in a BST is the **leftmost** node. Removing it: if the node has no left child, its right subtree takes its place. An inorder traversal lists the rest in priority order. Equal priorities go to the right, so they leave after the earlier one.

::: code-group
<<< @/../code/ds/papers/e24-q4.cpp#bst [BST functions]
<<< @/../code/ds/papers/e24-q4.cpp [Full program]
<<< @/../code/ds/papers/e24-q4.in{txt} [Input]
<<< @/../code/ds/papers/e24-q4.out{txt} [Output]
:::

Capacity 3, priorities 5 1 8 3 1 7: the robot processes 1, 1, 3, reports that the capacity is exceeded, and lists 5 7 8 as remaining. Insert and remove-min are O(h): O(log n) when balanced, O(n) for a skewed tree.

:::::

</Q>

<Q id="E24.Q5a">

Consider a double hashing scheme in which the primary hash function is h1(k) = k mod 29, and the secondary hash function is h2(k) = 1 + (k mod 19). Assume that the table size is 29. Calculate the address returned by probe 3 in the probe sequence (assume that the probe sequence begins at probe 0) for key value k = 101. Need to show all the calculations.

::::: details Solution (Unit 8, end-semester only)

Double hashing: probe i goes to **(h1(k) + i · h2(k)) mod 29**.

- h1(101) = 101 mod 29 = 101 − 87 = **14**
- h2(101) = 1 + (101 mod 19) = 1 + (101 − 95) = **7**

| Probe i | (14 + 7i) mod 29 |
|---|---|
| 0 | 14 |
| 1 | 21 |
| 2 | 28 |
| 3 | 35 mod 29 = **6** |

**Probe 3 returns address 6.**

:::::

</Q>

<Q id="E24.Q5b">

Write a runnable function to check whether a given array of n elements is a max heap or not?

::::: details Solution (Unit 8, end-semester only)

With the root at index 0, node i has children 2i + 1 and 2i + 2. It is a max-heap if **every parent is ≥ its children**; only indices 0 … (n − 2)/2 have children.

::: code-group
<<< @/../code/ds/papers/e24-q5b.cpp#answer [Answer to write]
<<< @/../code/ds/papers/e24-q5b.cpp [Full program]
<<< @/../code/ds/papers/e24-q5b.out{txt} [Output]
:::

O(n). A max-heap must also be a complete tree, which an array with no gaps automatically is.

:::::

</Q>
