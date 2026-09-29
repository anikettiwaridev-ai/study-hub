---
title: Mock mid-semester paper
---

# Mock mid-semester paper

<PaperHeader :rows="[
  ['Written for', 'Object Oriented Programming, mid-semester practice'],
  ['Maximum marks', '30'],
  ['Time allowed', '1.5 hours'],
  ['Note', 'Attempt all questions. Assume the missing data.'],
]" />

::: info How this paper was made
It copies the structure of the October 2025 paper exactly (3 + 3, 4 + 2, 9 + 3, 3 + 3) and its difficulty. Every question tests a pattern she has used, with **new** data, names and a twist, so it tests understanding rather than memory. Two topics that are in the syllabus but have never been asked (run-time polymorphism as an opener, and a friend `==` on a dynamic class) are included on purpose. **Set a timer, keep the solutions closed, and write on paper.** Every program in the solutions was compiled and run.
:::

<Q id="MK.Q1a">

A program keeps an array of pointers to a base class `Shape`. Calling `draw()` through each pointer prints "Drawing a circle" for one element and "Drawing a square" for the other, even though the call is written the same way. Which OOP concept is this? How is it different from the kind of polymorphism provided by function overloading? Explain with an example.

::::: details Solution

**Run-time (dynamic) polymorphism**, through **function overriding** with a **`virtual`** function. The call `shapes[i]->draw()` is the same, but which `draw()` runs is decided **while the program runs**, from the actual object the pointer points to. That is late binding.

Function overloading is **compile-time (static) polymorphism**: the compiler picks the version from the arguments before the program runs (early binding), and inheritance is not needed.

::: code-group
<<< @/../code/oop/mock/mk-q1a.cpp [Program]
<<< @/../code/oop/mock/mk-q1a.out{txt} [Output]
:::

| | Compile time | Run time |
|---|---|---|
| Mechanism | overloading (functions, operators) | overriding a `virtual` function |
| Decided by | the argument types | the object's actual type |
| Needs inheritance | no | yes, plus a base pointer or reference |

::: tip Marking
Name it (1), contrast it with overloading (1), example (1).
:::

:::::

</Q>

<Q id="MK.Q1b">

A ticket-booking class keeps a count of all tickets sold, a function hands out ticket numbers starting from 101, and a global variable holds the day's total. Compare the global variable, the static data member and the static local variable used here in terms of default value, scope, lifetime and memory location. Also state where a plain local variable of `main` is stored.

::::: details Solution

::: code-group
<<< @/../code/oop/mock/mk-q1b.cpp [Program]
<<< @/../code/oop/mock/mk-q1b.out{txt} [Output]
:::

| | Default value | Scope | Lifetime | Memory |
|---|---|---|---|---|
| Global `total` | 0 | whole program | whole run | data segment |
| Static data member `Ticket::sold` | 0 (must be defined once) | the class; used as `Ticket::sold` | whole run | data segment, one copy for all objects |
| Static local `id` in `nextId()` | 0 | only inside `nextId` | whole run; initialised once | data segment |
| Local `local` in `main` | garbage | its block | until the block ends | stack |

The output shows it: `total` is 0 without being set; three objects made `sold` 3; `id` kept its value between calls (101, then 102).

:::::

</Q>

<Q id="MK.Q2a">

Find the output in both cases. If the output is different, state the reasons behind such difference.

::: code-group
<<< @/../code/oop/mock/mk-q2a-pointer.cpp [Case 1: int *p]
<<< @/../code/oop/mock/mk-q2a-value.cpp [Case 2: int p]
:::

::::: details Solution

::: code-group
<<< @/../code/oop/mock/mk-q2a-pointer.out{txt} [Case 1 output]
<<< @/../code/oop/mock/mk-q2a-value.out{txt} [Case 2 output]
:::

`step` is **static** and **doubles** each call: 2 → 4 on the first call, 4 → 8 on the second.

- **Case 1, pass by pointer:** `*p` is `m` itself. 10 + 4 = **14**, then 14 + 8 = **22**.
- **Case 2, pass by value:** `p` is a copy; `m` stays **10** both times.

**Reasons:** a pointer gives the function the address of `m`, so writing through `*p` changes `m`; a value parameter is a separate copy destroyed at return. `step` is static, so it is initialised once and keeps its value, which is why the second call adds 8 rather than 4.

::: danger The twist
The paper versions used `&` and added 1, 2. Here it is a **pointer** and `step *= 2` runs **before** it is added: the first call adds 4, not 2.
:::

:::::

</Q>

<Q id="MK.Q2b">

Find the output. Justify each value.

<<< @/../code/oop/mock/mk-q2b.cpp

::::: details Solution

<<< @/../code/oop/mock/mk-q2b.out{txt} [Output]

- `y = (x++, x += 3, x * 2);` → brackets, so the comma operator: x = 3, then x = 6, value 6 × 2 = 12 → **y = 12**, **x = 6**.
- `int z = x, w = (y, x);` → the first comma is a **separator** (two variables declared); `(y, x)` is the **operator**, value x = 6 → **z = 6, w = 6**.

Output: `6 12 6 6`.

:::::

</Q>

<Q id="MK.Q3a">

Create a class named `Vector` with two private data members, `int *elements` and `int size`.
(i) Initialise two objects `v1` and `v2` through a parameterized dynamic constructor that allocates memory with `new` equal to the number of elements passed.
(ii) Create `v4` as a copy of `v1` through a constructor that makes a **deep** copy.
(iii) Overload `+` as a **member function** so that `v3 = v1 + v2` adds the elements at corresponding positions; the size of `v3` is the larger of the two sizes, and a missing element counts as 0.
(iv) Overload `==` as a **friend function** that returns true only if both objects have the same size and the same elements.
(v) Show that changing an element of a copy does not change the original.
(vi) Overload the assignment operator so that `v5 = v3` also makes a deep copy.
(vii) Release all memory in a destructor. Display all objects.

::::: details Solution

::: code-group
<<< @/../code/oop/mock/mk-q3a.cpp [Program]
<<< @/../code/oop/mock/mk-q3a.out{txt} [Output]
:::

**Where the 9 marks usually go.**

| Part | What earns it |
|---|---|
| (i) class + dynamic constructor (2) | private members; length passed in (an array parameter is a pointer); `new int[size]`; copy loop |
| (ii) deep copy constructor (1) | `const Vector &` parameter; **new** block; copy the values |
| (iii) member `+` (2) | one parameter; result size = larger; missing element = 0; returns a new `Vector` |
| (iv) friend `==` (1.5) | two parameters; size check first, then every element |
| (v), (vi) (1.5) | self-assignment check, `delete[]` old, new block, `return *this` by reference; the output line proving `v3` did not change |
| (vii) destructor and display (1) | `delete[] elements` |

::: danger What a shallow class would do here
Without (ii) and (vi), `v4` and `v5` would share memory with `v1` and `v3`: `v5.set(0, 999)` would change `v3` too, and two destructors would free the same block at the end (a double free).
:::

:::::

</Q>

<Q id="MK.Q3b">

For the class below, write the output of `main` and name which special member function each line calls.

<<< @/../code/oop/mock/mk-q3b.cpp

::::: details Solution

<<< @/../code/oop/mock/mk-q3b.out{txt} [Output]

| Line | Code | Calls | Prints |
|---|---|---|---|
| 1 | `Item a(5);` | parameterised constructor | P |
| 2 | `Item b = a;` | copy constructor (b is new) | C |
| 3 | `Item c;` | default constructor | D |
| 4 | `c = b;` | copy **assignment** (c exists) | A |
| 5 | `show(a);` | copy constructor: **pass by value** copies the argument | C |
| 6 | `look(a);` | nothing: **pass by reference** makes no copy | |
| 7 | `Item d = 7;` | parameterised constructor (basic → class conversion) | P |

**Output: `P C D A C P`**. The traps are lines 5 and 6 (passing, not declaring, can call the copy constructor) and line 7 (`=` with an `int` on the right calls `Item(int)`, not the copy constructor; since C++17 no copy is made at all).

:::::

</Q>

<Q id="MK.Q4a">

We have two classes, `Dollars` and `Rupees`. The statement `r = d;` should store in the `Rupees` object `r` the rupee value of the `Dollars` object `d` (1 dollar = 83 rupees). Which type conversion is this? Write it using a conversion function in the **source** class, and state the other way it could be written and why both must not be written together.

::::: details Solution

**Class to class conversion.** Source class `Dollars`, destination class `Rupees`.

::: code-group
<<< @/../code/oop/mock/mk-q4a.cpp [Program]
<<< @/../code/oop/mock/mk-q4a.out{txt} [Output]
:::

`operator Rupees() const` inside `Dollars` converts; `r = d;` becomes `r = d.operator Rupees();`, and 12 × 83 = 996.

**The other way:** a one-argument constructor in the destination, `Rupees(const Dollars &d)`, which needs the dollar amount through a getter or friendship.

**Why not both:** the compiler would then have two equally good ways to convert and standard C++ rejects `r = d;` as ambiguous ([proof in the notes](./notes/unit-4#class-to-class)).

:::::

</Q>

<Q id="MK.Q4b">

What is the output? Explain how the compiler decides which function runs for `a++` and `++a`.

<<< @/../code/oop/mock/mk-q4b.cpp

::::: details Solution

<<< @/../code/oop/mock/mk-q4b.out{txt} [Output]

The compiler picks by the **dummy `int` parameter**: `operator++(int)` is postfix (`a++`), `operator++()` is prefix (`++a`).

- `Score b = a++;` → postfix: prints `post`, remembers old (1), then **s += 10** → a = 11; b gets the old value **1**.
- `Score c = ++a;` → prefix: prints `pre`, a = 12, returns a copy → c = **12**.
- Final line: `12 1 12`.

::: danger The twist
The postfix body adds **10**, not 1. Always trace the function body; never assume `++` means +1 once it is overloaded.
:::

:::::

</Q>
