---
title: Mid-semester remedial, October 2024
---

# Mid-semester remedial, October 2024

<PaperHeader :rows="[
  ['Programme', 'B.Tech. (CSE/AI), 2nd year'],
  ['Course code', 'CSN3004 / AIN3002'],
  ['Maximum marks', '30'],
  ['Time allowed', '1.5 hours'],
  ['Note on the paper', 'Attempt all questions. Each question carries six marks. Assume the missing data.'],
]" />

::: info The same skeleton as September 2024
This re-sit copies the September paper question for question: a concept opener, a dynamic-constructor class, a member operator, a `modifyValue` output pair, a conversion and a two-mark program. Only the data, names and operator change. That is the strongest evidence that her papers recycle.
:::

<Q id="R24.Q1a">

In C++, which features enables, calling of a function of same name but with different input arguments more than on time in the program? Explain it.

::::: details Solution

**Function overloading**, a form of **compile-time (static) polymorphism**. Several functions share one name but differ in their parameter list: the number of parameters, their types, or their order. The compiler looks at the arguments of each call and picks the matching version before the program runs.

::: code-group
<<< @/../code/oop/papers/r24-q1a.cpp [Program]
<<< @/../code/oop/papers/r24-q1a.out{txt} [Output]
:::

The compiler's choice, in order of preference: an **exact** match, then a **promotion** (such as `char` → `int`, `float` → `double`), then a **standard conversion** (such as `int` → `double`). If two candidates tie at the same level, the call is ambiguous and does not compile.

::: danger Overloads must differ in parameters, not return type
`int area(int)` and `double area(int)` cannot both exist. The return type is not part of the signature, so the compiler reports a redefinition.
:::

:::::

</Q>

<Q id="R24.Q1b">

How comma as a "separator" is different from comma as an "operator"? In the code snippet given below, clearly locate where comma is used as a separator or as an operator. Also, find the output of this code.

<<< @/../code/oop/papers/r24-q1b.cpp

::::: details Solution

**Separator**: the comma only lists things, like the commas in a declaration (`int a = 3, b = 5;`) or between function arguments. It produces no value.

**Operator**: `(e1, e2)` evaluates `e1`, throws its value away, then evaluates `e2`; the whole thing takes the value of `e2`. It has the **lowest precedence** of all operators and guarantees left-to-right order (each comma is a sequence point).

**Locating them.**
- `int a = 3, b = 5;` → **separator** (declaring two variables).
- `(a++, b++, (++b, a + b))` → every comma here is an **operator**, including the one inside the inner brackets.

**Trace, left to right.**

| Step | a | b | value |
|---|---|---|---|
| start | 3 | 5 | |
| `a++` | 4 | 5 | 3, thrown away |
| `b++` | 4 | 6 | 5, thrown away |
| `++b` | 4 | 7 | 7, thrown away |
| `a + b` | 4 | 7 | **11**, kept |

<<< @/../code/oop/papers/r24-q1b.out{txt} [Output]

**Output: 11.**

:::::

</Q>

<Q id="R24.Q2">

Create a Class named Array that takes two private data members, int\* dynamicArray and arrayLength of type integer. Create two Array objects named array1 and array2 and initialise these objects through a parameterized dynamic constructor which takes one integer array as an argument.

A. In parameterized constructor, these object variables are initialized as follows:
I. arrayLength is equal to the number of elements in an array passed as an argument to the constructor.
II. dynamicArray should get memory at run time (use new) and its memory space should be equal to the length of array passed as an argument to the constructor.
III. Copy the integer array obtained as a constructor argument into dynamicArray data member.

B. Display these two arrays on screen using a public member function.

C. Create an another object named array3 that uses another class member function called mergeArrays to merge the two arrays objects named array1 and array 2 in such a way:
i. arrayLength of third array object is equal to the sum of the lengths of these two arrays.
ii. dynamicArray variable of third array object should get memory at run time (use new) and its memory space should be equal to the length computed in step i.
iii. The value of dynamicArray variable is the combination of array values of both name1 and name2 objects.

::::: details Solution

::: warning The question cannot be done exactly as written
"A constructor which takes **one** integer array" and "arrayLength is the number of elements in the array passed". Inside a function, an array parameter is only a pointer to the first element (`int arr[]` means `int *arr`), so the constructor cannot count the elements; `sizeof(arr)` there gives the size of a pointer. Write this assumption in one line and pass the length as a second parameter. The "Assume the missing data" note on the paper covers it, and the syllabus lists "importance of passing size" for exactly this reason.
:::

::: code-group
<<< @/../code/oop/papers/r24-q2.cpp [Program]
<<< @/../code/oop/papers/r24-q2.out{txt} [Output]
:::

It is the String question from September with `int` in place of `char`, so the steps line up one to one:

- **A.I** `arrayLength = n;`
- **A.II** `new int[arrayLength]`. **No `+ 1` here**: integer arrays have no `'\0'` terminator.
- **A.III** A loop copies each element; there is no `strcpy` for `int` arrays.
- **C** `mergeArrays` sets the new length to the sum, frees any old block, allocates, then copies `a`'s elements followed by `b`'s using a second index `k`.

The length is measured with `sizeof(first) / sizeof(first[0])` **in `main`**, where `first` is still a real array.

::: danger Also note
The question says "combination of … name1 and name2 objects". That is a leftover from the String question; it means array1 and array2.
:::

:::::

</Q>

<Q id="R24.Q3">

Create a class named Sample with two private data members named a and b of type integer. Now create three objects named abj1, abj2, and abj3 of this class. Intialize the data members of abj1 and abj2, and display them on console. The values of data members of abj3 are obtained using the statement abj3=abj1+abj2. In order to work this statement properly, perform the following tasks:
i. Overload the plus operator as a member function of class Sample.
ii. The overloaded function should return the values of the type Sample object.
Finally, display the values of third object abj3 on the console.

::::: details Solution

::: code-group
<<< @/../code/oop/papers/r24-q3.cpp [Program]
<<< @/../code/oop/papers/r24-q3.out{txt} [Output]
:::

`abj3 = abj1 + abj2` becomes `abj1.operator+(abj2)`. Inside, `a` and `b` are `abj1`'s; `other` is `abj2`. The function builds a new `Sample` with (2 + 4, 3 + 5) = (6, 8) and returns it.

This is September 2024 Q3 with `+` for `-`, `Sample` for `ABC` and `a, b` for `x, y`. The same three traps apply: one parameter for a member, return a new object, never change `*this`.

:::::

</Q>

<Q id="R24.Q4a">

Find the output in both cases. If the output is different, state the reasons behind such difference.

::: code-group
<<< @/../code/oop/papers/r24-q4a-local.cpp [Case 1: int counter]
<<< @/../code/oop/papers/r24-q4a-static.cpp [Case 2: static int counter]
:::

::::: details Solution

:::: danger First, the honest part: `x = ++x + x++ + x++;` is undefined behaviour
It changes `x` several times inside one expression with no sequence point between the changes. The C++ standard gives such code **no defined result**, and the compiler says so:

```txt
warning: operation on 'x' may be undefined [-Wsequence-point]
```

In the exam, give the "textbook" left-to-right answer below **and** write one line saying the expression is undefined behaviour. That line is what separates a full-marks answer.
::::

**The textbook reading.** Evaluate left to right, each `++` taking effect immediately:
`++x` → x goes up by 1 and gives the new value; `x++` gives the current value and then x goes up by 1.

**Case 1, `int counter` (a fresh local each call).** `counter` is always 1.

| | x on entry | after `x += counter` (printed) | ++x | x++ | x++ | x = sum |
|---|---|---|---|---|---|---|
| call 1 | 8 | 9 | 10 | 10 (x→11) | 11 (x→12) | 10 + 10 + 11 = **31** |
| call 2 | 31 | 32 | 33 | 33 (x→34) | 34 (x→35) | 33 + 33 + 34 = **100** |

**Case 2, `static int counter`.** `counter` is 1 on the first call and 2 on the second.

| | x on entry | after `x += counter` (printed) | sum |
|---|---|---|---|
| call 1 | 8 | 8 + 1 = 9 | **31** |
| call 2 | 31 | 31 + 2 = 33 | 34 + 34 + 35 = **103** |

The same logic written as separate, fully defined statements gives exactly these numbers:

::: code-group
<<< @/../code/oop/papers/r24-q4a-defined.cpp [Defined version]
<<< @/../code/oop/papers/r24-q4a-defined.out{txt} [Output]
:::

What GCC actually printed for the two original programs (it happens to match, but another compiler may not):

::: code-group
<<< @/../code/oop/papers/r24-q4a-local.out{txt} [Case 1, GCC]
<<< @/../code/oop/papers/r24-q4a-static.out{txt} [Case 2, GCC]
:::

**Reason for the difference.** Both functions take `x` by reference, so the changes reach `a`. The only difference is `counter`: a plain local is re-created as 0 on every call, so it always adds 1; a `static` local is created once and remembers its value, so the second call adds 2. That extra 1 on entry to the second call turns 100 into 103.

:::::

</Q>

<Q id="R24.Q4b">

Write the syntax to access or call the static member functions in main function? Also mention the limitations of static member functions in c++.

::::: details Solution

**Syntax:** `ClassName::functionName(arguments);`
It can also be called through an object (`obj.functionName()`), but the class-name form is the correct one, because a static function belongs to the class, not to any object. It can even be called before any object exists.

::: code-group
<<< @/../code/oop/papers/r24-q4b.cpp [Program]
<<< @/../code/oop/papers/r24-q4b.out{txt} [Output]
:::

**Limitations.**
1. It has **no `this` pointer**, because it is not called on an object.
2. So it can use **only static data members and other static member functions** directly. Touching a non-static member is a compile error:

::: code-group
<<< @/../code/oop/papers/r24-q4b-error.cpp [Program]
<<< @/../code/oop/papers/r24-q4b-error.out{txt} [Compiler says]
:::

3. It cannot be `const`, because `const` on a member function promises not to change `*this`, and there is no `*this`.
4. It cannot be `virtual`.

**Way around limitation 2:** pass an object in as a parameter (`showId(const Counter &c)` above), then use `c.id`.

:::::

</Q>

<Q id="R24.Q5a">

We have two classes one for "computer" and another for "mobile". Suppose if we wish to assign "price" of computer to mobile then how it can be achieved by the statement below: mob=comp; where mob and comp are the object of mobile and computer classes, respectively. Which type conversion will be used in this scenario? Explain with a suitable C++ example.

::::: details Solution

**Class to class conversion** (one user-defined type to another). There are two ways to write it; use **one**, not both.

**Way 1: a conversion operator in the source class (`Computer`).** `Computer` says how to turn itself into a `Mobile`.

::: code-group
<<< @/../code/oop/papers/r24-q5a.cpp [Program]
<<< @/../code/oop/papers/r24-q5a.out{txt} [Output]
:::

**Way 2: a one-argument constructor in the destination class (`Mobile`).** `Mobile` says how to build itself from a `Computer`. It needs to read the price, so `Computer` offers a getter (or declares `Mobile` a friend).

::: code-group
<<< @/../code/oop/papers/r24-q5a-ctor.cpp [Program]
<<< @/../code/oop/papers/r24-q5a-ctor.out{txt} [Output]
:::

Either way, `mob = comp;` first makes a temporary `Mobile` from `comp`, then the assignment operator copies it into `mob`.

::: danger Never define both routes
If `Computer` has `operator Mobile()` **and** `Mobile` has `Mobile(const Computer&)`, then `mob = comp;` has two equally good ways to convert and standard C++ rejects it as ambiguous. (Plain GCC quietly picks one, which hides the mistake; in strict mode it reports `conversion from 'Computer' to 'Mobile' is ambiguous`.) See the notes on conversions.
:::

:::::

</Q>

<Q id="R24.Q5b">

Write a program to compute the Fibonacci series.

::::: details Solution

::: code-group
<<< @/../code/oop/papers/r24-q5b.cpp [Program]
<<< @/../code/oop/papers/r24-q5b.in{txt} [Input]
<<< @/../code/oop/papers/r24-q5b.out{txt} [Output]
:::

Keep two numbers, `first` and `second`. Print `first`, then slide the window: the new `first` is the old `second`, and the new `second` is their sum. For 8 terms: 0 1 1 2 3 5 8 13.

::: tip Say which convention you use
Some books start the series at 1 1 2 3. Starting at 0 1 is the usual one; state it in a comment so either is accepted.
:::

:::::

</Q>
