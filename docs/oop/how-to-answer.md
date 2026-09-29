---
title: How to answer
---

# How to answer

The same syllabus is examined two ways. The quiz rewards fast, exact recall; the mid-semester rewards complete, well-laid-out answers. This page is how to earn the marks in each.

## Mid-semester: written answers

<PaperHeader :rows="[
  ['Marks and time', '30 marks in 1.5 hours: about 3 minutes per mark'],
  ['Shape', 'A concept opener, an output pair, a long class, a conversion or operator question, a short program'],
  ['Note on every paper', 'Attempt all questions. Assume the missing data.'],
]" />

### "Which OOP concept is this?" (2 to 3 marks)

1. **Name** the concept in the first line, in bold.
2. **Define** it in one sentence.
3. **Why it matters** in one sentence (if asked "why").
4. **A tiny example**: a class of 5 to 8 lines, with a comment pointing at the line that shows the concept.

A one-word answer gets half the marks at best. See <Src r="O25.Q1a" />.

### "Find the output… if different, state the reasons" (3 to 4 marks)

1. Check for a **compile error** first.
2. Write each program's output separately and exactly (spaces, line breaks, missing separators).
3. Show a small **trace table** (the variable after each call).
4. **Reasons**, as numbered points: value vs reference (copy vs alias), and anything `static` changes. The reasons are about half the marks.

See <Src r="S24.Q4a" />.

### The long class question (6 to 10 marks)

1. Read the specification and **number its requirements**; it is a checklist, and the marks follow it.
2. Use the **exact names** given (`stringName`, `joinStrings`, `displayComplexNumber`).
3. Write the class, then `main`, then **a sample output** (they ask "with output").
4. Put a short comment on each numbered requirement: `// A.II: +1 for '\0'`.
5. If the class uses `new`: destructor; deep copy constructor if objects are copied or returned; `delete[]` before re-allocating.
6. If the specification is impossible or contradicts itself, write **one line** with your assumption and carry on. The [traps page](./traps#mistakes-in-her-papers-state-an-assumption) lists the known ones.

See <Src r="O25.Q3a" />.

### Conversion questions (4 marks)

Name the type (**basic → class**, **class → basic**, **class → class**), name the mechanism (constructor / `operator type()` / either one), then a complete small program that uses the exact statement from the question (`duration = t;`) and its output. See <Src r="S24.Q5a" />.

### Two-mark programs

A whole program with `#include`, `main`, input, output and a label. Handle the edge cases (0! = 1, negative input). See <Src r="S24.Q5b" />.

### Time plan for 1.5 hours

| Minutes | Do |
|---|---|
| 0–5 | Read the whole paper; mark the long question |
| 5–25 | Concept questions and output questions (fast, reliable marks) |
| 25–65 | The long class question |
| 65–85 | Conversion, operators, short programs |
| 85–90 | Check exact names, `;` after classes, `+ 1`, `delete[]` |

## Quiz: fast and exact

- **Trace fully, never estimate.** The wrong options are built from specific mistakes (forgetting `static`, forgetting a shadowed variable, an off-by-one), so a close-but-wrong answer is almost always listed.
- **Look for "Error" first.** Ambiguous overloads, `int a = 5, 4;`, private access, a static function using a non-static member.
- **Watch the separators in `cout`.** `cout << a << x;` prints `1526`, not `15 26`.
- **More than one option can be correct** (Quiz 1 Q4). Read every option before choosing.
- **Output with side effects:** `d = (cout << "hello", 3)` prints `hello` at that moment, before anything printed later.

### The tracing method

1. Draw the memory map: stack, heap, data segment, with defaults (garbage / 0 / 0).
2. Circle every `static`: initialised once, survives calls.
3. Rewrite every `++` / `--` as two plain statements.
4. Comma: separator or operator? If operator, `=` binds tighter and the value is the rightmost.
5. Recursion: build bottom-up from the base case.
6. `for` loops with calls: one row per slot (init, condition, body, update).
7. Names: local → enclosing block → global; a parameter can hide a global; `::x` is the global.
8. Objects: list every construction in order, destroy in reverse; inner blocks at their `}`; pass by value = a copy constructor call.

Practise with [Quiz practice](./quiz-practice) and [Quiz 1](./papers/quiz-1).
