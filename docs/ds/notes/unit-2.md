---
title: Unit 2 · Linked lists
---

# Unit 2 · Linked lists

Singly, doubly and circular lists, the function bank the papers draw from, and the two applications the papers ask about: polynomials and sparse matrices. <span class="hl-legend">Highlighted lines</span> are the likely lab-quiz blanks.

::: info How this unit is examined
- **Mid-semester:** a linked-list question was on **every one of the six papers**, usually "write a function" for 5–6 marks: insert in the middle (Sep 2023), merge two sorted lists (2024 B), insert into a sorted doubly linked list and remove duplicates (Mar 2024), `stretch` (2022 B), the smallest element (Oct 2022), a priority queue as a sorted list and sparse-matrix addition (Oct 2025). Plus a recursive output trace (Oct 2022, Sep 2023).
- **Theory quiz:** complexity with or without a tail pointer, the 8th node from the start or end, building a sorted list, memory of an array of lists.
- **Lab quiz:** both lab quizzes so far were linked lists: insert before a key, remove duplicates, merge (2025); delete a node from p alone, second largest (2026).
:::

## 1. The toolkit: what every operation costs {#toolkit}

| Operation | SLL, head only | SLL, head + tail | DLL, head + tail | Circular, tail only |
|---|---|---|---|---|
| insert at head | O(1) | O(1) | O(1) | O(1) (after `tail`) |
| insert at tail | O(n) | O(1) | O(1) | O(1) |
| delete head | O(1) | O(1) | O(1) | O(1) |
| delete tail | O(n) | **O(n)** (needs the node before) | O(1) (`tail->prev`) | O(n) |
| k-th from the start, k constant (e.g. the 8th) | O(1) | O(1) | O(1) | O(1) |
| k-th from the end, k constant | O(n) | O(n) | O(1) | O(n) |
| insert at / delete the 2nd-last | O(n) | O(n) | O(1) | O(n) |
| swap the first and last values | O(n) | O(1) | O(1) | O(1) |
| search, print, find the middle | O(n) | O(n) | O(n) | O(n) |

::: tip The two facts behind last year's and this year's answers
**A constant k is O(1).** Walking 8 steps from the head is 8 operations however big n is ([Quiz II 2025 Q4](../quizzes/2025-theory-2#q4), [TQ-1 2026 Q8](../quizzes/2026-theory-1#q8)).
**A tail pointer helps only at the tail.** It does not help anything that needs the node *before* the tail. Only a doubly linked list can step backwards. In a circular list kept by its tail, `tail->next` is the head, so both ends of insertion are O(1).
:::

## 2. The node, and how a function changes the head {#node}

```cpp
class Node {
public:
    int data;
    Node* next;
    Node(int val) { data = val; next = NULL; }
};
```

An operation that can change the head (insert at the front, delete the first node) must either take the head **by reference** or **return** the new head:

```cpp
void insertFront(Node*& head, int x);     // Node*& : changes main's head directly
Node* insertFront(Node* head, int x);     // returns it: call as head = insertFront(head, x);
```

A plain `Node* head` parameter is a copy: changing it inside the function changes nothing in `main`. The slides use the returning style (`ListStart = insertF(ListStart, ndata);`); lab quizzes use both.

**Building nodes by hand** (Practice sheet 2 Q4): local `Node first, second, third;` work only inside the function that declares them; a node made with `new` survives the function. After `delete p;` set `p = nullptr;` at once, so no later line can use the freed memory (a dangling pointer) or delete it twice.

## 3. The core templates {#core}

::: code-group
<<< @/../code/ds/notes/u2-sll.cpp#insertFront{3,4} [insertFront]
<<< @/../code/ds/notes/u2-sll.cpp#insertEnd{3,5,6} [insertEnd]
<<< @/../code/ds/notes/u2-sll.cpp#insertAtPosition [insertAtPosition]
<<< @/../code/ds/notes/u2-sll.cpp#deleteValue{6,11,14} [deleteValue]
<<< @/../code/ds/notes/u2-sll.cpp#search{3} [search]
<<< @/../code/ds/notes/u2-sll.cpp [Whole program]
<<< @/../code/ds/notes/u2-sll.out{txt} [Output]
:::

::: danger Three walk patterns: know which one you need
- `while (t != NULL)` visits **every** node (print, count, search).
- `while (t->next != NULL)` stops **on** the last node (insert at the end).
- `while (t->next != NULL && t->next->data != key)` stops on the node **before** the target (delete, insert before). You need the node before, because a singly linked list cannot step back.

Check `t != NULL` **before** `t->data`: `&&` stops at the first false, so the order is what prevents a NULL dereference.
:::

::: warning The slides' `deleteNode` deletes by position
The slides' `Linkedlist::deleteNode(int nodeOffset)` removes the n-th node, though the class declaration calls it `deleteNode(int)` and Practice sheet 2 Q1 asks to delete by **value**. The by-value version is above and [on the practice-sheet page](../practice/sheet-2#q1). The slides' `insertF` also uses `ndata` where the parameter is `nData`, which would not compile.
:::

## 4. The function bank {#function-bank}

Every list function the papers and quizzes have asked for. Each one runs; the outputs are on the linked pages.

| Function | Asked in | The one idea |
|---|---|---|
| [Insert in the middle](../papers/mst-2023-sep#q2a) | Sep 2023 Q2a | count n, stop on node ⌈n/2⌉ |
| [Insert into a sorted DLL](../papers/mst-2024-mar#q2b) | Mar 2024 Q2b | four pointer updates; skip the third at the end |
| [Remove duplicates, unsorted](../papers/mst-2024-mar#q2c) | Mar 2024 Q2c | for each p, delete later copies; advance only when nothing was deleted |
| [Remove duplicates, sorted](../quizzes/2025-lab-1#q2) | Lab I 2025 | duplicates are adjacent: compare with `next` |
| [Merge two sorted lists](../papers/mst-2024-b#q3b) | 2024 B Q3b, Lab I 2025 | dummy node + tail; attach the leftover list |
| [`stretch`](../papers/mst-2022-b#q3) | 2022 B Q3 | remember the next original node before inserting k copies |
| [Smallest element](../papers/mst-2022-a#q4) | Oct 2022 Q4 | start from the first node's value, not 0 |
| [Second largest](../quizzes/2026-lab-1#q3) | LQ-1 2026 | old first becomes second |
| [Delete the node at p, no head](../quizzes/2026-lab-1#q2) | LQ-1 2026 | copy the next node into p, delete the next |
| [Insert before a key](../quizzes/2025-lab-1#q1) | Lab I 2025 | stop on the node before: `t->next->data != key` |
| [k-th from the middle](../papers/endsem-2024#q2b) | Dec 2024 Q2b | node n/2 + 1 − k, or −1 |
| [Priority-queue ENQUEUE](../papers/mst-2025-oct#q5) | Oct 2025 Q5, LQ-2 2026 | walk past priorities ≥ p |
| [Sparse-matrix addition](../papers/mst-2025-oct#q6) | Oct 2025 Q6 | merge by (row, column); drop zero sums |

### Insert in the middle (Sep 2023 Q2a)

<<< @/../code/ds/papers/s23-q2a.cpp#answer{6,9,10}

### Reverse a list in place

::: code-group
<<< @/../code/ds/notes/u2-reverse.cpp#reverse{4,5,6,7} [reverseList]
<<< @/../code/ds/notes/u2-reverse.cpp#printReverse [printReverse (recursion)]
<<< @/../code/ds/notes/u2-reverse.out{txt} [Output]
:::

Three pointers, four lines, in this order: remember the rest, turn the arrow, step both. The old last node is the new head. O(n) time, O(1) space; the recursive print is O(n) space.

### Middle node: slow and fast pointers

`slow` moves one step and `fast` two; when `fast` reaches the end, `slow` is in the middle. One pass, O(n). With an even count n it stops on node n/2 + 1, the "middle" Dec 2024 Q2b defines.

```cpp
Node *slow = head, *fast = head;
while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
}
// slow is the middle
```

### Detect and remove a loop: Floyd's algorithm (Practice sheet 2 Q5)

::: code-group
<<< @/../code/ds/notes/u2-floyd.cpp#hasCycle{5,6} [hasCycle]
<<< @/../code/ds/notes/u2-floyd.cpp#removeCycle [removeCycle]
<<< @/../code/ds/notes/u2-floyd.out{txt} [Output]
:::

## 5. Recursive functions on lists: output traces {#recursive-trace}

Oct 2022 Q6 and Sep 2023 Q2b gave the same function:

```cpp
void solve(struct node* start) {
    if (start == NULL) return;
    printf("%d ", start->data);
    if (start->next != NULL) solve(start->next->next);   // skips one node
    printf("%d ", start->data);                          // runs on the way back
}
```

**Method:** list the calls going down, then the second prints coming back up in reverse.

| Call | First print | Calls next | Second print (on the way back) |
|---|---|---|---|
| solve(1) | 1 | solve(3) | 1 (last) |
| solve(3) | 3 | solve(5) | 3 |
| solve(5) | 5 | 5→next is 6, so solve(6→next) = solve(NULL) | 5 (first on the way back) |
| solve(NULL) | returns at once | | |

Output on 1→2→3→4→5→6: **1 3 5 5 3 1**.

::: code-group
<<< @/../code/ds/papers/a22-q6.cpp [Oct 2022 Q6, run]
<<< @/../code/ds/papers/a22-q6.out{txt} [Output]
:::

::: danger Sep 2023 printed with no spaces
Sep 2023's version is `cout << start->data;` with no separator, so on 9→12→34→37→40→49 the program literally prints `9344040349`. Write the numbers **and** say they print with no spaces: 9 34 40 40 34 9. Its `if (start == Null)` (lower-case `ull`) would not even compile; assume `NULL` and say so. [Full answer](../papers/mst-2023-sep#q2b).
:::

## 6. Doubly linked list {#dll}

Each node has `prev` and `next`; the list keeps `head` and `tail`.

| | |
|---|---|
| **Advantages** | traverse both ways; delete a node or insert before it without searching for the predecessor |
| **Disadvantages** | an extra pointer per node; more links to update, so more chances for bugs |

::: code-group
<<< @/../code/ds/notes/u2-dll.cpp#insertFront [insertFront]
<<< @/../code/ds/notes/u2-dll.cpp#insertEnd [insertEnd]
<<< @/../code/ds/notes/u2-dll.cpp#deleteNode{5,6,7,8} [deleteNode]
<<< @/../code/ds/notes/u2-dll.cpp#reverse [reverse]
<<< @/../code/ds/notes/u2-dll.out{txt} [Output]
:::

**Insert into a sorted DLL** (Mar 2024 Q2b): the same four links in a fixed order, new → successor, new ← t, successor ← new (skip at the end), t → new.

<<< @/../code/ds/papers/m24-q2b.cpp#answer{12,13,14,15}

::: tip Reversing a DLL is O(n)
Swap `prev` and `next` in every node, then swap `head` and `tail`. One pass: 2024 B Q4(b)'s answer.
:::

## 7. Circular linked list {#circular}

The last node points back to the first; there is no NULL except in an empty list. Kept either by a **header pointer** or a **header node** (a special node holding a sentinel value, e.g. −1 when all data is positive).

Keeping a pointer to the **tail** is the trick: `tail->next` is the head, so insert at either end is O(1).

::: code-group
<<< @/../code/ds/notes/u2-cll.cpp#insertEnd{3,4,5} [insertEnd]
<<< @/../code/ds/notes/u2-cll.cpp#printList{7} [printList]
<<< @/../code/ds/notes/u2-cll.cpp#josephus [josephus]
<<< @/../code/ds/notes/u2-cll.out{txt} [Output]
:::

::: danger Traversal must be a do-while
`while (t != head)` with `t = head` never runs at all. The body has to run once before the test: `do { … } while (t != head);`. And an empty list (`tail == NULL`) must be checked first.
:::

**Insert** (slides): into an empty list, the node points to itself; at the start, link the new node to the old first and the last node to the new one; in the middle, as in a singly linked list. **Delete**: the last remaining node (it points to itself) empties the list; from the front, the last node must skip to the second.

**Josephus** (Practice sheet 2 Q8): 7 people, every 3rd removed: 3, 6, 2, 7, 5, 1, and **4** survives.

## 8. Polynomials as linked lists {#polynomials}

Each node holds a coefficient and a power, sorted by **descending** power: 5x¹² + 2x⁹ − x³ is (5, 12) → (2, 9) → (−1, 3).

**Addition is a merge**: compare powers; the larger power goes first; equal powers add their coefficients (and a zero sum adds nothing); finally attach whatever is left. **Subtraction** = negate the second list, then add. Both are **O(N1 + N2)**: each term is looked at once ([TQ-1 2026 Q10](../quizzes/2026-theory-1#q10)).

::: code-group
<<< @/../code/ds/notes/u2-poly.cpp#polyAdd{5,6,8} [polyAdd]
<<< @/../code/ds/notes/u2-poly.cpp#polySub [polySub]
<<< @/../code/ds/notes/u2-poly.out{txt} [Output]
:::

::: warning The slides' pseudocode for addition is broken
It uses three separate `if`s instead of `if / else if`, so after the first branch advances `L1` it can test `L1->pow` on NULL; the third test `L1->pow = L2->pow` is an assignment; the last loop does `L1 = L2->next` (an infinite loop); and `L3` is never advanced. Learn the version above.
:::

## 9. Sparse matrices {#sparse}

**Sparse**: most elements are zero. Structured ones (diagonal, tridiagonal, triangular) map into a 1-D array with a formula. Unstructured ones are stored as a list of **(row, column, value) triples** in **row-major** order (all of row 1, then row 2…), as an array or as a linked list.

The slides' example (1-based):

| | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|
| **1** | 0 | 0 | 3 | 0 | 4 |
| **2** | 0 | 0 | 5 | 7 | 0 |
| **3** | 0 | 0 | 0 | 0 | 0 |
| **4** | 0 | 2 | 6 | 0 | 0 |

Triples: (1,3,3) (1,5,4) (2,3,5) (2,4,7) (4,2,2) (4,3,6). An **array of linked lists** keeps one list per row instead (row[1] → (3,3) → (5,4), row[3] empty…).

::: code-group
<<< @/../code/ds/notes/u2-sparse.cpp#toList [matrix → list of triples]
<<< @/../code/ds/notes/u2-sparse.cpp#rebuild [list → matrix]
<<< @/../code/ds/notes/u2-sparse.out{txt} [Output]
:::

**Memory** (slides): a 500 × 500 matrix with 1994 nonzeros. 2-D array: 500 × 500 × 4 = 10⁶ bytes. Single array of triples: 3 × 1994 × 4 = 23,928 bytes. Array of lists: 23,928 + 500 × 4 = 25,928 bytes (the slides ignore the next pointers; count them if the question gives a pointer size, as [Unit 1](./unit-1#memory) shows).

**Adding two sparse matrices** (Oct 2025 Q6) is a merge on (row, column), exactly like polynomial addition:

<<< @/../code/ds/papers/o25-q6.cpp#answer{11,13}

## 10. Linked list vs array {#vs-array}

**Two advantages of linked lists** (Mar 2024 Q2a, 2 marks): (1) the size is not fixed: nodes are added at run time until memory runs out, with no reallocation; (2) insertion and deletion at a known position only relink pointers, with no shifting of elements. **Disadvantages**: no random access (the k-th element costs O(k)), binary search is no faster than linear, and every node pays for a pointer.

**Growing an array** (slides; Theory Quiz 2 2026 Q2 S1): when a full array grows by a **constant c** cells, n pushes copy about n²/(2c) elements in total: **O(n²)**. When it **doubles**, the copies add up to fewer than 2n: **O(n)** total, O(1) amortised per push. And when you resize by hand, the old block must be `delete[]`d after copying, or it leaks ([TQ-1 2026 Q2](../quizzes/2026-theory-1#q2)).

**Variations** (slides): a **dummy head node** removes the special cases for the first node and keeps the head pointer fixed, at the cost of one extra node. A **sorted list** lets search stop early, but insert must find its place (Theory Quiz 1 2026 Q6: building a sorted list from n inputs is O(n) at best, when each input goes at the front, and O(n²) at worst).

## Traps and the 5-minute checklist {#traps}

| # | Trap | Correct version |
|---|---|---|
| 1 | changing `head` through a plain `Node*` parameter | `Node*&`, or return the new head |
| 2 | `t->data` before checking `t != NULL` | NULL check first; `&&` stops early |
| 3 | moving a pointer before linking | link the new node to the rest first, then move `head`/`rear`/`t->next` |
| 4 | reading `->data` after `delete` | read it into a variable first |
| 5 | advancing after deleting in a loop | removing all copies: advance only when nothing was deleted |
| 6 | a tail pointer makes delete-last O(1) | only a DLL does |
| 7 | the 8th node from the head is O(n) | constant k is O(1) |
| 8 | `while (t != head)` on a circular list | do-while |
| 9 | the smallest element starting from 0 | start from the first node's value |
| 10 | a sparse sum of 0 stored as a node | store nothing |

**The checklist for every list function:** empty list · one node · the head changes · the last node · memory freed and pointers reset · O(?) stated.

## Quick check {#quick-check}

<Drill n="1" tag="Complexity">

Singly linked list with head and tail pointers, n > 8. Time to find the 8th node from the beginning, and the 8th from the end?

<Mcq :options="['O(1), O(1)', 'O(n), O(n)', 'O(1), O(n)', 'O(n), O(1)']" answer="c">

8 steps from the head is a constant: O(1). From the end, a singly linked list cannot step back, so you walk n − 8 nodes: O(n). The tail pointer does not help.

</Mcq>

</Drill>

<Drill n="2" tag="Same/different">

<FillIn q="SLL with only a head pointer vs SLL with head and tail: deleting the 2nd-last node. Same or different?" answer="same">

Both need the 3rd-last node, found only by walking from the head: O(n) in both. A tail pointer doesn't give the node before the tail.

</FillIn>

</Drill>

<Drill n="3" tag="Same/different">

<FillIn q="SLL with only a head pointer vs SLL with head and tail: swapping the values of the first and last nodes. Same or different?" answer="different">

Head only: walk to the last node, O(n). With a tail pointer both are at hand, O(1).

</FillIn>

</Drill>

<Drill n="4" tag="Trace">

<FillIn q="Output of the `solve` function (prints, recurses on `start->next->next`, prints again) on 1→2→3→4→5→6? Numbers separated by spaces." answer="1 3 5 5 3 1">

Going down prints 1, 3, 5; from 5 the call is on 6→next = NULL. Coming back prints 5, 3, 1.

</FillIn>

</Drill>

<Drill n="5" tag="Lab blank">

<FillIn q="Remove duplicates from a SORTED list: `if (curr->data == curr->next->data) { Node* tmp = ____; curr->next = curr->next->next; delete tmp; }`" answer="curr->next">

`tmp` must be a `Node*`, the node being skipped. Writing `curr->next->data` would be an `int`: the type check catches it.

</FillIn>

</Drill>

<Drill n="6" tag="Lab blank">

<FillIn q="Delete the node p points to (not the last), with no head pointer: `Node* temp = p->next; p->data = temp->data; p->next = ____; delete temp;`" answer="temp->next">

Copy the next node into p, then unlink the next node. Its successor is `temp->next`.

</FillIn>

</Drill>

<Drill n="7" tag="Complexity">

Building a sorted singly linked list of n elements, read one by one, with only a head pointer. Best and worst case?

<Mcq :options="['O(n), O(n)', 'O(n), O(n²)', 'O(n²), O(n)', 'O(n²), O(n²)']" answer="b">

Best: every new element is the smallest and goes at the head, O(1) each, O(n) total. Worst: every element goes at the end, 1 + 2 + … + n = O(n²).

</Mcq>

</Drill>

<Drill n="8" tag="Applications">

<FillIn q="Two polynomials with N1 and N2 terms, stored as lists in descending power. Time for E1 − E2?" answer="O(N1 + N2)|O(N1+N2)|O(n1+n2)|O(n1 + n2)">

Negate and merge: every term is visited once.

</FillIn>

</Drill>
