---
title: End-semester, November 2024 (mid-semester part)
---

# End-semester, November 2024

<PaperHeader :rows="[
  ['Programme', 'B.Tech. (CSE/AI), 2nd year'],
  ['Course code', 'CSN3004 / AIN3002'],
  ['Maximum marks', '80'],
  ['Time allowed', '3 hours'],
  ['On this page', 'Only the questions that fall inside the mid-semester syllabus (Units 1 to 4)'],
]" />

::: info Why an end-semester paper is here
End-semester papers cover all eight units, but half of this one is Units 1 to 4, and two of its questions are word for word in Assignment 5. They are extra practice at exactly your level.

**Left out, because they are Units 5 to 8** (inheritance, file I/O, streams): Q1 (the diamond problem), Q5a and Q5b (base and derived classes), Q7a, Q7b and Q7c (stream formatting and files). They will be added when the end-semester section is built.
:::

<Q id="E24.Q2a">

An Array of 10 elements is entered from keyboard. Write a C++ program with output, that interchange it's even position elements with odd position elements.

::::: details Solution

::: code-group
<<< @/../code/oop/papers/e24-q2a.cpp [Program]
<<< @/../code/oop/papers/e24-q2a.in{txt} [Input]
<<< @/../code/oop/papers/e24-q2a.out{txt} [Output]
:::

"Position" counts from 1, as people do: position 1 swaps with position 2, 3 with 4, and so on. In index terms that is `arr[0]` ↔ `arr[1]`, `arr[2]` ↔ `arr[3]`, …, so the loop steps `i` by 2 and swaps `arr[i]` with `arr[i + 1]`. The condition `i + 1 < 10` keeps it from running past the end if the size were odd.

The question says "with output", so show a sample run, as the Output tab does.

:::::

</Q>

<Q id="E24.Q2b">

Can nested if be applied within a nested for loop? If the answer is yes, then explain with an example.

::::: details Solution

**Yes.** A loop body can hold any statements, including another loop, and any `if` can hold another `if`. The inner `if` runs on every iteration of the inner loop.

::: code-group
<<< @/../code/oop/papers/e24-q2b.cpp [Program]
<<< @/../code/oop/papers/e24-q2b.out{txt} [Output]
:::

The outer `for` picks `i`, the inner `for` picks `j`; the outer `if` keeps only pairs with `i < j`, and the inner `if` keeps only those with an even sum. Out of 16 pairs, only (1, 3) and (2, 4) pass both tests.

:::::

</Q>

<Q id="E24.Q3a">

Write a C++ program with output that calculates the sum of two numbers in a class and display the numbers and sum using the friend function. Also, demonstrate the use of This pointer.

::::: details Solution

This is **word for word Assignment 5 Q2**.

::: code-group
<<< @/../code/oop/papers/e24-q3a.cpp [Program]
<<< @/../code/oop/papers/e24-q3a.out{txt} [Output]
:::

**Two uses of `this` are shown.**
1. **Telling a member from a parameter with the same name:** in `setA(int a)`, plain `a` is the parameter and `this->a` is the member.
2. **Returning the object itself:** `return *this;` hands back the object the function was called on, which is what lets `n.setA(12).setB(30)` chain.

**The friend function** `sum` is not a member, so it has **no `this`**; it reaches the private members through its parameter `n`.

::: danger
Writing `this->a` inside the friend function is a compile error. Friends are outsiders with a key, not members.
:::

:::::

</Q>

<Q id="E24.Q3b">

Calculate the output of this program and Mention which type of constructor to use in this program.

<<< @/../code/oop/papers/e24-q3b.cpp

::::: details Solution

**The output is unpredictable.** `A` has no constructor written, so the compiler supplies an **implicit default constructor** that does nothing to `x` and `y`. `obj` is a local, so its members hold whatever garbage was on the stack. One run printed:

<<< @/../code/oop/papers/e24-q3b.out{txt} [One actual run]

Another run, or another compiler, will print something else. (A *global* object would print `0, 0`, because globals are zero-filled.)

**Which constructor to use:** a **user-defined default constructor** that sets both members, and optionally a parameterised one for chosen values:

::: code-group
<<< @/../code/oop/papers/e24-q3b-fixed.cpp [Fixed]
<<< @/../code/oop/papers/e24-q3b-fixed.out{txt} [Output]
:::

::: tip In the exam
Write "garbage values (undefined)" as the output, explain why, then give the fixed class. Inventing specific numbers like `0, 0` for the original loses the mark.
:::

:::::

</Q>

<Q id="E24.Q4">

Create a Class named String that takes two private data members, char \*stringName and stringLength of type integer. Create two string objects named string1 and string2 and initialise these objects through a parameterized dynamic constructor which takes one string as a parameter where the memory size allocated to stringName is determined from the length of string obtained through its parameter. After initialization, display the strings on the console using showOutput() member function and perform following functionalities:

A. Create a third object named string3 that adds (joins) the two strings of string1 and string2 objects by overloading + operator as Friend function in such a way:
I. stringLength of third string object is equal to the sum of the lengths of these two strings.
II. stringName variable of third string object should get memory at run time (use new) and its memory space should be equal to one greater than the length computed in step i.
III. The value of stringName variable is the combination of string values of both name1 and name2 objects.

B. Create a fourth object named string4 that compares the two strings of string1 and string3 objects by overloading + operator as class member function in such a way:
I. Compute the stringLength string string1 and string3 objects and compare these lengths and return boolean flag as an output.
II. In main function, compare the strings of string1 and string3 objects employing overloaded operator and display the smaller string on console.

::::: details Solution

This is **word for word Assignment 5 Q5** (which even repeats the same mistakes).

::: warning Part B cannot be done as written
It asks for `+` again, now as a member returning `bool`. A friend `operator+(const String&, const String&)` and a member `operator+(const String&)` accept exactly the same operands, so `string1 + string3` would match both and the call is **ambiguous**. Return types cannot tell them apart. The compiler proves it:

<<< @/../code/oop/papers/e24-q4-ambiguous.out{txt} [Both as '+']

**Assumption to write:** the comparison uses `<` (member), returning `true` if `*this` is shorter. That keeps "a member operator returning a boolean flag", which is clearly what was meant.
:::

::: code-group
<<< @/../code/oop/papers/e24-q4.cpp [Program]
<<< @/../code/oop/papers/e24-q4.out{txt} [Output]
:::

**Why this class needs more than the question lists.** `operator+` returns a `String` **by value**, and `string3 = …` may assign one. With only the compiler's shallow copy, two objects would share one `char` buffer and both destructors would free it (a double free crash). So the class has:
- a **deep copy constructor** (new buffer, copy the characters),
- a **deep copy assignment operator** (with a self-assignment check),
- a **destructor** that frees the buffer.

**Friend vs member, in one line each.**
- Friend `+`: not called on an object, so **both** operands are parameters: `operator+(a, b)`.
- Member `<`: called on the left operand, so **one** parameter: `string1.operator<(string3)`.

:::::

</Q>

<Q id="E24.Q5c">

Differentiate between following: a) Aggregation and Composition. b) Overloading and Overriding member function. Also, in the below-given code, Teacher, Student and Employee represent user-defined classes, and have their corresponding objects (T1, Student1, EmployeeId2, Employee1 and emp1). Ignore the extra objects and identify those representing the composition and aggregation.

::::: details Solution

::: info Syllabus note
Aggregation, composition and overriding belong to Units 5 and 6 (inheritance, virtual functions). Only **overloading** is mid-semester syllabus. The full answer is here for completeness.
:::

**a) Aggregation vs composition** (both are "has-a" relationships).

| | Composition | Aggregation |
|---|---|---|
| Ownership | Strong: the whole owns the part | Weak: the whole only uses the part |
| Lifetime | The part is created and destroyed with the whole | The part exists independently |
| In code | A member object: `Engine engine;` | A pointer or reference to an outside object: `Driver *driver;` |
| Example | House and its Rooms | Department and its Teachers |

**b) Overloading vs overriding.**

| | Overloading | Overriding |
|---|---|---|
| Where | Same class (or scope) | Base and derived class |
| Signature | Must **differ** in parameters | Must be the **same** |
| Decided | At compile time | At run time (with `virtual`) |
| Needs inheritance? | No | Yes |

::: code-group
<<< @/../code/oop/papers/e24-q5c.cpp [Program]
<<< @/../code/oop/papers/e24-q5c.out{txt} [Output]
:::

**The paper's code.** `Student Student1;` is a member object created and destroyed with the `Teacher`: **composition**. `Employee EmployeeId2;` is assigned from `Employee1`, an object that exists outside and is passed in: the intended answer is **aggregation** (the teacher uses an employee that lives on its own). The code itself does not compile (`Student1 = new student1;` assigns a pointer to an object, and `student1` is not a type), so say that, then answer the intended question.

:::::

</Q>

<Q id="E24.Q6a">

Differentiate between Copy constructor and Assignment operator in terms of initializing an object. Locate the copy as well as assignment initialization of an object in the main function of below given code. Also, determine the output of this code.

<<< @/../code/oop/papers/e24-q6a.cpp

::::: details Solution

| | Copy constructor | Assignment operator |
|---|---|---|
| When | A **new** object is created from an existing one | An **existing** object is given another object's values |
| Syntax that triggers it | `Test t3 = t1;`, `Test T4(t1);`, passing or returning by value | `t2 = t1;` where `t2` already exists |
| Memory | Creates the object | The object already exists; old resources must be released first |
| Returns | Nothing (it is a constructor) | Usually `Test&`, so `a = b = c` works |

**In `main`:**
- `t2 = t1;` → **assignment** (t2 was created on the line before) → prints `Hello World`.
- `Test t3 = t1;` → **copy initialisation** → copy constructor → `OOPS programming`.
- `Test T4(t1);` → **direct initialisation**, also the copy constructor → `OOPS programming`.

<<< @/../code/oop/papers/e24-q6a.out{txt} [Output]

`getchar()` only waits for a key press before the program ends.

:::::

</Q>

<Q id="E24.Q6b">

Determine the output of below given code. What unexpected behaviour is caused by static memory allocation in this code? How dynamic memory allocation is different from static allocation and can assist us in mitigating this problem. Convert the below given code to an efficient code with dynamic memory allocation.

<<< @/../code/oop/papers/e24-q6b.cpp

::::: details Solution

**Input:** n = 2, then n = 7 (as the comments say).

**The problem.** `arr` has room for **5** ints (indexes 0 to 4). The second loop writes `arr[5]` and `arr[6]`, and the printing loop reads up to `arr[7]`. C++ does **not** check array bounds, so this compiles and runs, but it writes into memory that belongs to something else: **undefined behaviour**. It may print garbage, silently change another variable (here possibly `n` or `i`, which sit next to `arr` on the stack), or crash.

One actual run printed this. The first seven values look right only by luck, and the eighth is garbage:

<<< @/../code/oop/papers/e24-q6b.out{txt} [One actual run]

**Static vs dynamic allocation.**

| | Static (fixed) array `int arr[5];` | Dynamic array `new int[n]` |
|---|---|---|
| Size decided | At compile time | At run time, from the input |
| Memory | Stack | Heap |
| Freed | Automatically at the end of the block | By you, with `delete[]` |
| Too small / too big | Overflow or wasted space | Exactly `n` elements |

**The dynamic version.** Allocate exactly `n` after reading it, loop to `n` (never to a fixed 8), free with `delete[]` before re-allocating, and set the pointer to `nullptr` at the end:

::: code-group
<<< @/../code/oop/papers/e24-q6b-dynamic.cpp [Program]
<<< @/../code/oop/papers/e24-q6b-dynamic.in{txt} [Input]
<<< @/../code/oop/papers/e24-q6b-dynamic.out{txt} [Output]
:::

:::::

</Q>
