---
title: Mid-semester remedial, November 2025
---

# Mid-semester remedial, November 2025

<PaperHeader :rows="[
  ['Programme', 'B.Tech., 2nd year, 3rd semester'],
  ['Course code', 'CSN3004 / AIN3001 (as printed)'],
  ['Maximum marks', '30'],
  ['Time allowed', '1.5 hours'],
  ['Note on the paper', 'All questions are compulsory.'],
]" />

::: info What this paper is
The file is labelled as the remedial (re-sit) of the October 2025 paper, though the header does not say so. It is the newest paper we have. It uses more, shorter questions (ten parts, mostly 2 to 4 marks) and no 9-mark class. Expect your paper to sit between this and October 2025.
:::

<Q id="N25.Q1">

In C++, which features enables you to demarcate the path of a class that need to be obscured from the view of the user and which need to be offered to the user as an interface to the class? Explain it.

::::: details Solution

**Access specifiers**, which implement **data hiding** (information hiding) as part of encapsulation.

- `private:` marks the part to be **obscured**. Only the class's own member functions (and its friends) can touch it. This is the default in a `class`.
- `public:` marks the **interface** offered to the user: the functions `main` and other code may call.
- `protected:` (a third level) is hidden from users but visible to derived classes.

::: code-group
<<< @/../code/oop/papers/n25-q1.cpp [Program]
<<< @/../code/oop/papers/n25-q1.out{txt} [Output]
:::

`marks` and the helper `valid()` are hidden; `setMarks` and `getMarks` are the interface. The user cannot bypass the check.

:::::

</Q>

<Q id="N25.Q2">

Explain diagrammatically how static member functions differ from non-static member functions in terms of object access and scope. Write a C++ program to define a class Counter with static variables and static functions to count the number of objects created and destroyed.

::::: details Solution

**Diagram.**

```txt
                 CLASS Counter  (one copy, data segment)
         +--------------------------------------------+
         |  static int created = 3                    |
         |  static int destroyed = 0                  |
         |  static void report()   <-- no 'this'      |
         +--------------------------------------------+
              ^ can reach ONLY the static members above

   STACK: every object has its OWN non-static data
   +-------------+   +-------------+   +-------------+
   | c1: id = 1  |   | c2: id = 2  |   | c3: id = 3  |
   +-------------+   +-------------+   +-------------+
        ^
        | c1.show() is really show(&c1): 'this' points at c1,
        | so a non-static function reaches c1's id AND the statics.
```

| | Non-static member function | Static member function |
|---|---|---|
| Called as | `obj.show()` | `Counter::report()` (object not needed) |
| Has `this`? | Yes, the calling object | No |
| Can use non-static members? | Yes | No, only static ones |
| Can use static members? | Yes | Yes |
| Exists before any object? | Needs an object to call it | Yes, callable any time |

**Program.**

::: code-group
<<< @/../code/oop/papers/n25-q2.cpp [Program]
<<< @/../code/oop/papers/n25-q2.out{txt} [Output]
:::

The constructor increments `created`; the destructor increments `destroyed`. `c3` is destroyed at the end of its inner block, so the third report shows 1 destroyed. The last two lines come from `c2` and `c1` being destroyed at the end of `main`, in reverse order of creation.

::: danger Static members need a definition
`static int created;` inside the class only declares it. Without `int Counter::created = 0;` outside (or `inline static int created = 0;` inside, C++17), the program fails to link.
:::

:::::

</Q>

<Q id="N25.Q3">

Compare and contrast call by value and call by reference parameter passing mechanisms. What will be the output of the program?

<<< @/../code/oop/papers/n25-q3.cpp

::::: details Solution

| | Call by value `f(int x)` | Call by reference `f(int &y)` |
|---|---|---|
| What the function gets | A copy of the argument | An alias for the argument itself |
| Changes reach the caller? | No | Yes |
| Extra memory | A new copy on the stack | None; no copy is made |
| Argument can be a literal like `f(5)`? | Yes | No (a non-const reference needs a variable) |
| Good for | Small values you must not change | Changing the caller's variable; large objects (use `const &` if read-only) |

<<< @/../code/oop/papers/n25-q3.out{txt} [Output]

**Trace.**

| Call | Inside prints | Variable afterwards | Why |
|---|---|---|---|
| `modifyValue(a)` | x = 15 | a = 10 | copy changed |
| `modifyReference(b)` | y = 25 | b = 25 | b itself changed |
| `modifyValue(b)` | x = 30 | b = 25 | copy of 25 changed |
| `modifyReference(a)` | y = 15 | a = 15 | a itself changed |

:::::

</Q>

<Q id="N25.Q4a">

Write a C++ program that uses the predefined sqrt() and pow() functions to calculate the square root and cube of a number entered by the user. Display the results with appropriate labels.

::::: details Solution

::: code-group
<<< @/../code/oop/papers/n25-q4a.cpp [Program]
<<< @/../code/oop/papers/n25-q4a.in{txt} [Input]
<<< @/../code/oop/papers/n25-q4a.out{txt} [Output]
:::

Both functions come from `<cmath>`. `pow(num, 3)` raises to the power 3. Use `double`, because `sqrt` of most numbers is not whole. Checking for a negative input earns the "appropriate" part of the marks.

:::::

</Q>

<Q id="N25.Q4b">

Write a C++ program with a user-defined function isEven(int num) that returns true if a number is even and false otherwise. Use this function in the main() to print whether a given integer is even or odd.

::::: details Solution

::: code-group
<<< @/../code/oop/papers/n25-q4b.cpp [Program]
<<< @/../code/oop/papers/n25-q4b.in{txt} [Input]
<<< @/../code/oop/papers/n25-q4b.out{txt} [Output]
:::

The function must return `bool` and take `int num`, exactly as named. `num % 2 == 0` is already true or false, so return it directly. (`(num & 1) == 0` also works; see Assignment 1 Q11.)

:::::

</Q>

<Q id="N25.Q5">

Write a C++ program to define two classes ClassA and ClassB, each containing private member variables. Create a friend function to calculate and return the sum of the private members of both classes. Additionally, write another function that compares two objects of different classes and returns the object with the larger sum of its private members.

::::: details Solution

::: code-group
<<< @/../code/oop/papers/n25-q5.cpp [Program]
<<< @/../code/oop/papers/n25-q5.out{txt} [Output]
:::

**The friend part.** One function `sumOfBoth` is declared `friend` inside **both** classes, so it may read the privates of each. Because `ClassA` mentions `ClassB` before `ClassB` is defined, a **forward declaration** `class ClassB;` is needed at the top.

::: warning The second half has no exact answer
"Returns the object with the larger sum" from two **unrelated** classes: a C++ function has one return type, and it cannot be "either a ClassA or a ClassB". State an assumption, as the program does: return which one is larger (1, 2 or 0 for equal) and display that object in `main`. Other acceptable assumptions: return the larger *sum*, or print the winning object inside the function. Writing one line about why is worth more than any of the three choices.
:::

:::::

</Q>

<Q id="N25.Q6">

What will happen if the commented line is uncommented?

<<< @/../code/oop/papers/n25-q6.cpp

::::: details Solution

As given, the program runs and prints:

<<< @/../code/oop/papers/n25-q6.out{txt} [Output as given]

With the line uncommented it **does not compile**:

::: code-group
<<< @/../code/oop/papers/n25-q6-uncommented.cpp [Uncommented]
<<< @/../code/oop/papers/n25-q6-uncommented.out{txt} [Compiler says]
:::

**Why:** `localVar` is a local variable of `printMessage`. Its **scope** is that function's body; it does not exist anywhere else, including `main`. (Its **lifetime** has also ended: the variable was destroyed when `printMessage` returned.) The error is at compile time, so there is no output at all.

::: tip A detail worth one line
In the paper, `return 0;` is inside the same comment as "Uncomment this line". That is harmless: `main` is the one function allowed to end without `return`, and it then returns 0 automatically.
:::

:::::

</Q>

<Q id="N25.Q7a">

We have a class employee and one object of employee "emp" and suppose we want to assign the employee code of employee "emp" by any integer variable say "Ecode" then the statement below is: emp=Ecode; where Ecode is of basic data type. Analyses in this scenario we are using which type conversion. Explain suitable C++ example of this type conversion.

::::: details Solution

**Basic type to class type** conversion. The `int` on the right must be turned into an `Employee`. This is done by a **constructor that takes one argument of the basic type**, `Employee(int c)`. Such a constructor doubles as a conversion function.

::: code-group
<<< @/../code/oop/papers/n25-q7a.cpp [Program]
<<< @/../code/oop/papers/n25-q7a.out{txt} [Output]
:::

`emp = Ecode;` is carried out as `emp = Employee(Ecode);`: a temporary `Employee` is built from the `int`, then assigned to `emp`.

**Implicit vs explicit** (the syllabus asks for both):
- Implicit: `emp = Ecode;` and `Employee emp2 = 2048;`. The compiler calls the constructor by itself.
- Explicit: `Employee emp3(4096);` or `emp = Employee(Ecode);`. You call it yourself.

Marking the constructor `explicit` switches off the implicit form:

::: code-group
<<< @/../code/oop/papers/n25-q7a-explicit.cpp [explicit constructor]
<<< @/../code/oop/papers/n25-q7a-explicit.out{txt} [Compiler says]
:::

:::::

</Q>

<Q id="N25.Q7b">

Write a C++ Program to perform the following tasks using the Operator Overloading:
1) Area of Triangle
2) Area of Circle
3) Area of Rectangle.

::::: details Solution

The question does not say which operator. State your assumption. The cleanest one: a class `Area` that overloads the **function-call operator `()`** three times, with the number of arguments choosing the shape.

::: code-group
<<< @/../code/oop/papers/n25-q7b.cpp [Program]
<<< @/../code/oop/papers/n25-q7b.out{txt} [Output]
:::

- Circle: one value, πr².
- Rectangle: two values, length × breadth.
- Triangle: three sides, Heron's formula: s = (a + b + c) / 2, area = √(s(s − a)(s − b)(s − c)). A 3-4-5 triangle has area 6.

**Another acceptable reading:** overload ordinary arithmetic operators on small classes, for example `Length * Length` for a rectangle and a unary operator for a circle:

::: code-group
<<< @/../code/oop/papers/n25-q7b-binary.cpp [Program]
<<< @/../code/oop/papers/n25-q7b-binary.out{txt} [Output]
:::

Either earns the marks if the operators are genuinely overloaded and all three areas are printed with labels.

:::::

</Q>

<Q id="N25.Q8">

What will be the output of this code snippet?

<<< @/../code/oop/papers/n25-q8.cpp

::::: details Solution

<<< @/../code/oop/papers/n25-q8.out{txt} [Output]

**Output: `First`.**

The class has two `operator++` functions. The compiler tells prefix and postfix apart by a **dummy `int` parameter**:
- `operator++()` (here written `operator++(void)`) is **prefix**, `++myObj`.
- `operator++(int)` is **postfix**, `myObj++`.

`main` writes `myObj++`, postfix, so `operator++(int)` runs and prints `First`. The `int` is never used; its only job is to make the two signatures different.

::: danger Distractors you will see in an MCQ version
"second" (the prefix one), "Firstsecond" (thinking both run) and "ambiguity error" (they are *not* ambiguous: the dummy `int` makes them different functions).
:::

:::::

</Q>
