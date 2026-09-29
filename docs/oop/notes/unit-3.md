---
title: Unit 3 · Classes and objects
---

# Unit 3 · Classes and objects

Member functions, static members, the memory layout of objects, passing and returning objects, friends, `const` and `constexpr` members, every kind of constructor, copying, and destructors.

::: info How this unit is examined
- **Mid-semester:** the long question (6 to 9 marks) is almost always a class written from a numbered specification: dynamic constructor, copy constructor, friend function, static counter. Short questions ask which constructor a line calls, or what static functions cannot do.
- **Quiz:** "which constructor runs", "does this compile", destructor order, `sizeof` with padding.
:::

## Defining member functions: inside or outside

```cpp
class Student {
    int rollno;
public:
    void show() { cout << rollno; }   // defined INSIDE: automatically inline
    void display();                   // only DECLARED inside
};
void Student::display() { cout << rollno; }   // defined OUTSIDE with ClassName::
```

- Inside the class: short functions; they are **implicitly inline**.
- Outside with `ClassName::`: longer functions. This keeps the class declaration readable and is the usual choice when the class lives in a header. Forget `Student::` and the compiler treats it as an unrelated free function, so `rollno` is "not declared".
- To make an outside definition inline, write `inline` in front of it:

::: code-group
<<< @/../code/oop/notes/u3-inline-outside.cpp [Program]
<<< @/../code/oop/notes/u3-inline-outside.out{txt} [Output]
:::

**Which is desirable?** Inside for one-liners (getters, setters); outside for anything longer. `inline` is only a request; the compiler decides.

## Nesting of member functions and private member functions

A member function can call another member function **directly by name**, without an object: that is **nesting**. A **private member function** cannot be called from `main`, but it can be called by a public member function of the same class. That is how helper functions are hidden.

::: code-group
<<< @/../code/oop/notes/u3-nesting.cpp [Program]
<<< @/../code/oop/notes/u3-nesting.out{txt} [Output]
:::

## The `this` pointer

Every non-static member function receives a hidden pointer to the object it was called on: `f1.display()` runs as `display(&f1)`. Inside, that pointer is `this`, and `*this` is the object itself.

**Use 1: when a parameter has the same name as a member.** Without `this`, the parameter hides the member, and `age = age;` assigns the parameter to itself:

::: code-group
<<< @/../code/oop/notes/u3-shadow.cpp [Program]
<<< @/../code/oop/notes/u3-shadow.out{txt} [Output]
:::

**Use 2: returning the object itself**, `return *this;`, for chaining (`n.setA(1).setB(2)`) and in `operator=`.

Static member functions and friend functions have **no `this`**.

## Static data members

A static data member belongs to the **class**, not to any object: **one copy**, shared by all objects, stored in the data segment, alive for the whole program. Use it for information every object must share: a count of objects, the next account number, a company name.

**Defining it.**

```cpp
class Fruit {
    static int count;              // traditional: this only DECLARES it
};
int Fruit::count = 0;              // the one DEFINITION, outside the class

class Fruit2 {
    inline static int count = 0;   // C++17: defined and initialised inside
};
```

The class body is a blueprint, so `static int count;` inside it only announces the variable. Storage must be created exactly once in the program, which is the job of the definition outside. `inline` tells the linker "this definition may appear more than once; keep one", which is why it can go inside the class.

::: code-group
<<< @/../code/oop/notes/u3-static-members.cpp [Program]
<<< @/../code/oop/notes/u3-static-members.out{txt} [Output]
:::

### `const`, `constexpr`, `inline constexpr`, `static constexpr`

| Declaration inside a class | Copies | Changeable | Value known | Initialised |
|---|---|---|---|---|
| `const int id;` | one per object | no | at run time | member initializer list |
| `static const int N = 10;` | one | no | compile time | inside is allowed for an integer literal |
| `inline static const int L = f();` | one | no | at run time | inside, needs `inline` |
| `static constexpr int MAX = 100;` | one | no | **compile time** | inside; `constexpr` static members are implicitly `inline` |
| `inline static int shared = 0;` | one | **yes** | run time | inside |

::: code-group
<<< @/../code/oop/notes/u3-const-constexpr.cpp [Program]
<<< @/../code/oop/notes/u3-const-constexpr.out{txt} [Output]
:::

`constexpr` demands a value the compiler can compute. A function result known only at run time is rejected:

::: code-group
<<< @/../code/oop/notes/u3-constexpr-error.cpp [Program]
<<< @/../code/oop/notes/u3-constexpr-error.out{txt} [Compiler says]
:::

::: danger A `const` member must be set in the member initializer list
`BankAccount(long n) : accountNumber(n) {}`. Assigning it in the constructor body is too late and does not compile. See [Assignment 4 Q6](../assignments/a4#q6).
:::

## Static member functions

| | Non-static member function | Static member function |
|---|---|---|
| Called as | `obj.f()` | `ClassName::f()` (an object is optional) |
| Has `this` | yes | **no** |
| Can use non-static members | yes | **no**, only through an object passed in |
| Can use static members | yes | yes |

**The rule runs one way.** Non-static functions may use everything. Static functions may use only static members, because there is no object to take a non-static member from. The way round it is to pass an object in: `static void show(const Fruit &f) { cout << f.shape; }`. See [Remedial 2024 Q4b](../papers/mst-2024-remedial#q4b) and [Nov 2025 Q2](../papers/mst-2025-nov#q2).

## Memory layout of a class and its objects

```txt
 CODE (TEXT) SEGMENT    setData()  display()  displayCount()   one copy of each function
 DATA SEGMENT           Fruit::count                           one copy for all objects
 STACK                  f1: [shape][colour]   f2: [shape][colour]   each object's own data
 HEAP                   whatever the objects' pointers point to (new)
```

Three kinds of object:

| Kind | Written as | Object lives in | Its pointed-to data | Destroyed |
|---|---|---|---|---|
| Static (automatic) | `String s1("abc");` | stack | — | automatically at the end of scope |
| Hybrid | a stack object with a pointer member that uses `new` | stack | heap | object automatically; heap block only by the destructor |
| Dynamic | `String *s = new String("abc");` | heap | heap | only by `delete s;` |

### Size of an object and padding

`sizeof(object)` counts **only the data members, plus padding**. Member functions, static members and access specifiers add nothing: a class with one `int` and ten functions is 4 bytes.

**Padding rule.** Each member must start at an offset that is a multiple of its own size (char 1, short 2, int/float 4, double/pointer 8). The compiler inserts unused bytes to make that true. Finally the total is rounded up to a multiple of the largest member's size, so arrays of objects stay aligned.

```txt
class A { char a; int b; int c; char d; int e; int *f; };

offset  0    1..3   4      8      12   13..15  16     20..23   24          32
       [a]  [pad]  [ b ]  [ c ]  [d]  [pad]   [ e ]  [ pad ]  [    f    ]
                                                      ^ f needs a multiple of 8; 20 is not, so 24
                                                                        total = 32
```

Order members **largest to smallest** and the gaps disappear: `int *f; int b; int c; int e; char a; char d;` uses 22 bytes of data, rounded up to **24**. You can remove the gaps inside; you cannot avoid rounding the total up to a multiple of 8.

::: code-group
<<< @/../code/oop/notes/u3-sizeof-class.cpp [Program]
<<< @/../code/oop/notes/u3-sizeof-class.out{txt} [Output]
:::

The second exercise from class, `char a; int b; char c; int arr[13]; int a1; char c1; int *a2;`, is **80** bytes as written and **72** with the pointer first. The `int arr[13]` alone is 52 bytes, so no ordering can make this class small; moving the 8-byte pointer to the front removes the padding it needed.

::: tip How to answer a padding question
Draw a row of boxes with offsets under them. Place each member at the next offset that is a multiple of its size; shade the gaps. Round the end up to a multiple of the largest member. Then reorder largest-first and repeat.
:::

## Passing and returning objects

::: code-group
<<< @/../code/oop/notes/u3-return-by-ref.cpp [Program]
<<< @/../code/oop/notes/u3-return-by-ref.out{txt} [Output]
:::

- **Pass by copy** (`void f(Counter c)`): the copy constructor runs; changes are lost. Fine for tiny objects.
- **Pass by reference** (`Counter &c`): no copy; the function can change the caller's object.
- **Pass by const reference** (`const Counter &c`): no copy and no changes. **The default choice for objects.**
- **Return by copy** (`Counter f()`): a new object is handed back. Required when returning a **local** object: a reference to a local would dangle.
- **Return by reference** (`Counter &f()`): the object itself is handed back, with no copy. Used for `return *this;` so calls chain, and in `operator=`, `operator<<`, and the singleton. In the output above, `addCopy(10).addCopy(20)` changes only a temporary copy the second time, so `c` gets +10, not +30.

## Array of objects

::: code-group
<<< @/../code/oop/notes/u3-array-of-objects.cpp [Program]
<<< @/../code/oop/notes/u3-array-of-objects.out{txt} [Output]
:::

`Student s[5];` runs the **default constructor** 5 times, so the class must have one. With only a parameterised constructor, this line does not compile.

## Friend functions and friend classes

A **friend** is a function (or class) that is not a member but is allowed to use the private and protected members. The class grants it by writing `friend` in front of its declaration. The section (private/public) where the friend declaration sits makes no difference.

### 1. A non-member friend function

```cpp
class Complex {
    int real, img;
public:
    Complex(int r, int i) { real = r; img = i; }
    friend Complex add(const Complex &a, const Complex &b);   // the grant
};
Complex add(const Complex &a, const Complex &b) {             // defined outside, no Complex::
    return Complex(a.real + b.real, a.img + b.img);
}
// in main:  Complex c3 = add(c1, c2);    not c3.add(...): it is not a member
```

It has no `this`, so every object it needs is a parameter.

:::: danger The friend declaration and the definition must match exactly
If the class says `friend Complex add(Complex a, Complex b);` but the definition takes `const Complex &`, those are **two different functions**. The one with a body is not the friend, so every private access in it fails:

::: code-group
<<< @/../code/oop/notes/u3-friend-mismatch.cpp [Program]
<<< @/../code/oop/notes/u3-friend-mismatch.out{txt} [Compiler says]
:::

Copy the parameter list character for character.
::::

### 2. A member function of another class as a friend

The order is the whole question (syllabus: "the importance of forward declaration, and when the object has incomplete logic"):

::: code-group
<<< @/../code/oop/notes/u3-friend-member.cpp [Correct order]
<<< @/../code/oop/notes/u3-friend-member.out{txt} [Output]
:::

1. `class Complex;` **forward declaration**: tells the compiler the name exists.
2. `class A` with `calculate` only **declared**. Complex is still **incomplete**: its size and members are unknown, so no code can touch `c1.real` yet, and it can only be passed by reference or pointer.
3. `class Complex` naming `A::calculate` as a friend.
4. `A::calculate` **defined after** `Complex` is complete.

Defining `calculate` inside `A` (before `Complex` is complete) fails:

::: code-group
<<< @/../code/oop/notes/u3-friend-incomplete.cpp [Wrong order]
<<< @/../code/oop/notes/u3-friend-incomplete.out{txt} [Compiler says]
:::

### 3. A friend class

If many functions of `A` need `Complex`'s privates, grant the whole class once: `friend class A;` inside `Complex`.

::: danger Friendship facts
It is **granted**, never taken: written inside the class being opened. It is **not mutual**: `Complex` friending `A` gives `Complex` nothing of `A`'s. It is **not inherited**.
:::

## Constructors

A constructor sets up a new object. Four hard facts:
1. Same name as the class, always.
2. **No return type**, not even `void`.
3. Runs automatically when an object is created.
4. Can be public or private.

::: danger A name mismatch turns it into a function
In `class Complex { Complex1() { … } };` the name does not match, so the compiler reads a *function* with no return type and reports that, which is confusing until you see the typo.
:::

### Default constructor

Takes no arguments: `Complex() { real = 0; img = 0; }`. If you write **no constructor at all**, the compiler supplies one that does nothing (members of a local object hold garbage; see [End-sem Q3b](../papers/endsem-2024#q3b)).

:::: danger Writing any constructor removes the free default one
::: code-group
<<< @/../code/oop/notes/u3-no-default.cpp [Program]
<<< @/../code/oop/notes/u3-no-default.out{txt} [Compiler says]
:::

Write `Complex() {}` yourself if objects without arguments, or arrays of objects, are needed.
::::

### Parameterised constructor and overloading

`Complex(int r, int i) { real = r; img = i; }` gives each object its own values: `Complex c1(5, 9), c2(8, 7);`. A class can have several constructors with different parameter lists (**constructor overloading**); the same exact > promotion > conversion rules as function overloading pick one.

::: danger Default arguments can make constructors ambiguous
`Complex(int a, int b = 6)` together with `Complex(int a)`: `Complex c1(4);` matches both exactly, so it does not compile. `Complex c2(4, 6);` is fine; only the first takes two. This is [Assignment 5 Q9](../assignments/a5#q9). Also: `Complex(int a = 0, int b)` is illegal (a default before a non-default).
:::

### Dynamic initialisation vs dynamic constructor

| Dynamic initialisation | Dynamic constructor |
|---|---|
| The **values** passed to the constructor are known only at run time: `cin >> r >> i; Complex c(r, i);` | The constructor itself **allocates memory with `new`**, so the object's storage size is decided at run time |
| No `new` needed | `name = new char[length + 1];` inside the constructor |

### A complete dynamic-constructor class

```cpp
class String {
    char *name;
    int length;
public:
    String(const char *s) {              // dynamic constructor
        length = strlen(s);              // computed at run time
        name = new char[length + 1];     // +1 for the '\0' at the end of a C string
        strcpy(name, s);
    }
    String() { length = 0; name = new char[1]; name[0] = '\0'; }
    void join(const String &a, const String &b) {
        length = a.length + b.length;
        delete[] name;                   // free the old block first: no leak
        name = new char[length + 1];
        strcpy(name, a.name);            // copy the first...
        strcat(name, b.name);            // ...then APPEND the second
    }
    ~String() { delete[] name; }
};
```

- `+ 1` only for `char` arrays (room for `'\0'`); an `int` array has no terminator.
- `strcpy` writes from position 0; a second `strcpy` would overwrite the first string. `strcat` appends after the existing `'\0'`.
- C strings (`char[]`, ending in `'\0'`) use `strcpy` / `strcat` from `<cstring>`. C++ `std::string` uses `=` and `+`. Do not mix them up.

If `join` must be a **free function**, make it a friend, return a `String` (the result), and call it as `s1 = join(name1, name2);`. Returning a `String` by value then **requires a deep copy constructor** (next section). The full exam version is [Sep 2024 Q2](../papers/mst-2024-sep#q2).

### Private constructor and the singleton pattern

A private constructor stops anyone outside the class from creating objects. A **static** member function becomes the only way in, and it always hands back the **same** object. That is the **singleton** (one head of department, one configuration, one logger).

::: code-group
<<< @/../code/oop/notes/u3-singleton.cpp [Program]
<<< @/../code/oop/notes/u3-singleton.out{txt} [Output]
:::

The `static Student s;` inside `setter()` is created on the first call only. The return type **must be a reference**, `Student &`: returning by value would hand out copies and defeat the pattern. Creating an object directly fails:

::: code-group
<<< @/../code/oop/notes/u3-singleton-error.cpp [Program]
<<< @/../code/oop/notes/u3-singleton-error.out{txt} [Compiler says]
:::

(A derived class can use a base constructor that is `protected`; with a truly `private` one it needs friendship. Inheritance is Unit 5.)

### Copy constructor

`Complex(const Complex &c)` builds a new object as a copy of an existing one. The compiler supplies one automatically (copying member by member) unless you write your own; writing *other* constructors does not remove it.

:::: danger The parameter must be a reference
`Complex(Complex c)` is rejected: passing `c` by value would itself need a copy, which would call the copy constructor, which needs a copy… The compiler says so:

::: code-group
<<< @/../code/oop/notes/u3-copy-by-value.cpp [Program]
<<< @/../code/oop/notes/u3-copy-by-value.out{txt} [Compiler says]
:::
::::

### Copy initialisation vs assignment

::: code-group
<<< @/../code/oop/notes/u3-which-constructor.cpp [Program]
<<< @/../code/oop/notes/u3-which-constructor.out{txt} [Output]
:::

| Line | Kind | Runs | Prints |
|---|---|---|---|
| `Complex c1(4, 6);` | direct initialisation | parameterised constructor | P |
| `Complex c2(c1);` | direct initialisation from an object | copy constructor | C |
| `Complex c3;` | default construction | default constructor | D |
| `c3 = c1;` | **assignment**: c3 already exists | assignment operator | A |
| `Complex c4 = c1;` | **copy initialisation**: c4 is being created | copy constructor | C |

**The only question to ask: does the left-hand object already exist?** Being declared on this line → copy constructor. Made earlier → assignment operator, no constructor at all.

### Shallow copy vs deep copy

This only matters when a class holds a **pointer** to memory it allocated.

```txt
 class Complex { int real; int *img; }       img = new int(6);

 SHALLOW (default: copies the address)     DEEP (your own: copies the value)
 c1.img = 2000 --+                         c1.img = 2000 --> [ 6 ]
                 +--> [ 6 ]  one block      c2.img = 3000 --> [ 6 ]  two blocks
 c2.img = 2000 --+    two owners
```

With a shallow copy:
- changing the value through `c2` changes `c1` too (**no isolation**);
- when one object is destroyed and frees the block, the other holds a **dangling pointer**;
- when the second destructor also frees it: **double free**, a crash.

```cpp
Complex(const Complex &c) {
    real = c.real;
    img = new int(*c.img);     // DEEP: a new block holding a copy of the VALUE
    // img = c.img;            // shallow: the same address
    // img = *c.img;           // type error: an int into an int*
}
```

::: code-group
<<< @/../code/oop/notes/u3-shallow-crash-free.cpp [Deep copy]
<<< @/../code/oop/notes/u3-shallow-crash-free.out{txt} [Output]
:::

The shallow version, and what happens to the original when the copy changes, is demonstrated in [Assignment 5 Q7](../assignments/a5#q7).

**Rule of three:** a class that needs a destructor (because it owns heap memory) also needs a deep copy constructor and a deep copy assignment operator.

## Destructors

`~ClassName()`: runs automatically when an object's lifetime ends.
1. Same name with `~` in front.
2. **No parameters**, so it **cannot be overloaded**: one per class.
3. No return type.
4. Objects are destroyed in **reverse order of construction**; an object in an inner block is destroyed at that block's closing brace.

::: code-group
<<< @/../code/oop/notes/u3-destructor-order.cpp [Program]
<<< @/../code/oop/notes/u3-destructor-order.out{txt} [Output]
:::

s1, s2, s3 are built (const1 const2 const3); the inner block ends, so s3 goes (dest3, count back to 2); s4 is built (const3); `main` ends and s4, s2, s1 go in reverse (dest3 dest2 dest1).

| Object | Write a destructor? | Who calls it? |
|---|---|---|
| Static/automatic, no pointers | not needed | automatic |
| Hybrid (holds `new`'d memory) | **yes**, to `delete` that memory | automatic at end of scope |
| Dynamic (`new Student`) | only if it holds heap memory | **you**, with `delete s;` |

::: warning A destructor is not a garbage collector
C++ has no garbage collector. "Automatic" means the destructor is *called* automatically; memory from `new` is freed only if your destructor says `delete`.
:::

## Quick check

<Drill n="1" tag="Output" from="v2 drill 11">

```cpp
class Complex {
public:
    Complex()                   { cout << "D"; }
    Complex(int, int)           { cout << "P"; }
    Complex(const Complex &)    { cout << "C"; }
};
int main() {
    Complex c1(4, 6);  Complex c2(c1);  Complex c3;
    c3 = c1;           Complex c4 = c1;
}
```

<Mcq :options="['PCDCC', 'PCDC', 'PCCDC', 'PDCC', 'PCD']" answer="b">

`c3 = c1` is assignment (c3 exists), and this class prints nothing for assignment, so **PCDC**. With a printing `operator=` it would be PCDAC, as in the program above.

</Mcq>

</Drill>

<Drill n="2" tag="Output" from="v2 drill 10">

```cpp
// count starts 0; constructor: count++ then print "const" << count
// destructor: print "dest" << count then count--
Student s1, s2;
{ Student s3; }
Student s4;
```

<FillIn q="Write the full output, space separated." answer="const1 const2 const3 dest3 const3 dest3 dest2 dest1">

The inner block destroys s3 at its `}`. Then s4 is made. At the end of `main`: s4, s2, s1 in reverse order. The constructor increments before printing, the destructor prints before decrementing, so `const3` and `dest3` each appear twice.

</FillIn>

</Drill>

<Drill n="3" tag="Error hunt" from="v2 drill 12">

```cpp
class Complex {
    int real, *img;
public:
    Complex(int a, int b) { real = a; img = new int(b); }
    Complex(Complex c)    { real = c.real; img = *c.img; }
    Complex1()            { real = 0; }
}
int main() {
    Complex c1(4, 6);
    Complex c2 = c1;
    Complex c3;
}
```

<FillIn q="How many separate errors are there?" answer="5|five">

1. `Complex(Complex c)`: a copy constructor must take `const Complex &`.
2. `img = *c.img;`: an `int` assigned to an `int*`. Deep copy is `img = new int(*c.img);`.
3. `Complex1()`: the name does not match the class, so it is read as a function with no return type.
4. Missing `;` after the class's closing `}`.
5. `Complex c3;`: a parameterised constructor exists, so there is no default constructor.

And even when fixed, the class leaks: it uses `new` and has no destructor.

</FillIn>

</Drill>

<Drill n="4" tag="Output" from="v2 drill 13">

```cpp
class Box {
    int *p;
public:
    Box(int v)  { p = new int(v); }
    ~Box()      { delete p; }
    void set(int v) { *p = v; }
    void show() { cout << *p; }
};
int main() { Box b1(5); Box b2 = b1; b2.set(9); b1.show(); }
```

<Mcq :options="['5', '9', 'Compile error', '9, then undefined behaviour at the end of main (double free)']" answer="d">

No copy constructor is written, so the default one copies the pointer: `b1.p` and `b2.p` share one block. `b2.set(9)` changes what `b1` shows, so it prints **9**. Then both destructors `delete` the same block: a double free. The fix is a deep copy constructor, `Box(const Box &b) { p = new int(*b.p); }`, as in the deep-copy program above.

</Mcq>

</Drill>

<Drill n="5" tag="Fill in" from="v2 drill 14">

<FillIn q="`class A { char a; int b; int c; char d; int e; int *f; };` sizeof(A) on a 64-bit machine is ____." answer="32">

a at 0 (then 3 padding), b at 4, c at 8, d at 12 (3 padding), e at 16, then 4 padding because the pointer needs a multiple of 8: f at 24, ending at 32. Verified above.

</FillIn>

</Drill>

<Drill n="6" tag="Concept" from="v2 drill 16">

```cpp
class Fruit {
    int shape; static int count;
public:
    void setData(int s)     { shape = s; count++; }
    static void showCount() { cout << count; }
    static void showShape() { cout << shape; }
};
```

<Mcq :options="['No errors', 'Error in setData', 'Error in showCount', 'Error in showShape']" answer="d">

A static member function has no `this`, so `shape` (non-static) has no object to belong to. `setData` is non-static, so it may use both; `showCount` is static using a static member, which is fine.

</Mcq>

</Drill>

<Drill n="7" tag="Output" from="v2 drill 17">

```cpp
class Student {
    int rollno;
    Student() { rollno = 0; }
public:
    static Student& setter() { static Student s; return s; }
    void set(int r) { rollno = r; }
    void show()     { cout << rollno; }
};
int main() {
    Student &a = Student::setter();
    Student &b = Student::setter();
    a.set(7);  b.show();
}
```

<Mcq :options="['0', '7', 'Compile error: private constructor', 'Garbage value']" answer="b">

`setter()` returns a reference to the same static object both times, so `a` and `b` are two names for one object. The private constructor is fine: it is called from inside the class.

</Mcq>

</Drill>

<Drill n="8" tag="Fill in">

<FillIn q="A `const` data member must be initialised in the constructor's ____." answer="member initializer list|initializer list|initialiser list|member initialiser list|initialization list">

After the colon: `Account(long n) : number(n) {}`. By the time the body runs, the member exists and cannot be assigned.

</FillIn>

</Drill>

<Drill n="9" tag="Concept">

A class declares `friend void show(Complex c);` and defines `void show(const Complex &c) { cout << c.real; }`. What happens?

<Mcq :options="['Works: they are the same function', 'Compile error: real is private in the defined function', 'Runtime error', 'Works, but makes a copy']" answer="b">

Different parameter lists make two different functions. Only the declared one is a friend; the defined one is an outsider, so `c.real` is inaccessible.

</Mcq>

</Drill>
