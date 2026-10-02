---
title: End-semester, December 2023
---

# End-semester, December 2023

<PaperHeader :rows="[
  ['Programme', 'B.Tech (AE/CE/EE/ECE/ME/MME/PIE), 2nd year'],
  ['Course code', 'CS6301'],
  ['Maximum marks', '80'],
  ['Time allowed', '3 hours'],
  ['Note on the paper', 'All questions are compulsory. Assume suitably and state additional data required, if any.'],
]" />

::: info What to do with this paper before the mid-semester
**In your mid-sem syllabus:** Q1a (recurrence), Q2 (a linked stack with an O(1) max, which came back as Lab Quiz 2 in 2026) and Q3b (postfix evaluation). The rest (AVL, heaps, B-trees, sorting, graphs, dynamic programming) is for the end-semester; the solutions are complete so you don't have to come back to this paper.
:::

<Q id="E23.Q1a">

Use the substitution method to solve the following recurrence relation: **T(n) = 2T(n/2) + n,  T(2) = 1**

::::: details Solution (in your mid-sem syllabus)

```text
T(n) = 2T(n/2) + n
     = 2[2T(n/4) + n/2] + n = 4T(n/4) + 2n
     = 4[2T(n/8) + n/4] + 2n = 8T(n/8) + 3n
after k steps:  2^k T(n/2^k) + kn
base: n/2^k = 2  ⇒  2^k = n/2  ⇒  k = log₂n − 1
T(n) = (n/2)·T(2) + n(log₂n − 1)
     = n/2 + n log₂n − n
     = n log₂n − n/2
```

**T(n) = n log₂n − n/2 = O(n log n).** Check: T(4) = 2·1 + 4 = 6 = 4·2 − 2 ✓; T(8) = 2·6 + 8 = 20 = 8·3 − 4 ✓.

::: danger The base case is T(2), not T(1)
So stop at n/2ᵏ = 2, which makes k = log₂n − 1. Using T(1) changes the exact formula (the Big-O stays the same, but the exact answer loses marks).
:::

:::::

</Q>

<Q id="E23.Q1b">

With the help of an example demonstrate AVL trees don't suffer from skewness.

::::: details Solution (Unit 6, end-semester only)

Insert the sorted keys **10, 20, 30, 40, 50, 60**.

**In a plain BST** each key becomes the right child of the previous one: a right-skewed chain of height 5 (n − 1). Search degrades to O(n), no better than a linked list.

**In an AVL tree** every node keeps |height(left) − height(right)| ≤ 1, and a rotation restores it after any insertion that breaks it:

| Insert | Imbalance | Fix | Tree afterwards |
|---|---|---|---|
| 10, 20 | none | | 10 → right 20 |
| 30 | 10 has balance −2 (right-right) | left rotate at 10 | 20 (10, 30) |
| 40 | none | | 20 (10, 30 → right 40) |
| 50 | 30 has balance −2 (RR) | left rotate at 30 | 20 (10, 40 (30, 50)) |
| 60 | 20 has balance −2 (RR) | left rotate at 20 | 40 (20 (10, 30), 50 (–, 60)) |

```text
          40
        /    \
      20      50
     /  \       \
   10    30      60
```

Height **2** instead of 5. An AVL tree's height is always O(log n) (at most about 1.44 log₂ n), so search, insert and delete stay O(log n) whatever the insertion order: it cannot become skewed.

:::::

</Q>

<Q id="E23.Q2">

Write a program in C++ to implement stack using linked list for storing non-negative integers using classes. Assume your system has infinite memory space. Your program should support following operations:
- i. push function which inserts input integer at the top of stack. Time complexity for push function should be O(1).
- ii. pop function which removes and returns the integer at the top of stack if stack is not empty and −1 otherwise. Time complexity of pop function should be O(1).
- iii. Implement a max function which returns the maximum integer present in the stack if stack is not empty and −1 otherwise. Time complexity for max function should be O(1). max Function having time complexity more than O(1) will get no marks.

::::: details Solution (in your mid-sem syllabus)

The top of the stack is the **head** of the list, so push and pop are O(1). For max in O(1), each node also stores **the maximum of itself and every node below it**. Push computes it from the old top in O(1); pop needs nothing, because the node underneath already stores its own maximum.

::: code-group
<<< @/../code/ds/papers/e23-q2.cpp#push [push]
<<< @/../code/ds/papers/e23-q2.cpp#pop [pop]
<<< @/../code/ds/papers/e23-q2.cpp#max [max]
<<< @/../code/ds/papers/e23-q2.cpp [Full program]
<<< @/../code/ds/papers/e23-q2.out{txt} [Output]
:::

Because the values are non-negative, −1 can safely mean "empty".

::: danger Why "keep one max variable" fails
A single `maxVal` member is easy on push, but after popping the maximum you would have to search the whole stack for the new one: O(n), and no marks. Storing the running maximum in each node is what makes pop O(1) too. Lab Quiz 2 (2026) used the same idea with `key` as the running maximum ([solved](../quizzes/2026-lab-2#q2)).
:::

:::::

</Q>

<Q id="E23.Q3a">

A Priority Queue (PQ) is implemented using a Min-Heap. Elements in Min-Heap is inserted as (key, priority) pair. Element with lower priority value has higher priority. Perform the following operation on the Min-Heap and show the content of heap after each operation.

Enqueue(23, 3); Enqueue(28, 2); Enqueue(34, 1); Enqueue(45, 2); Enqueue(13, 4); Dequeue(); Enqueue(21, 6); Enqueue(17, 3); Enqueue(55, 1); Dequeue()

::::: details Solution (Unit 8, end-semester only)

The heap is ordered by **priority** (smaller is closer to the root). Enqueue: append, then swap with the parent while the parent's priority is larger. Dequeue: remove the root, move the last element to the root, sift down to the smaller-priority child. Array shown from index 0.

| Operation | Removed | Heap array: (key, priority) |
|---|---|---|
| Enqueue(23, 3) | | (23,3) |
| Enqueue(28, 2) | | (28,2) (23,3) |
| Enqueue(34, 1) | | (34,1) (23,3) (28,2) |
| Enqueue(45, 2) | | (34,1) (45,2) (28,2) (23,3) |
| Enqueue(13, 4) | | (34,1) (45,2) (28,2) (23,3) (13,4) |
| Dequeue() | (34, 1) | (45,2) (23,3) (28,2) (13,4) |
| Enqueue(21, 6) | | (45,2) (23,3) (28,2) (13,4) (21,6) |
| Enqueue(17, 3) | | (45,2) (23,3) (28,2) (13,4) (21,6) (17,3) |
| Enqueue(55, 1) | | (55,1) (23,3) (45,2) (13,4) (21,6) (17,3) (28,2) |
| Dequeue() | (55, 1) | (28,2) (23,3) (45,2) (13,4) (21,6) (17,3) |

At each Dequeue the moved element sifts down past a child only when its priority is **strictly** larger; equal priorities stay put. (A heap does not keep equal priorities in arrival order. If a question demands that, store a sequence number as a tie-breaker.)

:::::

</Q>

<Q id="E23.Q3b">

Evaluate the following postfix evaluation and show each step clearly: **9 8 7 6 5 4 − + / ^ ∗**

::::: details Solution (in your mid-sem syllabus)

| Token | Operation (op2 = first pop) | Stack (bottom → top) |
|---|---|---|
| 9 8 7 6 5 4 | push all six | 9 8 7 6 5 4 |
| − | 5 − 4 = 1 | 9 8 7 6 1 |
| + | 6 + 1 = 7 | 9 8 7 7 |
| / | 7 / 7 = 1 | 9 8 1 |
| ^ | 8 ^ 1 = 8 | 9 8 |
| ∗ | 9 × 8 = 72 | 72 |

**Result: 72.** All six operands are on the stack before the first operator: the stack's maximum depth is 6.

:::::

</Q>

<Q id="E23.Q4">

Perform the following operations on the given 4-order B Tree in the given sequence and show each step clearly. Insert(15), Insert(14), Delete(9), Delete(4), Delete(5)

Given tree: root [3 | 6 | 10]; leaves [1 | 2], [4 | 5], [7 | 8 | 9], [11 | 12].

::::: details Solution (Unit 6, end-semester only)

**Order 4:** at most 4 children and **3 keys** per node; every node except the root needs at least ⌈4/2⌉ − 1 = **1 key**. Overflow (4 keys) splits the node; following the textbook (Horowitz and Sahni), the **2nd key** (position ⌈m/2⌉) moves up, the 1st stays left and the 3rd and 4th go right.

**Insert(15):** it belongs in leaf [11 12], which has room: **[11 12 15]**.

**Insert(14):** leaf [11 12 14 15] overflows. Split: [11] · **12** up · [14 15]. The root becomes [3 6 10 12], which also overflows. Split it: [3] · **6** up · [10 12]. 6 is the new root:

```text
                [6]
             /       \
          [3]         [10 | 12]
         /   \       /    |    \
     [1 2]  [4 5] [7 8 9] [11] [14 15]
```

**Delete(9):** a leaf with spare keys: [7 8 9] → **[7 8]**.

**Delete(4):** [4 5] → **[5]** (1 key is still allowed).

**Delete(5):** [5] → empty: **underflow**. Its left sibling [1 2] has a spare key, so **borrow through the parent**: the separator 3 moves down into the empty leaf and the sibling's largest key 2 moves up to replace it.

```text
                [6]
             /       \
          [2]         [10 | 12]
         /   \       /    |    \
      [1]    [3]  [7 8]  [11] [14 15]
```

::: info If your class splits at the other median
Promoting the **3rd** key on overflow is also common. Then Insert(14) sends 14 up, the root [3 6 10 14] splits with 10 up, and the deletions end as root [10]; [2 6] over [1], [3], [7 8]; [14] over [11 12], [15]. Either is accepted if you state the rule and apply it consistently.
:::

:::::

</Q>

<Q id="E23.Q5">

Perform the Bubble Sort on the following array of positive integers. Show the content of the array after each iteration along with total number of swaps in that iteration.

**13, 16, 11, 4, 12, 6, 7, 90, 67, 5, 20**

::::: details Solution (sorting: end-semester only)

Each pass compares neighbours left to right and swaps if the left one is larger, so the largest remaining value "bubbles" to the end. Stop after a pass with no swaps.

| Pass | Array after the pass | Swaps |
|---|---|---|
| 1 | 13 11 4 12 6 7 16 67 5 20 **90** | 8 |
| 2 | 11 4 12 6 7 13 16 5 20 **67 90** | 7 |
| 3 | 4 11 6 7 12 13 5 16 **20 67 90** | 4 |
| 4 | 4 6 7 11 12 5 13 **16 20 67 90** | 3 |
| 5 | 4 6 7 11 5 12 **13 16 20 67 90** | 1 |
| 6 | 4 6 7 5 11 **12 13 16 20 67 90** | 1 |
| 7 | 4 6 5 7 **11 12 13 16 20 67 90** | 1 |
| 8 | 4 5 6 7 11 12 13 16 20 67 90 | 1 |
| 9 | 4 5 6 7 11 12 13 16 20 67 90 | 0 (sorted: stop) |

Total swaps: 26. The small 5 near the end moves left only one place per pass, which is why passes 5–8 each make a single swap.

::: code-group
<<< @/../code/ds/papers/e23-q5.cpp [Program]
<<< @/../code/ds/papers/e23-q5.out{txt} [Output]
:::

:::::

</Q>

<Q id="E23.Q6">

Consider the data of various flights operated by Speed Airlines between source and destination cities along with its price and duration of flight.
- a. Represent the given flight data in form of directed graph along with edge information.
- b. Find the minimum time taking path from city 'B' to all other cities using Dijkstra's algorithm. Show each iteration clearly. Also, mention the path and total cost of each path.

| S.No | Src | Dst | Cost | Duration |
|---|---|---|---|---|
| 1 | A | B | 10,000 | 4 hrs |
| 2 | A | C | 6,500 | 2 hrs |
| 3 | B | C | 13,000 | 5 hrs |
| 4 | B | D | 25,000 | 10 hrs |
| 5 | C | E | 7,000 | 3 hrs |
| 6 | E | D | 11,000 | 4 hrs |
| 7 | B | A | 9,000 | 3.5 hrs |
| 8 | C | A | 8,000 | 2.5 hrs |
| 9 | C | B | 12,000 | 4 hrs |
| 10 | D | B | 28,000 | 11 hrs |
| 11 | E | C | 7,500 | 3.5 hrs |
| 12 | D | A | 9,500 | 5 hrs |

::::: details Solution (Unit 7, end-semester only)

**(a)** Five vertices A–E and twelve directed edges, each labelled (cost, duration). As adjacency lists:

```text
A → B (10000, 4)     A → C (6500, 2)
B → C (13000, 5)     B → D (25000, 10)    B → A (9000, 3.5)
C → E (7000, 3)      C → A (8000, 2.5)    C → B (12000, 4)
D → B (28000, 11)    D → A (9500, 5)
E → D (11000, 4)     E → C (7500, 3.5)
```

**(b)** Dijkstra on **duration** from B. Entries: hours (predecessor); ✓ = finalised.

| Visit | A | B | C | D | E |
|---|---|---|---|---|---|
| start | ∞ | 0 | ∞ | ∞ | ∞ |
| B | 3.5 (B) | ✓0 | 5 (B) | 10 (B) | ∞ |
| A | ✓3.5 | ✓0 | 5 (B) | 10 (B) | ∞ |
| C | ✓3.5 | ✓0 | ✓5 | 10 (B) | 8 (C) |
| E | ✓3.5 | ✓0 | ✓5 | 10 (B) | ✓8 |
| D | ✓3.5 | ✓0 | ✓5 | ✓10 | ✓8 |

From A, A → C would give 3.5 + 2 = 5.5, worse than 5; from E, E → D gives 8 + 4 = 12, worse than 10.

| To | Fastest path | Time | Total cost |
|---|---|---|---|
| A | B → A | 3.5 hrs | 9,000 |
| C | B → C | 5 hrs | 13,000 |
| E | B → C → E | 8 hrs | 13,000 + 7,000 = 20,000 |
| D | B → D | 10 hrs | 25,000 |

:::::

</Q>

<Q id="E23.Q7">

Consider the graph given and step-by-step construct the Minimum Spanning Tree using Prim's algorithm. Consider F as the starting vertex. Show each step clearly.

Edges: A–B 12, A–F 17, A–E 15, B–F 7, B–C 1, B–D 2, F–E 19, F–D 10, E–D 14, D–C 6.

::::: details Solution (Unit 7, end-semester only)

Prim grows one tree from F, each time adding the cheapest edge with exactly one end in the tree.

| Step | Tree so far | Crossing edges (cheapest first) | Add |
|---|---|---|---|
| 1 | F | B–F 7, F–D 10, A–F 17, F–E 19 | **B–F (7)** |
| 2 | F, B | B–C 1, B–D 2, F–D 10, A–B 12, … | **B–C (1)** |
| 3 | F, B, C | B–D 2, D–C 6, F–D 10, A–B 12, … | **B–D (2)** |
| 4 | F, B, C, D | A–B 12, E–D 14, A–F 17, F–E 19 | **A–B (12)** |
| 5 | F, B, C, D, A | E–D 14, A–E 15, F–E 19 | **D–E (14)** |

MST edges: F–B, B–C, B–D, B–A, D–E. **Total weight 7 + 1 + 2 + 12 + 14 = 36.**

:::::

</Q>

<Q id="E23.Q8">

Subset Sum problem is defined as "Given a set A of non-negative integers, and a value K, determine if there is a subset of the given set with sum equal to given K". … We will create a 2D array DP of size (A.size() + 1) × (K + 1) of type boolean. The state DP[i][j] will be 'True' if there exists a subset of elements from A[1…i] with sum value = 'j'. DP[0][j] will be initialized with 'False' for all values of 'j' followed by DP[i][0] initialized with 'True' for all values of 'i'. The condition to populate the remaining matrix:

if (A[i − 1] > j) DP[i][j] = DP[i − 1][j]  else DP[i][j] = DP[i − 1][j] OR DP[i − 1][j − A[i − 1]]

Using the above approach, populate the DP array for the given instance: **A = [3, 9, 4, 8, 5, 2] and K = 10.**

::::: details Solution (dynamic programming: end-semester only)

Row i allows the first i elements. T = True, F = False. (DP[0][0] is True: the empty set sums to 0, and the "DP[i][0] = True" rule sets it last.)

| i (A[i−1]) | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 0 (none) | T | F | F | F | F | F | F | F | F | F | F |
| 1 (3) | T | F | F | T | F | F | F | F | F | F | F |
| 2 (9) | T | F | F | T | F | F | F | F | F | T | F |
| 3 (4) | T | F | F | T | T | F | F | T | F | T | F |
| 4 (8) | T | F | F | T | T | F | F | T | T | T | F |
| 5 (5) | T | F | F | T | T | T | F | T | T | T | F |
| 6 (2) | T | F | T | T | T | T | T | T | T | T | **T** |

**DP[6][10] = True**: a subset summing to 10 exists, for example {8, 2} or {3, 5, 2}. Only the last element, 2, makes 10 reachable: DP[5][8] was True (from 8 alone), so DP[6][10] = DP[5][10] OR DP[5][8] = True. Time and space O(n · K) = 7 × 11 cells. Computed by a checker that applies the given recurrence.

:::::

</Q>
