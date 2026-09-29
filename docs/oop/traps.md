---
title: Most-trapped questions
pageClass: trap-page
---

# Most-trapped questions

The mistakes that cost the most marks across the four mid-semester papers, the end-semester paper, Quiz 1 and the five assignments, most frequent first. Each one says what students write, what is right, and where it was asked. For raw repeat counts per topic, see [how often questions repeat](./repeats).

::: tip Read this page the night before
It is the whole course compressed into the places where people slip. If a line surprises you, open the linked question.
:::

## 1. `static` inside a function remembers, and initialises once

**Students write:** the counter restarts every call; `static int s = n;` takes the new `n` each time.
**Right:** a static local is created once, lives in the data segment for the whole run, and its initialiser runs only on the **first** call, even when it is a variable.
**Asked:** <Src r="S24.Q4a" /> <Src r="R24.Q4a" /> <Src r="O25.Q2b" /> <Src r="QZ1.Q2" /> <Src r="A1.Q12" />

## 2. `&` or no `&`: the one-token output pair

**Students write:** the same output for both programs, or forget to explain.
**Right:** by value changes a copy (the caller's variable is unchanged); by reference or pointer changes the caller's variable. Half the marks are for **stating the reason**.
**Asked:** every mid-semester paper: <Src r="S24.Q4a" /> <Src r="R24.Q4a" /> <Src r="O25.Q4b" /> <Src r="N25.Q3" />, and <Src r="QZ1.Q6" />

## 3. The comma: separator vs operator

**Students write:** `a = 5, 4;` gives 4; `int a = 5, 4;` prints something.
**Right:** `=` binds tighter than the comma, so `a = 5, 4;` gives **5**; `a = (5, 4);` gives 4; `int a = 5, 4;` **does not compile** (in a declaration the comma is a separator and `4` is not a valid name).
**Asked:** <Src r="R24.Q1b" /> <Src r="O25.Q2a" /> <Src r="QZ1.Q1" /> <Src r="QZ1.Q9" /> <Src r="A1.Q8" /> <Src r="A1.Q9" />

## 4. `T b = a;` is the copy constructor; `b = a;` is assignment

**Students write:** anything with `=` is assignment.
**Right:** ask whether the left object **already exists**. Declared on this line → copy constructor. Made earlier → assignment operator, and no constructor runs. Passing an object **by value** also calls the copy constructor.
**Asked:** <Src r="O25.Q3b" /> <Src r="E24.Q6a" /> <Src r="A5.Q7" /> <Src r="O25.Q3a" />

## 5. Dynamic constructor details

**Students write:** `new char[strlen(s)]`; `strcpy` twice when joining; no `delete[]` before re-allocating; no destructor.
**Right:** `new char[len + 1]` (room for `'\0'`; no `+ 1` for `int` arrays); `strcpy` then `strcat`; `delete[]` the old block first; free it in `~String()`; and a deep copy constructor if objects are returned or copied.
**Asked:** <Src r="S24.Q2" /> <Src r="R24.Q2" /> <Src r="E24.Q4" /> <Src r="A5.Q3" /> <Src r="A5.Q4" /> <Src r="A5.Q5" />

## 6. Member operator: one parameter; friend operator: two

**Students write:** `ABC operator-(ABC a, ABC b)` inside the class; or change `x` and return `*this`.
**Right:** a member binary operator takes **one** parameter (the left operand is `*this`); a friend takes two and has no `this`. Build and **return a new object**; do not change the operands.
**Asked:** <Src r="S24.Q3" /> <Src r="R24.Q3" /> <Src r="A5.Q4" /> <Src r="A5.Q5" /> <Src r="N25.Q8" />

## 7. Type conversion: know which of the three

**Students write:** the wrong direction, or both routes for class to class.
**Right:** basic → class = one-argument **constructor**; class → basic = **`operator int()`** (no return type, no parameters, member); class → class = conversion operator in the source **or** constructor in the destination, **never both** (ambiguous).
**Asked:** <Src r="S24.Q5a" /> <Src r="R24.Q5a" /> <Src r="N25.Q7a" />. No assignment covers it; learn it from [Unit 4](./notes/unit-4#type-conversions).

## 8. Default arguments make overloads ambiguous

**Students write:** the compiler picks the one-parameter version.
**Right:** `f(int a, int b = 5)` is also a one-argument candidate, so alongside `f(int a)` the call `f(1)` is a **compile error**. Defaults fill from the right and go in the declaration only.
**Asked:** <Src r="QZ1.Q8" /> <Src r="QZ1.Q4" /> <Src r="A5.Q9" /> <Src r="A3.Q17" />

## 9. Static member functions have no `this`

**Students write:** a static function printing a non-static member; calling it only through an object.
**Right:** it can use static members only (or an object passed in); call it as `ClassName::f()`; it can run before any object exists; it cannot be `const` or `virtual`. A static data member also needs its one definition outside the class (or `inline static`).
**Asked:** <Src r="R24.Q4b" /> <Src r="N25.Q2" /> <Src r="A5.Q6" />

## 10. Undefined behaviour in increment questions

**Students write:** a confident single answer for `x = ++x + x++ + x++;`.
**Right:** give the left-to-right textbook answer **and** state that modifying `x` twice without a sequence point is undefined behaviour (GCC warns about it). The comma operator, by contrast, *is* a sequence point, so `b = (a++, ++a)` is fine.
**Asked:** <Src r="R24.Q4a" />

## 11. Output that is a compile error

**Students write:** an output.
**Right:** check for errors first. Recent examples: `int a = 5, 4;`, an ambiguous `test(10, 6)`, a local variable used in `main`, a static function reading a non-static member.
**Asked:** <Src r="O25.Q2a" /> <Src r="QZ1.Q8" /> <Src r="N25.Q6" /> <Src r="R24.Q4b" />

## 12. Array parameters are pointers

**Students write:** `sizeof(arr)` inside a function to find the length.
**Right:** an array parameter is a pointer (8 bytes); pass the size separately. In `main`, `sizeof(arr) / sizeof(arr[0])` works.
**Asked:** <Src r="R24.Q2" /> <Src r="QZ1.Q6" />

## 13. Uninitialised members hold garbage

**Students write:** `0, 0`.
**Right:** the compiler's default constructor does not set members; a local object prints garbage. Write your own default constructor.
**Asked:** <Src r="E24.Q3b" />

## 14. Friend declaration and definition must match

**Students write:** `friend Complex add(Complex, Complex);` but define `add(const Complex &, const Complex &)`.
**Right:** those are two different functions; the defined one is not a friend and cannot touch private data. A member of another class as a friend needs the forward declaration and a definition **after** both classes.
**Asked:** <Src r="N25.Q5" /> <Src r="A5.Q1" /> <Src r="A4.Q3" />

## Mistakes in her papers: state an assumption

The paper says "Assume the missing data". Where a question is impossible or contradicts itself, write one line naming the problem and your assumption, then answer. That line is worth marks.

| Question | The problem | Assumption to write |
|---|---|---|
| <Src r="R24.Q2" /> | A constructor taking "one integer array" must work out its length, but an array parameter is a pointer | Pass the length as a second parameter |
| <Src r="E24.Q4" />, <Src r="A5.Q5" /> | `+` used both to join (friend) and to compare (member): the two would be ambiguous | Use `<` (or another operator) for the comparison |
| <Src r="A5.Q5" /> | Two different objects both called `string3` | Call the fourth one `string4` |
| <Src r="A5.Q4" /> | Part IV(a) compares array1 with array3, part IV(b) with array2 | Compare array1 and array2 |
| <Src r="A5.Q1" /> | "Make Point a friend of calculate1" is backwards | `calculate1` is made a friend of `Point` |
| <Src r="A5.Q1" /> | "2DCrossProduc Magnitude" is not a legal identifier | Rename it, e.g. `crossProduct2DMagnitude` |
| <Src r="N25.Q5" /> | "Return the object with the larger sum" from two unrelated classes has no single return type | Return which one is larger, or its sum |
| <Src r="N25.Q7b" /> | "Using operator overloading" without saying which operator | Overload `()` (or `*`), and say so |
| <Src r="E24.Q5c" /> | `Student1 = new student1;` does not compile | Point it out, then answer the intended question |
| <Src r="R24.Q4a" /> | `x = ++x + x++ + x++;` is undefined behaviour | Give the textbook value and say it is UB |
