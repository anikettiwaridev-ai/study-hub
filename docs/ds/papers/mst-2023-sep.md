---
title: Mid-semester, September 2023
---

# Mid-semester, September 2023

<PaperHeader :rows="[
  ['Programme', 'B.Tech (AE/CE/EE/ECE/ME/MME/PIE), 2nd year'],
  ['Course code', 'CS6301'],
  ['Maximum marks', '25'],
  ['Time allowed', '1 hour 30 minutes'],
  ['Note on the paper', 'All questions are compulsory. Assume suitably and state additional data required, if any.'],
]" />

::: info Why this paper matters
The first appearance of **Biased Search** (repeated in Oct 2025) and of the recursive `next->next` print (also in Oct 2022). Its linked-list classes are given in C++, the way your papers give them.
:::

<Q id="S23.Q1">

Convert the below infix expression to postfix expression. Clearly show operation performed for each character, content of stack, and postfix string after each step.

**[a + (b − c)] ∗ [(d − e)/(f − g + h)]**

::::: details Solution

Square brackets behave exactly like round ones: push on `[`, pop to the matching `[` on `]`.

| Symbol | Operation | Stack (bottom → top) | Postfix string |
|---|---|---|---|
| [ | push [ | [ | |
| a | operand → output | [ | a |
| + | push + | [ + | a |
| ( | push ( | [ + ( | a |
| b | operand → output | [ + ( | ab |
| − | push − | [ + ( − | ab |
| c | operand → output | [ + ( − | abc |
| ) | pop − until (, drop ( | [ + | abc− |
| ] | pop + until [, drop [ | (empty) | abc−+ |
| ∗ | push ∗ | ∗ | abc−+ |
| [ | push [ | ∗ [ | abc−+ |
| ( | push ( | ∗ [ ( | abc−+ |
| d | operand → output | ∗ [ ( | abc−+d |
| − | push − | ∗ [ ( − | abc−+d |
| e | operand → output | ∗ [ ( − | abc−+de |
| ) | pop − until (, drop ( | ∗ [ | abc−+de− |
| / | push / | ∗ [ / | abc−+de− |
| ( | push ( | ∗ [ / ( | abc−+de− |
| f | operand → output | ∗ [ / ( | abc−+de−f |
| − | push − | ∗ [ / ( − | abc−+de−f |
| g | operand → output | ∗ [ / ( − | abc−+de−fg |
| + | pop − (equal), push + | ∗ [ / ( + | abc−+de−fg− |
| h | operand → output | ∗ [ / ( + | abc−+de−fg−h |
| ) | pop + until (, drop ( | ∗ [ / | abc−+de−fg−h+ |
| ] | pop / until [, drop [ | ∗ | abc−+de−fg−h+/ |
| end | pop ∗ | (empty) | abc−+de−fg−h+/∗ |

**Postfix: `abc-+de-fg-h+/*`**

::: danger f − g + h
Inside the last bracket, `+` arriving with `−` on top **pops** the `−` (same precedence, left to right): `fg−h+`, meaning (f − g) + h. Keeping both gives `fgh+−`, which is f − (g + h).
:::

:::::

</Q>

<Q id="S23.Q2a">

Consider the below implementation of linked list in C++ for both parts (a) and (b):

```cpp
class Node {                      class LL {
  public:                           public:
  int data;                         Node* head;
  Node* next;                       LL () {
  Node (int dt) {                     head = NULL;
    data = dt;                      }
    next = NULL;                  }
}}
```

a) Write a function to implement the function `LL::insertM(int key)` which inserts a new node with data key in the middle of linked list. If linked list have 4 nodes, new node will be inserted after the second node; if 5 nodes then new node will be inserted after third node.

::::: details Solution

With n nodes the new node goes after node **⌈n/2⌉**: 4 → after the 2nd, 5 → after the 3rd. In integer arithmetic that is `(n + 1) / 2`. Count the nodes, walk to that node, link the new node after it. Edge cases: an empty list (the new node becomes the head) and a single node (insert after it).

::: code-group
<<< @/../code/ds/papers/s23-q2a.cpp#answer [Answer to write]
<<< @/../code/ds/papers/s23-q2a.cpp [Full program]
<<< @/../code/ds/papers/s23-q2a.out{txt} [Output]
:::

The four runs: 4 nodes, 5 nodes, 1 node, empty list.

**One-pass alternative:** slow/fast pointers. Start `slow = head`, `fast = head->next`; while `fast && fast->next`, move slow one step and fast two. Slow stops on node ⌈n/2⌉. Either version is O(n).

::: danger Link before you redirect
`n->next = t->next;` must come before `t->next = n;`. The other order makes the new node point at itself and loses the second half of the list.
:::

:::::

</Q>

<Q id="S23.Q2b">

b) Consider a function is implemented as below:

```cpp
void fun (Node* start) {
    if (start == Null) return;
    cout<< start->data;
    if( start -> next != NULL)
        fun( start -> next -> next);
    cout<< start -> data;
}
```

What will be the output of the above function for the given linked list? **9 −> 12 −> 34 −> 37 −> 40 −> 49**

::::: details Solution

(`Null` as printed would not compile; assume `NULL`.)

The function prints a node, jumps **two** nodes ahead, and prints the node again on the way back.

| Call | Prints first | Next call | Prints on the way back |
|---|---|---|---|
| fun(9) | 9 | fun(34) (9 → 12 → 34) | 9 (last) |
| fun(34) | 34 | fun(40) | 34 |
| fun(40) | 40 | 40 → 49, so fun(49 → next) = fun(NULL) | 40 (first on the way back) |
| fun(NULL) | returns immediately | | |

Output: **9 34 40 40 34 9**. Because there is no separator in the `cout`, the screen literally shows **`9344040349`**. Write both, and say why.

::: code-group
<<< @/../code/ds/papers/s23-q2b.cpp [Program]
<<< @/../code/ds/papers/s23-q2b.out{txt} [Output]
:::

The same function on 1 → 2 → … → 6 was [Oct 2022 Q6](./mst-2022-a#q6).

:::::

</Q>

<Q id="S23.Q3">

Consider a Dqueue containing elements {10, 20, 30} where element 10 is at the front. Following operations are performed in the same order. Show the content of Dqueue after each operation.

InsertFront(23); DeleteFront( ); DeleteFront( ); InsertFront(28); InsertRear(34); Deletefront( ); InsertRear(45); InsertRear(13); DeleteRear( ); InsertRear(21);

::::: details Solution

| Operation | Deque (front → rear) |
|---|---|
| start | 10 20 30 |
| InsertFront(23) | 23 10 20 30 |
| DeleteFront() removes 23 | 10 20 30 |
| DeleteFront() removes 10 | 20 30 |
| InsertFront(28) | 28 20 30 |
| InsertRear(34) | 28 20 30 34 |
| DeleteFront() removes 28 | 20 30 34 |
| InsertRear(45) | 20 30 34 45 |
| InsertRear(13) | 20 30 34 45 13 |
| DeleteRear() removes 13 | 20 30 34 45 |
| InsertRear(21) | **20 30 34 45 21** |

No capacity is given, so assume the deque never overflows.

:::::

</Q>

<Q id="S23.Q4">

Biased Search is modified binary search where mid is calculated as below:

**mid = (2 ∗ s + e)/3**

where s is start index and e is end index. For the following sorted list of elements, apply Biased Search to search element 'X'. Show each step clearly.

**P Q R S T U V W X Y Z**

::::: details Solution

Indices 0 to 10. Integer division throughout.

| Step | s | e | mid = ⌊(2s + e)/3⌋ | A[mid] | Comparison | Action |
|---|---|---|---|---|---|---|
| 1 | 0 | 10 | ⌊10/3⌋ = 3 | S | X > S | s = 4 |
| 2 | 4 | 10 | ⌊18/3⌋ = 6 | V | X > V | s = 7 |
| 3 | 7 | 10 | ⌊24/3⌋ = 8 | X | X = X | **found at index 8** |

X is found at **index 8** after **3 comparisons**. The pseudocode and the Oct 2025 version (4 comparisons on N…Z) are on [that paper](./mst-2025-oct#q4); the program that checks both is in [Unit 1](../notes/unit-1#biased-search).

:::::

</Q>
