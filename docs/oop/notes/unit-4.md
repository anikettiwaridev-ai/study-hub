---
title: Unit 4 · Operator overloading and conversions
---

# Unit 4 · Operator overloading and type conversion

Unary and binary operators as members and as friends, prefix and postfix `++`, the assignment operator and what the default one breaks, `<<` and `>>`, operators that cannot be overloaded, conversions between classes and basic types, and the pitfalls.

::: info How this unit is examined
- **Mid-semester:** a member-operator class (Sep 2024 Q3, Remedial Q3), an operator inside the long class question (A5 Q4, Q5), and a **type-conversion** question worth 4 marks in three of the four papers, which no assignment covers. This page is the only place to learn conversions.
- **Quiz:** prefix vs postfix (`myObj++` calls the `int` version), how many parameters a member or friend operator takes, which operators cannot be overloaded.
:::

## Why overload an operator

`+`, `-`, `<<` and the rest work only on built-in types. For `Complex c3 = c1 + c2;` the compiler has no idea what `+` means for a `Complex`, so it reports an error. **Operator overloading** gives an existing operator a meaning for your class. It is **compile-time polymorphism**: the compiler turns the operator into a function call.

```cpp
ReturnType operator@(parameters) { … }    // @ is the operator: +, -, ==, <<, ++ …
```

## Member or friend: how many parameters

The compiler rewrites every use of an operator as a call:

| Expression | As a **member** | As a **friend** (non-member) |
|---|---|---|
| `-a` (unary) | `a.operator-()`: **0 parameters** | `operator-(a)`: **1 parameter** |
| `a + b` (binary) | `a.operator+(b)`: **1 parameter** | `operator+(a, b)`: **2 parameters** |
| `a++` (postfix) | `a.operator++(0)`: dummy `int` only | `operator++(a, 0)`: object **first**, dummy `int` second |

**A member always has one parameter fewer**, because the left (or only) operand is the object the function is called on: `*this`. A friend is not called on an object, so every operand is a parameter, and it has **no `this`**.

## Unary operators

### Unary minus as a member and as a friend

::: code-group
<<< @/../code/oop/notes/u4-unary-member.cpp [Member]
<<< @/../code/oop/notes/u4-unary-member.out{txt} [Output]
<<< @/../code/oop/notes/u4-unary-friend.cpp [Friend]
<<< @/../code/oop/notes/u4-unary-friend.out{txt} [Output]
:::

Both build and **return a new object** and leave `a1` alone, the way `-x` leaves `x` alone for an `int`.

::::: danger Pitfall: changing the operand
A common version negates the members in place and returns `*this`. It compiles, but `a2 = -a1` then **also negates `a1`**:

::: code-group
<<< @/../code/oop/notes/u4-unary-pitfall.cpp [Program]
<<< @/../code/oop/notes/u4-unary-pitfall.out{txt} [Output]
:::

And a friend written as `void operator-(abc a)` negates a **copy** and returns nothing, so `abc a2 = -a1;` does not even compile. Return the new object.
:::::

### Prefix and postfix `++`

The compiler tells them apart by a **dummy `int` parameter** that is never used:
- `operator++()` → **prefix**, `++a`: increment, then return the object itself (by reference).
- `operator++(int)` → **postfix**, `a++`: remember the old value, increment, return the **old** value (by value).

::: code-group
<<< @/../code/oop/notes/u4-increment-member.cpp [Member]
<<< @/../code/oop/notes/u4-increment-member.out{txt} [Output]
<<< @/../code/oop/notes/u4-increment-friend.cpp [Friend]
<<< @/../code/oop/notes/u4-increment-friend.out{txt} [Output]
:::

::::: danger `this` does not exist in a friend
A friend operator must return its parameter, not `*this`:

::: code-group
<<< @/../code/oop/notes/u4-friend-this.cpp [Program]
<<< @/../code/oop/notes/u4-friend-this.out{txt} [Compiler says]
:::

And the friend postfix form is `operator++(abc &a, int)`: the object first, the dummy `int` second, the object **by reference** (otherwise only a copy is incremented).
:::::

## Binary operators

::: code-group
<<< @/../code/oop/notes/u4-binary.cpp [Program]
<<< @/../code/oop/notes/u4-binary.out{txt} [Output]
:::

- `c1 + c2` → `c1.operator+(c2)`: `c1` is `this`, `c2` is the parameter.
- `c1 * c2` → `operator*(c1, c2)`: both are parameters.
- Complex multiplication is (a + bi)(c + di) = **(ac − bd) + (ad + bc)i**, not (ac) + (bd)i.
- **Precedence and associativity never change.** `c1 + c2 * c1` still does `*` first. Overloading changes what an operator *does*, never how an expression is grouped or how many operands it takes.

### When a binary operator has to be a friend

If the **left** operand is not an object of your class, a member cannot work, because a member is always called on its left operand:

::: code-group
<<< @/../code/oop/notes/u4-friend-needed.cpp [Program]
<<< @/../code/oop/notes/u4-friend-needed.out{txt} [Output]
:::

`m + 5` can be a member (`m.operator+(5)`), but `5 + m` would mean `5.operator+(m)`, and `5` is an `int`. It must be a friend (or plain non-member) `operator+(int, const Money&)`.

## The assignment operator

`o2 = o1;` on objects that already exist calls `operator=`. If you do not write one, the compiler supplies one that copies **member by member**. For a class with a pointer, that copies the **address**, a shallow copy, exactly like the default copy constructor.

```txt
 class A { int a; int *b; }      o1.b -> [40] at 1000     o2.b -> [50] at 2000

 after o2 = o1 with the DEFAULT operator=
 o1.b --+
        +--> [40] at 1000        [50] at 2000 is still allocated, but nothing points to it
 o2.b --+
```

**What the default assignment breaks** (syllabus Unit 4 item 3, word for word):

| Problem | What happens |
|---|---|
| **Memory leak** | `o2`'s old block (2000) is never freed; its only pointer was overwritten |
| **Object isolation** lost | `o1` and `o2` share one block: changing one changes the other |
| **Dangling pointer** | when one object is destroyed and frees 1000, the other still points there |
| **Double free crash** | when the second destructor frees 1000 again |

### A correct `operator=`

```cpp
A &operator=(const A &o) {
    if (this == &o) return *this;   // 1. a = a must not destroy itself
    delete b;                       // 2. free what this object holds: no leak
    b = new int(*o.b);              // 3. own block, copied VALUE: isolation
    return *this;                   // 4. return the object, by reference
}
```

::: code-group
<<< @/../code/oop/notes/u4-assignment.cpp [Program]
<<< @/../code/oop/notes/u4-assignment.out{txt} [Output]
:::

**Why return `*this` by reference.** `=` groups **right to left**, so `o1 = o2 = o3` means `o1 = (o2 = o3)`: the result of `o2 = o3` becomes the right side of the next assignment. Returning a reference hands back `o2` itself, with no copy.

::::: warning What returning by value or `void` actually does
- **By value** (`A operator=`): `a1 = a2 = a3` **still works**; every object ends up equal, just with extra copies. What breaks is `(a1 = a2) = a7;`, which then assigns to a temporary copy, not to `a1`:

::: code-group
<<< @/../code/oop/notes/u4-assign-by-value.cpp [Program]
<<< @/../code/oop/notes/u4-assign-by-value.out{txt} [Output]
:::

- **`void`**: a single `a1 = a2;` works, but `a1 = a2 = a3` does **not compile**, because `a2 = a3` gives nothing to assign to `a1`.
:::::

Copy constructor vs assignment: the constructor makes a **new** object and has nothing to free; `operator=` works on an object that **already exists** and must free what it held first. Rule of three: a class that needs a destructor needs a deep copy constructor and a deep `operator=` as well.

## Overloading `<<` and `>>`

::: code-group
<<< @/../code/oop/notes/u4-stream.cpp [Program]
<<< @/../code/oop/notes/u4-stream.in{txt} [Input]
<<< @/../code/oop/notes/u4-stream.out{txt} [Output]
:::

**Why they cannot be member functions** (of your class). In `cout << p`, the **left** operand is `cout`, an `ostream`. A member function is always called on its left operand, so a member `operator<<` would have to belong to `ostream`, a library class you cannot edit. So it is written as a non-member, and made a **friend** to reach the private data. (A member `operator<<` inside `Point` would have to be used as `p << cout`, which nobody wants.)

**Why the stream is passed and returned by reference.**
- A stream **cannot be copied** (its copy constructor is deleted), so it must be passed by reference.
- Returning the **same** stream is what lets `cout << p << ", " << q` chain: each `<<` returns `cout` for the next one.
- The object: `const Point &` for output (no copy, not changed), `Point &` for input (`>>` must write into it).

## Operators that cannot be overloaded

| Operator | Name | Why not |
|---|---|---|
| `.` | member access | would change how every member is reached |
| `.*` | pointer-to-member access | same reason |
| `::` | scope resolution | works on names at compile time, not on values |
| `?:` | conditional | must evaluate only one of its branches |
| `sizeof` | size of | a compile-time question about a type |
| `typeid` | type information | a built-in language feature |

::: code-group
<<< @/../code/oop/notes/u4-no-overload.cpp [Trying operator.]
<<< @/../code/oop/notes/u4-no-overload.out{txt} [Compiler says]
:::

:::: warning Unary `*` (dereference) CAN be overloaded
It is a common wrong entry in these lists. Smart pointers overload it:

::: code-group
<<< @/../code/oop/notes/u4-deref.cpp [Program]
<<< @/../code/oop/notes/u4-deref.out{txt} [Output]
:::
::::

**Operators that must be members:** `=`, `[]`, `()` and `->`. The language requires their left operand to be an object of the class. **Operators that in practice cannot be members:** `<<` and `>>` with a stream, and any binary operator whose left operand is a basic type (`5 + m`).

You cannot invent new operators (no `**`), change the number of operands, change precedence or associativity, or redefine an operator for built-in types only (`int + int` is fixed); at least one operand must be a class object.

## Type conversions

Three situations; learn this table first.

| Direction | Example statement | How | Written in |
|---|---|---|---|
| Basic → class | `emp = Ecode;` | constructor with one argument of the basic type | the class |
| Class → basic | `duration = t;` | conversion operator `operator int()` | the class |
| Class → class | `mob = comp;` | conversion operator in the **source**, **or** one-argument constructor in the **destination** | one of the two, **never both** |

### Basic to class (implicit and explicit)

::: code-group
<<< @/../code/oop/notes/u4-basic-to-class.cpp [Program]
<<< @/../code/oop/notes/u4-basic-to-class.out{txt} [Output]
:::

A constructor that can be called with one argument doubles as a converter. **Implicit:** `Meters a = 5.5;` and `b = 12;`, where the compiler calls it by itself. **Explicit:** `Meters c(3.0);` or `Meters(7)`, where you call it. Writing `explicit` before the constructor forbids the implicit form ([Nov 2025 Q7a](../papers/mst-2025-nov#q7a) shows the compiler's error).

### Class to basic

::: code-group
<<< @/../code/oop/notes/u4-class-to-basic.cpp [Program]
<<< @/../code/oop/notes/u4-class-to-basic.out{txt} [Output]
:::

`operator double() const { return m; }` has **no return type in front** (the name says it), **no parameters**, and must be a **member**. Marking it `explicit` means it runs only when you ask with a cast.

### Class to class

::: code-group
<<< @/../code/oop/notes/u4-class-to-class.cpp [Program]
<<< @/../code/oop/notes/u4-class-to-class.out{txt} [Output]
:::

- Route 1, in the **source** class: `operator Fahrenheit() const` inside `Celsius`.
- Route 2, in the **destination** class: `Kelvin(const Fahrenheit &)`. The destination needs access to the source's data, through getters or friendship.

::::: danger Never define both routes for the same pair
Then `B b = a;` has two equally good conversions and standard C++ rejects it:

::: code-group
<<< @/../code/oop/notes/u4-both-routes.cpp [Both routes]
<<< @/../code/oop/notes/u4-both-routes.out{txt} [Compiler says]
:::

Two details: plain GCC without strict flags quietly picks one and compiles, which hides the bug; and the direct form `B b(a);` compiles even in strict mode, because a direct constructor call prefers the constructor. Do not rely on either. Write one route.
:::::

## Pitfalls of operator overloading

1. **Surprising meaning.** `+` that subtracts, or `==` that compares only lengths without saying so, makes code lie. Keep the natural meaning.
2. **Changing the operands.** Binary and unary operators such as `+`, `-`, `*` should return a new object and leave their operands alone (the unary-minus pitfall above). Only `=`, `+=`, `++`, `--` are expected to change the object.
3. **Wrong return type.** `void operator+` makes `c3 = c1 + c2` impossible; `void operator=` breaks chaining; returning a reference to a **local** object leaves a dangling reference.
4. **Shallow copying.** Overloading `=` without also writing a deep copy constructor and destructor (or the other way round) still leaks, dangles or double-frees.
5. **Missing `const`.** A member operator that should not change `*this` should be `const`, or it cannot be used on `const` objects; take the other operand by `const &`.
6. **Precedence cannot be changed.** Overloading `^` for "power" still gives it lower precedence than `+`, so `a + b ^ 2` means `(a + b) ^ 2`.
7. **`&&`, `||` and `,` lose their special behaviour** when overloaded: the short-circuit (and, before C++17, the guaranteed order) is lost. Avoid overloading them.
8. **Ambiguity.** A conversion defined both ways (above), or a friend and a member version of the same operator with the same operands, makes calls ambiguous. See [End-sem 2024 Q4](../papers/endsem-2024#q4).
9. **Too many implicit conversions.** A one-argument constructor lets the compiler convert silently in places you did not intend. Use `explicit` when that is a risk.

## Quick check

<Drill n="1" tag="Output">

```cpp
class MyClass {
    int i;
public:
    MyClass(int num) { i = num; }
    void operator++(int)  { cout << "First"; }
    void operator++(void) { cout << "second"; }
};
int main() { MyClass myObj(10); myObj++; }
```

<Mcq :options="['First', 'second', 'Firstsecond', 'Compile error: ambiguous']" answer="a">

`myObj++` is postfix, which is the version with the dummy `int`. This is [Nov 2025 Q8](../papers/mst-2025-nov#q8).

</Mcq>

</Drill>

<Drill n="2" tag="Fill in">

<FillIn q="A binary operator overloaded as a friend function takes ____ parameters." answer="2|two">

A friend has no `this`, so both operands are parameters. As a member it takes 1.

</FillIn>

</Drill>

<Drill n="3" tag="Concept">

Which of these operators cannot be overloaded?

<Mcq :options="['* (dereference)', '[] (subscript)', ':: (scope resolution)', '<< (insertion)']" answer="c">

The list is `.` `.*` `::` `?:` `sizeof` `typeid`. Dereference `*` can be overloaded, and smart pointers do it.

</Mcq>

</Drill>

<Drill n="4" tag="Concept">

`duration = t;` where `t` is a `Time` object and `duration` is an `int`. What must the class provide?

<Mcq :options="['A constructor Time(int)', 'A conversion operator operator int()', 'An overloaded operator=', 'A friend function']" answer="b">

Class → basic needs a conversion operator in the class. `Time(int)` would be basic → class, the opposite direction. This is [Sep 2024 Q5a](../papers/mst-2024-sep#q5a).

</Mcq>

</Drill>

<Drill n="5" tag="Concept">

Why must `operator<<` for printing a class be a non-member (usually a friend)?

<Mcq :options="['Because it needs this', 'Because the left operand is cout, not an object of the class', 'Because members cannot return references', 'Because << cannot be overloaded as a member of any class']" answer="b">

A member is called on its left operand. In `cout << p` that is `cout`, whose class `ostream` you cannot edit. It is a friend so it can read the private data.

</Mcq>

</Drill>

<Drill n="6" tag="Fill in">

<FillIn q="In `o1 = o2 = o3;` the assignment done first is `o2 = o3`, because `=` associates ____." answer="right to left|right-to-left|from right to left">

That is why `operator=` returns `*this` by reference: the result of `o2 = o3` feeds the next assignment.

</FillIn>

</Drill>

<Drill n="7" tag="Output">

```cpp
class Score {
    int s;
public:
    Score(int v) { s = v; }
    Score operator++()    { ++s; return *this; }
    Score operator++(int) { Score old = *this; s += 10; return old; }
    int get() { return s; }
};
int main() {
    Score a(1);
    Score b = a++;
    Score c = ++a;
    cout << a.get() << " " << b.get() << " " << c.get();
}
```

<Mcq :options="['3 1 3', '12 1 12', '12 11 12', '2 1 3']" answer="b">

Read the bodies, not the operator names: this postfix adds **10**. `a++` hands back the old value 1 (so b = 1) and makes a = 11; `++a` makes a = 12 and returns it (c = 12). Output `12 1 12`. The [mock paper's version](../mock-mst#q4b) also prints which operator ran, and confirms it.

</Mcq>

</Drill>
