---
title: Object Oriented Programming
---

# Object Oriented Programming

<PaperHeader :rows="[
  ['Course', 'AIN3002, 4 credits'],
  ['Faculty', 'Dr. Satnam Kaur'],
  ['Next exams', 'Quizzes and the mid-semester'],
  ['Mid-semester', '30 marks, 1.5 hours, Units 1 to 4'],
]" />

<Progress />

<div class="modes">
<div class="mode">

### Preparing for the mid-semester

Written answers: explanations, full programs, output traces with reasons.

- [Past papers](./papers/), solved
- [Assignment 5](./assignments/a5) first
- [Mock paper](./mock-mst), timed
- [How to answer](./how-to-answer)

</div>
<div class="mode quiz">

### Preparing for a quiz

Output MCQs with trap options, concept picks, fill in the blanks.

- [Quiz practice](./quiz-practice) and a mock quiz
- [Quiz 1](./papers/quiz-1), answerable on the page
- **Quick check** at the end of each [notes](./notes/) unit
- [Most-trapped questions](./traps)

</div>
</div>

## What to study, in order

1. **[Past papers](./papers/) and [Assignment 5](./assignments/a5) together.** They are one question bank: A5 Q2, Q3, Q5 and Q8 were asked word for word, and Q4's first two parts are word for word Remedial 2024 Q2.
2. **[Unit 4 notes](./notes/unit-4): type conversion, unary operators, prefix and postfix `++`, `<<` and `>>`.** No assignment covers any of these, yet conversion alone carried 12 of the last 120 mid-semester marks.
3. **[Assignment 1](./assignments/a1) Q5 to Q12, [Assignment 3](./assignments/a3) Q6 to Q9 and Q12 to Q18, [Assignment 4](./assignments/a4) Q3 and Q6 to Q12.** Output tracing, passing mechanisms, default arguments, dynamic memory, `const` and static members.
4. **The [mock paper](./mock-mst)**, timed, then **[Quiz practice](./quiz-practice)**.
5. **The rest of Assignments 3 and 4, and from [Assignment 2](./assignments/a2) only factorial, Fibonacci and the prime check.** Good practice, rarely the shape of a paper question.

[How often each topic comes back](./repeats) and [the most-trapped questions](./traps) have the evidence behind this order.

## How much do the assignments help?

Counted from the four mid-semester papers (120 marks):

| | Marks | Share |
|---|---|---|
| Questions asked **word for word** from an assignment (19 marks fully, plus Remedial 2024 Q2, whose first two parts are A5 Q4 verbatim) | 25 | 21% |
| Questions on a topic some assignment covers | 71 | 59% |
| Topics **no** assignment covers (concept openers, storage classes, most output pairs, conversions, library functions) | 49 | 41% |

So the assignments are necessary but not enough. **Assignment 5** is by far the most valuable (every verbatim repeat except the two-mark programs comes from it). **Assignments 3 and 4** matter for their passing-mechanism and `const`/static questions, not for their array drills. **Assignment 1**'s tracing questions (Q8, Q9, Q12) are the quiz's style exactly. The other 41% comes only from the [notes](./notes/) and the [papers](./papers/).

## How the papers are set

The four recent mid-semester papers share a shape:
- a 2 or 3 mark **concept opener**: name the OOP feature from a description;
- an **output pair** comparing passing by value with passing by reference, usually two programs that differ by one token (`&` or `static`), where the marks are for explaining why the outputs differ;
- a **long class** written from a numbered specification (dynamic constructor, operators, copying) in most papers;
- a **type conversion** question (three of four papers);
- an **operator overloading** question and a **two-mark program**.

Specifications are long and literal: use the member names exactly as given. Some questions contradict themselves; the paper says to assume the missing data, so state your assumption in one line and carry on ([known cases](./traps#mistakes-in-her-papers-state-an-assumption)).

**Quizzes** (Quiz 1 so far) are ten questions: output prediction with options built from specific mistakes, "which concept" MCQs and fill in the blanks. One question can have two correct options.

## Mid-semester syllabus

**Unit 1, introduction.** Abstraction, objects, encapsulation, information hiding, methods, signatures, classes and instances, compile-time and run-time polymorphism, inheritance.

**Unit 2, programming basics.** Storage, scope, lifetime and default values of static, global and local variables. Constants, keywords, data types. Operators by operand count and by operation, including comma, scope resolution, and pre- and post-increment. Precedence and associativity. Implicit and explicit casting. Functions: placement above or below `main`, passing by value, reference and pointer, overloading and its ambiguities, default arguments, the four signature shapes, and passing arrays.

**Unit 3, classes and objects.** Access specifiers, member functions inside and outside the class, inline, nesting of member functions, private member functions, static data members and functions, `constexpr`, the memory layout of an object with and without padding, returning and passing objects, arrays of objects, friend functions and classes, forward declaration, constructors of every kind, the singleton pattern, deep and shallow copy, copy versus assignment initialisation, dynamic initialisation, dynamic constructors, destructors.

**Unit 4, operator overloading.** Unary and binary operators as members and as friends, the assignment operator and what the default one breaks (dangling pointers, leaks, double frees, lost isolation), `<<` and `>>`, operators that cannot be overloaded, conversions between classes and basic types, and the pitfalls of overloading.

Anything else covered in class is also in the syllabus.
