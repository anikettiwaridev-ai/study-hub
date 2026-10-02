---
title: Unit 4 · Queues
---

# Unit 4 · Queues

First in, first out. Linear and circular array queues, the linked queue, deques, priority queues, and the scheduling problems queues solve. <span class="hl-legend">Highlighted lines</span> are the likely lab-quiz blanks.

::: info How this unit is examined
- **Mid-semester:** a queue question was on **every one of the six papers**. It is a trace most of the time: a circular queue (Oct 2025 Q3, Mar 2024 Q5), a deque (Sep 2023 Q3, Oct 2022 Q7) or a priority queue (2022 B Q2). The rest are code: a priority queue kept as a sorted linked list (Oct 2025 Q5) and a queue simulation program (2024 B Q2, `candy_crush`).
- **Theory quiz:** overflow counting in a circular queue (Theory Quiz 2, 2026, Q7), queue-vs-stack complexity puzzles.
- **Lab quiz:** circular-queue insert (Lab Quiz I 2025), priority-queue ENQUEUE (Lab Quiz 2, 2026).
:::

## 1. The toolkit: the queue ADT and the conventions {#toolkit}

The slides' ADT: `enqueue(Q, key)` at the **rear**, `dequeue(Q)` from the **front**, `front(Q)`, `isEmpty`, `isFull`, `size`. The axioms say the same thing formally: the first thing enqueued into a new queue is its front, and dequeuing it gives back the empty queue.

The same queue can be stored four ways, and the trace answers differ, so **say which convention you use** in the first line of any trace answer.

| Convention | Start | Empty when | Full when | Cells usable |
|---|---|---|---|---|
| PPT linear | `front = rear = -1` | `front == -1` or `front == rear + 1` | `rear == N - 1` | each cell once only |
| Lab-quiz circular | `front = rear = -1` | `front == -1` | `(rear + 1) % N == front` | all N |
| Circular with a count | `front = 0, rear = -1, count = 0` | `count == 0` | `count == N` | all N |
| **Textbook circular** (Horowitz and Sahni, the course text) | `front = rear = 0` | `front == rear` | `(rear + 1) % N == front` | **N − 1** |

::: tip Which convention for which question
- "A circular queue of length 5 that is **full when 4** elements are stored" (Oct 2025 Q3) is the **textbook** convention: front sits one cell **before** the first element, rear **on** the last, and one cell always stays empty so that full and empty look different.
- Lab-quiz code with `front = -1, rear = -1` is the **lab-quiz** convention.
- Nothing said? Use the textbook one, state it, and trace.
:::

**Why −1?** −1 is not a valid index, so it can only mean "nothing stored". On the first enqueue, the single element is both front and rear, so `front` jumps to 0 along with `rear`. After that only `rear` moves on enqueue and only `front` moves on dequeue.

## 2. The linear queue and its flaw {#linear}

The slides' array queue (`front = rear = -1`): enqueue does `rear++`, dequeue does `front++`. Job scheduling (FCFS) runs on exactly this: jobs J1, J2, … join at the rear and the printer takes them from the front.

::: danger The flaw: "full" with free cells
Freed cells at the front are never reused. With N = 4: E E D E E D D E. The enqueues push rear to 3, the dequeues move front to 3. At the last E, `rear == N - 1`, so it reports **full while holding one element**. That is the drawback a circular queue fixes, the 2-mark answer to Mar 2024 Q5(a).
:::

## 3. The circular queue {#circular}

Once the end of the array is reached, wrap to the beginning: `rear = (rear + 1) % N` and `front = (front + 1) % N`.

### The textbook version (what the papers trace)

::: code-group
<<< @/../code/ds/notes/u4-circular-textbook.cpp#enqueue{2,3} [enqueue]
<<< @/../code/ds/notes/u4-circular-textbook.cpp#dequeue{2,3} [dequeue]
<<< @/../code/ds/notes/u4-circular-textbook.cpp [Oct 2025 Q3, run]
<<< @/../code/ds/notes/u4-circular-textbook.out{txt} [Output]
:::

The full step-by-step table for Oct 2025 Q3 is [on its paper page](../papers/mst-2025-oct#q3).

### The lab-quiz version (front = rear = −1)

Last year's Lab Quiz I Q3 blanked this out. All N cells are usable because "empty" is `front == -1`, not `front == rear`.

<<< @/../code/ds/quiz/la1.cpp#q3{7,9}

The matching dequeue must **reset to −1** when it removes the last element:

```cpp
int dequeue() {
    if (front == -1) return -1;              // underflow
    int v = arr[front];
    if (front == rear) front = rear = -1;    // that was the only element
    else front = (front + 1) % SIZE;
    return v;
}
```

::: danger Forget the reset and an empty queue reports overflow
Without `front = rear = -1`, front ends up one past rear after the last dequeue. The next enqueue sees `(rear + 1) % SIZE == front` and says **overflow on an empty queue**. Last year's paper wrote the full test as `(front == 0 && rear == SIZE-1) || (rear+1) % SIZE == front`. The first half is redundant, but if the blank is there, the answer is `SIZE - 1`.
:::

### The counted version (Practice sheet 3 Q6)

A `count` of stored elements tells empty (`count == 0`) from full (`count == CAP`), so `front == rear` is never ambiguous and every cell is used.

::: code-group
<<< @/../code/ds/notes/u4-circular-count.cpp#enqueue [enqueue]
<<< @/../code/ds/notes/u4-circular-count.cpp#dequeue [dequeue]
<<< @/../code/ds/notes/u4-circular-count.out{txt} [Output]
:::

### Fast tricks for trace questions

- `rear < front` after wrapping is **normal**. Don't "correct" it.
- **No table needed for the final state** (lab-quiz convention), as long as the queue never emptied completely in between and nothing was rejected: rear = (enqueues − 1) % N, front = dequeues % N, count = enqueues − dequeues.
- **Counting overflows** (Theory Quiz 2, 2026, Q7): array of 8 with one slot unused, so capacity 7. Track only the count: 6 enq → 6; 2 deq → 4; 5 enq → 3 fit, **2 overflow** (7); 2 deq → 5; 3 enq → 2 fit, **1 overflow** (7); 1 deq → 6; 3 enq → 1 fits, **2 overflow**. Total **5**.

## 4. The linked-list queue {#linked-queue}

Front = head (delete at the head is O(1)); rear = tail (insert after the tail is O(1)). The other way round, dequeue would need the node before the tail: O(n).

::: code-group
<<< @/../code/ds/notes/u4-ll-queue.cpp#enqueue{3,4} [enqueue]
<<< @/../code/ds/notes/u4-ll-queue.cpp#dequeue{5,6} [dequeue]
<<< @/../code/ds/notes/u4-ll-queue.out{txt} [Output]
:::

::: danger Two edge cases, both on the practice sheet
- Enqueue into an **empty** queue sets **both** pointers.
- Dequeuing the **last** node must set `rear = NULL`. Otherwise rear dangles, the next enqueue writes into freed memory, and front stays NULL.
:::

**Array queue vs linked queue** (Dec 2024 Q3b asks exactly this):

| | Array (circular) | Linked list (head + tail) |
|---|---|---|
| enqueue / dequeue | O(1) | O(1) → **same** |
| access the k-th element | O(1): `arr[(front + k) % N]` | O(k) → **different** |
| capacity | fixed; can overflow; may waste cells | grows until memory runs out |
| extra memory | unused cells reserved | one pointer per element |
| full/empty test | needs a convention (count, −1, or an empty slot) | `front == NULL` |

## 5. Deque: double-ended queue {#deque}

Insert and delete at **both** ends: `insertFront`, `insertRear`, `deleteFront`, `deleteRear`.

**Trace method for papers** (Oct 2022 Q7, Sep 2023 Q3): keep the deque as a written list, front on the left. InsertFront writes on the left, InsertRear on the right; the deletes cross out the leftmost or rightmost.

Oct 2022 Q7: InsertFront(10), InsertFront(20), InsertRear(30), DeleteFront(), InsertRear(40), InsertRear(10), DeleteRear(), InsertRear(15), display():

| Operation | Deque (front → rear) |
|---|---|
| InsertFront(10) | 10 |
| InsertFront(20) | 20 10 |
| InsertRear(30) | 20 10 30 |
| DeleteFront() removes 20 | 10 30 |
| InsertRear(40) | 10 30 40 |
| InsertRear(10) | 10 30 40 10 |
| DeleteRear() removes 10 | 10 30 40 |
| InsertRear(15) | 10 30 40 15 |

display() prints **10 30 40 15**, checked by running a circular deque:

::: code-group
<<< @/../code/ds/notes/u4-deque.cpp#deque{3,8,19} [circular deque]
<<< @/../code/ds/notes/u4-deque.out{txt} [Output]
:::

::: danger The modulo trap
In C++, `(0 - 1) % 5` is **−1**, not 4: `%` keeps the sign. Always write `(front - 1 + SIZE) % SIZE`. The slides' `insert_F` does `front = front - 1` with no wrap at all, which runs off the array at index 0.
:::

**Restricted deques** (slides):

| Type | Insert | Delete | Example | Impossible-output test (all inserted first) |
|---|---|---|---|---|
| Input-restricted | one end only | both ends | browser history | each output must be the smallest or largest of those not yet output |
| Output-restricted | both ends | one end only | | for every k, the numbers 1…k must be adjacent in the output |

**Why a singly linked list is a poor deque** (2022 B Q5): insert/delete at the head, O(1); insert at the tail, O(1) with a tail pointer; but **delete at the tail needs the node before the tail**, which a singly linked list can only find by walking from the head: **O(n)**. A doubly linked list (with `tail->prev`) makes all four operations O(1).

## 6. Priority queue {#priority-queue}

Every element carries a priority, and dequeue removes the **highest-priority** element; elements of equal priority leave in arrival order (FIFO). Read which way round the question defines it: 2022 B says a **larger** value is higher priority; Dec 2023 says a **lower** value is.

### Tracing one (2022 B Q2)

Keep the queue as a list sorted by priority (highest first), and put a new element **after** every element of equal priority. Dequeue removes the first. The full 20-step table is [on the paper page](../papers/mst-2022-b#q2).

### As a sorted singly linked list (Oct 2025 Q5, Lab Quiz 2 2026 Q1)

Keep the list sorted in **descending** priority, so dequeue is just "remove the head", O(1). ENQUEUE does the work, O(n):

1. Empty list → the new node is the list.
2. New priority **greater than the head's** → new head.
3. Otherwise walk while the **next** node's priority is **≥** the new one, then link the new node after that node.

::: code-group
<<< @/../code/ds/papers/o25-q5.cpp#answer{7,13,15,16} [ENQUEUE (Oct 2025 Q5)]
<<< @/../code/ds/papers/o25-q5.out{txt} [Output]
<<< @/../code/ds/quiz/lt2.cpp#q1 [Lab Quiz 2 (2026) version]
:::

::: danger `>=` keeps equal priorities first come, first served
Walking past nodes with priority **≥ p** puts the new node behind the earlier equal ones. With `>` it would jump ahead of them, which breaks FIFO among equals. And `if (p > head->priority)` uses strict `>` for the same reason: an equal-priority newcomer must not become the head.
:::

A heap-based priority queue (O(log n) both ways) is Unit 8, end-semester only.

## 7. Queue and stack problems {#queue-problems}

::: code-group
<<< @/../code/ds/notes/u4-queue-problems.cpp#reverseQueue{3,4,5} [reverse a queue (recursion)]
<<< @/../code/ds/notes/u4-queue-problems.cpp#reverseFirstK{5} [reverse the first k]
<<< @/../code/ds/notes/u4-queue-problems.cpp#twoStackQueue{4} [queue from two stacks]
<<< @/../code/ds/notes/u4-queue-problems.out{txt} [Output]
:::

- **reverseFirstK** rotates `size − k` times: after step 2 the reversed block is at the back, and the others must cycle behind it. Rotating k times moves the wrong block.
- **Queue from two stacks:** transfer only when `s2` is empty. Each element moves at most once, so dequeue is amortised O(1), O(n) at worst.
- **Reverse a queue using only another queue** (2024 B Q4c): with no stack and no recursion, you must rotate the queue to bring its last element to the front each time: (n−1) + (n−2) + … = **O(n²)**. [The paper page](../papers/mst-2024-b#q4) counts the operations by running it.

::: info A paragraph question, decoded (Theory Quiz 2, 2026, Q8)
"A stack and a queue support push, pop, enqueue and dequeue in O(1)… `for (s = 1; s < n; s *= 2) { for (i = 0; i < n; i++) push(dequeue()); while (!isEmpty()) enqueue(pop()); }`". The outer loop runs log n times (s doubles); each pass moves n elements queue → stack and n back. **O(n log n)**. Read the loop headers; the story around them is decoration.
:::

**Trace with `enqueue(dequeue())`** (Mar 2024 Q5c): each such statement moves the front element to the rear. Write the queue as a list and move the first item to the end. The full answer is [on the paper page](../papers/mst-2024-mar#q5b).

## 8. Scheduling: FCFS, Round Robin, SJF {#scheduling}

- **FCFS** (first come, first served): one queue; run each job to completion in arrival order. The slides' printer example.
- **Round Robin**: each turn runs `min(quantum, remaining)`; an unfinished job goes to the **back** of the queue. Jobs that arrive during a turn join **before** the preempted job re-enters.
- **SJF** (shortest job first): order by processing time, ties by arrival order (Dec 2024 Q3a).

Round Robin with arrivals (Practice sheet 3 Q10): P1 (burst 5, arrives 0), P2 (3, 1), P3 (1, 2), P4 (4, 3), quantum 2.

::: code-group
<<< @/../code/ds/notes/u4-round-robin.cpp#rr{7,12} [Round Robin loop]
<<< @/../code/ds/notes/u4-round-robin.out{txt} [Output]
:::

::: tip Two formulas, every scheduling question
**Turnaround = completion − arrival. Waiting = turnaround − burst.** When everything arrives at 0, waiting = completion − burst, and there is no need to add up the gaps. Number of slices in Round Robin = Σ ⌈burst / quantum⌉.
:::

::: danger Round Robin is not automatically better
It buys fairness and quick first response, not a lower average waiting time. With bursts 7, 4, 2 all at time 0 and quantum 3, FCFS averages 6 and Round Robin 6.67. An MCQ saying "RR always reduces average waiting time" is false.
:::

**Simulating with a queue** (2024 B Q2, `candy_crush`): each child takes `min(5, wanted, left)`; a child who still wants more rejoins at the back. Stop when the queue empties or the machine does. [Full program on the paper page](../papers/mst-2024-b#q2).

## 9. Ring buffer (overwrite when full) {#ring-buffer}

Practice sheet 3 Q8: always keep the last K values; a new value overwrites the oldest when full.

::: code-group
<<< @/../code/ds/notes/u4-ring-buffer.cpp#add{3,4} [add]
<<< @/../code/ds/notes/u4-ring-buffer.cpp [Whole program]
<<< @/../code/ds/notes/u4-ring-buffer.out{txt} [Output]
:::

When full, subtract `buf[front]` **before** overwriting it, and advance both front and rear. `(double) sum / count`: cast before dividing; `(double)(sum / count)` has already truncated.

## Traps and the 5-minute checklist {#traps}

| # | Trap | Correct version |
|---|---|---|
| 1 | tracing without stating the convention | first line of the answer: which convention, and how many cells are usable |
| 2 | "array of 5" holds 5 in the textbook circular queue | it holds **4**: one cell stays empty |
| 3 | no reset when the last element is dequeued | circular: `front = rear = -1`; linked: `rear = NULL` |
| 4 | `(front - 1) % SIZE` | `(front - 1 + SIZE) % SIZE` |
| 5 | "correcting" rear < front | normal after wrap-around |
| 6 | linear queue reports full while nearly empty | `rear == N-1` checks the position, not the count |
| 7 | priority ties served out of order | walk past `>=`; new head only on strict `>` |
| 8 | RR slice always = quantum | `min(quantum, remaining)` |
| 9 | `int x = q.pop();` | `pop()` returns void: `q.front()` first |
| 10 | singly linked deque "all O(1)" | delete at the tail is O(n) |

**The checklist:** state the convention · count capacity · empty, one element, full, wrap-around · reset on the last dequeue · priority direction and ties.

## Quick check {#quick-check}

<Drill n="1" tag="Trace">

<FillIn q="Circular queue, SIZE = 5, lab convention (`front = rear = -1`, `rear = (rear + 1) % SIZE`). Enqueue 10, 20, 30, 40; dequeue three times; enqueue 50, 60, 70. Final front and rear? Answer as `front, rear`." answer="3, 1|3,1|front = 3, rear = 1|front=3, rear=1">

After 4 enqueues: front 0, rear 3. Three dequeues: front 3. Enqueue 50 → rear 4; 60 → (4+1) % 5 = 0; 70 → 1. The queue holds 40 50 60 70, not full. rear &lt; front is normal.

</FillIn>

</Drill>

<Drill n="2" tag="Trace">

Linear array queue, N = 4, PPT convention. Operations: E, E, D, E, E, D, D, E. Does the last enqueue succeed?

<Mcq :options="['Yes, the queue has room', 'No: it reports full with 1 element inside', 'No: it reports full with 4 elements inside', 'Underflow']" answer="b">

Rear reaches 3 = N − 1, front reaches 3, so size = rear + 1 − front = 1, yet `rear == N-1` reports full. The wasted-space flaw the circular queue fixes.

</Mcq>

</Drill>

<Drill n="3" tag="S1/S2">

A queue is a singly linked list. S1: with only a head pointer and front = head, enqueue is O(1). S2: with head and tail pointers, front = tail and rear = head, dequeue is O(1).

<Mcq :options="['Only S1', 'Only S2', 'Both', 'Neither']" answer="d">

S1: enqueue happens at the end; without a tail pointer that is an O(n) walk. S2: dequeuing at the tail deletes the last node, which needs the node before it: O(n) even with a tail pointer. The right design is front = head, rear = tail.

</Mcq>

</Drill>

<Drill n="4" tag="Same/different">

<FillIn q="Circular-array queue vs linked queue (head + tail): access the k-th element from the front. Same or different?" answer="different">

Array: `arr[(front + k - 1) % SIZE]`, O(1). Linked: walk k nodes, O(k). Different. For enqueue and dequeue the answer would be "same".

</FillIn>

</Drill>

<Drill n="5" tag="Deque">

1, 2, 3, 4 go into an input-restricted deque (all at the rear), then only deletions happen, from either end. Which output is impossible?

<Mcq :options="['4 1 3 2', '1 4 2 3', '4 3 1 2', '1 3 2 4']" answer="d">

The deque is [1 2 3 4]; each deletion takes an end. After 1 is removed, the ends are 2 and 4, so 3 is in the middle and cannot come out next.

</Mcq>

</Drill>

<Drill n="6" tag="Scheduling">

<FillIn q="Round Robin, quantum 2, all arrive at 0: P1 burst 6, P2 burst 3, P3 burst 1. Average waiting time? (Two decimal places.)" answer="4.33|4.33 units|13/3">

Gantt: 0–2 P1, 2–4 P2, 4–5 P3 (done 5), 5–7 P1, 7–8 P2 (done 8), 8–10 P1 (done 10). Waiting = completion − burst: 4, 5, 4. Average 13/3 = 4.33. P3 runs 1, not 2.

</FillIn>

</Drill>

<Drill n="7" tag="Lab blank">

<FillIn q="Linked queue dequeue: `Node* t = front; int v = t->data; front = front->next; if (front == NULL) ____; delete t;`" answer="rear = NULL|rear=NULL|rear = nullptr">

If the only node was removed, rear still points at it and it is about to be freed. Without this the next enqueue writes into freed memory.

</FillIn>

</Drill>

<Drill n="8" tag="Priority queue">

<FillIn q="Sorted-list ENQUEUE, descending priority, FIFO among equals: `while (t->next != NULL && t->next->priority ____ p) t = t->next;`" answer=">=">

Walk past every node of priority ≥ p, so the newcomer goes behind earlier equal ones. `>` would let it jump ahead of them.

</FillIn>

</Drill>
