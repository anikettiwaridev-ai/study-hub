---
title: Mid-semester, October 2025
---

# Mid-semester, October 2025

<PaperHeader :rows="[
  ['Programme', 'B.Tech. (CSE/AI), 2nd year'],
  ['Course code', 'CSN3004 / AIN3002'],
  ['Maximum marks', '30'],
  ['Time allowed', '1.5 hours'],
  ['Note on the paper', 'Attempt all questions. Each question carries six marks. Assume the missing data.'],
]" />

::: info The paper closest to yours
This is the regular paper from last year's odd semester, the same point in the course you are at now. Its shape (two 3-mark concept questions, an output question with three programs, one 9-mark class, a copy-constructor question, a library-function question and a `modifyValue` pair) is the model for the [mock paper](../mock-mst).
:::

<Q id="O25.Q1a">

A class hides its data members but provides public methods to access and modify them. What principle of OOP does this illustrate? Explain why it is important with an example.

::::: details Solution

**Encapsulation** (with **data hiding**). Encapsulation bundles the data and the functions that work on it into one unit, the class, and keeps the data `private` so the outside world can reach it only through `public` methods.

**Why it matters.**
1. **Protection:** nobody can put the object into an invalid state; `balance = -500` is impossible from outside.
2. **Validation in one place:** every change goes through a method that can check it.
3. **Freedom to change the inside:** the class can change how it stores data without breaking code that uses it, because that code only sees the methods.

::: code-group
<<< @/../code/oop/papers/o25-q1a.cpp [Program]
<<< @/../code/oop/papers/o25-q1a.out{txt} [Output]
:::

`balance` is private; `deposit`, `withdraw` and `getBalance` are the only doors, and they refuse bad requests.

::: danger Abstraction is not the answer here
Abstraction is about showing *what* an object does and hiding *how* (design level). This question describes hidden data plus public access methods, which is encapsulation (implementation level). If a question describes both "essential operations exposed" and "internals hidden", as Quiz 1 Q5 did, the answer is both.
:::

:::::

</Q>

<Q id="O25.Q1b">

If a method in a parent class is reused by a child class without any change, but the child class adds new methods of its own, which OOP concept is being demonstrated? Explain briefly. With example

::::: details Solution

**Inheritance** (here, single inheritance). The child (derived) class receives the parent's (base's) members automatically, reuses them unchanged, and extends the class with its own new methods. This is the "is-a" relationship: a `Car` is a `Vehicle`.

::: code-group
<<< @/../code/oop/papers/o25-q1b.cpp [Program]
<<< @/../code/oop/papers/o25-q1b.out{txt} [Output]
:::

`start()` is written once in `Vehicle` and reused by `Car` as-is (reusability); `playMusic()` is new in `Car` (extension).

::: tip Not overriding
The method is reused *without change*. If the child redefined it, that would be overriding (run-time polymorphism), a different answer.
:::

:::::

</Q>

<Q id="O25.Q2a">

How 'comma' as separator is different from 'comma' as an operator. Justify your answer by considering below given cases. Also, find the output in each case and mention why parentheses matter in case of 'comma' operator?

::: code-group
<<< @/../code/oop/papers/o25-q2a-case1.cpp [Case 1]
<<< @/../code/oop/papers/o25-q2a-case2.cpp [Case 2]
<<< @/../code/oop/papers/o25-q2a-case3.cpp [Case 3]
:::

::::: details Solution

As a **separator**, the comma only lists things. `int a, b;` declares two variables and `f(x, y)` passes two arguments. There is no value involved.

As an **operator**, `(x, y)` evaluates `x`, discards the result, then evaluates `y`, and the whole expression takes `y`'s value. It has the lowest precedence of any operator, lower even than `=`.

::: code-group
<<< @/../code/oop/papers/o25-q2a-case1.out{txt} [Case 1 output]
<<< @/../code/oop/papers/o25-q2a-case2.out{txt} [Case 2 output]
<<< @/../code/oop/papers/o25-q2a-case3.out{txt} [Case 3 output]
:::

**Case 1 prints 5.** `=` binds tighter than `,`, so the line is read as `(a = 5), 4;`. `a` becomes 5; the 4 is evaluated and thrown away.

**Case 2 prints 4.** The parentheses make the comma operator run first. `(5, 4)` evaluates to 4, which is then assigned.

**Case 3 does not compile.** In a declaration the comma is a separator, so the compiler reads `4` as the name of a second variable. A name cannot start with a digit.

**Why parentheses matter:** without them, `=` always wins over the comma operator. Parentheses are the only way to make the comma decide the value.

::: danger
`int a = 5, 4;` is not a trick output question. It is a compile error, and writing an output for it loses the marks.
:::

:::::

</Q>

<Q id="O25.Q2b">

Find the output for the below given code. Also, justify the reason behind your output.

<<< @/../code/oop/papers/o25-q2b.cpp

::::: details Solution

<<< @/../code/oop/papers/o25-q2b.out{txt} [Output]

**The key line is `static int s = n;`.** A static local is initialised **only once**, the first time control reaches it. Here that first time is `calculate(5)`, so `s` starts at 5. On the later calls the initialisation line is skipped completely, even though `n` is now 10 and 15.

| Call | n | s before `s += 2` | s after | a = n + 2 |
|---|---|---|---|---|
| calculate(5) | 5 | 5 (initialised now) | 7 | 7 |
| calculate(10) | 10 | 7 (kept) | 9 | 12 |
| calculate(15) | 15 | 9 (kept) | 11 | 17 |

`a` is an ordinary local, rebuilt from `n` every call; `s` lives in the data segment for the whole program and remembers.

::: danger The trap
Most students re-initialise `s` from `n` each time and write `s = 12` and `s = 17`. A static's initialiser runs once, **even when it is a variable** like `n`, not only when it is a constant.
:::

:::::

</Q>

<Q id="O25.Q3a">

Create a Class named ComplexNumber that takes two private data members named real and imaginary of data type int. Create three objects named complex1, complex2 and complex3 of this class and dynamically initialize both complex1 through a parameterized constructor; and complex2 through a member function of this class. The third complex number complex3 should be created by copying the values of Complex1 into it; these values should be assigned through an appropriate constructor only. Display these complex1, complex2 and complex3 on screen using a public member function named displayComplexNumber. Create a function named addComplexNumbers (does not belong to ComplexNumber class) that generates a new complex number complex4 by adding three complex numbers (complex1, complex2 and complex3) and return that number to the user. Please note: In complex4, values of real are equal to sum of real values of complex1, complex2 and complex3, and value of imaginary is equal to the sum of imaginary values of complex1, complex2 and complex3. Display the fourth complex number on the screen.

::::: details Solution

This is **word for word Assignment 5 Q8**. It is worth 9 marks, the biggest single question in any paper we have.

::: code-group
<<< @/../code/oop/papers/o25-q3a.cpp [Program]
<<< @/../code/oop/papers/o25-q3a.in{txt} [Input]
<<< @/../code/oop/papers/o25-q3a.out{txt} [Output]
:::

**Reading the specification phrase by phrase.**

| Phrase in the question | What it means in code |
|---|---|
| "dynamically initialize … complex1 through a parameterized constructor" | *Dynamic initialisation* = the values are known only at run time. Read them with `cin`, then pass them to `ComplexNumber(int, int)`. |
| "complex2 through a member function" | Create it with the default constructor, then call a setter such as `setComplexNumber(r, i)`. |
| "complex3 … copying the values of complex1 … through an appropriate constructor only" | The **copy constructor**: `ComplexNumber complex3(complex1);`. Not `complex3 = complex1;` on an existing object, which is assignment. |
| "displayComplexNumber" | Use exactly this name. |
| "addComplexNumbers (does not belong to ComplexNumber class)" | A non-member function. It needs `real` and `imaginary`, which are private, so declare it a **friend** (or add getters). |
| "generates a new complex number complex4 … and return that number" | Build a new object inside and **return it by value**. |

**Marks usually go:** class and constructors 3, member-function initialisation and copy constructor 2, friend add function 3, display and `main` 1.

::: danger Where students lose marks
- Using `complex3 = complex1;` after `ComplexNumber complex3;`. That is the assignment operator, not "a constructor only".
- Writing the copy constructor as `ComplexNumber(ComplexNumber c)` (by value). It must be `const ComplexNumber &`, or the compiler rejects it.
- Making `addComplexNumbers` a member function. The question says it does not belong to the class.
- Hard-coding values for complex1. "Dynamically initialise" wants run-time input.
:::

:::::

</Q>

<Q id="O25.Q3b">

Let us suppose we create four objects named A, B, C and D of the ABC class as given below. Which of these objects will be initialized by calling the copy constructor. Justify your answer with valid reasons.

```cpp
ABC A(100);
ABC B(A);
ABC C=A;
ABC D;
D=A;
```

::::: details Solution

**B and C** are initialised by the copy constructor. A and D are not.

| Line | What runs | Why |
|---|---|---|
| `ABC A(100);` | Parameterized constructor | Created from an `int` |
| `ABC B(A);` | **Copy constructor** | A new object is created from an existing object (direct initialisation) |
| `ABC C = A;` | **Copy constructor** | Still a *new* object being created from `A`; the `=` here is initialisation syntax, not assignment (copy initialisation) |
| `ABC D;` | Default constructor | Created with no arguments |
| `D = A;` | **Copy assignment operator** | `D` already exists, so nothing is constructed; its values are overwritten |

A class that prints from each special function proves it:

::: code-group
<<< @/../code/oop/papers/o25-q3b.cpp [Program]
<<< @/../code/oop/papers/o25-q3b.out{txt} [Output]
:::

::: tip The one question to ask
For any `=` involving objects: **does the left-hand object already exist?** If it is being declared on this line, it is construction (copy constructor). If it was made earlier, it is assignment.
:::

:::::

</Q>

<Q id="O25.Q4a">

Can a user-defined function have the same name as a predefined function in a program? What happens if it does? Explain with reasoning. Also, write some predefined functions.

::::: details Solution

**Yes, and what happens depends on the parameter list.**

**1. Same name, different parameters: overloading.** Both versions exist; the compiler picks the best match for each call. Here `pow(int, int)` is ours and `pow(double, …)` is the library's:

::: code-group
<<< @/../code/oop/papers/o25-q4a-overload.cpp [Program]
<<< @/../code/oop/papers/o25-q4a-overload.out{txt} [Output]
:::

**2. Same name and same parameters, different return type: compile error.** The return type is not part of the signature, so the compiler sees two conflicting declarations of one function:

::: code-group
<<< @/../code/oop/papers/o25-q4a-error.cpp [Program]
<<< @/../code/oop/papers/o25-q4a-error.out{txt} [Compiler says]
:::

**3. Exactly the same signature** (for example writing your own `double sqrt(double)` after `#include <cmath>`): GCC compiles it and your version silently replaces the library one. The standard reserves library names, so this is undefined behaviour; never rely on it.

**The safe way:** put your function in your own namespace (or skip `using namespace std;` and call library functions as `std::...`). Then both names coexist without any clash:

::: code-group
<<< @/../code/oop/papers/o25-q4a-namespace.cpp [Program]
<<< @/../code/oop/papers/o25-q4a-namespace.out{txt} [Output]
:::

**Some predefined functions:** `sqrt()`, `pow()`, `abs()`, `ceil()`, `floor()` (from `<cmath>`); `strlen()`, `strcpy()`, `strcat()`, `strcmp()` (from `<cstring>`); `toupper()`, `isdigit()` (from `<cctype>`); `rand()`, `exit()` (from `<cstdlib>`); `max()`, `min()`, `swap()`, `sort()` (from `<algorithm>`).

:::::

</Q>

<Q id="O25.Q4b">

Find the output of below given code snippets. If the output is different, state the reasons behind such difference.

::: code-group
<<< @/../code/oop/papers/o25-q4b-ref.cpp [Case 1: int &x]
<<< @/../code/oop/papers/o25-q4b-val.cpp [Case 2: int x]
:::

::::: details Solution

::: code-group
<<< @/../code/oop/papers/o25-q4b-ref.out{txt} [Case 1 output]
<<< @/../code/oop/papers/o25-q4b-val.out{txt} [Case 2 output]
:::

`counter` is an **ordinary** local this time: it is set to 5 and becomes 6 on *every* call. So each call adds exactly 6.

- **Case 1 (`int &x`)**: `x` is `a` itself. 15 + 6 = **21**, then 21 + 6 = **27**.
- **Case 2 (`int x`)**: `x` is a copy. The copy becomes 21, then is destroyed; `a` stays **15** both times.

**Reason:** pass by reference changes the caller's variable; pass by value changes a private copy that disappears when the function returns.

::: danger Compare with September 2024 Q4a
There `counter` was `static`, so the second call added 2 instead of 1. Here it is not static, so both calls add the same 6. Always check for the word `static` before tracing.
:::

:::::

</Q>
