---
title: How to answer the mid-semester
---

# How to answer the mid-semester

<PaperHeader :rows="[
  ['Marks and time', '30 marks in 1.5 hours: 3 minutes per mark'],
  ['Shape (last two papers)', 'Six questions of 5, or five of 6: a conversion, a recurrence, a queue question, one or two linked-list functions, one extra'],
  ['Note on every paper', 'Assume suitably and state additional data required, if any'],
]" />

Each question type below has the layout that earns full marks, a worked example on a past paper, and the slips that cost marks.

## Infix → postfix / prefix "using stack" (5–6 marks) {#conversion}

The papers say: "clearly show the operation performed for each character, content of stack, and postfix string after each step". So the marks are for the **table**.

1. Write the precedence line once: `^` (right) > `* /` > `+ -`; equal precedence pops except `^`.
2. Draw four columns: **Symbol | Operation | Stack (bottom → top) | Postfix string**.
3. One row per symbol, including brackets and a final **end** row that empties the stack.
4. Box the final answer and check: operands in the original order; the main operator last.

For prefix: show the reversed and bracket-swapped string, the table of the modified pass, then the reversed result ([2024 B Q3a](./papers/mst-2024-b#q3a)). Model answer: [Oct 2025 Q1](./papers/mst-2025-oct#q1).

::: danger Lost marks
Popping only one operator when two qualify (`/` and `+` before `-`); popping `^` on a second `^`; forgetting the end row; no "operation" column.
:::

## Postfix evaluation (5 marks) {#evaluation}

Columns **Token | Operation | Stack**. Write `op2 = pop, op1 = pop, push op1 op op2` once at the top. A negative intermediate result is fine ([2022 B Q1](./papers/mst-2022-b#q1) ends at −2008).

## Recurrence by substitution (5–7 marks) {#recurrence}

1. Expand three times, with brackets, keeping constants visible.
2. Write the general k-th line.
3. Solve the base case for k (n/2ᵏ = 1, n − k = 1, …).
4. Substitute, sum the series, simplify, and state the Big-O.
5. One line of check with a small n (n = 4 or 16) shows the examiner your closed form is right.

For √n, substitute n = 2ᵐ first ([2024 B Q1](./papers/mst-2024-b#q1)). Model answer: [Oct 2025 Q2](./papers/mst-2025-oct#q2). Every recurrence asked so far is in [Unit 1](./notes/unit-1#substitution).

## Queue, circular queue, deque or priority-queue trace (5 marks) {#trace}

1. **First line: the convention** ("front = one cell before the first element, rear = last; full when (rear + 1) % N == front", or "front = rear = −1").
2. Columns: **Operation | Result | front | rear | array cells | queue (front → rear)**. For a deque or a priority queue, the last column is enough.
3. Write OVERFLOW / UNDERFLOW in the row where it happens, and leave the state unchanged.

Model answer: [Oct 2025 Q3](./papers/mst-2025-oct#q3).

## Linked-list function (5–6 marks each) {#list-function}

1. **Use the given class and names exactly** (`LL::insertM`, `mat_addition`, `ENQUEUE`, `node`, `head`, `tail`).
2. Write the signature, then the **edge cases as the first lines**: empty list, one node, the head changes, the tail changes.
3. Then the main walk, with a comment on which node it stops on ("t = node before the key").
4. One line after the code: the complexity, and any assumption ("equal priorities keep arrival order").
5. If the paper says **runnable**, add `#include`s and a `main` that builds a small list and calls the function ([2024 B](./papers/mst-2024-b)).

::: danger Lost marks
Moving a pointer before linking (losing the rest of the list); `->data` read after `delete`; not updating `tail`; storing a zero in a sparse sum; advancing after deleting a node in a loop.
:::

Model answers: [Sep 2023 Q2a](./papers/mst-2023-sep#q2a) (insert in the middle), [Oct 2025 Q5](./papers/mst-2025-oct#q5) (priority queue), [Oct 2025 Q6](./papers/mst-2025-oct#q6) (sparse addition), [2024 B Q3b](./papers/mst-2024-b#q3b) (merge).

## Pseudocode questions (2–4 marks) {#pseudocode}

Numbered steps, ← for assignment, the node fields named as the question names them (`START`, `info`, `next`). Mar 2024 accepted "pseudocode/algorithm": [Q2b](./papers/mst-2024-mar#q2b), [Q2c](./papers/mst-2024-mar#q2c), [Q4](./papers/mst-2024-mar#q4).

## Biased Search (5 marks) {#biased}

Pseudocode (the while loop with mid = ⌊(2s + e)/3⌋), then a table **Step | s | e | mid | A[mid] | comparison | action**, then "found at index … after … comparisons". [Oct 2025 Q4](./papers/mst-2025-oct#q4).

## Tree questions (new this year) {#trees}

- **Traversals:** draw the tree first, write the rule (Left-Root-Right…) at the top, then the sequence.
- **Build from two traversals:** a table **Step | root | inorder split | parts**, then the drawn tree, then the asked traversal. [Dec 2024 Q3d](./papers/endsem-2024#q3d).
- **Code:** empty tree first; then combine the two recursive calls ([Unit 5](./notes/unit-5#code)).

## "Worst case with an example" (6 marks) {#worst-case}

For each part: the Big-O, one sentence of why, and a 3–4 element example traced in one line. [2024 B Q4](./papers/mst-2024-b#q4).

## A time plan for 90 minutes {#time-plan}

| Minutes | Do |
|---|---|
| 0–3 | Read the whole paper; mark the two code questions |
| 3–15 | The conversion table |
| 15–25 | The recurrence |
| 25–35 | The queue trace |
| 35–45 | Biased Search or the tree question |
| 45–80 | The two linked-list functions |
| 80–90 | Check: names exactly as given, `;` after classes, every edge case, the boxed final answers |
