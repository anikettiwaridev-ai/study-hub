// Single source of truth for OOP repeat tracking.
// Every badge, count and mark total on the site is computed from this file.
//
// Refs look like "S24.Q2" or "A2.Q3-i": <source id>.<part>.
// A source's `href` stays null until its page exists; chips then become links.

const range = (n, marks = null) =>
  Object.fromEntries(Array.from({ length: n }, (_, i) => [`Q${i + 1}`, marks]))

export const sources = {
  S24: {
    title: 'Mid-semester, September 2024',
    short: 'Sep 2024',
    kind: 'mst', maxMarks: 30, time: '1.5 hours',
    href: '/oop/papers/mst-2024-sep',
    parts: { Q1a: 2, Q1b: 4, Q2: 6, Q3: 6, Q4a: 4, Q4b: 2, Q5a: 4, Q5b: 2 },
  },
  R24: {
    title: 'Mid-semester remedial, October 2024',
    short: 'Remedial 2024',
    kind: 'mst', maxMarks: 30, time: '1.5 hours',
    href: '/oop/papers/mst-2024-remedial',
    parts: { Q1a: 2, Q1b: 4, Q2: 6, Q3: 6, Q4a: 4, Q4b: 2, Q5a: 4, Q5b: 2 },
  },
  O25: {
    title: 'Mid-semester, October 2025',
    short: 'Oct 2025',
    kind: 'mst', maxMarks: 30, time: '1.5 hours',
    href: '/oop/papers/mst-2025-oct',
    parts: { Q1a: 3, Q1b: 3, Q2a: 4, Q2b: 2, Q3a: 9, Q3b: 3, Q4a: 3, Q4b: 3 },
  },
  N25: {
    title: 'Mid-semester remedial, November 2025',
    note: 'The re-sit of the October 2025 paper, and the newest paper we have',
    short: 'Nov 2025',
    kind: 'mst', maxMarks: 30, time: '1.5 hours',
    href: '/oop/papers/mst-2025-nov',
    parts: { Q1: 2, Q2: 5, Q3: 3, Q4a: 2, Q4b: 2, Q5: 4, Q6: 2, Q7a: 4, Q7b: 4, Q8: 2 },
  },
  E24: {
    title: 'End-semester, November 2024',
    note: 'Only the questions inside the mid-semester syllabus',
    short: 'End-sem 2024',
    kind: 'endsem', maxMarks: 80, time: '3 hours',
    href: '/oop/papers/endsem-2024',
    parts: { Q2a: 6, Q2b: 4, Q3a: 6, Q3b: 4, Q4: 10, Q5c: 6, Q6a: 4, Q6b: 8 },
  },
  QZ1: {
    title: 'Quiz 1, 2026',
    short: 'Quiz 1',
    kind: 'quiz', maxMarks: null, time: null,
    href: '/oop/papers/quiz-1',
    parts: range(10),
  },
  MK: {
    title: 'Mock mid-semester paper',
    note: 'Written for this site in the shape of the 2025 papers. Not a real paper.',
    short: 'Mock MST',
    kind: 'mock', maxMarks: 30, time: '1.5 hours',
    href: '/oop/mock-mst',
    parts: { Q1a: 3, Q1b: 3, Q2a: 4, Q2b: 2, Q3a: 9, Q3b: 3, Q4a: 3, Q4b: 3 },
  },
  A1: { title: 'Assignment 1', href: '/oop/assignments/a1', topic: 'Variables, data types, operators and expressions', short: 'A1', kind: 'assignment', parts: range(12) },
  A2: { title: 'Assignment 2', href: '/oop/assignments/a2', topic: 'Control flow, loops and patterns', short: 'A2', kind: 'assignment', parts: range(8) },
  A3: { title: 'Assignment 3', href: '/oop/assignments/a3', topic: 'Functions, arrays and dynamic memory', short: 'A3', kind: 'assignment', parts: range(20) },
  A4: { title: 'Assignment 4', href: '/oop/assignments/a4', topic: 'Classes, friends, const, inline static and constexpr', short: 'A4', kind: 'assignment', parts: range(12) },
  A5: { title: 'Assignment 5', href: '/oop/assignments/a5', topic: 'Friends, dynamic constructors, operator overloading, copying', short: 'A5', kind: 'assignment', parts: range(9) },
}

// A cluster is one topic that keeps coming back.
// `groups` decides the label between two appearances:
//   same group of kind 'exact'    -> ⟳ Exact     (word for word)
//   same group of kind 'reworded' -> ≈ Reworded  (same ask, different wording)
//   different groups              -> Δ Variant   (same structure, different data)
// Each mid-semester part belongs to exactly one cluster (or to `singles`),
// so the marks table adds up to 120. scripts/check-data.mjs enforces this.
export const clusters = [
  {
    id: 'operator-overloading',
    title: 'Binary operator overloading as a member, returning an object',
    trap: 'The member form takes one parameter because the left operand is `this`. Build and return a new object; do not modify `*this`.',
    groups: [
      { kind: 'single', refs: ['S24.Q3'] },
      { kind: 'single', refs: ['R24.Q3'] },
      { kind: 'single', refs: ['N25.Q7b'] },
      { kind: 'single', refs: ['A5.Q4'] },
      { kind: 'exact', refs: ['E24.Q4', 'A5.Q5'] },
    ],
    notes: {
      'S24.Q3': 'Minus, class ABC, members x and y',
      'R24.Q3': 'Plus, class Sample, members a and b',
      'N25.Q7b': 'Areas of shapes through overloaded operators',
      'A5.Q4': 'Minus on two dynamic arrays',
    },
  },
  {
    id: 'pass-by-value-vs-reference-output',
    title: 'Pass by value vs reference: side-by-side output',
    trap: 'A value parameter is a copy, so main never sees the change; `&` edits the caller. The marks are for stating why the two outputs differ.',
    groups: [
      { kind: 'single', refs: ['S24.Q4a'] },
      { kind: 'single', refs: ['R24.Q4a'] },
      { kind: 'single', refs: ['O25.Q4b'] },
      { kind: 'single', refs: ['N25.Q3'] },
      { kind: 'single', refs: ['QZ1.Q6'] },
    ],
    notes: {
      'S24.Q4a': 'Static counter, `&` vs value',
      'R24.Q4a': 'Local vs static counter; also contains `x = ++x + x++ + x++`, which is undefined behaviour',
      'O25.Q4b': 'Local counter, `&` vs value',
      'N25.Q3': 'Also asks you to compare the two mechanisms',
      'QZ1.Q6': 'Reference, value and array parameters in one call',
    },
  },
  {
    id: 'concept-opener',
    title: 'Name the OOP concept from a description',
    trap: 'A one-word answer loses marks. Name it, define it in one line, then show it in a three-line class.',
    groups: [
      { kind: 'reworded', refs: ['O25.Q1a', 'N25.Q1', 'QZ1.Q5'] },
      { kind: 'reworded', refs: ['S24.Q1a', 'O25.Q1b'] },
      { kind: 'single', refs: ['R24.Q1a'] },
    ],
    notes: {
      'O25.Q1a': 'Hidden data, public methods: encapsulation',
      'N25.Q1': 'Hidden part vs interface: access specifiers',
      'QZ1.Q5': 'Essential operations exposed, internals hidden: abstraction and encapsulation',
      'S24.Q1a': 'Message passing, plus inheritance for reuse',
      'O25.Q1b': 'Child reuses parent and adds methods: inheritance',
      'R24.Q1a': 'Same name, different arguments: function overloading',
    },
  },
  {
    id: 'dynamic-constructor-class',
    title: 'Dynamic-constructor class: String or Array, then combine two objects',
    trap: '`new char[len + 1]` leaves room for the null terminator. `delete[]` the old buffer before allocating a new one. A class holding a raw pointer needs a destructor and a deep copy constructor.',
    groups: [
      { kind: 'exact', refs: ['S24.Q2', 'A5.Q3'] },
      { kind: 'single', refs: ['R24.Q2'] },
      { kind: 'single', refs: ['A5.Q4'] },
      { kind: 'exact', refs: ['E24.Q4', 'A5.Q5'] },
      { kind: 'single', refs: ['A3.Q9'] },
    ],
    notes: {
      'R24.Q2': 'Parts A and B are word for word A5 Q4 parts I and II; only the third part differs (merge vs overloaded minus)',
      'E24.Q4': 'Uses `+` to compare strings, which is an error in the paper. State your assumption.',
      'A3.Q9': 'The merge logic on its own, without a class',
    },
  },
  {
    id: 'type-conversion',
    title: 'Type conversion between a class and a basic type',
    trap: 'Basic to class needs a one-argument constructor. Class to basic needs `operator int()`. Class to class needs a constructor in the destination or a conversion operator in the source, never both.',
    uncovered: true,
    groups: [
      { kind: 'single', refs: ['S24.Q5a'] },
      { kind: 'single', refs: ['R24.Q5a'] },
      { kind: 'single', refs: ['N25.Q7a'] },
    ],
    notes: {
      'S24.Q5a': 'Class to basic: `duration = t`',
      'R24.Q5a': 'Class to class: `mob = comp`',
      'N25.Q7a': 'Basic to class: `emp = Ecode`',
    },
  },
  {
    id: 'complex-number-class',
    title: 'ComplexNumber: three kinds of initialisation and a non-member add',
    trap: 'Copying complex1 into complex3 "through an appropriate constructor" means the copy constructor, not assignment.',
    groups: [{ kind: 'exact', refs: ['O25.Q3a', 'A5.Q8'] }],
  },
  {
    id: 'comma-operator',
    title: 'Comma: separator vs operator',
    trap: '`=` binds tighter than `,`, so `a = 5, 4;` stores 5. In a declaration the comma is a separator, so `int a = 5, 4;` does not compile.',
    groups: [
      { kind: 'single', refs: ['R24.Q1b'] },
      { kind: 'single', refs: ['O25.Q2a'] },
      { kind: 'single', refs: ['QZ1.Q1'] },
      { kind: 'single', refs: ['QZ1.Q9'] },
      { kind: 'single', refs: ['A1.Q8'] },
      { kind: 'single', refs: ['A1.Q9'] },
    ],
    notes: {
      'O25.Q2a': 'Three cases; the third is a compile error',
      'QZ1.Q9': 'The same pair as Oct 2025 Q2a, with 6 and 5',
    },
  },
  {
    id: 'two-mark-program',
    title: 'Two-mark "write a program"',
    trap: 'Write the whole program with `main`, not just the function. Handle 0 and 1 for factorial and Fibonacci.',
    groups: [
      { kind: 'exact', refs: ['S24.Q5b', 'A2.Q3-i'] },
      { kind: 'exact', refs: ['R24.Q5b', 'A2.Q3-viii'] },
      { kind: 'single', refs: ['N25.Q4a'] },
      { kind: 'single', refs: ['N25.Q4b'] },
      { kind: 'single', refs: ['A1.Q11'] },
    ],
    notes: {
      'S24.Q5b': 'Factorial',
      'R24.Q5b': 'Fibonacci',
      'N25.Q4a': 'Using `sqrt()` and `pow()`',
      'N25.Q4b': '`isEven()`',
      'A1.Q11': 'Odd or even with bitwise `&`',
    },
  },
  {
    id: 'static-member-functions',
    title: 'Static member functions and counting objects',
    trap: 'A static member function has no `this`, so it can only touch static members directly. Call it as `ClassName::f()`.',
    groups: [
      { kind: 'single', refs: ['R24.Q4b'] },
      { kind: 'single', refs: ['N25.Q2'] },
      { kind: 'single', refs: ['A5.Q6'] },
    ],
    notes: {
      'R24.Q4b': 'Calling syntax and limitations',
      'N25.Q2': 'Diagram, plus a Counter class for objects created and destroyed',
    },
  },
  {
    id: 'storage-classes',
    title: 'Storage classes and where memory lives',
    trap: '`register` was removed in C++17. Static and global variables live in the data segment; dynamic arrays live on the heap.',
    groups: [
      { kind: 'single', refs: ['S24.Q1b'] },
      { kind: 'single', refs: ['QZ1.Q10'] },
    ],
    notes: { 'S24.Q1b': 'Adds auto, register and extern to the table' },
  },
  {
    id: 'friend-across-classes',
    title: 'Friend functions across two classes',
    trap: 'A friend that is a member of another class needs a forward declaration and must be defined after both classes are complete.',
    groups: [
      { kind: 'single', refs: ['N25.Q5'] },
      { kind: 'single', refs: ['A5.Q1'] },
      { kind: 'single', refs: ['A4.Q3'] },
    ],
    notes: { 'N25.Q5': 'Returning "the object with the larger sum" from two unrelated classes has no single return type. State your assumption.' },
  },
  {
    id: 'copy-vs-assignment',
    title: 'Copy constructor vs assignment: which line calls what',
    trap: '`T c = a;` is copy construction despite the `=`. `d = a;` on an object that already exists is assignment and never calls the copy constructor.',
    groups: [
      { kind: 'single', refs: ['O25.Q3b'] },
      { kind: 'single', refs: ['E24.Q6a'] },
      { kind: 'single', refs: ['A5.Q7'] },
    ],
  },
  {
    id: 'static-local-trace',
    title: 'Static local variables: output trace',
    trap: 'A static local is initialised once, even from a runtime value like `n`, and keeps its value between calls. A parameter named like a global is a separate copy.',
    groups: [
      { kind: 'single', refs: ['O25.Q2b'] },
      { kind: 'single', refs: ['QZ1.Q2'] },
      { kind: 'single', refs: ['A1.Q12'] },
    ],
    notes: {
      'O25.Q2b': '`static int s = n;` takes its first value from a parameter',
      'A1.Q12': 'Same structure as Quiz 1 Q2: global x, a shadowing parameter, static s',
    },
  },
  {
    id: 'passing-mechanisms',
    title: 'Value, reference, pointer or const reference: which to use',
    trap: 'Large and read-only: const reference. Must modify: reference. Might be null: pointer.',
    groups: [
      { kind: 'single', refs: ['S24.Q4b'] },
      { kind: 'reworded', refs: ['QZ1.Q3', 'A4.Q11'] },
      { kind: 'single', refs: ['A3.Q12'] },
      { kind: 'single', refs: ['A3.Q16'] },
      { kind: 'single', refs: ['A4.Q10'] },
      { kind: 'single', refs: ['A4.Q12'] },
    ],
  },
  {
    id: 'overload-ambiguity',
    title: 'Overloading and default-argument ambiguity',
    trap: 'A default parameter makes a two-argument function a one-argument candidate too. Two exact matches is a compile error.',
    groups: [
      { kind: 'single', refs: ['QZ1.Q8'] },
      { kind: 'single', refs: ['QZ1.Q4'] },
      { kind: 'single', refs: ['A5.Q9'] },
      { kind: 'single', refs: ['A3.Q17'] },
      { kind: 'single', refs: ['A3.Q18'] },
    ],
    notes: { 'QZ1.Q4': 'Two options are correct' },
  },
  {
    id: 'dynamic-memory',
    title: 'Static array overflow, dynamic arrays, leaks and dangling pointers',
    trap: 'Writing past a static array compiles and silently corrupts memory. `new[]` pairs with `delete[]`; set the pointer to `nullptr` afterwards.',
    groups: [
      { kind: 'single', refs: ['E24.Q6b'] },
      { kind: 'single', refs: ['A3.Q6'] },
      { kind: 'single', refs: ['A3.Q7'] },
      { kind: 'single', refs: ['A3.Q8'] },
    ],
  },
  {
    id: 'const-static-constexpr-members',
    title: 'const, inline static and constexpr members',
    trap: 'A `const` member is set in the member initializer list, never in the constructor body. `inline static` is shared and changeable; `static constexpr` is shared and fixed at compile time.',
    groups: [
      { kind: 'single', refs: ['A4.Q6'] },
      { kind: 'single', refs: ['A4.Q7'] },
      { kind: 'reworded', refs: ['A4.Q8', 'A4.Q9'] },
      { kind: 'single', refs: ['A5.Q6'] },
    ],
    notes: { 'A5.Q6': 'Also asks why `count` is defined outside the class' },
  },
  {
    id: 'friend-function-this',
    title: 'Friend function sum and the this pointer',
    groups: [{ kind: 'exact', refs: ['E24.Q3a', 'A5.Q2'] }],
  },
]

// Asked once in a paper. Still fair game.
export const singles = [
  { ref: 'O25.Q4a', topic: 'A user-defined function with the same name as a predefined one' },
  { ref: 'N25.Q6', topic: 'Using a local variable outside its function' },
  { ref: 'N25.Q8', topic: 'Prefix vs postfix `++` overloading and the dummy `int`' },
  { ref: 'E24.Q3b', topic: 'An implicit default constructor leaves members uninitialised' },
  { ref: 'E24.Q2a', topic: 'Swapping even- and odd-position array elements' },
  { ref: 'E24.Q2b', topic: 'A nested `if` inside a nested `for`' },
  { ref: 'E24.Q5c', topic: 'Overloading vs overriding, aggregation vs composition. Only the overloading half is mid-semester syllabus' },
  { ref: 'QZ1.Q7', topic: 'Recursion that multiplies by repeated addition' },
]

export default { sources, clusters, singles }
