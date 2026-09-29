---
title: Quiz practice
---

# Quiz practice

Quizzes test the same syllabus as the mid-semester in a different form: output prediction with trap options, "which concept" questions and fill in the blanks. Speed and precision matter more than explanation. Everything here marks itself.

::: tip How to use this page
1. Do the **mock quiz** in one sitting, about 15 minutes, without notes.
2. For every miss, read the explanation, then find the topic in the notes.
3. Use **rapid recall** the morning of the quiz.

More questions of the same kind: the **Quick check** at the end of each notes unit ([1](./notes/unit-1#quick-check), [2](./notes/unit-2#quick-check), [3](./notes/unit-3#quick-check), [4](./notes/unit-4#quick-check)) and [Quiz 1 itself](./papers/quiz-1).
:::

## Mock quiz

Ten questions in the style of Quiz 1, weighted towards Units 3 and 4. Every output was produced by running the code.

<Drill n="1" tag="Output">

```cpp
class Seat {
    static int booked;
public:
    Seat()  { booked++; }
    ~Seat() { booked--; }
    static int count() { return booked; }
};
int Seat::booked = 0;
int main() {
    Seat a, b;
    { Seat c, d; cout << Seat::count() << " "; }
    Seat e;
    cout << Seat::count();
}
```

<Mcq :options="['4 5', '4 3', '4 4', '2 3', '4 1']" answer="b">

<<< @/../code/oop/quiz/qp-q1.out{txt} [Output]

Four seats exist inside the block (4). At its `}`, c and d are destroyed and the count drops to 2; e makes it 3. The trap answer 5 forgets that destructors run at the end of the inner block.

</Mcq>

</Drill>

<Drill n="2" tag="Output">

```cpp
int a = 1, b = 2;
int c = (a += b, b += a, a * b);
cout << a << b << c;
```

<Mcq :options="['3 5 15', '3515', '1215', '355', 'Undefined behaviour']" answer="b">

<<< @/../code/oop/quiz/qp-q2.out{txt} [Output]

The comma operator runs left to right with a sequence point after each part: a = 3, then b = 5, then 3 × 5 = 15. Nothing is printed between the numbers, so they run together: `3515`.

</Mcq>

</Drill>

<Drill n="3" tag="Concept">

```cpp
class Box {
public:
    Box()                  { }
    Box(int l, int w = 2)  { }
    Box(int l)             { }
};
```

Which declaration does **not** compile?

<Mcq :options="['Box a;', 'Box b(4);', 'Box c(4, 5);', 'All three compile']" answer="b">

`Box b(4)` matches `Box(int, int = 2)` and `Box(int)` equally well: ambiguous. `Box a` has only one candidate and `Box c(4, 5)` has only one candidate.

</Mcq>

</Drill>

<Drill n="4" tag="Output">

```cpp
class Wallet {
    int *cash;
public:
    Wallet(int c) { cash = new int(c); }
    Wallet(const Wallet &w) { cash = new int(*w.cash); }
    ~Wallet() { delete cash; }
    void spend(int x) { *cash -= x; }
    int left() { return *cash; }
};
int main() {
    Wallet w1(500);
    Wallet w2 = w1;
    w2.spend(200);
    cout << w1.left() << " " << w2.left();
}
```

<Mcq :options="['300 300', '500 300', '500 500', 'Crash: double free']" answer="b">

<<< @/../code/oop/quiz/qp-q4.out{txt} [Output]

This copy constructor is **deep**: `new int(*w.cash)` gives w2 its own block. Spending from w2 leaves w1 alone. With the default (shallow) copy, the answer would be `300 300` followed by a double free.

</Mcq>

</Drill>

<Drill n="5" tag="Output">

```cpp
class Level {
    int n;
public:
    Level(int x) { n = x; }
    Level &operator++() { ++n; return *this; }
    int get() { return n; }
};
int main() { Level a(5); ++(++a); cout << a.get(); }
```

<Mcq :options="['5', '6', '7', 'Compile error']" answer="c">

<<< @/../code/oop/quiz/qp-q5.out{txt} [Output]

Prefix `++` returns `*this` **by reference**, so the outer `++` works on `a` itself: 5 → 6 → 7. If it returned by value, the second `++` would change a temporary copy and the answer would be 6.

</Mcq>

</Drill>

<Drill n="6" tag="Concept">

Which operator can **not** be overloaded?

<Mcq :options="['->', '()', '?:', '[]', 'unary *']" answer="c">

`?:` must evaluate only one branch, so it cannot become an ordinary function call. The full list: `.` `.*` `::` `?:` `sizeof` `typeid`. `->`, `()` and `[]` can be overloaded but must be members.

</Mcq>

</Drill>

<Drill n="7" tag="Output">

```cpp
class Item {
    int id;
public:
    Item(int i) { id = i; cout << "C" << id << " "; }
    Item(const Item &o) { id = o.id + 10; cout << "K" << id << " "; }
    ~Item() { cout << "D" << id << " "; }
};
void use(Item x) { cout << "use "; }
int main() {
    Item a(1);
    use(a);
    Item *p = new Item(2);
    delete p;
    cout << "end ";
}
```

<FillIn q="Write the complete output." answer="C1 K11 use D11 C2 D2 end D1">

<<< @/../code/oop/quiz/qp-q7.out{txt} [Output]

`use(a)` takes its parameter **by value**, so the copy constructor makes `x` (id 11); `x` is destroyed when `use` returns (D11). The heap object is destroyed exactly when `delete p` runs (D2). `a` is destroyed at the end of `main`, after "end".

</FillIn>

</Drill>

<Drill n="8" tag="Output">

```cpp
class P1 { char a; double b; char c; };
class P2 { double b; char a; char c; };
cout << sizeof(P1) << " " << sizeof(P2);
```

<Mcq :options="['10 10', '24 16', '24 24', '16 16', '17 10']" answer="b">

<<< @/../code/oop/quiz/qp-q8.out{txt} [Output]

P1: `a` at 0, 7 padding, `b` at 8 to 16, `c` at 16, then round 17 up to a multiple of 8: **24**. P2: `b` 0 to 8, `a` at 8, `c` at 9, round 10 up to **16**. Largest first saves 8 bytes.

</Mcq>

</Drill>

<Drill n="9" tag="Fill in">

<FillIn q="A static member function cannot directly use ____ data members, because it has no `this` pointer." answer="non-static|nonstatic|non static">

It can use static members only, unless an object is passed to it as a parameter.

</FillIn>

</Drill>

<Drill n="10" tag="Output">

```cpp
class M {
    int v;
public:
    M(int x) { v = x; cout << "C"; }
    operator int() { cout << "O"; return v; }
};
int main() {
    M m = 5;
    int k = m + 2;
    cout << k;
}
```

<Mcq :options="['C7', 'CO7', 'OC7', 'Compile error', 'CO5']" answer="b">

<<< @/../code/oop/quiz/qp-q10.out{txt} [Output]

`M m = 5;` is basic → class, so the constructor runs (C). `m + 2`: no `operator+` exists for `M`, so the compiler converts `m` to `int` with `operator int()` (O), and 5 + 2 = 7.

</Mcq>

</Drill>

## Rapid recall

One-liners she can ask cold. Type the answer; spelling variants are accepted.

<Drill n="1" tag="Fill in">

<FillIn q="Memory for member functions is in the ____ segment, one copy for all objects." answer="code|text|code (text)|text (code)">

Only data members are per object; `sizeof` counts them alone.

</FillIn>

</Drill>

<Drill n="2" tag="Fill in">

<FillIn q="The default value of a global or static variable is ____." answer="0|zero">

Locals start with garbage.

</FillIn>

</Drill>

<Drill n="3" tag="Fill in">

<FillIn q="The comma operator has the ____ precedence of all operators." answer="lowest|least">

Lower even than `=`, so `a = 5, 4;` stores 5.

</FillIn>

</Drill>

<Drill n="4" tag="Fill in">

<FillIn q="`Complex c4 = c1;` calls the ____." answer="copy constructor">

c4 is being created, so it is construction, not assignment.

</FillIn>

</Drill>

<Drill n="5" tag="Fill in">

<FillIn q="A copy constructor's parameter must be passed by ____." answer="reference|const reference|const&|const &">

By value would need a copy to make a copy: infinite recursion, so the compiler rejects it.

</FillIn>

</Drill>

<Drill n="6" tag="Fill in">

<FillIn q="Destructors are called in ____ order of construction." answer="reverse|the reverse|opposite">

And an inner block's objects at that block's closing brace.

</FillIn>

</Drill>

<Drill n="7" tag="Fill in">

<FillIn q="A class can have exactly ____ destructor(s)." answer="1|one">

No parameters, so no overloading.

</FillIn>

</Drill>

<Drill n="8" tag="Fill in">

<FillIn q="Memory from `new[]` must be released with ____." answer="delete[]|delete []">

`new` pairs with `delete`, `new[]` with `delete[]`.

</FillIn>

</Drill>

<Drill n="9" tag="Fill in">

<FillIn q="A pointer that still holds the address of freed memory is a ____ pointer." answer="dangling">

Set it to `nullptr` after `delete`.

</FillIn>

</Drill>

<Drill n="10" tag="Fill in">

<FillIn q="The keyword that stops a one-argument constructor being used for implicit conversion is ____." answer="explicit">

`explicit Employee(int c);` then `emp = 5;` no longer compiles.

</FillIn>

</Drill>

<Drill n="11" tag="Fill in">

<FillIn q="The postfix `++` operator is told apart from prefix by a dummy parameter of type ____." answer="int">

`operator++(int)` is postfix, `operator++()` is prefix.

</FillIn>

</Drill>

<Drill n="12" tag="Fill in">

<FillIn q="Class to basic type conversion uses a ____ function, such as `operator int()`." answer="conversion|conversion operator|casting operator|casting|type conversion">

No return type written, no parameters, must be a member.

</FillIn>

</Drill>

<Drill n="13" tag="Fill in">

<FillIn q="Friendship is not mutual and not ____." answer="inherited|transitive">

Also not transitive: a friend of a friend is not a friend.

</FillIn>

</Drill>

<Drill n="14" tag="Fill in">

<FillIn q="A constructor that allocates memory with `new` is called a ____ constructor." answer="dynamic">

Dynamic *initialisation* is different: it only means the values are known at run time.

</FillIn>

</Drill>

<Drill n="15" tag="Fill in">

<FillIn q="The design pattern that uses a private constructor and a static function returning a reference to one object is the ____ pattern." answer="singleton">

Example from class: the head of department.

</FillIn>

</Drill>

<Drill n="16" tag="Fill in">

<FillIn q="In a `class`, the default access specifier is ____; in a `struct` it is public." answer="private">

That is the only difference between them.

</FillIn>

</Drill>
