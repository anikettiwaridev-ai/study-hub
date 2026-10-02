---
title: Mid-semester, October 2025
---

# Mid-semester, October 2025

<PaperHeader :rows="[
  ['Programme', 'B.Tech. (CS / CS(AI)), 2nd year'],
  ['Course code', 'CTN301 / AIN301'],
  ['Maximum marks', '30'],
  ['Time allowed', '1 hour 30 minutes'],
  ['Note on the paper', 'All questions are compulsory. Assume suitably and state additional data required, if any.'],
]" />

::: info The paper closest to yours
Last year's batch, the same course, the same point in the semester. Six questions of 5 marks: one conversion, one recurrence, one circular-queue trace, Biased Search, and two linked-list functions in C++. The [mock paper](../mock-mst) copies this shape and adds the Unit 5 tree question your syllabus now includes. Give yourself 90 minutes, about 13 per question.
:::

<Q id="O25.Q1">

Convert the below infix expression to postfix expression using stack. Clearly show the operation performed for each character, the content of stack, and the postfix string after each step.

**a − (b + c ∗ d / (e / f ∗ g + h) − i)**

::::: details Solution

Precedence: `^` > `* /` > `+ -`; equal precedence pops (left-associative) except `^`. On `)`, pop to the matching `(`.

| Symbol | Operation | Stack (bottom → top) | Postfix string |
|---|---|---|---|
| a | operand → output | (empty) | a |
| − | push − | − | a |
| ( | push ( | − ( | a |
| b | operand → output | − ( | ab |
| + | push + (top is `(`) | − ( + | ab |
| c | operand → output | − ( + | abc |
| ∗ | push ∗ (∗ > +) | − ( + ∗ | abc |
| d | operand → output | − ( + ∗ | abcd |
| / | pop ∗ (equal), push / | − ( + / | abcd∗ |
| ( | push ( | − ( + / ( | abcd∗ |
| e | operand → output | − ( + / ( | abcd∗e |
| / | push / (top is `(`) | − ( + / ( / | abcd∗e |
| f | operand → output | − ( + / ( / | abcd∗ef |
| ∗ | pop / (equal), push ∗ | − ( + / ( ∗ | abcd∗ef/ |
| g | operand → output | − ( + / ( ∗ | abcd∗ef/g |
| + | pop ∗ (higher), push + | − ( + / ( + | abcd∗ef/g∗ |
| h | operand → output | − ( + / ( + | abcd∗ef/g∗h |
| ) | pop + until (, drop ( | − ( + / | abcd∗ef/g∗h+ |
| − | pop / and + (≥ −), push − | − ( − | abcd∗ef/g∗h+/+ |
| i | operand → output | − ( − | abcd∗ef/g∗h+/+i |
| ) | pop − until (, drop ( | − | abcd∗ef/g∗h+/+i− |
| end | pop remaining − | (empty) | abcd∗ef/g∗h+/+i−− |

**Postfix: `abcd*ef/g*h+/+i--`**

The table was produced by running the algorithm and the result checked by converting back. The same expression runs through the C++ version in [Unit 3](../notes/unit-3#infix-postfix).

::: danger Where marks go
- At the inner `−`, both `/` and `+` pop: `/` is higher, and `+` is equal precedence and left-associative. Popping only `/` gives the wrong order.
- The last two symbols are both `−`: the inner one (from inside the brackets) comes first, the outer last. The outer `−` is the main operator, so it must be the final symbol.
:::

:::::

</Q>

<Q id="O25.Q2">

Solve the following recurrence relation using the substitution method.

**T(n) = 2T(n/4) + n;  T(1) = 1**

::::: details Solution

```text
T(n) = 2T(n/4) + n                                         ...(1)
     = 2[2T(n/16) + n/4] + n      = 4T(n/16) + n/2 + n      ...(2)
     = 4[2T(n/64) + n/16] + n/2 + n = 8T(n/64) + n/4 + n/2 + n   ...(3)

After k substitutions:
T(n) = 2^k T(n/4^k) + n (1 + 1/2 + 1/4 + ... + 1/2^(k−1))

Base case: n/4^k = 1  ⇒  4^k = n  ⇒  k = log₄n
Then 2^k = 2^(log₄n) = n^(1/2) = √n

Geometric series: 1 + 1/2 + ... + 1/2^(k−1) = 2(1 − 1/2^k) = 2(1 − 1/√n)

T(n) = √n · T(1) + 2n(1 − 1/√n)
     = √n + 2n − 2√n
     = 2n − √n
```

**T(n) = 2n − √n = O(n)** (indeed Θ(n)).

Check with n = 16: T(4) = 2T(1) + 4 = 6 and T(16) = 2·6 + 16 = 28; the formula gives 32 − 4 = 28 ✓.

::: tip Why it is linear
Level i of the expansion costs n/2ⁱ: the levels shrink geometrically, so the top level (n) dominates. Master-theorem check: a = 2, b = 4, n^(log₄2) = √n, and f(n) = n is polynomially larger: case 3, Θ(n).
:::

:::::

</Q>

<Q id="O25.Q3">

Consider a circular queue is implemented using an array of length 5. The queue is full when 4 elements are stored in the queue. Show the content of the circular queue after each operation if the operation is executed successfully, show underflow/overflow otherwise.

Enqueue(10), Enqueue(20), Enqueue(30), Enqueue(40), Enqueue(50), Dequeue(), Enqueue(60), Dequeue(), Dequeue(), Dequeue(), Dequeue(), Dequeue(), Enqueue(70), Enqueue(80), Dequeue()

::::: details Solution

"Full at 4 out of 5" is the textbook convention: **front** points one cell **before** the first element, **rear** at the last element. Initially front = rear = 0.
- Empty: `front == rear`. Full: `(rear + 1) % 5 == front`.
- Enqueue: rear = (rear + 1) % 5, then Q[rear] = x. Dequeue: front = (front + 1) % 5, then return Q[front].

| Operation | Result | front | rear | Q[0] Q[1] Q[2] Q[3] Q[4] | Queue (front → rear) |
|---|---|---|---|---|---|
| Enqueue(10) | Q[1] = 10 | 0 | 1 | – 10 – – – | 10 |
| Enqueue(20) | Q[2] = 20 | 0 | 2 | – 10 20 – – | 10 20 |
| Enqueue(30) | Q[3] = 30 | 0 | 3 | – 10 20 30 – | 10 20 30 |
| Enqueue(40) | Q[4] = 40 | 0 | 4 | – 10 20 30 40 | 10 20 30 40 |
| Enqueue(50) | **Overflow**: (4 + 1) % 5 = 0 = front | 0 | 4 | – 10 20 30 40 | 10 20 30 40 |
| Dequeue() | removes 10 | 1 | 4 | – – 20 30 40 | 20 30 40 |
| Enqueue(60) | rear wraps to 0, Q[0] = 60 | 1 | 0 | 60 – 20 30 40 | 20 30 40 60 |
| Dequeue() | removes 20 | 2 | 0 | 60 – – 30 40 | 30 40 60 |
| Dequeue() | removes 30 | 3 | 0 | 60 – – – 40 | 40 60 |
| Dequeue() | removes 40 | 4 | 0 | 60 – – – – | 60 |
| Dequeue() | removes 60 | 0 | 0 | – – – – – | (empty) |
| Dequeue() | **Underflow**: front == rear | 0 | 0 | – – – – – | (empty) |
| Enqueue(70) | Q[1] = 70 | 0 | 1 | – 70 – – – | 70 |
| Enqueue(80) | Q[2] = 80 | 0 | 2 | – 70 80 – – | 70 80 |
| Dequeue() | removes 70 | 1 | 2 | – – 80 – – | 80 |

Final queue: **80** (front = 1, rear = 2). One overflow (Enqueue 50) and one underflow (the sixth Dequeue).

::: code-group
<<< @/../code/ds/notes/u4-circular-textbook.cpp [Checked by running]
<<< @/../code/ds/notes/u4-circular-textbook.out{txt} [Output]
:::

::: danger The trap
"Array of length 5" tempts you to store 50. The paper says it is full at 4: one cell is always kept empty so that full and empty look different. If you use the `front = rear = -1` convention instead, you must still reject 50, and you should say which convention you used.
:::

:::::

</Q>

<Q id="O25.Q4">

Biased Search is modified binary search where mid is calculated as below:

**mid = (2 ∗ s + e) / 3**

where s is the start index and e is end index. Write the pseudo-code for the Biased Search and apply Biased Search to search element 'X' in the following sorted list of elements. Show each step clearly.

**N O P Q R S T U V W X Y Z**

::::: details Solution

**Pseudocode**

```text
BiasedSearch(A, n, key)
    s ← 0
    e ← n − 1
    while s ≤ e do
        mid ← ⌊(2·s + e) / 3⌋
        if A[mid] = key then
            return mid                    // found
        else if key > A[mid] then
            s ← mid + 1                   // search the right part
        else
            e ← mid − 1                   // search the left part
    return −1                             // not found
```

**Applying it** to N O P Q R S T U V W X Y Z (indices 0 to 12), key = X:

| Step | s | e | mid = ⌊(2s + e)/3⌋ | A[mid] | Comparison | Action |
|---|---|---|---|---|---|---|
| 1 | 0 | 12 | ⌊12/3⌋ = 4 | R | X > R | s = 5 |
| 2 | 5 | 12 | ⌊22/3⌋ = 7 | U | X > U | s = 8 |
| 3 | 8 | 12 | ⌊28/3⌋ = 9 | W | X > W | s = 10 |
| 4 | 10 | 12 | ⌊32/3⌋ = 10 | X | X = X | **found at index 10** |

X is found at **index 10** (the 11th element) after **4 comparisons**.

::: code-group
<<< @/../code/ds/notes/u1-biased-search.cpp#answer [Checked by running]
<<< @/../code/ds/notes/u1-biased-search.out{txt} [Output]
:::

::: tip If they ask for the complexity
In the worst case the search continues into the larger part (about 2/3 of the range): T(n) = T(2n/3) + 1 = **O(log n)**, the same order as binary search with a larger constant.
:::

:::::

</Q>

<Q id="O25.Q5">

Consider the following code snippets for node class and PQ (Priority Queue) class:

```cpp
class node {
    int priority;
    int key;
    int value;
    node * next;
    node (int p, int k, int v) {
        priority = p;
        key = k;
        value = v;
        next = NULL;
} };

class PQ {
    node * head;
    node * tail;
    PQ ( ){
        head = NULL;
        tail = NULL;
    }
    ENQUEUE (int p, int k, int v);
};
```

Write a function in C++ to implement the ENQUEUE operation that inserts a node into a priority queue implemented using a SLL. The nodes in the SLL should be inserted in such a way that the priority queue remains sorted in descending order of priority (i.e., the highest-priority node appears first).

::::: details Solution

Assumptions (stated, as the paper allows): the members are accessible (the classes as printed have no `public:`), and nodes of **equal priority keep their arrival order** (first come, first served), which is what a queue means.

Three cases: (1) empty queue; (2) the new node beats the head, so it becomes the head; (3) otherwise walk while the **next** node's priority is **≥ p**, and link after it, moving `tail` if it went at the end.

::: code-group
<<< @/../code/ds/papers/o25-q5.cpp#answer [Answer to write]
<<< @/../code/ds/papers/o25-q5.cpp [Full program]
<<< @/../code/ds/papers/o25-q5.out{txt} [Output]
:::

The run shows each case: priority 5 becomes the head, priority 1 the tail, the second priority-3 node goes **behind** the first one, and priority 4 lands in the middle.

**Complexity:** ENQUEUE is O(n) (it may walk the whole list); DEQUEUE is O(1), because the highest priority is always the head. That trade-off is the reason to keep the list sorted.

::: danger Marks are lost on
- `>` instead of `>=` in the walk: equal priorities then jump ahead of earlier ones.
- `if (p >= head->priority)` for the new-head case: same problem.
- Forgetting `tail` when inserting at the end, or forgetting the empty-list case.
:::

The same function was a fill-in-the-blanks in [Lab Quiz 2 (2026)](../quizzes/2026-lab-2#q1).

:::::

</Q>

<Q id="O25.Q6">

Write a function in C++ to perform addition of two sparse matrices. Each sparse matrix is represented using a SLL in row-wise order. Each node in the SLL contains three data members: row, col, and value; representing the position and value of a non-zero element in the matrix. Define a function `node* mat_addition(node* mat1, node* mat2);` that takes pointers to the two matrices as input and returns a pointer to the resultant matrix after addition. The node structure in the SLL is given below.

(Note: When all the non-zero values of the first row are stored first, followed by the values of the second row, third row, and so on, the matrix is said to be stored in row-wise order.)

```cpp
class node {
    int row;
    int column;
    int value;
    node * next;
    node (int r, int c, int v) {
        row = r;
        column = c;
        value = v;
        next = NULL;
} };
```

::::: details Solution

Both lists are sorted by (row, column), so adding them is **merging two sorted lists**:
- the same cell in both → add the values; store a node only if the sum is not 0;
- otherwise the cell that comes **first in row-wise order** (smaller row, or same row and smaller column) is copied and that list advances;
- when one list ends, copy the rest of the other.

The result is a new list in row-wise order; the inputs are left unchanged. Both matrices are assumed to have the same dimensions (needed for addition).

::: code-group
<<< @/../code/ds/papers/o25-q6.cpp#answer [Answer to write]
<<< @/../code/ds/papers/o25-q6.cpp [Full program]
<<< @/../code/ds/papers/o25-q6.out{txt} [Output]
:::

In the run, cell (1, 3) holds 4 in one matrix and −4 in the other, so the sum list has no node for it.

**Complexity:** O(m + n) for m and n nonzeros: each node is looked at once.

::: danger Marks are lost on
- comparing only rows (two nodes in the same row must be ordered by column);
- storing a 0 when values cancel;
- not copying the leftover nodes after the loop.
:::

:::::

</Q>
