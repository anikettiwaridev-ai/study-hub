---
title: Theory Quiz II, 2025
---

# Theory Quiz II, 2025

<PaperHeader :rows="[
  ['Course', 'Data Structures, CSN3001 / AIN3001 / DSN3001, batch 25261 (last year)'],
  ['Format', '10 questions, 1 mark each, 10 minutes'],
  ['Covers', 'Postfix, stacks, linked-list complexity, a buggy bracket checker'],
]" />

<QuizTimer :minutes="10" label="Theory Quiz II" />

<Q id="QA2.Q1">

The result of evaluating the following postfix expression, where elements are separated by ','. **12, 7, 3, −, /, 2, 1, 6, +, ∗, +**

<Mcq :options="['19', '17', '18', '15']" answer="b">

7 − 3 = 4; 12 / 4 = 3; 1 + 6 = 7; 2 × 7 = 14; 3 + 14 = **17**.

</Mcq>

</Q>

<Q id="QA2.Q2">

What is the corresponding postfix for given infix? **((A + B) ∗ D) ^ (E − F)**

<Mcq :options="['AB+D*EF-^', 'AB+D*E-F*^', '+*A^BD-EF', 'AB+DE*-F*']" answer="a">

(A + B) → `AB+`; × D → `AB+D*`; (E − F) → `EF-`; the `^` joins them last: `AB+D*EF-^`. (c) is not even postfix (it starts with an operator).

</Mcq>

</Q>

<Q id="QA2.Q3">

Which of the following statement(s) is/are TRUE about PUSH and POP operations in a stack?
S1: Can be implemented in O(1) using arrays.  S2: Can be implemented in O(1) using linked lists.

<Mcq :options="['Only S1', 'Only S2', 'Both S1 and S2', 'Neither S1 nor S2']" answer="c">

Array: `arr[++top]` / `arr[top--]`. Linked list: insert and delete at the head. Both O(1).

</Mcq>

</Q>

<Q id="QA2.Q4">

What are the time complexities of finding 8th element from beginning and 8th element from end in a singly linked list with tail pointer of length n, where n > 8?

<Mcq :options="['O(1), O(1)', 'O(n), O(n)', 'O(1), O(n)', 'O(n), O(1)']" answer="c">

8 steps from the head is constant. From the end you cannot step back from the tail; walk n − 8 nodes from the head: O(n).

</Mcq>

</Q>

<Q id="QA2.Q5">

What are the time complexities of finding 8th element from beginning and 8th element from end in a doubly linked list with tail pointer of length n, where n > 8?

<Mcq :options="['O(1), O(1)', 'O(n), O(n)', 'O(1), O(n)', 'O(n), O(1)']" answer="a">

With `prev` pointers you can walk 8 steps back from the tail: constant both ways.

</Mcq>

</Q>

::: info Q6–Q8: same or different?
"Consider you have two options: a Singly Linked List (SLL) with only a head pointer and a SLL with both head & tail pointers. Compare the time complexity of the most efficient algorithms performing the following operations using the two options. If both options have the same time complexity, write answer as 'same', write 'different' otherwise."
:::

<Q id="QA2.Q6">

Inserting node at the 2nd last position, if any.

<FillIn q="same or different?" answer="same">

Inserting before the last node needs the node before it (the 2nd-last's predecessor), found only by walking from the head in both: O(n) and O(n).

</FillIn>

</Q>

<Q id="QA2.Q7">

Deleting the 2nd last node, if any.

<FillIn q="same or different?" answer="same">

Needs the 3rd-last node: a walk in both. A tail pointer gives the last node, which doesn't help.

</FillIn>

</Q>

<Q id="QA2.Q8">

Swapping the values of first and last node.

<FillIn q="same or different?" answer="different">

Head only: walk to the last node, O(n). Head + tail: both at hand, O(1).

</FillIn>

</Q>

::: info Q9–Q10: the faulty bracket checker
"Following is an incorrect pseudocode for the algorithm which is supposed to determine whether a sequence of simple parentheses is balanced:"

```text
declare a character stack
while (more input is available)
{
    read a character
    if (the character is a '(')
        push it on the stack
    else if (the character is a ')' and the stack is not empty)
        pop a character from the stack
    else
        print "unbalanced" and exit
}
print "balanced"
```

**The bug:** it never checks whether the stack is empty at the end, so leftover `(` go unnoticed.
:::

<Q id="QA2.Q9">

Write an unbalanced sequence of brackets (length less than 5) that the above pseudocode will consider balanced.

<FillIn q="A sequence:" answer="(()|(|((|(((|((()|()(|(()(|()((">

Any sequence with unmatched `(` left at the end: `(`, `((`, `(()`… Every `)` finds something to pop, so it reaches "balanced".

</FillIn>

</Q>

<Q id="QA2.Q10">

Write an unbalanced sequence of brackets (length less than 5) that the above pseudocode will also consider unbalanced.

<FillIn q="A sequence:" answer="())|)|)(|())(|)()|())(">

Any sequence where a `)` meets an empty stack: `)`, `)(`, `())`. That check exists, so these are correctly rejected. This year's version of the question will have a different missing check: go through the three cases (empty stack on a closer, wrong type, leftovers) every time ([Unit 3](../notes/unit-3#brackets)).

</FillIn>

</Q>
