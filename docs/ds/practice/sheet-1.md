---
title: Practice sheet 1 · Classes and pointers
---

# Practice sheet 1 · Classes, objects and pointers

<PaperHeader :rows="[
  ['Topics', 'Classes and objects (Q1–Q6), pointers (Q7–Q10)'],
  ['Exam weight', 'Quiz material (Unit 1): access rules, constructors, pointer arithmetic, new/delete'],
]" />

<Q id="P1.Q1">

**Class vs struct access.** Write two versions of a simple Point type storing int x, y: one as a `struct Point` with a member function `print()`, one as a `class Point` with the same members. In `main()`, create an object of each and directly set x and y (e.g. `p.x = 5;`) without using any setter function. Add comments showing which lines compile and which fail, and why.

::::: details Solution

A `struct`'s members are **public** by default, so direct access compiles; a `class`'s are **private** by default, so it does not.

::: code-group
<<< @/../code/ds/practice/p1-q1-struct.cpp [struct: compiles]
<<< @/../code/ds/practice/p1-q1-struct.out{txt} [Output]
<<< @/../code/ds/practice/p1-q1-class.cpp [class: does not]
<<< @/../code/ds/practice/p1-q1-class.out{txt} [Compiler says]
:::

The compiler stops at the first error (`p.x = 5;`); `p.y = 7;` and `p.print();` would fail for the same reason. Adding `public:` at the top of the class makes it behave like the struct.

:::::

</Q>

<Q id="P1.Q2">

**Class design.** A class `Rectangle` with private `double length, width`; a constructor taking both (default both to 1.0 with no arguments, using constructor overloading); public `setLength()`, `setWidth()`, `getArea()`, `getPerimeter()`; a `const` member function `display()` printing the dimensions and area. Implement every member function outside the class with `::`.

::::: details Solution

One program answers Q2, Q4 and Q6:

::: code-group
<<< @/../code/ds/practice/p1-rectangle.cpp [Program]
<<< @/../code/ds/practice/p1-rectangle.out{txt} [Output]
:::

`getArea`, `getPerimeter` and `display` are `const` because they don't change the object; that also lets them be called on a `const Rectangle&`, which Q6's `operator==` needs.

:::::

</Q>

<Q id="P1.Q3">

**Constructors and invariants.** A `BankAccount` with a private `double balance`. The constructor accepts a starting balance only if it is non-negative, otherwise it throws a nested `InvalidBalance {}`. `deposit(amount)` and `withdraw(amount)`, where withdraw must not let the balance go negative (throw `InsufficientFunds {}`). Test both exceptions with try/catch.

::::: details Solution

The invariant "balance ≥ 0" is checked in the two places that could break it: the constructor and `withdraw`. The same program answers Q10.

::: code-group
<<< @/../code/ds/practice/p1-bank.cpp [Program]
<<< @/../code/ds/practice/p1-bank.out{txt} [Output]
:::

A nested class is named from outside as `BankAccount::InvalidBalance`, and it is caught by reference.

:::::

</Q>

<Q id="P1.Q4">

**Direct vs dynamic allocation.** Using Rectangle: create one as a local variable and one with `new` through a pointer; call `getArea()` on both (`.` and `->`); delete the dynamic one and set its pointer to `nullptr`.

::::: details Solution

In the Q2 program above: `Rectangle r1;` lives on the stack and is destroyed automatically at the end of `main`; `new Rectangle(3, 4)` lives on the heap until `delete`. `r1.getArea()` versus `r2->getArea()` (which means `(*r2).getArea()`). After `delete r2;`, `r2 = nullptr;` so the dangling pointer can't be used by mistake.

:::::

</Q>

<Q id="P1.Q5">

**Enumerations and classes.** `enum class Day { mon, tue, wed, thu, fri, sat, sun };` and a class `Schedule` storing a Day and a string activity, with a constructor and `isWeekend()` (true for sat or sun). Create one weekday and one weekend schedule and print whether each is a weekend.

::::: details Solution

::: code-group
<<< @/../code/ds/practice/p1-schedule.cpp [Program]
<<< @/../code/ds/practice/p1-schedule.out{txt} [Output]
:::

`enum class` values must be written `Day::sat`, and they do not convert to int, which is the point: `Schedule(3, "x")` would not compile.

:::::

</Q>

<Q id="P1.Q6">

**Operator overloading.** Overload `==` for Rectangle as a non-member helper, so two rectangles are equal if they have the same area. Show two rectangles with different sides but the same area reported as equal.

::::: details Solution

In the Q2 program: `bool operator==(const Rectangle& a, const Rectangle& b)` compares `a.getArea()` and `b.getArea()`; 2 × 6 and 3 × 4 are "equal". It needs only the public getter, so it doesn't have to be a friend: the slides' advice to keep the class interface small and put such helpers outside.

:::::

</Q>

<Q id="P1.Q7">

**Pointer basics.** Declare an int and a pointer to it; print the value, its address and the dereferenced value; change the variable through the pointer and print it.

::::: details Solution

::: code-group
<<< @/../code/ds/practice/p1-q7.cpp [Program]
<<< @/../code/ds/practice/p1-q7.out{txt} [Output (the address differs every run)]
:::

:::::

</Q>

<Q id="P1.Q8">

**Pointers and functions.** `void swapValues(int *a, int *b)` swaps two integers through pointers; call it with `&` and print before and after.

::::: details Solution

::: code-group
<<< @/../code/ds/practice/p1-pointers.cpp [Program (Q8 and Q9)]
<<< @/../code/ds/practice/p1-pointers.out{txt} [Output]
:::

Passing `&m` gives the function m's address, so `*a = …` changes m itself. Passing by value (`int a`) would swap only copies.

:::::

</Q>

<Q id="P1.Q9">

**Pointer arithmetic and arrays.** For `int scores[] = {55, 68, 72, 90, 81};`: point `int *sPtr` at the first element; print every element with pointer arithmetic only; show `scores[2]` equals `*(sPtr + 2)`; print the number of elements between `&scores[0]` and `&scores[4]` by subtracting the pointers.

::::: details Solution

In the Q8 program above. `sPtr + i` moves i **ints**, not i bytes; `&scores[4] - &scores[0]` is **4** (elements), even though the addresses differ by 16 bytes.

:::::

</Q>

<Q id="P1.Q10">

**Dynamic memory and pointers to objects.** An array of 3 `BankAccount*`, each created with `new BankAccount(...)` with a different starting balance; deposit into each through `->`; print each balance; delete each account and set each pointer to `nullptr`.

::::: details Solution

The second half of the Q3 program. `BankAccount* accounts[3];` is an array of three pointers (the array itself is not dynamic, the objects are). Each `delete accounts[i]` is followed at once by `accounts[i] = nullptr`.

:::::

</Q>
