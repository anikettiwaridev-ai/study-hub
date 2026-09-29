---
title: Mid-semester, September 2024
---

# Mid-semester, September 2024

<PaperHeader :rows="[
  ['Programme', 'B.Tech. (CSE/AI), 2nd year'],
  ['Course code', 'CSN3004 / AIN3002'],
  ['Maximum marks', '30'],
  ['Time allowed', '1.5 hours'],
  ['Note on the paper', 'Attempt all questions. Each question carries six marks. Assume the missing data.'],
]" />

::: info How to use this page
Read the question, write your answer on paper, then open **Solution**. Every program below was compiled and run; the output tab is the program's real output. The small labels above a question show where else it has been asked.
:::

<Q id="S24.Q1a">

In C++, which features enable an object to send data to another object or request to invoke a method and which features overcome the problem of reusability and redundancy? Explain it.

::::: details Solution

**Two features are being asked for.**

1. **Message passing** lets one object send data to another or ask it to run a method. In C++ a "message" is simply a call to a public member function of another object: `printer.print(report)`. The sender needs no knowledge of how `print` works inside; it only knows the method's name and parameters (its signature).
2. **Inheritance** removes repeated code. A derived class gets every member of its base class automatically and only adds what is new, so common code is written once. That solves both *reusability* (use existing code again) and *redundancy* (no duplicate copies of the same code).

::: code-group
<<< @/../code/oop/papers/s24-q1a.cpp [Program]
<<< @/../code/oop/papers/s24-q1a.out{txt} [Output]
:::

`t.sendReport(p)` is message passing: the `Student` part of `t` sends a message to the `Printer`. `Topper` never re-writes `sendReport`; it inherits it, which is the reusability.

::: tip How to score the 2 marks
Name both features, give a one-line definition of each, and point at the exact line in a tiny example. A bare "inheritance" is half an answer.
:::

:::::

</Q>

<Q id="S24.Q1b">

Differentiate between auto, register, static and extern storage classes based on the default value, scope, lifetime and memory location.

::::: details Solution

| Storage class | Default value | Scope | Lifetime | Memory |
|---|---|---|---|---|
| `auto` (ordinary local) | Garbage | The block it is declared in | Until the block ends | Stack |
| `register` | Garbage | The block | Until the block ends | CPU register if possible, else stack |
| `static` (local) | 0 | The block | The whole program run | Data segment |
| `static` (global) | 0 | Only that source file | The whole program run | Data segment |
| `extern` | 0 | Every file that declares it | The whole program run | Data segment |

- **auto**: every plain local variable. It is created each time the block runs and destroyed at the closing brace.
- **register**: a *request* to keep the variable in a CPU register for speed. You cannot take its address with `&`.
- **static**: created once, keeps its value between calls, initialised only the first time.
- **extern**: says "this variable is defined somewhere else, possibly in another file". It declares without creating storage.

::: code-group
<<< @/../code/oop/papers/s24-q1b.cpp [Program]
<<< @/../code/oop/papers/s24-q1b.out{txt} [Output]
:::

`a` is re-created as 0 each call and ends at 1; `s` survives and climbs 1, 2, 3. The global prints 0 because globals start at zero.

:::: warning Modern C++ changed two of these keywords
`auto` stopped being a storage class in C++11; it now means "work out the type for me" (`auto x = 5;` makes an `int`). `register` was removed completely in C++17. Old-style code using them no longer compiles:

::: code-group
<<< @/../code/oop/papers/s24-q1b-keywords.cpp [Old syntax]
<<< @/../code/oop/papers/s24-q1b-keywords.out{txt} [Compiler says]
:::

Still write the table the question asks for, and add one line saying this. It shows you know the language as it is today.
::::

:::::

</Q>

<Q id="S24.Q2">

Create a Class named String that takes two private data members, char \*stringName and stringLength of type integer. Create two string objects named name1 and name2 and initialise these objects through a parameterized dynamic constructor which takes one string as a parameter.

A. In parameterized constructor, these object variables are initialized as follows:
I. stringLength is equal to the length of the string passed as an argument to the constructor.
II. stringName should get memory at run time (use new) and its memory space should be equal to one greater than the length of string passed as an argument to the constructor.
III. Copy the string obtained as a constructor argument into stringName data member.

B. Display these two strings on screen using a public member function.

C. Create an another object named name3 that uses another class member function called joinStrings to join the two strings of name1 and name2 objects in such a way:
i. stringLength of third string object is equal to the sum of the lengths of these two strings.
ii. stringName variable of third string object should get memory at run time (use new) and its memory space should be equal to one greater than the length computed in step i.
iii. The value of stringName variable is the combination of string values of both name1 and name2 objects.

::::: details Solution

::: code-group
<<< @/../code/oop/papers/s24-q2.cpp [Program]
<<< @/../code/oop/papers/s24-q2.out{txt} [Output]
:::

**How each numbered step is met.** Examiners tick these one by one, so label them in your answer the way the comments do.

- **A.I** `stringLength = strlen(s);` counts the characters, not including `'\0'`.
- **A.II** `new char[stringLength + 1]` asks for memory at run time. The `+ 1` is the slot for the terminating `'\0'`: "Hello" has 5 letters but needs 6 bytes.
- **A.III** `strcpy` copies the characters *and* the `'\0'`.
- **B** `display()` is public, so `main` can call it.
- **C.i–iii** `joinStrings` sets the new length, frees the old buffer, allocates `length + 1`, copies the first string with `strcpy`, then **appends** the second with `strcat`.

**Why a default constructor too?** `name3` must exist before `name3.joinStrings(...)` can be called, and the question gives it no string. `String()` makes an empty string (length 0, one byte holding `'\0'`).

::: danger Traps that cost marks here
- `new char[strlen(s)]` without `+ 1`: no room for `'\0'`; `strcpy` writes past the end.
- `strcpy` twice in `joinStrings`: the second call overwrites the first string instead of adding to it. Use `strcpy` then `strcat`.
- Allocating the new buffer without `delete[]` on the old one: the old block is lost for ever (a memory leak).
- Forgetting the destructor. A class that calls `new` should release it in `~String()`.
:::

:::::

</Q>

<Q id="S24.Q3">

Create a class named ABC with two private data members named x and y of type integer. Now create three objects named obj1, obj2, and obj3 of this class. Intialize the data members of obj1 and obj2, and display them on console. The values of data members of obj3 are obtained using the statement obj3=obj1-obj2. In order to work this statement properly, perform the following tasks:
i. Overload the minus operator as a member function of class ABC.
ii. The overloaded function should return the values of the type ABC object.
Finally, display the values of third object obj3 on the console.

::::: details Solution

::: code-group
<<< @/../code/oop/papers/s24-q3.cpp [Program]
<<< @/../code/oop/papers/s24-q3.out{txt} [Output]
:::

**What the compiler does with `obj3 = obj1 - obj2`.** It rewrites the subtraction as a function call on the *left* operand: `obj1.operator-(obj2)`. Inside the function, `x` and `y` belong to `obj1` (that is `*this`), and `other` is `obj2`. So:

| | x | y |
|---|---|---|
| obj1 | 10 | 20 |
| obj2 | 4 | 5 |
| obj3 = obj1 − obj2 | 6 | 15 |

**Why one parameter?** A binary operator has two operands. As a member function, one of them is the object the function is called on, so only the other one is passed in.

**Why return `ABC`?** Part (ii) asks for it, and it is what makes `obj3 = ...` possible: the function builds a new `ABC` holding the differences and hands it back, and the (default) assignment copies it into `obj3`.

::: danger Common mistakes
- Writing `ABC operator-(ABC a, ABC b)` inside the class. A *member* binary operator takes one parameter; two parameters is the *friend* form.
- Changing `x` and `y` inside `operator-` (`x = x - other.x; return *this;`). That silently changes `obj1` as well. Build a new object instead.
- Returning `void`. Then `obj3 = obj1 - obj2` has nothing to assign.
:::

:::::

</Q>

<Q id="S24.Q4a">

Find the output in both cases. If the output is different, state the reasons behind such difference.

::: code-group
<<< @/../code/oop/papers/s24-q4a-ref.cpp [Case 1: int &x]
<<< @/../code/oop/papers/s24-q4a-val.cpp [Case 2: int x]
:::

::::: details Solution

::: code-group
<<< @/../code/oop/papers/s24-q4a-ref.out{txt} [Case 1 output]
<<< @/../code/oop/papers/s24-q4a-val.out{txt} [Case 2 output]
:::

The two programs differ by **one character**: the `&` in the parameter.

**Trace, case 1 (`int &x`, pass by reference).** `x` is another name for `a` itself.

| Call | counter before | counter after | x += counter | a in main |
|---|---|---|---|---|
| 1st | 0 | 1 | 5 + 1 = 6 | **6** |
| 2nd | 1 | 2 | 6 + 2 = 8 | **8** |

**Trace, case 2 (`int x`, pass by value).** `x` is a *copy* of `a`. The copy becomes 6, then 7, but each copy is thrown away when the function returns. `a` stays **5** both times.

**Reasons for the difference.**
1. With `&`, the function works on the caller's variable, so changes stay after the call.
2. Without `&`, the function gets a private copy on its own stack frame; changes to it vanish when the function ends.
3. `counter` is `static` in both programs: it is created once, lives in the data segment, and keeps its value between calls. That is why the second call adds 2, not 1. (In case 2 it still counts 1, 2; you just never see it.)

::: tip How to score the 4 marks
Two outputs (1 mark each) and the reasons (2 marks). The reason must mention *both* ideas: `&` vs copy, **and** what `static` does to `counter`.
:::

:::::

</Q>

<Q id="S24.Q4b">

How pass-by reference differs from pass-by pointers parameters passing approach to functions.

::::: details Solution

| | Pass by reference `f(int &r)` | Pass by pointer `f(int *p)` |
|---|---|---|
| What is passed | An alias: another name for the same variable | The variable's address, copied into a pointer |
| Call looks like | `f(a)` | `f(&a)` |
| Inside the function | Use `r` directly | Dereference: `*p` |
| Can it be null? | No, a reference must refer to something | Yes, so check `if (p != nullptr)` |
| Can it be re-pointed? | No, it stays bound to one variable | Yes, `p = &b;` is allowed |
| Must be initialised? | Yes, at declaration | No |
| Extra memory | None needed in principle | A pointer variable (8 bytes on 64-bit) |

Both let the function change the caller's variable. References are simpler and safer; pointers are needed when "no object" is a valid answer or the target must change.

::: code-group
<<< @/../code/oop/papers/s24-q4b.cpp [Program]
<<< @/../code/oop/papers/s24-q4b.out{txt} [Output]
:::

:::::

</Q>

<Q id="S24.Q5a">

We have a class Time and one object of Time class "t" and suppose we want to assign the total time of object "t" to any integer variable say "duration" then the statement below is: Duration=t; where t is object and duration is of basic data type. Which type conversion is used in this scenario? Explain a suitable C++ example of this type conversion.

::::: details Solution

**Class type to basic type** conversion. The object is on the right, the `int` on the left, so the class must know how to turn itself into an `int`. That is done with a **conversion operator** (also called a casting operator function) inside the class:

```cpp
operator int() const { ... return some int; }
```

Rules for writing it: it must be a member function, it has **no return type** written in front (the name `int` already says it), and it takes **no parameters**.

::: code-group
<<< @/../code/oop/papers/s24-q5a.cpp [Program]
<<< @/../code/oop/papers/s24-q5a.out{txt} [Output]
:::

`duration = t;` makes the compiler call `t.operator int()`, which returns 2 × 60 + 30 = 150.

::: tip The three conversions, side by side
- Basic → class: a constructor taking one argument, `Time(int minutes)`.
- Class → basic: a conversion operator, `operator int()`.
- Class → class: a conversion operator in the source **or** a constructor in the destination.

Learn this table; one of the three has appeared in three of the four mid-semester papers.
:::

:::::

</Q>

<Q id="S24.Q5b">

Write a program to compute the factorial of a number.

::::: details Solution

::: code-group
<<< @/../code/oop/papers/s24-q5b.cpp [Program]
<<< @/../code/oop/papers/s24-q5b.in{txt} [Input]
<<< @/../code/oop/papers/s24-q5b.out{txt} [Output]
:::

n! = 1 × 2 × … × n. Start `fact` at 1, multiply by every number from 2 to n. Because the loop does nothing for n = 0 or 1, both correctly give 1.

::: danger Small things that lose the 2 marks
- `int fact`: 13! already overflows an `int`. `long long` is safe up to 20!.
- Starting `fact` at 0: everything multiplies to 0.
- No handling of negative input.
- Writing only the function, without `main` and the input/output.
:::

:::::

</Q>
