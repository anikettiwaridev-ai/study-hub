---
title: Unit 2 · Programming basics
---

# Unit 2 · Programming basics

Variables and storage, constants and keywords, data types, operators, precedence, type casting, functions and parameter passing, default arguments, overloading, arrays and dynamic memory.

::: info How this unit is examined
This is the **output-tracing** unit. Every mid-semester paper has a `modifyValue` pair (value vs reference, with or without `static`), and the comma operator has appeared in four papers and quizzes. Quizzes turn the same traces into MCQs whose wrong options are the common mistakes. The method at the bottom of this page is how you avoid them.
:::

## Program anatomy

```cpp
#define PI 3.14        // macro: plain text substitution BEFORE compiling
#include <iostream>    // the preprocessor pastes the header in
using namespace std;   // lets you write cout instead of std::cout

int main() {           // execution ALWAYS starts here
    cout << "Hello";   // cout is an OBJECT of class ostream; << is insertion
    return 0;
}
```

`source.cpp → preprocessor → compiler → .obj → linker → .exe`. **Compilation** reads top to bottom (which is why a function must be declared before it is called); **execution** starts at `main()`.

| Term | Meaning |
|---|---|
| `#` | Preprocessor directive. Not C++ code; handled before compilation |
| namespace | A named scope that stops name clashes; `std` is the standard library's |
| `::` | Scope resolution: `std::cout`, `ClassName::member`, `::x` for the global `x` |
| keyword | A reserved word (`int`, `class`, `static`, `return` …); cannot be a name |
| identifier | A name you choose: letters, digits, `_`; must not start with a digit |

## Data types

| Type | char | bool | short | int | float | long long | double | pointer |
|---|---|---|---|---|---|---|---|---|
| Bytes | 1 | 1 | 2 | 4 | 4 | 8 | 8 | 8 (64-bit) |

`long` is 4 bytes on Windows and 8 on Linux. Ranges for n bits: signed −2ⁿ⁻¹ to 2ⁿ⁻¹ − 1 (`char`: −128 to 127), unsigned 0 to 2ⁿ − 1.

### Constants: `#define`, `const`, `constexpr`

| | When fixed | Type-checked | Notes |
|---|---|---|---|
| `#define PI 3.14` | Before compiling (text swap) | No | No type, no scope |
| `const int c = x;` | At run time, then read-only | Yes | Must be initialised where declared |
| `constexpr int c = 10;` | At compile time | Yes | Initialiser must be a compile-time constant |

```cpp
const int c;      // ERROR: uninitialised const
const int b = 30;
b = 40;           // ERROR: assignment of read-only variable
```

## Variables: storage, scope, lifetime, default value

| Variable | Memory | Default | Scope | Lifetime |
|---|---|---|---|---|
| Local | Stack | Garbage | Its block | Until the block ends |
| Global | Data segment | 0 | Whole program (after its declaration) | Whole program |
| Static local | Data segment | 0 | Its block only | Whole program |
| Dynamic (`new`) | Heap | Garbage | Reached through a pointer | Until `delete` |

```txt
 STACK            locals, parameters, call frames   freed automatically on return
 HEAP             new / new[]                       freed only by delete / delete[]
 DATA SEGMENT     globals and statics               live for the whole run, start at 0
 CODE SEGMENT     function bodies (one copy each)   live for the whole run
```

::: danger A static local is still local
`static` changes the **lifetime** (whole program) and where it lives (data segment), not the **scope**. Another function still cannot see it:

```cpp
void fun() { static int s; }
void de()  { cout << s; }   // ERROR: 's' was not declared in this scope
```
:::

::: danger A static local is initialised once, even from a variable
`static int s = n;` takes `n`'s value on the **first** call only; later calls skip the line entirely (Oct 2025 Q2b).
:::

**Name lookup** goes local → enclosing block → global. A parameter or local named `x` **hides** (shadows) a global `x`; write `::x` to reach the global. A parameter passed by value is a fresh copy every call; a global changed directly inside a function keeps the change.

**Storage-class keywords** (Sep 2024 Q1b): `auto`, `register`, `static`, `extern`. In modern C++, `auto` means type deduction, and `register` was removed in C++17; see the [Sep 2024 solution](../papers/mst-2024-sep#q1b) for the full table.

## Operators

**By number of operands.** Unary (one: `++a`, `-a`, `!a`, `~a`), binary (two: `a + b`), ternary (three: only `?:`).

**By operation.** Arithmetic `+ - * / %` · relational `< <= > >= == !=` · logical `&& || !` · bitwise `& | ^ ~ << >>` · assignment `= += -= …` · conditional `?:` · special: comma `,`, scope resolution `::`, `sizeof`.

### Precedence and associativity (high to low)

| Operators | Associativity |
|---|---|
| `::` | — |
| `()` `[]` `.` `->` postfix `a++` `a--` | left to right |
| prefix `++a` `--a`, `!` `~` unary `-` `sizeof` casts | **right to left** |
| `*` `/` `%` | left to right |
| `+` `-` | left to right |
| `<<` `>>` | left to right |
| `<` `<=` `>` `>=` | left to right |
| `==` `!=` | left to right |
| `&` then `^` then `\|` | left to right |
| `&&` then `\|\|` | left to right |
| `?:` | **right to left** |
| `=` `+=` `-=` … | **right to left** |
| `,` (comma operator), the **lowest** | left to right |

::: warning Precedence is not order of evaluation
Precedence decides how an expression is *grouped*. It does not decide *when* each part runs. For `+`, `-`, `*` and most others, C++ does not promise left-to-right evaluation of the operands. Only `&&`, `||`, `?:` and `,` guarantee an order.
:::

### Pre and post increment

```cpp
c = ++a;   // a = a + 1; then c = a;   (hand over the NEW value)
c = a++;   // c = a; then a = a + 1;   (hand over the OLD value)
```

::: code-group
<<< @/../code/oop/notes/u2-increment-defined.cpp [Program]
<<< @/../code/oop/notes/u2-increment-defined.out{txt} [Output]
:::

::::: danger Changing a variable twice in one expression is undefined behaviour
`b = a++ + ++a;` and `x = ++x + x++ + x++;` modify the same variable more than once with no sequence point in between. The standard gives them **no defined answer**, and GCC warns `operation on 'a' may be undefined`. Papers still ask them. Give the left-to-right "textbook" answer **and** one line saying it is undefined behaviour.

::: code-group
<<< @/../code/oop/notes/u2-drill1.cpp [Program]
<<< @/../code/oop/notes/u2-drill1.out{txt} [GCC printed]
:::

Textbook: `a++` gives 5 (a → 6), `++a` makes a = 7 and gives 7, b = 5 + 7 = 12.
:::::

### The comma: separator or operator

- **Separator**: in declarations and argument lists: `int a = 3, b = 5;`, `f(x, y)`. No value.
- **Operator**: `(e1, e2, e3)` evaluates left to right, each part completely finished before the next (**a sequence point**), and the value is the **last** one. It has the lowest precedence of all, below `=`.

```cpp
a = 5, 4;        // (a = 5), 4;      a is 5
a = (5, 4);      // brackets first:  a is 4
int a = 5, 4;    // COMPILE ERROR: in a declaration the comma is a separator,
                 // so 4 would be a second variable name
b = (a++, ++a);  // well defined, because the comma is a sequence point
```

::: code-group
<<< @/../code/oop/notes/u2-drill3.cpp [Side effect]
<<< @/../code/oop/notes/u2-drill3.out{txt} [Output]
:::

`cout << "abc"` runs for its side effect (printing), the comma throws its value away, and `a` becomes 2: output `abc2`.

### Conditional operator `?:`

::: code-group
<<< @/../code/oop/notes/u2-ternary.cpp [Program]
<<< @/../code/oop/notes/u2-ternary.out{txt} [Output]
:::

### Bitwise, worked

```txt
a = 6 -> 110     a & b = 010 = 2     ~a     = -7    (~n is always -(n+1))
b = 3 -> 011     a | b = 111 = 7     a << 1 = 12    (x 2)
                 a ^ b = 101 = 5     a >> 1 = 3     (/ 2)
```

## Type casting

- **Implicit** (automatic): the compiler converts, usually from a smaller to a larger type (`int` → `double`). In mixed arithmetic, the smaller operand is promoted.
- **Explicit** (a cast you write): `(double)a` in C style, `static_cast<double>(a)` in C++ style.

::: code-group
<<< @/../code/oop/notes/u2-casting.cpp [Program]
<<< @/../code/oop/notes/u2-casting.out{txt} [Output]
:::

`int t = 9.99;` stores **9**: conversion to an integer **cuts off** the fraction, it does not round. `7 / 2` is integer division (3); make one operand a `double` to get 3.5. Casting the result, `(double)(7 / 2)`, is too late: 3.0.

## Functions

### Above or below `main`

A function must be **declared** before it is called. Defined above `main`, the definition is also the declaration. Defined below `main`, a **prototype** is needed above:

::: code-group
<<< @/../code/oop/notes/u2-below-main.cpp [With prototype]
<<< @/../code/oop/notes/u2-below-main.out{txt} [Output]
<<< @/../code/oop/notes/u2-below-main-error.cpp [Without]
<<< @/../code/oop/notes/u2-below-main-error.out{txt} [Compiler says]
:::

### The four signature shapes

::: code-group
<<< @/../code/oop/notes/u2-signatures.cpp [Program]
<<< @/../code/oop/notes/u2-signatures.out{txt} [Output]
:::

### Passing parameters

| | Syntax | What the function gets | Changes the caller? |
|---|---|---|---|
| By value | `f(int a)` | A copy | No |
| By reference | `f(int &a)` | An alias for the caller's variable | Yes |
| By pointer | `f(int *a)` | A copy of the address | Yes, through `*a` |
| By const reference | `f(const T &a)` | An alias that cannot be changed | No, and no copy is made |

A reference must be initialised, cannot be re-seated and cannot be null. A pointer can be all three. **Large and read-only → `const &`** (Quiz 1 Q3).

### Default arguments

:::: danger Rule 1: defaults fill from the right, with no gaps
```cpp
void fun(int a = 10, int b);   // ERROR
void fun(int a, int b = 10);   // fine
```
If `a` had a default and `b` did not, `fun(7)` could not say which parameter 7 is for.

::: code-group
<<< @/../code/oop/notes/u2-default-order.cpp [Program]
<<< @/../code/oop/notes/u2-default-order.out{txt} [Compiler says]
:::
::::

::: danger Rule 2: the default goes in the declaration only
If the function is declared above `main` and defined below it, put the default in the declaration (the prototype the caller sees). Writing it in both places is a redefinition error.
:::

### Overloading and its ambiguities

The compiler ranks each candidate: **exact match** > **promotion** (`char`/`short`/`bool` → `int`, `float` → `double`) > **standard conversion** (`int` → `double`, `int` → `float`, `double` → `float` …). One best candidate is called; a tie is a compile error.

::: code-group
<<< @/../code/oop/notes/u2-overload.cpp [Resolved]
<<< @/../code/oop/notes/u2-overload.out{txt} [Output]
:::

`change('A')` calls the `int` version and prints 65: `char` → `int` is a promotion, which beats `char` → `double`.

**Ambiguity 1, conversion ties.** With only `float` and `double` versions, `change(10)` needs `int` → `float` or `int` → `double`, both standard conversions:

::: code-group
<<< @/../code/oop/notes/u2-overload-ambiguous.cpp [Program]
<<< @/../code/oop/notes/u2-overload-ambiguous.out{txt} [Compiler says]
:::

**Ambiguity 2, a default argument.** `change(int, int = 10)` is also a one-argument candidate:

::: code-group
<<< @/../code/oop/notes/u2-default-ambiguous.cpp [Program]
<<< @/../code/oop/notes/u2-default-ambiguous.out{txt} [Compiler says]
:::

This is Quiz 1 Q8 and Assignment 5 Q9.

### inline and recursion

`inline` is a **request** to paste the function body at each call instead of jumping to it. The compiler may refuse (recursive functions, large bodies). Member functions defined inside a class are inline automatically.

For recursion, **build bottom-up from the base case**; never trace top-down.

::: code-group
<<< @/../code/oop/notes/u2-drill9.cpp [Program]
<<< @/../code/oop/notes/u2-drill9.out{txt} [Output]
:::

fun(0) and fun(−1) print nothing. fun(1) = `1` · fun(−1) · `2` · fun(0) · `2` = **122**. fun(2) = `2` · fun(0) · `3` · fun(1) · `4` = **231224**. fun(3) = `3` · fun(1) · `4` · fun(2) · `6` = **312242312246**. fun(4) = `4` · fun(2) · `5` · fun(3) · `8` = 4 · 231224 · 5 · 312242312246 · 8, which is the output above.

## Arrays and pointers

::: code-group
<<< @/../code/oop/notes/u2-sizes.cpp [Program]
<<< @/../code/oop/notes/u2-sizes.out{txt} [Output]
:::

- An array is **not** a pointer: `sizeof(arr)` in `main` is 16 (4 ints).
- In most expressions the array name **decays** to a pointer to its first element: `int *p = arr;`.
- **An array parameter is always a pointer.** `int arr[]`, `int arr[4]` and `int *arr` are the same parameter, so `sizeof` inside the function gives 8. That is why the **size must be passed separately** (syllabus: "importance of passing size"; Remedial 2024 Q2).
- To keep the size, take a reference to the array: `int (&arr)[4]`, with the brackets. `int &arr[4]` means "array of references", which is illegal.

### Dynamic arrays

```cpp
int *arr = new int[n];   // size decided at run time, on the heap
delete[] arr;            // brackets go with the keyword: delete[] arr, never delete arr[]
arr = nullptr;           // so the pointer cannot dangle
```

| Problem | What happened | Fix |
|---|---|---|
| **Memory leak** | The last pointer to a heap block was lost before `delete[]` | `delete[]` before the pointer goes away |
| **Dangling pointer** | The block was freed but the pointer still holds its address | Set it to `nullptr` after `delete[]` |
| **Double free** | The same block is deleted twice (often via a shallow copy) | Deep copy; one owner per block |
| **Overflow** | Writing past the end of a fixed array | Use the real size; allocate `new int[n]` |

`new` pairs with `delete`, `new[]` with `delete[]`; mixing them is undefined behaviour. See [Assignment 3 Q6 to Q9](../assignments/a3#q6) and [End-sem Q6b](../papers/endsem-2024#q6b).

## Control flow in one screen

- `while` and `for` check **before** each pass (may run 0 times); `do { } while (…);` checks **after** (runs at least once) and needs the final `;`.
- All three parts of `for (;;)` are optional; a missing condition means "true for ever".
- `switch` works on integral values (`int`, `char`, `enum`, `bool`), not `float` or `string`. Case labels must be constants. Without `break`, execution **falls through** into the next case.
- `continue` skips the rest of this pass; `break` leaves the loop (or the `switch`).
- Every non-zero value is true; only 0 is false. `if (a = 5)` **assigns** 5 and is always true; you meant `==`.

## How to trace any output question

1. Draw the memory map: stack, heap, data segment, with defaults (garbage / 0 / 0).
2. Circle every `static`: initialised once, survives calls.
3. Rewrite every `++` and `--` as two plain statements before evaluating.
4. For a comma: separator or operator? If operator, `=` binds tighter and the result is the rightmost value.
5. For recursion, build bottom-up from the base case.
6. For a `for` loop with function calls, write a row for each slot: init, condition, body, update.
7. Name lookup: local → enclosing block → global; watch for a parameter shadowing a global.
8. Check for a compile error **first** (`int a = 5, 4;`, ambiguous overloads, private access). "Error" is often the right option.

## Quick check

<Drill n="1" tag="Output" from="v2 drill 4">

```cpp
int a = 8, b;
b = (a++, ++a, a >> 2);
cout << a << " " << b;
```

<Mcq :options="['9 2', '10 2', '10 3', '9 1', 'Undefined behaviour']" answer="b">

<<< @/../code/oop/notes/u2-drill4.out{txt} [Output]

The comma is a sequence point, so this is well defined: a → 9 → 10, then 10 >> 2 = `1010` shifted twice = `10` = 2.

</Mcq>

</Drill>

<Drill n="2" tag="Output" from="v2 drill 6">

```cpp
int fun() { static int num = 16; return num--; }
int main() {
    for (fun(); fun(); fun())
        cout << fun() << " ";
}
```

<Mcq :options="['16 13 10 7 4 1', '15 12 9 6 3', '14 11 8 5 2', '14 11 8 5 2 -1', 'Infinite loop']" answer="c">

<<< @/../code/oop/notes/u2-drill6.out{txt} [Output]

All four slots call the same `fun`, and `num` is static. Each call returns the current value, then decreases it. Log every call: init returns 16; condition 15 (true); body **14**; update 13; condition 12; body **11**; update 10; condition 9; body **8**; update 7; condition 6; body **5**; update 4; condition 3; body **2**; update 1; condition returns **0**, which is false, so the loop stops.

</Mcq>

</Drill>

<Drill n="3" tag="Output" from="v2 drill 7">

```cpp
int a = 0, b = 0;
void printA() {
    static int a = 2;
    int b = 1;
    a += ++b;
    cout << a << " " << b << endl;
}
int main() {
    static int a = 1;
    printA();
    a = a + 1;
    printA();
    cout << a << " " << b << endl;
}
```

<FillIn q="What are the three lines printed? Write them as: line1 / line2 / line3" answer="4 2 / 6 2 / 2 0|4 2/6 2/2 0|42/62/20">

<<< @/../code/oop/notes/u2-drill7.out{txt} [Output]

Three different `a`s: the global (0), `printA`'s static (starts 2), `main`'s static (starts 1). Call 1: static a = 2 + 2 = 4, b = 2. `main`'s a becomes 2. Call 2: static a keeps 4, b is a fresh local again, so a = 4 + 2 = 6. Finally `main` prints its own a (2) and, having no local b, the **global** b (0).

</FillIn>

</Drill>

<Drill n="4" tag="Output">

```cpp
int a;
a = 5, 4;
cout << a;
```

<Mcq :options="['4', '5', '9', 'Compile error']" answer="b">

`=` binds tighter than the comma: `(a = 5), 4;`. It would be 4 only as `a = (5, 4);`, and a compile error as `int a = 5, 4;`.

</Mcq>

</Drill>

<Drill n="5" tag="Fill in">

<FillIn q="Inside `void f(int arr[])`, `sizeof(arr)` on a 64-bit machine is ____ bytes." answer="8|8 bytes">

The parameter is really `int *arr`, and a pointer is 8 bytes on 64-bit. The array's length must be passed separately.

</FillIn>

</Drill>

<Drill n="6" tag="Concept">

`void change(float); void change(double);` What does `change(10);` do?

<Mcq :options="['Calls change(float)', 'Calls change(double)', 'Compile error: ambiguous', 'Runtime error']" answer="c">

`int` → `float` and `int` → `double` are both standard conversions; neither is better, so the call is ambiguous. (`change(10.0)` or `change(10.0f)` would be exact matches.)

</Mcq>

</Drill>

<Drill n="7" tag="Fill in">

<FillIn q="`int x = 7.9;` stores the value ____." answer="7">

Converting to an integer truncates (cuts off the fraction); it never rounds.

</FillIn>

</Drill>
