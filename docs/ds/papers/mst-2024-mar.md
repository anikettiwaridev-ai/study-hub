---
title: Mid-semester, March 2024 (Paper A)
---

# Mid-semester, March 2024 (Paper A)

<PaperHeader :rows="[
  ['Programme', 'B.Tech (CSE-DS), 2nd year, 3rd semester'],
  ['Course code', 'DSN3001'],
  ['Maximum marks', '30'],
  ['Time allowed', '1.5 hours'],
  ['Note on the paper', 'All questions are compulsory. Check the paper for any discrepancy before starting.'],
]" />

::: info About this paper
The data-science branch's version of the course (DSN3001), with the same syllabus. The compiled PDF files it under 2024-25, but the paper itself says March 2024. It is the only paper that asked the **master theorem**, and the only one that splits questions into many 2–2.5 mark parts, so short answers must still be complete.
:::

<Q id="M24.Q1a">

Solve the following recurrence relation and find its big oh notation:

T(n) = T(n − 1) + n for n > 1;  T(n) = 1 for n = 1

::::: details Solution

```text
T(n) = T(n−1) + n
     = [T(n−2) + (n−1)] + n         = T(n−2) + (n−1) + n
     = [T(n−3) + (n−2)] + (n−1) + n = T(n−3) + (n−2) + (n−1) + n
after k steps:  T(n−k) + (n−k+1) + ... + (n−1) + n
base: n − k = 1  ⇒  k = n − 1
T(n) = T(1) + 2 + 3 + ... + n
     = 1 + 2 + 3 + ... + n
     = n(n + 1)/2 = (n² + n)/2
```

**T(n) = n(n + 1)/2 = O(n²).** This is the slides' Example 3, and the same recurrence was an MCQ in [Theory Quiz 1 (2026)](../quizzes/2026-theory-1#q7).

:::::

</Q>

<Q id="M24.Q1b">

Solve the following recurrence relations using master theorem:

(i) T(n) = 2T(n/2) + √n  (ii) T(n) = 6T(n/3) + n² log n

::::: details Solution

Master theorem for T(n) = aT(n/b) + f(n): compare f(n) with n^(log_b a).

**(i)** a = 2, b = 2, so n^(log₂2) = n¹ = n. f(n) = √n = n^0.5 = O(n^(1 − ε)) with ε = 0.5: f is polynomially **smaller**.
Case 1: **T(n) = Θ(n)**.

**(ii)** a = 6, b = 3, so n^(log₃6) ≈ n^1.63. f(n) = n² log n = Ω(n^(1.63 + ε)) with ε ≈ 0.37: f is polynomially **larger**.
Regularity: a·f(n/b) = 6·(n/3)²·log(n/3) = (2/3)·n²·log(n/3) ≤ (2/3)·n² log n, so c = 2/3 &lt; 1 ✓.
Case 3: **T(n) = Θ(n² log n)**.

::: tip The three cases in one line each
Smaller f: the leaves win, Θ(n^(log_b a)). Equal: every level costs the same, multiply by log n. Larger f (and regular): the root wins, Θ(f(n)). See [Unit 1](../notes/unit-1#master).
:::

:::::

</Q>

<Q id="M24.Q2a">

Give any two advantages of linked list over arrays?

::::: details Solution

1. **Dynamic size.** A linked list grows and shrinks at run time, one node at a time, until memory runs out. An array's size is fixed when it is created; growing it means allocating a bigger block and copying every element.
2. **Cheap insertion and deletion.** At a known position, inserting or deleting a node only changes a couple of pointers, O(1). In an array every element after the position must be shifted, O(n).

(Also acceptable: no wasted reserved space; the nodes need not be contiguous in memory. The price is no random access, O(k) to reach the k-th element, and an extra pointer per node.)

:::::

</Q>

<Q id="M24.Q2b">

Given a sorted doubly linked list L in ascending order of integers with START pointing to the first node of L. Write a pseudocode/algorithm for insertion of element q into L.

::::: details Solution

```text
INSERT_SORTED(START, q)
1. NEW ← create node;  NEW.data ← q;  NEW.prev ← NULL;  NEW.next ← NULL
2. if START = NULL then                     // empty list
       START ← NEW;  return
3. if q ≤ START.data then                   // becomes the first node
       NEW.next ← START;  START.prev ← NEW;  START ← NEW;  return
4. T ← START
5. while T.next ≠ NULL and T.next.data < q do
       T ← T.next                           // T = last node smaller than q
6. NEW.next ← T.next                        // (1) new → successor
7. NEW.prev ← T                             // (2) new ← T
8. if T.next ≠ NULL then T.next.prev ← NEW  // (3) successor ← new (skip at the end)
9. T.next ← NEW                             // (4) T → new
```

The same in C++, checked: inserting 25 (middle), 5 (front) and 50 (end), and printing backwards proves every `prev` link is right.

::: code-group
<<< @/../code/ds/papers/m24-q2b.cpp#answer [C++]
<<< @/../code/ds/papers/m24-q2b.out{txt} [Output]
:::

::: danger Order of the four links
Step 9 must come **after** steps 6 and 8: once `T.next` points at NEW, the old successor is reachable only through `NEW.next`. And at the end of the list there is no successor, so step 8 is skipped.
:::

:::::

</Q>

<Q id="M24.Q2c">

Given an unsorted singly linked list L with START pointing to the first node of L. Write a pseudocode/algorithm to remove duplicate nodes from L.

::::: details Solution

Keep the **first** occurrence of each value. For each node P, scan the rest of the list with Q (where Q.next is the node being checked) and delete every node equal to P.

```text
REMOVE_DUPLICATES(START)
1. P ← START
2. while P ≠ NULL do
3.     Q ← P
4.     while Q.next ≠ NULL do
5.         if Q.next.data = P.data then
6.             D ← Q.next;  Q.next ← D.next;  free(D)    // unlink the duplicate
7.         else
8.             Q ← Q.next                                // advance only if nothing was deleted
9.     P ← P.next
```

::: code-group
<<< @/../code/ds/papers/m24-q2c.cpp#answer [C++]
<<< @/../code/ds/papers/m24-q2c.out{txt} [Output]
:::

**Complexity:** O(n²) time (a nested scan), O(1) extra space. With a hash set it would be O(n), but hashing is Unit 8. If the list were **sorted**, duplicates would be adjacent and one pass would do ([Lab Quiz I 2025 Q2](../quizzes/2025-lab-1#q2)).

::: danger The classic bug
Advancing Q after a deletion skips the node that just moved into `Q.next`, so `5 5 5` would keep a duplicate. Advance only in the `else`.
:::

:::::

</Q>

<Q id="M24.Q3">

Convert the given infix expression into an equivalent postfix expression with each intermediate step:

**A − B − C ∗ (D + E/F − G) − H**

Hence, evaluate the resulted postfix expression for A = 45, B = F = 2, C = 5, D = 3, E = 6, G = 4 and H = 3.

::::: details Solution

**Conversion** (equal precedence pops, since `+ - * /` are left-associative):

| Symbol | Operation | Stack (bottom → top) | Postfix string |
|---|---|---|---|
| A | operand → output | (empty) | A |
| − | push − | − | A |
| B | operand → output | − | AB |
| − | pop − (equal), push − | − | AB− |
| C | operand → output | − | AB−C |
| ∗ | push ∗ | − ∗ | AB−C |
| ( | push ( | − ∗ ( | AB−C |
| D | operand → output | − ∗ ( | AB−CD |
| + | push + | − ∗ ( + | AB−CD |
| E | operand → output | − ∗ ( + | AB−CDE |
| / | push / | − ∗ ( + / | AB−CDE |
| F | operand → output | − ∗ ( + / | AB−CDEF |
| − | pop / and + (≥ −), push − | − ∗ ( − | AB−CDEF/+ |
| G | operand → output | − ∗ ( − | AB−CDEF/+G |
| ) | pop − until (, drop ( | − ∗ | AB−CDEF/+G− |
| − | pop ∗ and − (≥ −), push − | − | AB−CDEF/+G−∗− |
| H | operand → output | − | AB−CDEF/+G−∗−H |
| end | pop − | (empty) | AB−CDEF/+G−∗−H− |

**Postfix: `AB-CDEF/+G-*-H-`**

**Evaluation** with A = 45, B = 2, C = 5, D = 3, E = 6, F = 2, G = 4, H = 3, i.e. `45 2 - 5 3 6 2 / + 4 - * - 3 -`:

| Token | Operation | Stack (bottom → top) |
|---|---|---|
| 45, 2 | push | 45 2 |
| − | 45 − 2 = 43 | 43 |
| 5, 3, 6, 2 | push | 43 5 3 6 2 |
| / | 6 / 2 = 3 | 43 5 3 3 |
| + | 3 + 3 = 6 | 43 5 6 |
| 4 | push | 43 5 6 4 |
| − | 6 − 4 = 2 | 43 5 2 |
| ∗ | 5 × 2 = 10 | 43 10 |
| − | 43 − 10 = 33 | 33 |
| 3 | push | 33 3 |
| − | 33 − 3 = 30 | 30 |

**Value = 30.** Check directly: 45 − 2 − 5·(3 + 6/2 − 4) − 3 = 43 − 5·2 − 3 = 30 ✓.

::: danger The first `− −`
When the second `−` arrives with `−` on top, it **pops** it (equal precedence, left-associative), giving `AB−` early. Keeping both on the stack would make it A − (B − …), the wrong value.
:::

:::::

</Q>

<Q id="M24.Q4">

We want to implement push and pop operations on Linked Stack. Give algorithms for these operations; taking start as the starting address of list, start -> info as the data part of the node and start -> next as the pointer to the next node.

::::: details Solution

The top of the stack is the **first node** (`start`), so both operations work at the head in **O(1)**.

```text
PUSH(start, x)
1. p ← new node                  // if allocation fails: overflow
2. p -> info ← x
3. p -> next ← start             // link in front of the old top
4. start ← p                     // p is the new top

POP(start)
1. if start = NULL then print "Stack underflow"; return
2. p ← start
3. x ← p -> info                 // save the data before freeing
4. start ← start -> next         // the next node becomes the top
5. free(p)
6. return x
```

::: code-group
<<< @/../code/ds/papers/m24-q4.cpp#push [push in C++]
<<< @/../code/ds/papers/m24-q4.cpp#pop [pop in C++]
<<< @/../code/ds/papers/m24-q4.out{txt} [Output]
:::

A linked stack never overflows unless memory runs out; underflow (pop on empty) must be checked.

:::::

</Q>

<Q id="M24.Q5a">

What is circular queue? Give the major drawback of queues that is handled by circular queue?

::::: details Solution

A **circular queue** is an array queue in which the last position is followed by the first: `rear = (rear + 1) % N` and `front = (front + 1) % N`, so after reaching the end of the array, insertion continues at index 0 if that cell is free.

**The drawback it fixes:** in a linear array queue, cells freed at the front by dequeues are never reused. Once `rear` reaches N − 1 the queue reports **full even when most cells are empty** (for example 4 dequeues from a full queue of 8 still leave it "full"). The circular queue reuses those cells.

:::::

</Q>

<Q id="M24.Q5b">

Consider the following operations on a Queue data structure that stores int values.

```c
enqueue (3);
enqueue (5);
enqueue (9);
printf("%d", dequeue());   // d1
enqueue (2);
enqueue (4);
printf("%d", dequeue());   // d2
printf("%d", dequeue());   // d3
enqueue (1);
enqueue (8);
```

- a. Show the contents of above code step by step stating front and rear in every step?
- b. After the code above executes, how many elements would remain in the queue?
- c. If we replace the printf statements (denoted in comments as d1, d2 and d3) with the statement enqueue(dequeue()); the Queue would contain which order of int values after all instructions have executed?

::::: details Solution

Assume an array queue with front = rear = −1 initially, large enough (no wrap-around needed).

**(a)**

| Statement | front | rear | Queue (front → rear) | Printed |
|---|---|---|---|---|
| enqueue(3) | 0 | 0 | 3 | |
| enqueue(5) | 0 | 1 | 3 5 | |
| enqueue(9) | 0 | 2 | 3 5 9 | |
| printf(dequeue()) d1 | 1 | 2 | 5 9 | 3 |
| enqueue(2) | 1 | 3 | 5 9 2 | |
| enqueue(4) | 1 | 4 | 5 9 2 4 | |
| printf(dequeue()) d2 | 2 | 4 | 9 2 4 | 5 |
| printf(dequeue()) d3 | 3 | 4 | 2 4 | 9 |
| enqueue(1) | 3 | 5 | 2 4 1 | |
| enqueue(8) | 3 | 6 | 2 4 1 8 | |

The program prints `359` (no separators in the `printf`).

**(b) 4 elements** remain: 2 4 1 8.

**(c)** Each `enqueue(dequeue())` moves the front element to the rear:

| Statement | Queue (front → rear) |
|---|---|
| enqueue 3, 5, 9 | 3 5 9 |
| enqueue(dequeue()) moves 3 | 5 9 3 |
| enqueue 2, 4 | 5 9 3 2 4 |
| enqueue(dequeue()) moves 5 | 9 3 2 4 5 |
| enqueue(dequeue()) moves 9 | 3 2 4 5 9 |
| enqueue 1, 8 | **3 2 4 5 9 1 8** |

::: code-group
<<< @/../code/ds/papers/m24-q5b.cpp [Part (a), run]
<<< @/../code/ds/papers/m24-q5b.out{txt} [Output]
:::

:::::

</Q>
