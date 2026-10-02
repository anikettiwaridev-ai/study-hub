---
title: Data Structures
---

# Data Structures

<PaperHeader :rows="[
  ['Course', 'AIN3001, 4 credits (3-0-2)'],
  ['Faculty', 'Sudesh Rani'],
  ['Mid-semester', '30 marks, 1.5 hours, Units 1 to 5'],
  ['Weightage', 'Mid-term 20 · Theory quizzes 20 · Practical quizzes and viva 20 · End-term 40'],
]" />

<Progress />

<div class="modes">
<div class="mode">

### Preparing for the mid-semester

Written answers: stack tables, substitution steps, traces, C++ functions.

- [Past papers](./papers/), solved in exam layout
- [Mock paper](./mock-mst), timed, with the new tree question
- [How to answer](./how-to-answer), question type by type

</div>
<div class="mode quiz">

### Preparing for a quiz

10 minutes: MCQs, paragraph questions, code blanks.

- [Beat the 10-minute clock](./quiz-clock): the routine and two timed drills
- [All 11 quizzes](./quizzes/), answerable on the page
- **Quick check** at the end of each [notes](./notes/) unit

</div>
</div>

## What to study, in order {#order}

1. **[Unit 3, Part A: expressions](./notes/unit-3).** An expression question was on all six mid-semester papers, and it is mechanical marks once the table format is automatic. Then do [Oct 2025 Q1](./papers/mst-2025-oct#q1) and [2024 B Q3a](./papers/mst-2024-b#q3a) on paper.
2. **[Unit 1: recurrences by substitution](./notes/unit-1#substitution)**, on 5 of 6 papers. Every recurrence ever asked is worked there. Then **[Biased Search](./notes/unit-1#biased-search)**: on 2 papers including the latest, and in no slide.
3. **[Unit 4: queues](./notes/unit-4)**, on all six papers: the circular-queue convention (full at N − 1), deque traces, the priority queue as a sorted list.
4. **[Unit 2: the linked-list function bank](./notes/unit-2#function-bank).** Write each paper function on paper from memory: insert in the middle, merge, remove duplicates, sorted DLL insert, priority-queue ENQUEUE, sparse-matrix addition.
5. **[Unit 5: trees](./notes/unit-5).** New to the mid-semester this year, so no past paper shows how it will be asked. Expect traversals, building a tree from two traversals, and a recursive count or height.
6. **Timed papers:** [Oct 2025](./papers/mst-2025-oct), [2024 B](./papers/mst-2024-b), [Mar 2024](./papers/mst-2024-mar), then the [mock](./mock-mst).
7. **The night before:** [most-trapped questions](./traps).

## How the papers are set {#pattern}

Counted over six mid-semester papers (170 marks; details in [the repeat map](./repeats)):

| Every paper had… | Typical marks |
|---|---|
| an infix → postfix/prefix conversion or a postfix evaluation, graded on the stack table | 5–6 |
| a linked-list function to write (or a recursive list trace) | 5–12 |
| a queue question: circular queue, deque, priority queue, or a queue simulation | 5–6 |
| and 5 of 6 had a recurrence, "by substitution, show every step" | 5–7 |

The two latest papers ([2024 B](./papers/mst-2024-b), [Oct 2025](./papers/mst-2025-oct)) add **Biased Search** or **worst-case complexities** and want **runnable C++**. Your syllabus adds **trees**.

## About the quizzes {#quizzes}

Theory and lab quizzes are 10 minutes each, and the clock is the real opponent: Theory Quiz 2 had five 50–90-word paragraphs; the lab quizzes had ten blanks across unfamiliar functions. Two facts help:

- **They repeat.** This year's Theory Quiz 1 reused last year's Quiz I question by question, and Lab Quiz 2 was two past exam questions. Your next quizzes will probably follow last year's [Quiz III](./quizzes/2025-theory-3) and [Lab Quiz II](./quizzes/2025-lab-2) (trees).
- **Paragraphs have skeletons.** Every long question so far reduces to one of about fifteen types. [Beat the 10-minute clock](./quiz-clock) lists them with the recipe for each.

## Where this comes from {#sources}

Built from the lecture slides (Units 1–5), the three practice sheets, eight past papers, last year's seven quizzes and this year's four official keys. Every program is compiled as strict C++17 and run; every trace and table was produced by running code. Where the slides are wrong, the notes say so.
