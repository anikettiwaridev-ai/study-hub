---
title: Beat the 10-minute quiz clock
---

# Beat the 10-minute quiz clock

You studied, and still scored 0 in both lab quizzes and 6 in Theory Quiz 2. That is a **time** problem, not a knowledge problem, and it has a specific cause in each quiz type. This page names the cause, gives a routine for each type, and ends with two timed drills.

## What went wrong, quiz by quiz {#diagnosis}

| Quiz | Budget | What ate the time |
|---|---|---|
| Theory Quiz 2 | 10 marks in 10 minutes: **about 60 seconds a mark** | 5 of 9 questions are paragraphs of 50–90 words. Reading one carefully and then working out what it is asking takes 40–60 seconds before any thinking starts. |
| Lab Quiz 1 | 10 blanks in 10 minutes | 3 unfamiliar functions (recursion with a remainder, delete without a head, second largest), each to be understood before its blanks can be filled. |
| Lab Quiz 2 | 10 blanks in 10 minutes | Long descriptions (about 120 words each) and a 9-item option list per question to scan for every blank. |

The common thread: **you were deriving answers that should have been recognised.** In a 60-second budget there is time to recognise a pattern and apply it, not to understand a new situation from scratch. Every question on these quizzes was a variant of a question from last year's quizzes or the past papers, so recognition can be learnt.

## The theory-quiz routine {#theory}

1. **Two passes.** In the first pass (about 4 minutes) answer only the short ones: a code snippet, a conversion, an MCQ with a one-line stem. Put a mark next to every paragraph question and skip it.
2. **For each paragraph, read the last sentence first.** It is the question ("How many enqueue operations overflow?", "What is the minimum number of elements…?"). Then scan the paragraph only for **numbers, code and the words "only", "not", "strictly", "each"**. The rest is story.
3. **Name the type** from the decoder below. Each type has a fixed recipe.
4. **Never leave a blank.** For an S1/S2 question, judge S1 alone, then S2 alone; the letter follows mechanically. For an MCQ, eliminate by Big-O sanity (an O(n²) option for a single loop is wrong).

## The paragraph decoder {#decoder}

Every paragraph type from the last two years of quizzes, reduced to its skeleton:

| You see… | The skeleton | The recipe | Asked |
|---|---|---|---|
| an array that grows by **c extra cells** / **doubles** when full | total copying cost | +c: about n²/(2c), **O(n²)**; doubling: under 2n, **O(n)** | [TQ-2 Q2](./quizzes/2026-theory-2#q2), [Quiz I Q2](./quizzes/2025-theory-1#q2) |
| "array of capacity C … vs linked list … int = a bytes, address = b bytes" | two memory formulas | array = C·a (+ extras, **always full size**); list = n(a + b) + b; solve the inequality | [TQ-2 Q4](./quizzes/2026-theory-2#q4), [TQ-1 Q9](./quizzes/2026-theory-1#q9) |
| "array of linked lists … m people … r records" | heads + nodes | m × pointer + r × (fields + pointer) | [TQ-1 Q9](./quizzes/2026-theory-1#q9) |
| "circular queue of size N, one slot unused … how many overflow" | a counter | capacity N − 1; track only the count | [TQ-2 Q7](./quizzes/2026-theory-2#q7) |
| "stack using two queues … push/pop as described … n pushes then n pops" | which side is costly | either version: **O(n²)** total | [TQ-2 Q3](./quizzes/2026-theory-2#q3) |
| loops around stack/queue operations "each O(1)" | read only the loop headers | outer × inner; `s *= 2` is log n | [TQ-2 Q8](./quizzes/2026-theory-2#q8) |
| "8th node from the beginning / end … pointer to …" | constant k; can it step back? | from the start O(1); from the end O(n) unless doubly linked | [TQ-1 Q8](./quizzes/2026-theory-1#q8), [Quiz II Q4–5](./quizzes/2025-theory-2#q4) |
| "SLL with head only vs head + tail … same or different" | does the operation happen **at** the tail? | only "at the tail" operations get faster; anything needing the node *before* the tail stays O(n) | [Quiz II Q6–8](./quizzes/2025-theory-2#q6) |
| "sorted linked list built from n inputs, head only … best and worst" | where each insert lands | best O(n) (all at the head), worst O(n²) | [TQ-1 Q6](./quizzes/2026-theory-1#q6) |
| "incorrect pseudocode for balanced brackets … write a sequence it accepts" | which of 3 checks is missing | missing final check → `((`; missing type check → `(]`; missing empty check → `)` | [Quiz II Q9–10](./quizzes/2025-theory-2#q9) |
| a while inside a for that only pops what was pushed | aggregate count | **O(n)** | [TQ-2 Q1](./quizzes/2026-theory-2#q1) |
| "binary search … minimum and maximum comparisons" | best and worst probes | 1 and ⌈log₂(N + 1)⌉ | [Quiz I Q1](./quizzes/2025-theory-1#q1) |
| "maximum number of operators in the stack" / "maximum stack depth" | run the algorithm, watch the stack column | right-associative `^` stacks up | [TQ-2 Q5, Q9](./quizzes/2026-theory-2#q5) |
| "which output sequence is NOT possible" (stack) | big … small … middle | simulate: push until the number is on top | [TQ-2 Q6](./quizzes/2026-theory-2#q6) |
| "how many distinct binary trees / BSTs" | Catalan | shapes = 1, 2, 5, 14, 42; labelled × n! | [Quiz III Q6–7](./quizzes/2025-theory-3#q6) |

::: tip Practise recognition, not reading
Take any long question from a past quiz and, before solving it, write its skeleton in one line, as in the dashed boxes on the [Theory Quiz 2](./quizzes/2026-theory-2) page. When you can do that in 15 seconds, the time problem goes away.
:::

## The lab-quiz routine {#lab}

1. **First 30 seconds: scan everything.** For each function write two or three words in the margin naming what it does ("insert before key", "second largest", "max-stack push"). The code names are meaningless on purpose (`x`, `y`, `gamma`, `fun`). Note the shared class's field names: `data/next`, or `key/val`.
2. **Fill the free blanks first** (about a third of them): `return` lines (`head`, `newNode`, `root`, `-1`), base cases (`return 0;`, `return 1;`, `return -1;`), and **a line that mirrors the line next to it** (`gamma(h1->next, h2)` → `gamma(h1, h2->next)`; `curr + '1'` → `curr + '0'`; the empty-stack branch already writes `new Node(data, data)`).
3. **Type-check every remaining blank.** Left side and right side must match: `Node*` ↔ `Node*`, `int` ↔ `->data`, index ↔ index. This alone decides most of them: `S = F` (pointers), `T->data > S->data` (ints), `min = left` (an index, not `a[left]`).
4. **Pointer order:** link the new node to the rest first, then move the old pointer (`n->next = t->next; t->next = n;`).
5. **Recursion:** base case, a call on a smaller input (`->next`, `->left`, `n/2`), then combine.
6. **With an option list** (Lab Quiz 2): the type check leaves 3 or 4 of the 9 options; pick from those.
7. **Never leave a blank.** Each blank is its own mark; a likely template line often gets it.

### The templates to write in under a minute each {#templates}

These cover every blank the five lab quizzes so far have asked:

| Template | Where |
|---|---|
| insert at the front / end; insert before a key; delete by value | [Unit 2 §3](./notes/unit-2#core), [Lab I Q1](./quizzes/2025-lab-1#q1) |
| reverse a list; remove duplicates (sorted, unsorted); merge two sorted lists (iterative and recursive) | [Unit 2 §4](./notes/unit-2#function-bank) |
| delete the node at p without the head; second largest | [Lab Quiz 1 (2026)](./quizzes/2026-lab-1) |
| array stack push/pop; linked stack push/pop | [Unit 3 §10](./notes/unit-3#stack-implementations) |
| max-stack push (running max in the node) | [Unit 3 §11](./notes/unit-3#max-stack) |
| circular queue enqueue/dequeue (−1 convention); linked queue enqueue/dequeue | [Unit 4 §3–4](./notes/unit-4#circular) |
| priority-queue ENQUEUE into a sorted list | [Unit 4 §6](./notes/unit-4#priority-queue) |
| countLeaves, height, the three traversals, BFS | [Unit 5 §8](./notes/unit-5#code) |

Your **next lab quiz** will most likely be trees (last year's Lab Quiz II): countLeaves, height, traversals, then BST insert/findMin/LCA and an AVL rotation.

## Drill A: five paragraph questions in five minutes {#drill-a}

New questions in the style of Theory Quiz 2. Start the timer, then answer each one with the routine above.

<QuizTimer :minutes="5" label="Drill A" />

<Drill n="1" tag="Paragraph">

A queue is kept in a circular array of size 10 in which one slot always stays unused, so that a full queue can be told apart from an empty one. Starting from an empty queue, the following are performed in order: 7 enqueues, 3 dequeues, 6 enqueues, 1 dequeue, 4 enqueues. How many enqueue operations overflow?

<FillIn q="Overflows:" answer="4">

Skeleton: capacity 9, count only. 7 → 7; −3 → 4; +6: 5 fit (9), **1** overflows; −1 → 8; +4: 1 fits (9), **3** overflow. Total 4.

</FillIn>

</Drill>

<Drill n="2" tag="Paragraph">

A stack of capacity 100 is stored as an array of integers plus an integer variable top. Alternatively it is stored as a singly linked list whose nodes hold one integer and one next pointer, plus a head pointer. An integer takes 4 bytes and an address takes 8 bytes. What is the minimum number of elements the stack must hold for the linked list to occupy strictly more memory than the array, given that the array is always allocated at full capacity?

<FillIn q="Minimum elements:" answer="34">

Array = 100 × 4 + 4 = 404. List = n(4 + 8) + 8 = 12n + 8. 12n + 8 > 404 → n > 33 → **34**.

</FillIn>

</Drill>

<Drill n="3" tag="S1/S2">

S1: A queue stored as a singly linked list with head and tail pointers, where the front is at the head, supports both enqueue and dequeue in O(1). S2: A doubly linked list with only a head pointer can delete its last node in O(1).

<Mcq :options="['Only S1', 'Only S2', 'Both', 'Neither']" answer="a">

S1: enqueue after the tail, dequeue at the head, both O(1): true. S2: without a tail pointer you must walk to the last node first, O(n), even though `prev` exists: false.

</Mcq>

</Drill>

<Drill n="4" tag="Loop">

`for (int i = 1; i < n; i *= 3) for (int j = 0; j < n; j += i) cout << j;`

<Mcq :options="['O(n log n)', 'O(n)', 'O(log n)', 'O(n²)']" answer="b">

The inner loop runs n/i times for i = 1, 3, 9, …: n(1 + 1/3 + 1/9 + …) ≈ 1.5n. **O(n)**, though the outer loop alone runs log₃ n times.

</Mcq>

</Drill>

<Drill n="5" tag="Paragraph">

10, 20, 30 and 40 are enqueued into an empty queue. Then the following pair of steps is done twice: x = dequeue(); push(x) onto an initially empty stack. Finally the stack is popped once and the popped value is enqueued. What does the queue hold, front to rear?

<FillIn q="Queue, front to rear (spaces):" answer="30 40 20">

Dequeue 10 → push; dequeue 20 → push (stack top 20). The queue is 30 40. Pop 20 and enqueue it: **30 40 20**.

</FillIn>

</Drill>

## Drill B: ten blanks in ten minutes {#drill-b}

<QuizTimer :minutes="10" label="Drill B" />

Shared class: `class Node { public: int data; Node* next; Node(int v) { data = v; next = NULL; } };` (Q3 uses a tree node with `left` and `right`.)

<Drill n="1" tag="Lab: 3 blanks">

Count the nodes of a singly linked list recursively.

```cpp
int count(Node* h) {
    if (h == NULL) return ___(1)___;
    return ___(2)___ + count(___(3)___);
}
```

<FillIn q="Blanks (1), (2), (3) as `a, b, c`:" answer="0, 1, h->next|0,1,h->next">

An empty list has 0 nodes; otherwise this node (1) plus the rest. The recursive call must be on a smaller input: `h->next`.

</FillIn>

</Drill>

<Drill n="2" tag="Lab: 3 blanks">

Insert at the end of a circular linked list kept by its tail pointer.

```cpp
void ins(Node*& tail, int x) {
    Node* n = new Node(x);
    if (tail == NULL) { n->next = ___(1)___; tail = n; return; }
    n->next = ___(2)___;
    tail->next = n;
    tail = ___(3)___;
}
```

<FillIn q="Blanks (1), (2), (3) as `a, b, c`:" answer="n, tail->next, n|n,tail->next,n">

A single node points to itself. The new node points at the head (`tail->next`) before the old tail is redirected to it, and then it becomes the tail.

</FillIn>

</Drill>

<Drill n="3" tag="Lab: 2 blanks">

Sum of all values in a binary tree.

```cpp
int sum(Node* r) {
    if (r == nullptr) return ___(1)___;
    return r->data + sum(___(2)___) + sum(r->right);
}
```

<FillIn q="Blanks (1), (2) as `a, b`:" answer="0, r->left|0,r->left">

Empty tree sums to 0; the right call is given, so the blank mirrors it.

</FillIn>

</Drill>

<Drill n="4" tag="Lab: 2 blanks">

Dequeue from a linked queue with front and rear pointers.

```cpp
int dq() {
    if (front == NULL) return -1;
    Node* t = front;
    int v = ___(1)___;
    front = front->next;
    if (front == NULL) ___(2)___;
    delete t;
    return v;
}
```

<FillIn q="Blanks (1), (2) as `a, b`:" answer="t->data, rear = NULL|t->data,rear=NULL|t->data, rear = nullptr|t->data,rear=nullptr">

`v` is an int: `t->data`, read before `delete`. When the last node leaves, `rear` must be reset or it dangles.

</FillIn>

</Drill>

## Will the mid-semester have the same problem? {#mid-sem}

Less, but it has its own clock. The mid-semester gives **90 minutes for 30 marks: 3 minutes a mark**, three times the quiz rate. The questions are long too (Oct 2025 Q5 and Q6 are specifications with class code), but you have time to read them. The risk moves from **reading** to **writing volume**: a conversion table runs to 20+ rows, and two list functions with edge cases take a page each.

| Question type | Marks | Budget | How to save time |
|---|---|---|---|
| Infix → postfix/prefix table | 5–6 | 12 min | draw the four column headings first; one row per symbol, no prose |
| Recurrence by substitution | 5–6 | 10 min | the four steps in a code-style block; check with n = 4 or 16 |
| Queue / deque / PQ trace | 5 | 10 min | state the convention in line 1; one row per operation |
| Biased search or a tree question | 5 | 10 min | the s, e, mid table / draw the tree before any traversal |
| Linked-list function ×2 | 5–6 each | 15 min each | signature first, then the edge cases as `if` lines, then the main loop |
| Check | | 5 min | `;` after classes, `->data` vs pointers, overflow and underflow messages |

**Order:** the mechanical questions first (conversion, recurrence, trace), because they are certain marks and settle your nerves; then the code. See [How to answer](./how-to-answer) for the layout of each answer.
