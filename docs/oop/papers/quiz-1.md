---
title: Quiz 1, 2026
---

# Quiz 1, 2026

<PaperHeader :rows="[
  ['Course', 'Object Oriented Programming, CTN304 / AIN302'],
  ['Format', '10 questions: output prediction, multiple choice and fill in the blanks'],
  ['On this page', 'Answer on the page. Every answer is checked and explained.'],
]" />

::: info How her quiz questions are built
Every wrong option is a specific wrong idea, not a random number. In Q2, **45 51 8 66** is exactly what you get if you forget that `s` is static, and **45 54 8 66** is what you get if you forget the last call adds 3 more to `s`. So "close" options are traps by design: trace fully, never estimate. For more questions in this style, see [Quiz practice](../quiz-practice).
:::

<Q id="QZ1.Q1">

Predict the output of the following program.

<<< @/../code/oop/papers/qz1-q1.cpp

<FillIn q="Answer: x = ___, y = ___, z = ___ (write the three numbers separated by commas)" answer="3, 6, 11|3,6,11|3 6 11|x = 3, y = 6, z = 11|x=3, y=6, z=11|x=3,y=6,z=11">

<<< @/../code/oop/papers/qz1-q1.out{txt} [Output]

Every comma inside the brackets is the **comma operator**: it runs strictly left to right and keeps only the last value. Trace:

| Step | x | y | z | value |
|---|---|---|---|---|
| start | 2 | 3 | 4 | |
| `x += 3` | 5 | 3 | 4 | |
| `y *= 2` | 5 | 6 | 4 | 6, dropped |
| `z++` | 5 | 6 | 5 | |
| `x + y` | 5 | 6 | 5 | 11, dropped |
| `x -= 2` | 3 | 6 | 5 | |
| `y + z` | 3 | 6 | 5 | **11**, the value of the whole expression |
| `z = 11` | 3 | 6 | **11** | |

The trap: `z` was changed to 5 in the middle, but it is then overwritten by the final assignment.

</FillIn>

</Q>

<Q id="QZ1.Q2">

Predict the output of the following program.

<<< @/../code/oop/papers/qz1-q2.cpp

<Mcq :options="['45 54 8 69', '45 51 8 66', '45 54 5 69', '30 39 8 69', '45 54 8 66', '45 51 5 66']" answer="a">

<<< @/../code/oop/papers/qz1-q2.out{txt} [Output]

The parameter `x` **shadows** the global `x` and is a **copy**, so `fun` never changes the global. Only `s` (static) carries over between calls.

| Call | local x = x + s | s after += 3 | y = 2 + x | return x + y + s |
|---|---|---|---|---|
| fun(5) | 5 + 10 = 15 | 13 | 17 | 15 + 17 + 13 = **45** |
| fun(5) | 5 + 13 = 18 | 16 | 20 | 18 + 20 + 16 = **54** |
| global x += y (main's y = 3) | | | | x = **8** |
| fun(8) | 8 + 16 = 24 | 19 | 26 | 24 + 26 + 19 = **69** |

Why each wrong option exists: (b) forgets `s` is static (it restarts at 10); (c) forgets `x += y` changes the global; (d) forgets `x += s` before using `x`; (e) uses `s` before the last `+= 3`.

</Mcq>

</Q>

<Q id="QZ1.Q3">

An online banking application receives a customer object merely to display account information. The object is very large and should neither be copied nor modified. Which choice is most appropriate?

<Mcq :options="['Pass by value', 'Pass by const reference', 'Pass by reference', 'Duplicate the object globally']" answer="b">

"Should not be **copied**" rules out pass by value. "Should not be **modified**" rules out a plain reference. `const Customer &c` gives both: no copy is made, and the compiler refuses any change. The rule: large and read-only → `const &`.

</Mcq>

</Q>

<Q id="QZ1.Q4">

Which of the following statements about default arguments is correct?

<Mcq :options="['Default argument must be specified every time the function is called.', 'Default arguments must always be written in both declaration and definition.', 'A default argument is normally specified in the declaration visible to the caller.', 'A non-default parameter cannot follow a parameter with a default argument', 'A non-default parameter can follow a parameter with a default argument', 'Default parameters generally make a parameter constant and cannot take any other value']" answer="c,d">

Two options are correct, which is unusual; tick both.

- **(c) is true.** The caller's compiler must see the default, so it goes in the declaration (prototype). Writing it in *both* declaration and definition is a redefinition error, which is why (b) is false.
- **(d) is true.** Defaults fill from the right: `f(int a = 1, int b)` is an error, because `f(5)` could not say which parameter 5 belongs to. So (e) is false.
- (a) is false: the point of a default is that you may leave it out.
- (f) is false: a default is only used when the argument is missing; any value can still be passed.

</Mcq>

</Q>

<Q id="QZ1.Q5">

A system exposes only the essential operations of an object while keeping its internal implementation details inaccessible to other parts of the program. Which two concepts are most closely represented?

<Mcq :options="['Inheritance and polymorphism', 'Signature and method overloading', 'Abstraction and encapsulation', 'Object and instance']" answer="c">

"Exposes only the **essential operations**" is **abstraction** (show what, hide how). "Keeping internal details **inaccessible**" is **encapsulation** with data hiding (private members behind public methods). The question asks for two concepts because it describes both.

</Mcq>

</Q>

<Q id="QZ1.Q6">

What will be the output of the following code?

<<< @/../code/oop/papers/qz1-q6.cpp

<Mcq :options="['3 4 14', '3 9 14', '3 4 5', '5 9 5', '5 9 12', '5 4 12', '5 4 14', '5 9 14']" answer="g">

<<< @/../code/oop/papers/qz1-q6.out{txt} [Output]

Three parameters, three passing mechanisms:
- `int &a` → reference: `x` becomes 3 + 2 = **5**.
- `int b` → copy: inside, b = 4 + 5 = 9, but `y` in `main` stays **4**.
- `int c[]` → an array parameter is a pointer to `arr[0]`, so `c[0] += b` changes the real array: 5 + 9 = **14**.

(The real output has two spaces between numbers, because the program prints `"  "`.)

</Mcq>

</Q>

<Q id="QZ1.Q7">

What will be the output of the following code?

<<< @/../code/oop/papers/qz1-q7.cpp

<Mcq :options="['7', '8', '9', '10', '11', '12', '13', 'infinite recursion']" answer="f">

<<< @/../code/oop/papers/qz1-q7.out{txt} [Output]

`fun(x, y)` adds `x` to itself `y` times: multiplication by repeated addition. Build from the base case:
fun(3, 0) = 0 → fun(3, 1) = 3 → fun(3, 2) = 6 → fun(3, 3) = 9 → fun(3, 4) = **12**.
It is not infinite: `y` drops by 1 each call and stops at 0.

</Mcq>

</Q>

<Q id="QZ1.Q8">

What will be the output of the following code?

<<< @/../code/oop/papers/qz1-q8.cpp

<Mcq :options="['First', 'Second', 'SecondSecond', 'FirstSecond', 'Compilation error due to ambiguity', 'Runtime error']" answer="e">

<<< @/../code/oop/papers/qz1-q8.out{txt} [Compiler says]

`test(10, 6)` passes two `int`s. Candidates:
1. `test(int, int, int = 10)`: exact match (c takes its default).
2. `test(int, int = 5)`: exact match.
3. `test(double, int = 5)`: needs `int` → `double`, a worse conversion.

Candidates 1 and 2 tie as exact matches, so the call is **ambiguous** and the program does not compile. A default parameter turns a three-parameter function into a two-parameter candidate as well: that is the trap.

</Mcq>

</Q>

<Q id="QZ1.Q9">

What will be the output of the following code?

<<< @/../code/oop/papers/qz1-q9.cpp

<Mcq :options="['Error', '5, 5, 5, hello', '5, 5, 5, 3', 'hello6, 5, 5, 3', 'hello5, 5, 5, 3', '6, 5, 5, 3', '6, 5, 5, hello', '6, 6, 6, 3', '6, 6, 6, hello']" answer="d">

<<< @/../code/oop/papers/qz1-q9.out{txt} [Output]

- `a = 6, 5;` stores 6, because `=` binds before the comma.
- `int b = (6, 5);` and `c = (6, 5);` use the comma operator inside brackets: 5.
- `d = (cout << "hello", 3)` prints `hello` **immediately**, as a side effect, then stores 3.

`hello` therefore appears before the final line prints anything: `hello6,5,5,3`. (The real output has no spaces after the commas; the options on the paper do.)

</Mcq>

</Q>

<Q id="QZ1.Q10">

Where is the memory allocated to a static storage class and to a dynamic array? (Options: Stack, Heap, Data Segment, Queue.)

<FillIn q="Dynamic array: ___" answer="heap|the heap">

`new int[n]` takes memory from the **heap** at run time; it stays until `delete[]`.

</FillIn>

<FillIn q="Static storage class: ___" answer="data segment|the data segment|data">

`static` variables (and globals) live in the **data segment** for the whole run, which is why they keep their values and start at 0. "Queue" is not a memory region at all.

</FillIn>

</Q>
