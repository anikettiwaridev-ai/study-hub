---
title: Theory Quiz 1, 2026
---

# Theory Quiz 1, 2026

<PaperHeader :rows="[
  ['Course', 'Data Structures, CTN301 / DSN301 / AIN301, batch 26271'],
  ['Format', '10 questions, 1 mark each, 10 minutes'],
  ['Covers', 'Unit 1 (complexity, recurrences, dynamic arrays) and Unit 2 (linked lists)'],
  ['Answers', 'From the official key uploaded on 2 October 2026, each checked'],
]" />

<QuizTimer :minutes="10" label="Theory Quiz 1" />

::: tip Do it the way the clock wants
Answer the six short ones first (Q1, Q3, Q4, Q5, Q7, Q10), then the long ones (Q2, Q6, Q8, Q9). For a long question, read its **last sentence first**: that is the question; the paragraph before it is the data. The [quiz-clock page](../quiz-clock) explains the method.
:::

<Q id="QT1.Q1">

What is the time complexity of the following code snippet in terms of 'N'?

```cpp
int i = N;
while (i > 0) {
    cout << i;
    i = i/2;
}
```

<FillIn q="Answer (Big-O):" answer="O(log n)|O(logn)|O(log N)|O(logN)|O(log2 n)|log n">

i goes N, N/2, N/4, …, 1, 0: about log₂ N + 1 iterations. **O(log N).**

</FillIn>

</Q>

<Q id="QT1.Q2">

Which among the following statement(s) is/are true regarding manually resizing a dynamically allocated array in C++?

S1: To increase the size of a dynamically allocated array, a new larger memory block must be allocated, and the existing elements must be copied or moved to the new memory block, resulting in time overhead.
S2: After the elements are copied or moved to the new memory block, the old memory block should be explicitly deallocated using `delete[]` to avoid memory overhead.

<details class="skeleton"><summary>Skeleton: open it after you try</summary>

Resizing = allocate bigger, copy (S1: time cost), free the old block with `delete[]` (S2: otherwise a leak). Both describe what you must do.

</details>

<Mcq :options="['S1 is correct and S2 is not correct', 'S1 is not correct and S2 is correct', 'Both S1 and S2 are correct', 'Both S1 and S2 are not correct']" answer="c">

C++ arrays cannot grow in place: allocate, copy, then `delete[]` the old block, or it leaks. Both statements are true. (Last year's version had a second statement that was wrong. Read every word of S2.)

</Mcq>

</Q>

<Q id="QT1.Q3">

What is the time complexity of the following code snippet?

```cpp
for (int i=n; i>1; i/=2)
    for (int j=1; j<=i; j*=2)
        cout << j;
```

<FillIn q="Answer (Big-O):" answer="O((log n)^2)|O(log^2 n)|O((logn)^2)|O(log n)^2|O(log²n)|O((log n)²)|O(log(n)^2)|O((log(n))^2)">

The outer loop runs log n times; for each i the inner loop doubles j up to i: about log i + 1 times. Total ≈ log n + log(n/2) + … ≈ (log n)²/2. **O((log n)²).** (For n = 1024 the inner statement runs 65 times; (log₂ n)² = 100.)

</FillIn>

</Q>

<Q id="QT1.Q4">

If an algorithm has O(n²) time complexity and runtime 'r'. If we double the input size, how does runtime approximately change?

<Mcq :options="['Runtime also doubles', 'Runtime remains same', 'Runtime increase 4 times', 'Runtime reduces by half']" answer="c">

(2n)² = 4n²: four times. Last year's Quiz I asked the mirror image: halving the input gives one quarter.

</Mcq>

</Q>

<Q id="QT1.Q5">

What would be the time complexity of finding the middle node in a linked list having 'n' nodes?

<FillIn q="Answer (Big-O):" answer="O(n)">

You must walk to it: either count then walk n/2 nodes, or one pass with slow and fast pointers. Either way **O(n)**.

</FillIn>

</Q>

<Q id="QT1.Q6">

What are the best-case and worst-case time complexities of creating a sorted singly linked list of 'n' elements, when the input elements are read one by one and only a pointer to the first node is maintained?

<details class="skeleton"><summary>Skeleton: open it after you try</summary>

N sorted inserts, head pointer only. Best: each insert at the head, O(1). Worst: each insert at the end, O(k).

</details>

<Mcq :options="['O(n), O(n)', 'O(n), O(n²)', 'O(n²), O(n)', 'O(n²), O(n²)']" answer="b">

Best case: the input arrives in decreasing order, so every element goes at the front: n × O(1) = O(n). Worst case: increasing order, so every element walks to the end: 1 + 2 + … + n = O(n²).

</Mcq>

</Q>

<Q id="QT1.Q7">

Solve: T(n) = T(n − 1) + n; T(1) = 1

<Mcq :options="['O(n log n)', 'O(n)', 'O(log n)', 'O(n²)']" answer="d">

T(n) = 1 + 2 + … + n = n(n + 1)/2. The same recurrence was 3 marks in [Mar 2024 Q1a](../papers/mst-2024-mar#q1a).

</Mcq>

</Q>

<Q id="QT1.Q8">

What are the time complexities of finding the 8th node from the beginning and the 8th node from the end, respectively, in a circular linked list containing 'n' nodes (n > 8), if only a pointer to the tail node is maintained?

<details class="skeleton"><summary>Skeleton: open it after you try</summary>

Circular + tail pointer → the head is `tail->next`. "8th" is a constant.

</details>

<Mcq :options="['O(1), O(1)', 'O(1), O(n)', 'O(n), O(1)', 'O(n), O(n)']" answer="b">

From the beginning: `tail->next` is the head, then 7 steps: O(1). From the end: a singly linked circle cannot step backwards, so you walk n − 8 nodes forward from the head: O(n).

</Mcq>

</Q>

<Q id="QT1.Q9">

Consider the data of co-authorship among 10⁴ researchers that need to be stored in a program. Two researchers are co-authors if they have published at least one research article together. We need to store the ID of the co-author and the number of articles jointly published for each pair of co-authors. If every integer requires 2 bytes and an address requires 4 bytes of memory, compute the memory required to store the information in an array-of-linked-lists representation for 500 valid co-authorship records.

<details class="skeleton"><summary>Skeleton: open it after you try</summary>

Array of lists = (number of lists × pointer) + (number of records × node size). Node = co-author ID + count + next.

</details>

<FillIn q="Answer in bytes:" answer="44000|44,000|44000 bytes|44,000 bytes">

Array: one list head per researcher, 10,000 × 4 = 40,000 bytes. Nodes: ID (2) + count (2) + next (4) = 8 bytes, × 500 records = 4,000. **Total 44,000 bytes** (the official key: (2 + 2 + 4) × 500 + 10,000 × 4).

The key counts each record once. If every co-authorship were stored in both researchers' lists there would be 1,000 nodes and 48,000 bytes; give 44,000 and mention the assumption if you have time. More of this type in [Unit 1](../notes/unit-1#memory).

</FillIn>

</Q>

<Q id="QT1.Q10">

Consider two polynomial expressions E1 and E2 with N1 and N2 terms, respectively, are represented as linked lists. What is the time complexity of the operation E1 − E2? Assume that the terms in both polynomial expressions are stored in descending order of their exponents.

<FillIn q="Answer (Big-O):" answer="O(N1 + N2)|O(N1+N2)|O(n1+n2)|O(n1 + n2)|O(m+n)|O(m + n)">

Subtraction is addition with E2's coefficients negated: one merge pass over both sorted lists. Each term is visited once: **O(N1 + N2)**.

</FillIn>

</Q>
