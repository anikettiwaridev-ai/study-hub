---
title: Theory Quiz 2, 2026
---

# Theory Quiz 2, 2026

<PaperHeader :rows="[
  ['Course', 'Data Structures, CTN301 / DSN301 / AIN301, batch 26271'],
  ['Format', '9 questions in 10 minutes: Q1–Q8 one mark each, Q9 two marks'],
  ['Covers', 'Unit 3 (stacks) and Unit 4 (queues)'],
  ['Answers', 'From the official key uploaded on 2 October 2026, each checked by simulation'],
]" />

<QuizTimer :minutes="10" label="Theory Quiz 2" />

::: info Why this one hurt
Five of the nine questions (Q2, Q3, Q4, Q7, Q8) are paragraphs of 50–90 words. Reading each one carefully takes about as long as the quiz allows per question, before any thinking starts. But every paragraph here reduces to a one-line skeleton (in the dashed box under each question: open it after you have tried) and a known recipe. The way to beat this quiz is to recognise the skeleton in 15 seconds, not to read faster. Try the quiz with the timer first, then read the skeletons, then redo it.
:::

<Q id="QT2.Q1">

What is the time complexity of the following code snippet in terms of 'n'? (A[] has n elements, and S[] is an integer array of size n used as a stack.)

```cpp
int top = -1;
for (int i = 0; i < n; i++) {
    while(top != -1 && A[S[top]] <= A[i])
        top--;
    S[++top] = i;
}
```

<details class="skeleton"><summary>Skeleton: open it after you try</summary>

Each index is pushed once (`S[++top] = i`) and popped at most once (`top--`). Total work ≤ 2n.

</details>

<FillIn q="Answer (Big-O):" answer="O(n)">

It looks like O(n²) (a while inside a for), but the while loop can pop only what was pushed, and each of the n indices is pushed exactly once. All the `top--` steps over the whole run add up to at most n. **O(n)**: the monotonic stack ([Unit 3](../notes/unit-3#next-greater)).

</FillIn>

</Q>

<Q id="QT2.Q2">

Which among the following statement(s) is/are true?

S1: In an array-based stack that grows by allocating a new array with c extra cells (c is a fixed constant) and copying all existing elements whenever it overflows, the total time complexity of performing n push operations on an initially empty stack is O(n²).
S2: A queue implemented using a singly linked list with only a head pointer can perform both enqueue (at the tail) and dequeue (at the head) in O(1) time.

<details class="skeleton"><summary>Skeleton: open it after you try</summary>

S1 = "grow by a constant" → copies c + 2c + 3c + … → O(n²)? S2 = "enqueue at the tail with no tail pointer" → O(1)?

</details>

<Mcq :options="['S1 is correct and S2 is not correct', 'S1 is not correct and S2 is correct', 'Both S1 and S2 are correct', 'Both S1 and S2 are not correct']" answer="a">

**S1 true:** the array overflows every c pushes, and each overflow copies everything so far: c + 2c + 3c + … up to n ≈ n²/(2c) copies, O(n²). (Doubling instead of adding c would make it O(n).)
**S2 false:** with only a head pointer, reaching the tail to enqueue is an O(n) walk.

</Mcq>

</Q>

<Q id="QT2.Q3">

A stack is implemented using two queues, q1 and q2. push(x) enqueues x into q1. pop() dequeues all elements except the last from q1 and enqueues them into q2. It then dequeues and returns the last element of q1, and finally swaps the names q1 and q2. What is the total time complexity of performing 'n' push operations followed by 'n' pop operations?

<details class="skeleton"><summary>Skeleton: open it after you try</summary>

Stack from two queues, **pop-costly** version. n pushes O(1) each; pop number i moves (remaining − 1) elements.

</details>

<FillIn q="Answer (Big-O):" answer="O(n^2)|O(n²)|O(n2)">

Pushes: n × O(1) = O(n). Pops: the first moves n − 1 elements, the next n − 2, …: about n²/2. Total **O(n²)**. The push-costly version gives the same total for this sequence ([Unit 3](../notes/unit-3#stack-from-queues)).

</FillIn>

</Q>

<Q id="QT2.Q4">

A stack of maximum capacity 200 is to be stored using an array of integers, plus one integer variable top. Alternatively, it can be stored as a singly linked list where each node has one integer and one next pointer, plus a head pointer. If every integer requires 2 bytes and an address requires 4 bytes, what is the minimum number of elements the stack must hold so that the linked list representation occupies strictly more memory than the array representation? (The array is allocated with full capacity regardless of occupancy.)

<details class="skeleton"><summary>Skeleton: open it after you try</summary>

Array = 200 × 2 + 2 = 402 (fixed). List = n × (2 + 4) + 4 = 6n + 4. Solve 6n + 4 > 402.

</details>

<FillIn q="Answer (number of elements):" answer="67">

6n + 4 > 402 → 6n > 398 → n > 66.33, so the smallest whole n is **67**. The recipe for every question like this is in [Unit 1](../notes/unit-1#memory).

</FillIn>

</Q>

<Q id="QT2.Q5">

Convert the below infix expression to postfix using a stack. **A + B ∗ C ^ D ^ E − F / G**. What is the maximum number of operators present in the stack at any instant during the conversion?

<details class="skeleton"><summary>Skeleton: open it after you try</summary>

Run the operator-stack algorithm and watch the height. `^` is right-associative, so the second `^` does not pop the first.

</details>

<Mcq :options="['3', '4', '5', '6']" answer="b">

After `+`, `*`, `^`, `^` the stack is `+ * ^ ^` (4): `*` doesn't pop `+` (higher), `^` doesn't pop `*`, and the second `^` doesn't pop the first. Then `-` pops all four. Postfix: `ABCDE^^*+FG/-`.

</Mcq>

</Q>

<Q id="QT2.Q6">

The elements 1, 2, 3, 4, 5 are pushed onto an initially empty stack in this order, with pops allowed at any time. Which of the following output sequences is NOT possible?

<Mcq :options="['2 1 5 4 3', '3 4 2 1 5', '4 5 3 1 2', '1 3 2 5 4']" answer="c">

For 4 5 3 1 2: push 1–4, pop 4; push 5, pop 5; pop 3; now 1 and 2 remain with **2 on top**, so 1 cannot come out before 2. The rule: after a number is popped, the smaller ones still waiting must come out in decreasing order ([Unit 3](../notes/unit-3#pop-sequences)).

</Mcq>

</Q>

<Q id="QT2.Q7">

A circular queue is implemented using an array of size 8 (indices 0 to 7). One slot is kept unused to distinguish a full queue from an empty one. The following operations are performed in order: 6 enqueues, 2 dequeues, 5 enqueues, 2 dequeues, 3 enqueues, 1 dequeue, 3 enqueues. How many enqueue operations resulted in queue overflow?

<details class="skeleton"><summary>Skeleton: open it after you try</summary>

Capacity = 8 − 1 = **7**. Track only the count; an enqueue at count 7 overflows.

</details>

<FillIn q="Answer (number of overflows):" answer="5">

| Operations | Count after | Overflows |
|---|---|---|
| 6 enqueues | 6 | 0 |
| 2 dequeues | 4 | |
| 5 enqueues | 7 | 2 (only 3 fit) |
| 2 dequeues | 5 | |
| 3 enqueues | 7 | 1 (2 fit) |
| 1 dequeue | 6 | |
| 3 enqueues | 7 | 2 (1 fits) |

Total **5**. You never need front and rear for this: the count is enough.

</FillIn>

</Q>

<Q id="QT2.Q8">

A stack and a queue support the operations push(x), pop(), isEmpty(), enqueue(x) and dequeue(), each taking O(1) time. pop() and dequeue() return the removed element. The stack is initially empty, and the queue initially contains n elements. Consider the following function:

```cpp
void f(int n) {
    for (int s = 1; s < n; s *= 2) {
        for (int i = 0; i < n; i++)
            push(dequeue());
        while (!isEmpty())
            enqueue(pop());
    }
}
```

What is the time complexity of the function f?

<details class="skeleton"><summary>Skeleton: open it after you try</summary>

Read only the loop headers. Outer: `s *= 2` → log n passes. Inside: n moves to the stack + n moves back.

</details>

<FillIn q="Answer (Big-O):" answer="O(n log n)|O(nlogn)|O(n logn)">

log n passes × 2n O(1) operations = **O(n log n)**. (Each pass also reverses the queue; that doesn't affect the cost.)

</FillIn>

</Q>

<Q id="QT2.Q9">

Evaluate the following postfix expression: **5 3 2 ∗ + 8 4 / − 2 3 ^ ∗**. What is the final result and the maximum stack depth reached during evaluation, respectively?

<FillIn q="Answer as `result, depth`:" answer="72, 3|72,3|72 3">

| Token | Stack |
|---|---|
| 5 3 2 | 5 3 2 (depth 3) |
| ∗ | 5 6 |
| + | 11 |
| 8 4 | 11 8 4 (depth 3) |
| / | 11 2 |
| − | 9 |
| 2 3 | 9 2 3 (depth 3) |
| ^ | 9 8 |
| ∗ | 72 |

**72, and a maximum depth of 3.** Two marks: one for each value.

</FillIn>

</Q>

## The paragraph decoder for this quiz {#decoder}

| Q | Words | The skeleton | The recipe | Seconds once you know it |
|---|---|---|---|---|
| Q2 | ~70 | constant growth; SLL enqueue without a tail | +c growth is O(n²); no tail pointer, O(n) enqueue | 15 |
| Q3 | ~50 | pop-costly two-queue stack, n push + n pop | Σ(n − i) = O(n²) | 10 |
| Q4 | ~80 | array (fixed) vs list (per node) memory | write both formulas, solve the inequality | 40 |
| Q7 | ~55 | circular queue, one slot unused | capacity N − 1; count only | 40 |
| Q8 | ~60 | loops around O(1) operations | outer log n × inner n | 15 |

Every one of them, and the other paragraph types from the last two years, is in the [quiz-clock page](../quiz-clock#decoder).
