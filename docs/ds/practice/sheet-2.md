---
title: Practice sheet 2 · Linked lists
---

# Practice sheet 2 · Linked lists

<PaperHeader :rows="[
  ['Topics', 'Singly (Q1–Q5), doubly and circular (Q6–Q8), stack/queue and applications (Q9–Q10)'],
  ['Exam weight', 'High: every mid-semester paper has a linked-list function'],
]" />

<Q id="P2.Q1">

**Node class and basic list operations.** A `Node` class (int data, Node* next, default and parameterised constructors) and a `Linkedlist` class with a private head and public `insertNode(int data)` (at the end), `printList()` ("List empty" for no nodes) and `deleteNode(int data)` (removes the first node matching data). Insert 5 integers, print, then delete from the front, middle and end, printing after each.

::::: details Solution

::: code-group
<<< @/../code/ds/practice/p2-q1-q4.cpp#deleteNode [deleteNode (by value)]
<<< @/../code/ds/practice/p2-q1-q4.cpp [Program (Q1 and Q4)]
<<< @/../code/ds/practice/p2-q1-q4.out{txt} [Output]
:::

::: warning The slides' deleteNode deletes by position
The slides' version takes `nodeOffset` and removes the n-th node. The sheet asks for **by value**, as above. Deleting the head is the special case in both.
:::

:::::

</Q>

<Q id="P2.Q2">

**Insert at a specific position.** `insertAtPosition(Node* &head, int data, int pos)` with a 1-based pos: handle inserting at the head, at the end, and a position beyond the end (print an error and do nothing).

::::: details Solution

::: code-group
<<< @/../code/ds/notes/u2-sll.cpp#insertAtPosition [insertAtPosition]
<<< @/../code/ds/notes/u2-sll.out{txt} [Output of the whole program]
:::

pos = 1 is the head case; pos = length + 1 appends; anything larger walks off the end (`t == NULL`) and is rejected. The run inserts 25 at 3, 50 at 6 (= length + 1) and rejects 99 at 9.

:::::

</Q>

<Q id="P2.Q3">

**Search and reverse.** `Node* findNode(Node* head, int key)` returns the node or nullptr; `Node* reverseList(Node* head)` reverses in place with pointer changes only. Search for a present and an absent value; print before and after reversing.

::::: details Solution

::: code-group
<<< @/../code/ds/notes/u2-sll.cpp#search [findNode]
<<< @/../code/ds/notes/u2-reverse.cpp#reverse [reverseList]
<<< @/../code/ds/notes/u2-reverse.out{txt} [Output]
:::

Reversal needs three pointers (prev, curr, next) and no extra list: O(n) time, O(1) space.

:::::

</Q>

<Q id="P2.Q4">

**Direct vs node-by-node allocation.** Build a 4-node list with `insertNode()`; separately build a 3-node list by hand with `new` and `->next`; print both; delete every hand-built node one at a time, setting each pointer to nullptr, and explain why.

::::: details Solution

In the Q1 program. **Why nullptr matters:** after `delete a;`, `a` still holds the old address (a dangling pointer). Any later `a->data` reads freed memory, and a second `delete a` is undefined behaviour. With `a = nullptr`, a mistaken `delete a` does nothing, and a mistaken `a->data` fails immediately instead of silently.

:::::

</Q>

<Q id="P2.Q5">

**Detect and remove a loop.** Create a cycle deliberately; implement Floyd's `hasCycle(Node* head)`; extend it to `removeCycle(Node* head)`; demonstrate on a cyclic and an acyclic list.

::::: details Solution

::: code-group
<<< @/../code/ds/notes/u2-floyd.cpp#hasCycle [hasCycle]
<<< @/../code/ds/notes/u2-floyd.cpp#removeCycle [removeCycle]
<<< @/../code/ds/notes/u2-floyd.out{txt} [Output]
:::

The fast pointer gains one node per step on the slow one, so inside a loop it must catch up: O(n) time, O(1) space. To remove the loop, restart one pointer from the head; moving both one step at a time, they meet at the loop's first node, and the node before that meeting is the last node of the loop.

:::::

</Q>

<Q id="P2.Q6">

**Doubly linked list.** A `DNode` (data, prev, next) and a `DoublyLinkedList` with `insertFront`, `insertEnd`, `deleteNode(key)` (fixing both neighbours; first and last as special cases), `printForward`, `printBackward`. Delete from each end and the middle, printing after each.

::::: details Solution

::: code-group
<<< @/../code/ds/notes/u2-dll.cpp [Program]
<<< @/../code/ds/notes/u2-dll.out{txt} [Output]
:::

Printing backward after every change is how you prove the `prev` links are right.

:::::

</Q>

<Q id="P2.Q7">

**Circular linked list.** `insertEnd(int data)` and a `printList()` that stops after one full loop. Test with an empty list and a list of 5 nodes.

::::: details Solution

::: code-group
<<< @/../code/ds/notes/u2-cll.cpp#insertEnd [insertEnd]
<<< @/../code/ds/notes/u2-cll.cpp#printList [printList]
<<< @/../code/ds/notes/u2-cll.out{txt} [Output (with Q8)]
:::

Keeping the **tail** makes both ends O(1): the head is `tail->next`. The print is a do-while, so a one-node list still prints once.

:::::

</Q>

<Q id="P2.Q8">

**Josephus.** `josephus(Node* &head, int k)` removes every k-th node until one remains, printing each removal. Run with 7 nodes and k = 3 and print the survivor.

::::: details Solution

<<< @/../code/ds/notes/u2-cll.cpp#josephus

With 7 and k = 3: removes 3, 6, 2, 7, 5, 1; **4 survives** (output above). Keep `prev`, the node before the current one, so each removal is a single relink.

:::::

</Q>

<Q id="P2.Q9">

**Stack and queue using linked lists.** A stack (push, pop, peek, isEmpty) with the head as the top and underflow handling; a queue (enqueue, dequeue, isEmpty) with front and rear pointers so both are O(1).

::::: details Solution

::: code-group
<<< @/../code/ds/notes/u3-ll-stack.cpp [Stack (throws on underflow)]
<<< @/../code/ds/notes/u3-ll-stack.out{txt} [Stack output]
<<< @/../code/ds/notes/u4-ll-queue.cpp [Queue]
<<< @/../code/ds/notes/u4-ll-queue.out{txt} [Queue output]
:::

:::::

</Q>

<Q id="P2.Q10">

**Polynomial addition and sparse matrices.** (1) Polynomials as lists of (coeff, pow) in descending power; `polyAdd(L1, L2)` returns the sum. Test 5x¹² + 2x⁹ − x³ and 5x¹¹ − 4x⁹ + 2x³ − x. (2) Scan a mostly-zero 2-D array in row-major order into a list of (row, col, value) triples, print them, then rebuild the matrix from the list.

::::: details Solution

::: code-group
<<< @/../code/ds/notes/u2-poly.cpp#polyAdd [polyAdd]
<<< @/../code/ds/notes/u2-poly.out{txt} [Polynomial output]
<<< @/../code/ds/notes/u2-sparse.cpp [Sparse matrix]
<<< @/../code/ds/notes/u2-sparse.out{txt} [Sparse output]
:::

The sum is **5x¹² + 5x¹¹ − 2x⁹ + x³ − x**, exactly as on the slides. Adding two sparse matrices stored this way is the same merge: [Oct 2025 Q6](../papers/mst-2025-oct#q6).

:::::

</Q>
