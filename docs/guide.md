---
title: Using this site
---

# Using this site

## Practising with it

**Solutions start hidden.** Attempt the question, then open its solution. **Show solutions** in the top bar opens every solution on the page at once, for revision.

**Traps only** strips a page down to its traps and corrections, the things that actually cost marks. Use it the night before.

**Mark done** sits beside every question. Tick it only when you could answer without looking. Progress is saved on this device, so your phone and laptop keep separate counts.

**Two kinds of practice.** Mid-semester papers are answered in writing, so their solutions are full explanations and programs. Quiz-style questions (the Quiz 1 page, *Quiz practice*, and the **Quick check** at the end of every notes unit) are answered on the page: tap an option, or type into a blank and press **Check**. Blanks accept common spellings; **Show answer** gives up gracefully.

**Repeat labels** sit above a question when it has appeared elsewhere:

- **⟳ Exact**: the same question word for word.
- **≈ Reworded**: the same question in different words.
- **Δ Variant**: the same structure with different data, names or operator.

"Asked 6 times" opens that topic in [the repeat map](/oop/repeats), with every appearance listed.

## Installing it on your phone

On Android, open the site in Chrome, open the menu, and choose **Install app** or **Add to Home screen**. On iPhone, open it in Safari, tap **Share**, then **Add to Home Screen**.

It then opens like an app and works offline. When new questions are published, it updates itself the next time you open it with a connection.

## What a solved question looks like

This is Oct 2025 Q2a, as it will appear in the papers section. The program output in the solution comes from compiling and running the code, not from working it out by hand.

<Q id="O25.Q2a" subject="oop">

How is the comma as a *separator* different from the comma as an *operator*? Find the output in each case, and explain why parentheses matter for the comma operator.

::: code-group
<<< @/../code/oop/papers/o25-q2a-case1.cpp [Case 1]
<<< @/../code/oop/papers/o25-q2a-case2.cpp [Case 2]
<<< @/../code/oop/papers/o25-q2a-case3.cpp [Case 3]
:::

::::: details Solution

As a **separator**, the comma only lists things. `int a, b;` declares two variables and `f(x, y)` passes two arguments. There is no value involved.

As an **operator**, `(x, y)` evaluates `x`, discards the result, then evaluates `y`, and the whole expression takes `y`'s value. It has the lowest precedence of any operator, lower even than `=`.

::: code-group
<<< @/../code/oop/papers/o25-q2a-case1.out{txt} [Case 1 output]
<<< @/../code/oop/papers/o25-q2a-case2.out{txt} [Case 2 output]
<<< @/../code/oop/papers/o25-q2a-case3.out{txt} [Case 3 output]
:::

**Case 1 prints 5.** `=` binds tighter than `,`, so the line is read as `(a = 5), 4;`. `a` becomes 5; the 4 is evaluated and thrown away.

**Case 2 prints 4.** The parentheses make the comma operator run first. `(5, 4)` evaluates to 4, which is then assigned.

**Case 3 does not compile.** In a declaration the comma is a separator, so the compiler reads `4` as the name of a second variable. A name cannot start with a digit.

**Why parentheses matter:** without them, `=` always wins over the comma operator. Parentheses are the only way to make the comma decide the value.

::: danger
`int a = 5, 4;` is not a trick output question. It is a compile error, and writing an output for it loses the marks.
:::

:::::

</Q>

Quiz questions become multiple choice you can answer on the page.

<Q id="QZ1.Q9" subject="oop">

What will be the output of the following code?

<<< @/../code/oop/papers/qz1-q9.cpp

<Mcq :options="['Error', '5, 5, 5, hello', '5, 5, 5, 3', 'hello6, 5, 5, 3', 'hello5, 5, 5, 3', '6, 5, 5, 3', '6, 5, 5, hello', '6, 6, 6, 3', '6, 6, 6, hello']" answer="d">

<<< @/../code/oop/papers/qz1-q9.out{txt}

`a = 6, 5;` stores 6, because `=` binds before the comma. `b` and `c` are given the parenthesised `(6, 5)`, which evaluates to 5. `d = (cout << "hello", 3)` prints `hello` as a side effect the moment it runs, then stores 3. That happens before the last line prints anything, so `hello` comes first.

The real output has no spaces after the commas; the options on the paper do.

</Mcq>

</Q>

## Adding to it

The site is Markdown files in a GitHub repository, so anyone in the class can correct or extend it with a pull request. The README in the repository explains how to add a subject, a question or a program. Every program is compiled and run before a change goes live, and a change that breaks one is not published.
