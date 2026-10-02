---
title: Most-trapped questions
pageClass: trap-page
---

# Most-trapped questions

The mistakes that cost the most marks across six mid-semester papers, two end-semester papers, eleven quizzes and the practice sheets, roughly most frequent first. Each one says what people write, what is right, and where it was asked.

::: tip Read this the night before
If a line surprises you, open the linked question. For raw repeat counts, see [how often questions repeat](./repeats).
:::

## 1. `^` is right-associative

**People write:** `A^B^C` → `AB^C^`; a second `^` pops the first.
**Right:** `A^(B^C)` → `ABC^^`. In the stack algorithm, equal precedence pops **except** for `^`. With `^ ^` stacked, the most-operators-on-the-stack count goes up.
**Asked:** <Src r="A22.Q2b" /> <Src r="QT2.Q5" /> <Src r="MK.Q1" />

## 2. Equal precedence pops (for + − ∗ /)

**People write:** at `a − b − c`, keep both `−` on the stack, giving `abc−−`.
**Right:** the second `−` pops the first: `ab−c−`. At `f − g + h`, the `+` pops the `−`. When two operators on the stack both qualify (`/` then `+` before an incoming `−`), pop **both**.
**Asked:** <Src r="M24.Q3" /> <Src r="S23.Q1" /> <Src r="O25.Q1" />

## 3. Pop order in evaluation

**People write:** first pop = left operand.
**Right:** postfix: the first pop is the **right** operand (`op2`), the second is `op1`; push `op1 op op2`. Prefix (scanned backwards): the first pop is the **left** operand. A negative answer is often right.
**Asked:** <Src r="B22.Q1" /> <Src r="A22.Q1c" /> <Src r="QT2.Q9" /> <Src r="QA2.Q1" /> <Src r="E24.Q2c" />

## 4. The textbook circular queue holds N − 1

**People write:** an array of 5 holds 5; Enqueue(50) succeeds.
**Right:** "full when 4 elements are stored" means front sits one cell before the first element and one cell stays empty. State the convention in your first line. For overflow counting, capacity = N − 1 and only the count matters.
**Asked:** <Src r="O25.Q3" /> <Src r="QT2.Q7" /> <Src r="MK.Q3" />

## 5. Two loops are not always n²

**People write:** nested loops → O(n²).
**Right:** add up what the inner loop really does. Halving outer + linear inner = n + n/2 + … ≈ 2n: **O(n)**. `j += i` = harmonic: **O(n log n)**. Halving outer + doubling inner: **O((log n)²)**. A while that only pops what a for pushed: **O(n)**.
**Asked:** <Src r="QA1.Q3" /> <Src r="QT1.Q3" /> <Src r="A22.Q1a" /> <Src r="QT2.Q1" />

## 6. A tail pointer doesn't make delete-last O(1)

**People write:** with head and tail, every end operation is O(1).
**Right:** deleting the last node of a singly linked list needs the node **before** it: O(n) even with a tail pointer. Only a doubly linked list steps back. A constant k (the 8th node) is O(1).
**Asked:** <Src r="B22.Q5" /> <Src r="QA2.Q4" /> <Src r="QA2.Q7" /> <Src r="QT1.Q8" /> <Src r="P24.Q4" />

## 7. Link first, then move

**People write:** `t->next = n; n->next = t->next;` (the new node now points at itself).
**Right:** `n->next = t->next;` then `t->next = n;`. Push: `n->next = top; top = n;`. Every insertion follows this order.
**Asked:** <Src r="S23.Q2a" /> <Src r="M24.Q2b" /> <Src r="O25.Q5" /> <Src r="LT2.Q1" /> <Src r="LA1.Q1" />

## 8. Stop on the node before

**People write:** `while (t->next && t->data != key)` to insert before or delete the key.
**Right:** to insert before or delete, you need the **previous** node: test `t->next->data != key`.
**Asked:** <Src r="LA1.Q1" /> <Src r="P2.Q1" />

## 9. Type-check every lab blank

**People write:** `T = T->data`, `Rank[y] += x`, `min = a[left]`, `S = F->data`.
**Right:** left and right sides must match: `Node*` with `Node*` (`S = F`), `int` with `->data`, index with index (`min = left`), a size with a size (`Rank[y] += Rank[x]`).
**Asked:** <Src r="LT1.Q3" /> <Src r="LA3.Q2" /> <Src r="LA3.Q4" />

## 10. Equal priorities keep arrival order

**People write:** a new element jumps ahead of an equal-priority one; `>` in the walk.
**Right:** walk past every node with priority **≥** the new one; become the new head only on strictly greater priority. And read the direction: 2022 B says larger = higher, Dec 2023 says lower = higher.
**Asked:** <Src r="O25.Q5" /> <Src r="LT2.Q1" /> <Src r="B22.Q2" /> <Src r="E23.Q3a" />

## 11. Reset on the last dequeue

**People write:** dequeue just moves front.
**Right:** circular (−1 convention): `if (front == rear) front = rear = -1;`. Linked: `if (front == NULL) rear = NULL;`. Otherwise an empty queue reports overflow, or the next enqueue writes into freed memory.
**Asked:** <Src r="LA1.Q3" /> <Src r="P3.Q7" />

## 12. Substitution needs the base-case step

**People write:** the expansions, then jump to a Big-O.
**Right:** the k-th line, k from the base case (note T(2) = 1 gives k = log n − 1), the sum of the series, then the Big-O. For √n, substitute n = 2ᵐ. A one-line check with n = 4 or 16 catches errors.
**Asked:** <Src r="O25.Q2" /> <Src r="P24.Q1" /> <Src r="M24.Q1a" /> <Src r="E23.Q1a" /> <Src r="A22.Q2a" />

## 13. Biased Search: integer division, then ±1

**People write:** mid = 10.67; after a miss, s = mid.
**Right:** ⌊(2s + e)/3⌋; then s = mid + 1 or e = mid − 1. Show the s, e, mid table.
**Asked:** <Src r="O25.Q4" /> <Src r="S23.Q4" /> <Src r="MK.Q4" />

## 14. Recursion is space

**People write:** no array, so O(1) space.
**Right:** space = maximum recursion depth × frame. Recursive factorial is O(n); reversing a stack with recursion is O(n) space and O(n²) time.
**Asked:** <Src r="QA1.Q8" /> <Src r="P24.Q4" />

## 15. The recursive print prints twice, and Sep 2023 had no spaces

**People write:** 1 3 5 (only the first prints).
**Right:** statements after the recursive call run on the way back: **1 3 5 5 3 1**. Sep 2023's `cout` has no separator, so the screen shows `9344040349`; write both forms.
**Asked:** <Src r="A22.Q6" /> <Src r="S23.Q2b" />

## 16. Undefined behaviour and compile errors are answers

**People write:** "prints 10" for a returned local address; "garbage values" for a class without a default constructor.
**Right:** `return &local;` is **undefined behaviour**. Writing any constructor removes the default one: `X obj;` is a **compile error**. `int x = s.pop();` with `std::stack` is a compile error (`pop()` returns void).
**Asked:** <Src r="QA1.Q6" /> <Src r="QA1.Q10" />

## 17. Memory questions: the array is always full size

**People write:** the array costs only the elements in use.
**Right:** array = capacity × element size + extras, regardless of occupancy; list = n × (data + pointer) + head. Solve the strict inequality and round up.
**Asked:** <Src r="QT2.Q4" /> <Src r="QT1.Q9" />

## 18. Counting trees

**People write:** 3 labelled nodes make 5 (or 15) binary trees.
**Right:** shapes = Catalan(3) = 5; labelled = 5 × 3! = **30**; BSTs on 3 keys = 5. Preorder = postorder only for a single node.
**Asked:** <Src r="QA3.Q6" /> <Src r="QA3.Q7" /> <Src r="QA3.Q5" />

## Mistakes in the material: state an assumption {#material-errors}

- **Sep 2023 Q2b** writes `Null`: assume `NULL`.
- **Oct 2025 Q5, Q6** print the classes without `public:`: assume the members are accessible.
- **2022 B Q3** gives a Python node class for a C++ course: answer in C++ and say so.
- **The slides:** the polynomial-addition pseudocode does not work, `deleteNode` deletes by position, `insertF` uses `ndata` for `nData`, and the pointer slide's `delete q;` after `q = p; delete p;` is a double delete. The notes use corrected versions ([Unit 2](./notes/unit-2#polynomials), [Unit 1](./notes/unit-1#pointers)).
