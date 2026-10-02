---
title: Practice sheet 3 · Stacks and queues
---

# Practice sheet 3 · Stacks and queues

<PaperHeader :rows="[
  ['Topics', 'Stacks and their applications (Q1–Q5), queues and their applications (Q6–Q10)'],
  ['Exam weight', 'High: Q4–Q5 are on every mid-semester paper; Q6 is last year’s circular-queue question'],
]" />

<Q id="P3.Q1">

**Stack using an array.** A `Stack` class with a private array, a capacity and a top index: `push` (print "overflow" when full), `pop` (print "underflow" when empty), `peek`, `isEmpty`, `isFull`. Capacity 5: push 6 values (the 6th overflows), pop 3 printing each, then peek and print what remains.

::::: details Solution

::: code-group
<<< @/../code/ds/notes/u3-array-stack.cpp [Program]
<<< @/../code/ds/notes/u3-array-stack.out{txt} [Output]
:::

:::::

</Q>

<Q id="P3.Q2">

**Stack using a linked list.** The same interface with the head as the top. No overflow; `pop()` or `peek()` on an empty stack throws a custom `StackUnderflowException` derived from `std::exception`; catch it in `main()`.

::::: details Solution

::: code-group
<<< @/../code/ds/notes/u3-ll-stack.cpp [Program]
<<< @/../code/ds/notes/u3-ll-stack.out{txt} [Output]
:::

Deriving from `std::exception` and overriding `what()` lets one `catch (const exception& e)` handle it like any library exception.

:::::

</Q>

<Q id="P3.Q3">

**Balanced brackets.** `bool isBalanced(string expr)` with a stack, for (), {} and [] together. Test: balanced, an unmatched closer, an unmatched opener, a wrong closing type, and an empty string.

::::: details Solution

::: code-group
<<< @/../code/ds/notes/u3-balanced.cpp [Program]
<<< @/../code/ds/notes/u3-balanced.out{txt} [Output]
:::

The three ways to be unbalanced, and the line that catches each, are in [Unit 3](../notes/unit-3#brackets). An empty string is balanced.

:::::

</Q>

<Q id="P3.Q4">

**Infix to postfix.** `string infixToPostfix(string expr)` for single-letter operands and `+ - * / ^`, with standard precedence and right-to-left associativity for `^`. Test `a+b*c-d`, `(a+b)*(c-d)` and `a+b*c^d^e`.

::::: details Solution

::: code-group
<<< @/../code/ds/notes/u3-infix-postfix.cpp [Program]
<<< @/../code/ds/notes/u3-infix-postfix.out{txt} [Output]
:::

The one condition that encodes right-associativity: on equal precedence, pop unless the incoming operator is `^`. So `a+b*c^d^e` gives `abcde^^*+`.

:::::

</Q>

<Q id="P3.Q5">

**Challenging: postfix evaluation and infix to prefix.** Part 1: `int evaluatePostfix(string expr)` for single-digit operands; test "53+82-*" and explain the stack states at each step. Part 2: `string infixToPrefix(string expr)` (reverse, swap brackets, modified postfix pass, reverse); test `(a-b/c)*(a/k-l)` and verify by evaluating with sample values.

::::: details Solution

**Part 1.** `53+82-*`:

| Token | Stack (bottom → top) |
|---|---|
| 5, 3 | 5 3 |
| + | 8 |
| 8, 2 | 8 8 2 |
| − | 8 6 |
| ∗ | **48** |

::: code-group
<<< @/../code/ds/notes/u3-postfix-eval.cpp [Part 1]
<<< @/../code/ds/notes/u3-postfix-eval.out{txt} [Part 1 output]
<<< @/../code/ds/notes/u3-infix-prefix.cpp [Part 2]
<<< @/../code/ds/notes/u3-infix-prefix.out{txt} [Part 2 output]
:::

**Part 2.** `(a-b/c)*(a/k-l)` → **`*-a/bc-/akl`**. Check with a = 8, b = 6, c = 2, k = 4, l = 1. Infix: (8 − 6/2) × (8/4 − 1) = 5 × 1 = 5. Prefix, from the right: `/ 8 4` = 2, `- 2 1` = 1; `/ 6 2` = 3, `- 8 3` = 5; `* 5 1` = **5** ✓.

:::::

</Q>

<Q id="P3.Q6">

**Circular array queue.** front and rear wrap with `(index + 1) % capacity`; `enqueue`, `dequeue`, `isEmpty`, `isFull`. A naive `front == rear` test cannot tell empty from full: fix it with a count or by leaving one slot unused, and explain the choice. Capacity 5: enqueue 5, dequeue 2, enqueue 2 more, printing the queue at each stage.

::::: details Solution

**Choice: a count.** `count == 0` is empty and `count == CAP` is full, so all 5 cells are usable and front and rear are never compared. (Leaving one slot unused also works, with only CAP − 1 usable: the convention Oct 2025 Q3 used.)

::: code-group
<<< @/../code/ds/notes/u4-circular-count.cpp [Program]
<<< @/../code/ds/notes/u4-circular-count.out{txt} [Output]
:::

After two dequeues, 60 and 70 wrap into cells 0 and 1 (rear = 1 &lt; front = 2: normal).

:::::

</Q>

<Q id="P3.Q7">

**Queue using a linked list.** front and rear pointers for O(1) enqueue and dequeue; when a dequeue empties the queue, both must become nullptr.

::::: details Solution

::: code-group
<<< @/../code/ds/notes/u4-ll-queue.cpp [Program]
<<< @/../code/ds/notes/u4-ll-queue.out{txt} [Output]
:::

:::::

</Q>

<Q id="P3.Q8">

**Ring buffer that overwrites when full.** `add(int)` always succeeds (overwriting the oldest when full), a print from oldest to newest, `isFull()`, `size()`. Capacity 4, add 6 values printing after each; then a moving average of the stored values.

::::: details Solution

::: code-group
<<< @/../code/ds/notes/u4-ring-buffer.cpp [Program]
<<< @/../code/ds/notes/u4-ring-buffer.out{txt} [Output]
:::

After 6 adds only the last 4 remain (2 8 6 3). The running sum makes the average O(1).

:::::

</Q>

<Q id="P3.Q9">

**Challenging: stack using two queues.** Push and pop backed by two queues only; choose push O(1) / pop O(n) or push O(n) / pop O(1), and explain the sequence of operations. Push 4 values and pop them in LIFO order.

::::: details Solution

::: code-group
<<< @/../code/ds/notes/u3-stack-queues.cpp [Both versions]
<<< @/../code/ds/notes/u3-stack-queues.out{txt} [Output]
:::

**Push-costly:** put the new element into the empty helper queue, move every old element behind it, and swap names. The newest is now at the front, so pop is one dequeue. **Pop-costly:** push is one enqueue; pop moves all but the last element to the other queue, dequeues the last, and swaps. n pushes followed by n pops cost O(n²) either way ([TQ-2 2026 Q3](../quizzes/2026-theory-2#q3)).

:::::

</Q>

<Q id="P3.Q10">

**Round Robin CPU scheduling with a queue.** Processes as a struct (id, burstTime, arrivalTime); load them in arrival order; repeatedly dequeue, run for min(quantum, remaining), print it (the Gantt chart), and re-enqueue if unfinished; finally print each turnaround and waiting time. At least 4 processes, quantum 2.

::::: details Solution

::: code-group
<<< @/../code/ds/notes/u4-round-robin.cpp [Program]
<<< @/../code/ds/notes/u4-round-robin.out{txt} [Output]
:::

Turnaround = completion − arrival; waiting = turnaround − burst. A process that arrives during a time slice joins the queue **before** the interrupted process goes back to the end.

:::::

</Q>
