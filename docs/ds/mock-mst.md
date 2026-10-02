---
title: Mock mid-semester paper
---

# Mock mid-semester paper

<PaperHeader :rows="[
  ['Course', 'Data Structures, AIN3001 (written for this site; not a real paper)'],
  ['Syllabus', 'Units 1 to 5'],
  ['Maximum marks', '30 (six questions of 5)'],
  ['Time allowed', '1 hour 30 minutes'],
  ['Note', 'All questions are compulsory. Assume suitably and state additional data required, if any.'],
]" />

<QuizTimer :minutes="90" label="Mock paper" />

::: info How this paper was built
It follows the template of the two latest papers ([2024 B](./papers/mst-2024-b) and [Oct 2025](./papers/mst-2025-oct)): a conversion, a recurrence, a circular-queue trace, Biased Search and a linked-list function. Q5 is the **tree question** your syllabus adds this year, modelled on the end-semester tree questions. Every expression, trace and program answer was produced by running code.
:::

<Q id="MK.Q1">

Convert the following infix expression to postfix using a stack. Clearly show the operation performed for each character, the content of the stack, and the postfix string after each step.

**(p + q) ∗ r − s / (t − u ^ v ^ w)**

::::: details Solution

| Symbol | Operation | Stack (bottom → top) | Postfix string |
|---|---|---|---|
| ( | push ( | ( | |
| p | operand → output | ( | p |
| + | push + | ( + | p |
| q | operand → output | ( + | pq |
| ) | pop + until (, drop ( | (empty) | pq+ |
| ∗ | push ∗ | ∗ | pq+ |
| r | operand → output | ∗ | pq+r |
| − | pop ∗ (higher), push − | − | pq+r∗ |
| s | operand → output | − | pq+r∗s |
| / | push / (higher than −) | − / | pq+r∗s |
| ( | push ( | − / ( | pq+r∗s |
| t | operand → output | − / ( | pq+r∗st |
| − | push − (top is `(`) | − / ( − | pq+r∗st |
| u | operand → output | − / ( − | pq+r∗stu |
| ^ | push ^ (higher than −) | − / ( − ^ | pq+r∗stu |
| v | operand → output | − / ( − ^ | pq+r∗stuv |
| ^ | push ^: **right-associative, does not pop the first ^** | − / ( − ^ ^ | pq+r∗stuv |
| w | operand → output | − / ( − ^ ^ | pq+r∗stuvw |
| ) | pop ^ ^ − until (, drop ( | − / | pq+r∗stuvw^^− |
| end | pop / then − | (empty) | pq+r∗stuvw^^−/− |

**Postfix: `pq+r*stuvw^^-/-`** (for practice, the prefix is `-*+pqr/s-t^u^vw`).

Marking points: the second `^` must be pushed, not popped (`stuvw^^`, not `stuv^w^`); at `−` after `r`, the `∗` pops; at the end, `/` comes out before `−`.

:::::

</Q>

<Q id="MK.Q2">

Solve the following recurrence relation using the substitution method: **T(n) = 4T(n/2) + n,  T(1) = 1**

::::: details Solution

```text
T(n) = 4T(n/2) + n
     = 4[4T(n/4) + n/2] + n   = 16T(n/4) + 2n + n
     = 16[4T(n/8) + n/4] + 3n = 64T(n/8) + 4n + 2n + n
after k steps:  4^k T(n/2^k) + n(1 + 2 + 4 + ... + 2^(k−1)) = 4^k T(n/2^k) + n(2^k − 1)
base: n/2^k = 1  ⇒  k = log₂n,  2^k = n,  4^k = n²
T(n) = n²·1 + n(n − 1) = 2n² − n
```

**T(n) = 2n² − n = O(n²).** Check: T(2) = 4·1 + 2 = 6 = 8 − 2 ✓; T(4) = 4·6 + 4 = 28 = 32 − 4 ✓.

Here each level costs **more** than the one above (n, 2n, 4n, …), so the bottom level (n² leaves) dominates. Master-theorem check: n^(log₂4) = n² beats f(n) = n: case 1, Θ(n²).

:::::

</Q>

<Q id="MK.Q3">

A circular queue is implemented using an array of length 6 and is full when it holds 5 elements. Show the content of the queue, front and rear after each operation, or overflow/underflow:

Enqueue(5), Enqueue(15), Enqueue(25), Dequeue(), Dequeue(), Enqueue(35), Enqueue(45), Enqueue(55), Enqueue(65), Enqueue(75), Dequeue(), Enqueue(85)

::::: details Solution

Textbook convention: front = rear = 0 initially; front is one cell **before** the first element. Full when (rear + 1) % 6 == front.

| Operation | Result | front | rear | Q[0] … Q[5] | Queue |
|---|---|---|---|---|---|
| Enqueue(5) | Q[1] = 5 | 0 | 1 | – 5 – – – – | 5 |
| Enqueue(15) | Q[2] = 15 | 0 | 2 | – 5 15 – – – | 5 15 |
| Enqueue(25) | Q[3] = 25 | 0 | 3 | – 5 15 25 – – | 5 15 25 |
| Dequeue() | removes 5 | 1 | 3 | – – 15 25 – – | 15 25 |
| Dequeue() | removes 15 | 2 | 3 | – – – 25 – – | 25 |
| Enqueue(35) | Q[4] = 35 | 2 | 4 | – – – 25 35 – | 25 35 |
| Enqueue(45) | Q[5] = 45 | 2 | 5 | – – – 25 35 45 | 25 35 45 |
| Enqueue(55) | rear wraps, Q[0] = 55 | 2 | 0 | 55 – – 25 35 45 | 25 35 45 55 |
| Enqueue(65) | Q[1] = 65 | 2 | 1 | 55 65 – 25 35 45 | 25 35 45 55 65 |
| Enqueue(75) | **Overflow**: (1 + 1) % 6 = 2 = front | 2 | 1 | 55 65 – 25 35 45 | 25 35 45 55 65 |
| Dequeue() | removes 25 | 3 | 1 | 55 65 – – 35 45 | 35 45 55 65 |
| Enqueue(85) | Q[2] = 85 | 3 | 2 | 55 65 85 – 35 45 | 35 45 55 65 85 |

Final: **35 45 55 65 85**, front = 3, rear = 2 (full again).

::: code-group
<<< @/../code/ds/mock/mock-q3.cpp [Checked by running]
<<< @/../code/ds/mock/mock-q3.out{txt} [Output]
:::

:::::

</Q>

<Q id="MK.Q4">

Biased Search uses mid = (2s + e)/3. Write its pseudocode, apply it to search 'M' in the sorted list A B C D E F G H I J K L M N O P, showing each step, and give its worst-case time complexity with a recurrence.

::::: details Solution

Pseudocode as in [Oct 2025 Q4](./papers/mst-2025-oct#q4). Indices 0–15:

| Step | s | e | mid = ⌊(2s + e)/3⌋ | A[mid] | Action |
|---|---|---|---|---|---|
| 1 | 0 | 15 | ⌊15/3⌋ = 5 | F | M > F: s = 6 |
| 2 | 6 | 15 | ⌊27/3⌋ = 9 | J | M > J: s = 10 |
| 3 | 10 | 15 | ⌊35/3⌋ = 11 | L | M > L: s = 12 |
| 4 | 12 | 15 | ⌊39/3⌋ = 13 | N | M &lt; N: e = 12 |
| 5 | 12 | 12 | ⌊36/3⌋ = 12 | M | **found at index 12** |

**Complexity:** in the worst case the search always continues in the larger part, about two thirds of the range: **T(n) = T(2n/3) + 1**, so T(n) = log₍₃⁄₂₎ n + 1 = **O(log n)**: the same order as binary search, with a larger constant (about 1.71 log₂ n probes).

:::::

</Q>

<Q id="MK.Q5">

The preorder traversal of a binary tree is A B D G H E C F I and its inorder traversal is G D H B E A F I C.
- (a) Construct the tree. (2)
- (b) Give its postorder and level-order traversals. (2)
- (c) Is it full? Is it complete? What is its height? (1)

::::: details Solution

**(a)** The first preorder element is the root; it splits the inorder.

| Step | Root | Inorder split |
|---|---|---|
| 1 | A | [G D H B E] · A · [F I C] |
| 2 | B (next in preorder) | [G D H] · B · [E] |
| 3 | D | [G] · D · [H] |
| 4 | C (first of the right part's preorder C F I) | [F I] · C · [ ] |
| 5 | F | [ ] · F · [I] (I is F's right child) |

```text
          A
        /   \
       B     C
      / \   /
     D   E F
    / \     \
   G   H     I
```

**(b)** Postorder: **G H D E B I F C A**. Level order: **A B C D E F G H I**. (Checked by running the builder in [Unit 5](./notes/unit-5#build).)

**(c)** Not full: C and F each have one child. Not complete: C has no right child while the last level has nodes, and I is a right child with no left sibling. Height **3** (edges): A → B → D → G, or A → C → F → I.

:::::

</Q>

<Q id="MK.Q6">

Using the class below, write a C++ function `Node* removeAll(Node* head, int key)` that deletes **every** node whose data equals key from a singly linked list, frees their memory, and returns the new head.

```cpp
class Node {
public:
    int data;
    Node* next;
    Node(int val) { data = val; next = NULL; }
};
```

::::: details Solution

Two phases: (1) strip matching nodes from the **front**, since the head itself changes; (2) walk with `prev`, unlinking `prev->next` while it matches, and advancing only when it doesn't.

::: code-group
<<< @/../code/ds/mock/mock-q6.cpp#answer [Answer to write]
<<< @/../code/ds/mock/mock-q6.cpp [Full program]
<<< @/../code/ds/mock/mock-q6.out{txt} [Output]
:::

The four test lines: matches at the front, middle and end (3 3 1 3 3 2 3 → 1 2); every node matching (empty result); no match; an empty list. O(n) time, O(1) extra space.

**Marking points:** the head can change (return it); consecutive matches (do not advance after deleting); `delete` every removed node; the empty list.

:::::

</Q>
