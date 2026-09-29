---
title: Unit 1 · OOP concepts
---

# Unit 1 · Introduction to OOP

Abstraction, objects, encapsulation, information hiding, methods, signatures, classes and instances, polymorphism, inheritance.

::: info How this unit is examined
- **Mid-semester:** every paper opens with a 2 or 3 mark "which OOP feature is this?" question. The description is a scenario; you name the feature, define it in one line, and show it in a short class. A one-word answer gets half marks at best.
- **Quiz:** "which two concepts are represented" MCQs, where the distractors are real concepts that almost fit.
:::

## Class and object

A **class** is a blueprint: a user-defined type that lists data (**data members**) and the functions that work on it (**member functions**, also called **methods**). An **object** is one **instance** of that class, a real thing in memory built from the blueprint.

```cpp
class Fruit {             // class: the blueprint
    int shape, colour;    // data members
public:
    void setData(int s, int c) { shape = s; colour = c; }   // member function (method)
};

Fruit f1, f2;             // two objects (instances) of Fruit
```

**What gets memory when an object is created.**
- **Data members**: every object gets its own copy. This is what `sizeof(object)` measures.
- **Member functions**: one shared copy of the code, in the code (text) segment. Objects do not carry their own copy of the functions.
- **Static data members**: one shared copy for the whole class, in the data segment, not inside any object.

So memory is given to **objects, not to the class**. The class alone occupies nothing until an object is made.

Because functions are shared, `f1.setData(10, 14)` is really `setData(&f1, 10, 14)`: the function has to be told which object to work on. That hidden argument is the **`this` pointer** (Unit 3).

## The four pillars

| Pillar | One line | Level | Example |
|---|---|---|---|
| **Abstraction** | Show *what* an object does, hide *how* | Design | You call `car.start()`; you do not see the ignition code |
| **Encapsulation** | Bind data and functions into one unit, and restrict access to the data | Implementation | `balance` is private; only `deposit()` and `withdraw()` touch it |
| **Inheritance** | A new class reuses an existing class and extends it | Reuse | `Car` inherits `start()` from `Vehicle` and adds `playMusic()` |
| **Polymorphism** | One name, many forms | Behaviour | `area(int)` and `area(double)`; `shape->draw()` |

::: danger Abstraction vs encapsulation
The two most confused words in the course. Abstraction is about **hiding complexity** (the user sees a simple interface). Encapsulation is about **hiding and protecting data** (private members behind public methods). A steering wheel is abstraction; the bonnet bolted shut is encapsulation. When a question describes "essential operations exposed **and** internals inaccessible", as Quiz 1 Q5 did, the answer is **both**.
:::

**Information hiding** (data hiding) is the mechanism that makes encapsulation work: marking members `private` so outside code cannot reach them. Its tool is the **access specifier** (Nov 2025 Q1).

**Message passing**: objects communicate by calling each other's public methods, `printer.print(text)` (Sep 2024 Q1a).

### Cohesion and coupling

| | Meaning | Want it |
|---|---|---|
| Cohesion | A class does its own job with its own members | **High** |
| Coupling | How much a class depends on other classes | **Low** |

Single responsibility: one class, one job. A `Student` class should not contain `bookTickets()`.

## Access specifiers

| Specifier | Reachable from |
|---|---|
| `private` | The class itself and its friends |
| `protected` | The class, its friends, and classes derived from it |
| `public` | Anywhere |

::: danger Default access
In a `class` the default is **private**; in a `struct` it is **public**. That is the only difference between them.
:::

## Method and signature

A **method** is a function that is a member of a class. A **signature** is a function's **name plus its parameter list** (the number, types and order of parameters). The return type is **not** part of the signature.

```cpp
int  add(int a);
void add(int a);   // ERROR: same signature, only the return type differs
int  add(int a, int b);   // fine: different parameter list, so an overload
```

## Polymorphism

```txt
Polymorphism ("many forms")
├── Compile time (static, early binding): decided by the compiler
│   ├── Function overloading      area(int), area(int, int)
│   └── Operator overloading      c1 + c2 for a Complex class
└── Run time (dynamic, late binding): decided while the program runs
    └── Function overriding       virtual draw() in Shape, redefined in Circle,
                                  called through a Shape* or Shape&
```

::: danger "Operator overriding" is not a thing
Operators are **overloaded**, and that is compile time. Overriding needs inheritance and `virtual`.
:::

## Inheritance

A **derived** (child) class inherits the members of a **base** (parent) class, reuses them unchanged and adds its own. It models an "is-a" relationship: a `Car` **is a** `Vehicle`. It solves **reusability** (write common code once) and **redundancy** (no duplicate copies). Oct 2025 Q1b and Sep 2024 Q1a asked exactly this. Types of inheritance and constructors in derived classes are Unit 5, after the mid-semester.

## Quick check

<Drill n="1" tag="Concept">

A class keeps its data private and lets other code change it only through public functions that check every value. Which principle is this?

<Mcq :options="['Abstraction', 'Encapsulation', 'Inheritance', 'Polymorphism']" answer="b">

Hidden data plus controlled public access is **encapsulation** (with data hiding). Abstraction would be about hiding *how* an operation works.

</Mcq>

</Drill>

<Drill n="2" tag="Concept">

Which of these is part of a function's signature?

<Mcq :options="['The return type', 'The parameter types and their order', 'The function body', 'The access specifier']" answer="b">

Signature = name + parameter list. Two functions that differ only in return type cannot coexist.

</Mcq>

</Drill>

<Drill n="3" tag="Fill in">

<FillIn q="Function overloading and operator overloading are examples of ____ polymorphism." answer="compile time|compile-time|static|compile time (static)|early binding">

Both are resolved by the compiler, before the program runs. Run-time polymorphism needs `virtual` functions and inheritance.

</FillIn>

</Drill>

<Drill n="4" tag="Fill in">

<FillIn q="In a `class`, members are ____ by default." answer="private">

`struct` defaults to public; that is the only difference.

</FillIn>

</Drill>

<Drill n="5" tag="Concept">

A child class reuses a parent's method without changing it and adds two methods of its own. Which concept?

<Mcq :options="['Overriding', 'Inheritance', 'Encapsulation', 'Overloading']" answer="b">

Reuse unchanged plus extension is **inheritance** (Oct 2025 Q1b). If the child *redefined* the method, that would be overriding.

</Mcq>

</Drill>
