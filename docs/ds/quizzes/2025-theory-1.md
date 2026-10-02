---
title: Theory Quiz I, 2025
---

# Theory Quiz I, 2025

<PaperHeader :rows="[
  ['Course', 'Data Structures, CSN3001 / AIN3001 / DSN3001, batch 25261 (last year)'],
  ['Format', '10 questions, 1 mark each, 10 minutes'],
  ['Covers', 'Complexity, recurrences, pointers, classes'],
  ['Answers', 'Worked out and checked here; the scanned sheet is one student’s marked answers'],
]" />

<QuizTimer :minutes="10" label="Theory Quiz I" />

::: info The template for this year's TQ-1
This year's Theory Quiz 1 reused this quiz's skeletons: Q2 (dynamic array S1/S2), Q3 (a halving loop), Q4 (input scaling) and Q7 (T(n − 1) + something) all came back with the numbers changed. Expect the same between the next quizzes.
:::

<Q id="QA1.Q1">

What will be the minimum and maximum number of comparisons required using binary search over for a list of N numbers? In each iteration middle element is compared to the key element before continuing search in left or right half.

<Mcq :options="['1, ⌈log₂(N+1)⌉', '1, ⌊log₂(N+1)⌋', '0, ⌈log₂N⌉', '0, ⌊log₂N⌋ + 1']" answer="a">

Minimum: the key is the first middle element, 1 comparison. Maximum: the number of halvings until one element is left, ⌈log₂(N + 1)⌉ (= ⌊log₂N⌋ + 1). Option (d) has the right maximum but a minimum of 0, which is impossible.

</Mcq>

</Q>

<Q id="QA1.Q2">

A simple dynamic array can be constructed by allocating an array of fixed-size, typically larger than the number of elements immediately required. When all space is consumed, and an additional element is to be added, then the underlying fixed-sized array needs to be increased in size which is done by dynamically allocating array of larger size. This process is repeated each time all space in underlying array are consumed. Which among below is/are true in regards of dynamic array?

S1: Dynamic array has time overhead for copying data into dynamically allocated array.
S2: Dynamic array has memory overhead as every dynamically allocated array resides in memory.

<Mcq :options="['S1 is correct and S2 is not correct', 'S1 is not correct and S2 is correct', 'Both S1 and S2 are correct', 'Both S1 and S2 are not correct']" answer="a">

S1 is true: every growth copies all elements. S2's reason is false: the old array is freed after copying, so arrays don't pile up in memory. (A dynamic array does keep some spare capacity, but that is not what S2 says.) This year's version replaced S2 with "free the old block with `delete[]`", which is true.

</Mcq>

</Q>

<Q id="QA1.Q3">

What is the time complexity of the following code snippet?

```cpp
for (int i=n; i>0; i/=2) {
    for (int j=0; j<i; j++) {
        cout << j;   } }
```

<Mcq :options="['O(n log n)', 'O(n)', 'O(n²)', 'O(log n)']" answer="b">

The inner loop runs i times, and i halves: n + n/2 + n/4 + … + 1 ≈ 2n. **O(n)**. On the scanned sheet the student chose O(n²) and lost the mark; "nested loops = n²" is exactly the trap.

</Mcq>

</Q>

<Q id="QA1.Q4">

If an algorithm has O(n²) time complexity, and you reduce input size by half, how does runtime approximately change?

<Mcq :options="['It becomes half', 'It becomes one-fourth', 'It stays the same', 'It becomes one-tenth']" answer="b">

(n/2)² = n²/4.

</Mcq>

</Q>

<Q id="QA1.Q5">

If no access specifier is mentioned for a class in C++, what is the default?

<Mcq :options="['public', 'protected', 'private', 'Undefined']" answer="c">

Class members are private by default; struct members are public.

</Mcq>

</Q>

<Q id="QA1.Q6">

What will be the outcome of following program?

```cpp
#include <iostream>
using namespace std;
int* func() {
    int a = 10;
    return &a;
}
int main() {
    int *p = func();
    cout << *p;
}
```

<Mcq :options="['Prints 10', 'Runtime error', 'Compilation error', 'Undefined behaviour']" answer="d">

`a` is destroyed when `func` returns, so `p` dangles and `*p` is **undefined behaviour**. It compiles (with a warning). "Prints 10" is what you might see on some compilers, which is why it is the trap; GCC actually returns a null pointer here and the program crashes.

</Mcq>

</Q>

<Q id="QA1.Q7">

Solve: T(n) = T(n − 1) + 1, T(1) = 1

<Mcq :options="['O(1)', 'O(n)', 'O(log n)', 'O(n log n)']" answer="b">

T(n) = T(1) + (n − 1) = n.

</Mcq>

</Q>

<Q id="QA1.Q8">

What is the space complexity of the recursive factorial function?

```cpp
int fact(int n) {
    if(n==0) return 1;
    return n*fact(n-1);
}
```

<FillIn q="Answer (Big-O):" answer="O(n)">

n + 1 frames are on the call stack at the deepest point. Recursion depth is space.

</FillIn>

</Q>

<Q id="QA1.Q9">

What will be the output?

```cpp
#include <iostream>
using namespace std;
int main() {
    int arr[4] = {2,4,6,8};
    int *p = arr;
    cout << *(p+2);
}
```

<Mcq :options="['2', '4', '6', '8']" answer="c">

`*(p + 2)` is `arr[2]` = 6.

</Mcq>

</Q>

<Q id="QA1.Q10">

If a class has only parameterized constructors and no default constructor, what happens when we declare an object without arguments?

<Mcq :options="['The compiler will automatically provide a default constructor.', 'The object will be created with garbage values.', 'Compilation error will occur.', 'The object will be created but uninitialized.']" answer="c">

Writing any constructor stops the compiler from generating the default one, so `Box b;` has no constructor to call: compile error ([checked](../notes/unit-1#classes)).

</Mcq>

</Q>
