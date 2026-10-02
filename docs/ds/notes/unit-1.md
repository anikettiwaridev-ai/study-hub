---
title: Unit 1 · Complexity, recursion, pointers
---

# Unit 1 · Complexity, recursion, pointers and classes

Time and space complexity, loops, recurrences by substitution (every recurrence the papers have asked, worked), binary and **biased** search, and the parts of pointers and classes the quizzes test.

::: info How this unit is examined
- **Mid-semester:** a recurrence on **five of the six** papers, 5–7 marks, almost always "by substitution, show every step" (the master theorem appeared once, Mar 2024). **Biased Search** on two papers, including the latest, and in no slide.
- **Theory quiz:** loop complexity, input-size scaling, recurrences as MCQs, space of recursion, memory arithmetic with "int = 2 bytes, address = 4 bytes", pointer and constructor traps.
:::

## Part A · Complexity

### 1. The toolkit {#toolkit}

**Growth rates, slowest to fastest** (slides): 1 &lt; log n &lt; n &lt; n log n &lt; n² &lt; n³ &lt; 2ⁿ &lt; 3ⁿ &lt; n! &lt; nⁿ

| n | log₂ n | n log₂ n | n² | n³ | 2ⁿ |
|---|---|---|---|---|---|
| 2 | 1 | 2 | 4 | 8 | 4 |
| 8 | 3 | 24 | 64 | 512 | 256 |
| 32 | 5 | 160 | 1024 | 32768 | 4294967296 |

**Scaling an input** (a theory-quiz regular): for O(nᵏ), multiplying n by c multiplies the time by cᵏ. O(n²) with the input **doubled** runs **4×** as long ([TQ-1 2026 Q4](../quizzes/2026-theory-1#q4)); with the input **halved**, **¼** of the time ([Quiz I 2025 Q4](../quizzes/2025-theory-1#q4)).

**Measuring a program** (slides): *analytically* (count operations or steps as a function of n, without running it) or *experimentally* (time it on many inputs; the result depends on the machine). Compile time is never counted.

### 2. Counting loops {#loops}

| Loop shape | Total inner work | Big-O | Asked |
|---|---|---|---|
| `for (i = 0; i < n; i++)` | n | O(n) | |
| `i *= 2`, `i /= 2`, `while (n > 1) n = n / 2;` | log₂ n | O(log n) | [TQ-1 2026 Q1](../quizzes/2026-theory-1#q1) |
| `for (i = 1; i * i <= n; i++)` | √n | O(√n) | |
| two nested loops, both to n | n² | O(n²) | |
| nested, inner `j < i` | n(n−1)/2 | O(n²) | insertion sort |
| outer `i = n; i > 0; i /= 2`, inner `j < i` | n + n/2 + n/4 + … ≈ **2n** | **O(n)** | [Quiz I 2025 Q3](../quizzes/2025-theory-1#q3) |
| outer `i = n; i > 1; i /= 2`, inner `j = 1; j <= i; j *= 2` | log n + log(n/2) + … ≈ (log n)²/2 | **O((log n)²)** | [TQ-1 2026 Q3](../quizzes/2026-theory-1#q3) |
| outer `i = 1..n`, inner `j = 1; j < n; j += i` | n/1 + n/2 + … + n/n ≈ n ln n | **O(n log n)** | [Oct 2022 Q1a](../papers/mst-2022-a#q1a) |
| for, with an inner while that only pops what was pushed | at most 2n in total | **O(n)** | [TQ-2 2026 Q1](../quizzes/2026-theory-2#q1) |
| outer `s *= 2` up to n, n work inside | n log n | O(n log n) | [TQ-2 2026 Q8](../quizzes/2026-theory-2#q8) |

::: tip The rule in one line
**Add up what the inner loop actually does on each pass of the outer loop.** "Two loops means n²" is wrong whenever the inner bound depends on the outer variable (halving, doubling, `j += i`) or the inner loop's total work is capped (each element popped once).
:::

::: danger The slides' exercise
`for (i…) for (j = 1; j < i; j++) if (j % n == 0) for (k…)`. Since 1 ≤ j &lt; n, `j % n == 0` is never true, so the k-loop never runs and the answer is O(n²) from the two outer loops. The slide's first version starts j at 0, where `0 % n == 0` *is* true, so the k-loop does run, but only once per i (when j = 0): that adds n × n, and the answer is still O(n²). The slide's frequency column (0 for the k-loop) fits only the version starting at 1. Read the loop bounds.
:::

**Operation count vs step count** (slides). An *operation count* counts one key operation (comparisons in insertion sort: 1 + 2 + … + (n−1) = n(n−1)/2 at worst). A *step count* gives every statement a steps-per-execution and a frequency and adds everything: insertion sort comes to n² + 3n − 4. Both give O(n²).

### 3. Asymptotic notation {#notation}

| Notation | Meaning | Definition |
|---|---|---|
| f = O(g) | upper bound | f(n) ≤ c·g(n) for all n ≥ n₀ |
| f = Ω(g) | lower bound | f(n) ≥ c·g(n) for all n ≥ n₀ |
| f = Θ(g) | tight bound | c₁·g(n) ≤ f(n) ≤ c₂·g(n) for all n ≥ n₀ |
| f = o(g) | loose upper bound | f = O(g) but not Θ(g): f grows strictly slower |
| f = ω(g) | loose lower bound | f = Ω(g) but not Θ(g): f grows strictly faster |

Example (slides): f(n) = 2n² + 7n − 10 is Ω(n²) (c = 1, n₀ = 2) and O(n²), so Θ(n²). Insertion sort is O(n²) and Ω(n), so not Θ of either; heapsort is Θ(n log n).

### 4. Space complexity {#space}

Program space = **instruction space + data space + stack space**. Total = **C** (fixed: code, simple variables, constants) + **Sₚ(n)** (variable: dynamic memory and the recursion stack).

- `abc(a, b, c)` and an iterative `sum(a, n)`: variable part **0**: no space grows with n.
- Recursive `rSum(a, n)`: each frame holds a reference to `a`, the value of `n` and a return address, 2 bytes each in the slides' accounting, and the recursion is n deep: **S(n) = 6n**.
- Recursive factorial: **O(n)** stack space, even with no array ([Quiz I 2025 Q8](../quizzes/2025-theory-1#q8)).

::: danger "No extra variables" is not O(1) space
Recursion depth × frame size is space. Recursive binary search is O(log n) space; the iterative version is O(1).
:::

### 5. Recurrences by substitution {#substitution}

**The four steps** (write all four; the marks follow them):
1. **Expand** the recurrence three times, keeping the constants visible.
2. Write the **k-th line**: the pattern after k expansions.
3. Choose k so the argument hits the **base case**.
4. **Substitute** k and add the series. State the Big-O.

Every recurrence that has appeared, with its answer:

| Recurrence | Answer | Where |
|---|---|---|
| T(n) = T(n−1) + 1 | n, O(n) | [Quiz I 2025 Q7](../quizzes/2025-theory-1#q7) |
| T(n) = T(n−1) + n, T(1) = 1 | n(n+1)/2, **O(n²)** | [Mar 2024 Q1a](../papers/mst-2024-mar#q1a), [TQ-1 2026 Q7](../quizzes/2026-theory-1#q7), slides |
| T(n) = T(n/2) + 1, T(1) = 1 | log₂ n + 1, O(log n) | [Dec 2024 Q2a](../papers/endsem-2024#q2a), binary search |
| T(n) = 2T(n/2) + n, T(2) = 1 | n log₂ n − n/2, **O(n log n)** | [Dec 2023 Q1a](../papers/endsem-2023#q1a) |
| T(n) = 2T(n/4) + n, T(1) = 1 | 2n − √n, **O(n)** | [Oct 2025 Q2](../papers/mst-2025-oct#q2) |
| T(n) = T(√n) + 1 | log log n, **O(log log n)** | [2024 B Q1](../papers/mst-2024-b#q1) |
| T(n) = 2T(n/2) + log n | O(n) | [2024 B Q1](../papers/mst-2024-b#q1) |
| T(n) = 8T(√n) + (log n)² | O((log n)³) | [Oct 2022 Q2a](../papers/mst-2022-a#q2a) |
| T(n) = 2T(n−1) + c, T(1) = 1 | 2ⁿ⁻¹ + c(2ⁿ⁻¹ − 1), **O(2ⁿ)** | [Dec 2024 Q2a](../papers/endsem-2024#q2a) |
| T(n) = 2T(n/2) + 2, T(2) = 1 | 3n/2 − 2, O(n) | slides' exercise |
| S(n) = 2S(n−1) + 10000, S(1) = 50000 | 60000·2ⁿ⁻¹ − 10000 | [2022 B Q4](../papers/mst-2022-b#q4) |

#### Linear: T(n) = T(n−1) + n, T(1) = 1

```text
T(n) = T(n−1) + n
     = T(n−2) + (n−1) + n
     = T(n−3) + (n−2) + (n−1) + n
     ...
after k steps:  T(n−k) + (n−k+1) + ... + (n−1) + n
base: n − k = 1, so k = n − 1
T(n) = T(1) + 2 + 3 + ... + n = 1 + 2 + ... + n = n(n+1)/2  =  O(n²)
```

#### Halving: T(n) = 2T(n/2) + n, T(2) = 1

```text
T(n) = 2T(n/2) + n
     = 2[2T(n/4) + n/2] + n  = 4T(n/4) + 2n
     = 4[2T(n/8) + n/4] + 2n = 8T(n/8) + 3n
after k steps:  2^k T(n/2^k) + kn
base: n/2^k = 2, so 2^k = n/2 and k = log₂n − 1
T(n) = (n/2)·1 + n(log₂n − 1) = n log₂n − n/2  =  O(n log n)
check n = 8: 2T(4) + 8 = 2(2·1 + 4) + 8 = 20, and 8·3 − 4 = 20 ✓
```

#### Unequal split: T(n) = 2T(n/4) + n, T(1) = 1 (Oct 2025 Q2)

```text
T(n) = 2T(n/4) + n
     = 2[2T(n/16) + n/4] + n  = 4T(n/16) + n/2 + n
     = 4[2T(n/64) + n/16] + n/2 + n = 8T(n/64) + n/4 + n/2 + n
after k steps:  2^k T(n/4^k) + n(1 + 1/2 + 1/4 + ... + 1/2^(k−1))
base: n/4^k = 1, so k = log₄n and 2^k = 2^(log₄n) = √n
geometric sum: 1 + 1/2 + ... + 1/2^(k−1) = 2(1 − 1/2^k) = 2 − 2/√n
T(n) = √n·T(1) + n(2 − 2/√n) = √n + 2n − 2√n = 2n − √n  =  O(n)
check n = 16: 2T(4) + 16 = 2(2·1 + 4) + 16 = 28, and 32 − 4 = 28 ✓
```

::: tip Spot the shape before expanding
Each level of the expansion costs **(a/b)ⁱ · n** (here (2/4)ⁱ · n). If a/b &lt; 1 the levels shrink and the **first** term dominates: O(n). If a/b = 1 every level costs n and there are log n levels: O(n log n). If a/b &gt; 1 the **last** level dominates. Use this to check your final answer.
:::

#### Square roots: substitute n = 2ᵐ first

`T(n) = T(√n) + 1`. Let n = 2ᵐ and S(m) = T(2ᵐ). Since √n = 2^(m/2), the recurrence becomes **S(m) = S(m/2) + 1**, which is the binary-search recurrence: S(m) = log₂ m + c. Back in n: **T(n) = O(log log n)**. Or directly: T(n) = T(n^(1/2)) + 1 = T(n^(1/4)) + 2 = … = T(n^(1/2ᵏ)) + k; stop when n^(1/2ᵏ) = 2, i.e. 2ᵏ = log₂ n, so k = log₂ log₂ n.

`T(n) = 8T(√n) + (log n)²` becomes S(m) = 8S(m/2) + m²: expanding gives 8ᵏ S(m/2ᵏ) + m²(1 + 2 + … + 2ᵏ⁻¹); with k = log₂ m, 8ᵏ = m³, so S(m) = m³ S(1) + m²(m − 1) = Θ(m³) and **T(n) = Θ((log n)³)**.

#### A log term: T(n) = 2T(n/2) + log n (2024 B Q1, log base 2)

```text
T(n) = 2T(n/2) + log n
     = 4T(n/4) + 2 log(n/2) + log n
     = 8T(n/8) + 4 log(n/4) + 2 log(n/2) + log n
after k steps:  2^k T(n/2^k) + Σ (i = 0 to k−1) 2^i (log n − i)
base: k = log n, 2^k = n
Σ 2^i (k − i) = 2^(k+1) − k − 2 = 2n − log n − 2
T(n) = n·T(1) + 2n − log n − 2  =  O(n)
```

#### Exponential: T(n) = 2T(n−1) + c, T(1) = 1

```text
T(n) = 2T(n−1) + c = 4T(n−2) + 2c + c = 8T(n−3) + 4c + 2c + c
after k steps:  2^k T(n−k) + c(2^k − 1)
base: k = n − 1
T(n) = 2^(n−1) + c(2^(n−1) − 1)  =  O(2^n)
```

#### Word problems: build the recurrence first (2022 B Q4)

"Salary starts at $50,000; every year it doubles, plus $10,000." **S(1) = 50,000; S(n) = 2S(n−1) + 10,000.** Expanding: S(n) = 2ᵏ S(n−k) + 10,000(2ᵏ − 1); with k = n − 1: S(n) = 50,000·2ⁿ⁻¹ + 10,000(2ⁿ⁻¹ − 1) = **60,000·2ⁿ⁻¹ − 10,000**. Check: S(2) = 110,000 = 2 × 50,000 + 10,000 ✓.

The slides' bank example is the same shape without the constant: Pₙ = 1.11 Pₙ₋₁ with P₀ = 10,000 gives Pₙ = (1.11)ⁿ × 10,000 (P₃₀ = $228,992.97). *Forward substitution* builds up from the base (a₂, a₃, …); *backward substitution* expands down from aₙ, as above. Both give the same closed form.

### 6. The master theorem {#master}

For **T(n) = aT(n/b) + f(n)**, compare f(n) with **n^(log_b a)**:

| Case | When | T(n) |
|---|---|---|
| 1 | f(n) is polynomially **smaller** | Θ(n^(log_b a)) |
| 2 | f(n) = Θ(n^(log_b a) · logᵏ n) | Θ(n^(log_b a) · logᵏ⁺¹ n) |
| 3 | f(n) is polynomially **larger**, and a·f(n/b) ≤ c·f(n) for some c &lt; 1 | Θ(f(n)) |

Mar 2024 Q1b, the one time it was asked:
- **T(n) = 2T(n/2) + √n**: n^(log₂2) = n, and √n = n^0.5 is polynomially smaller. Case 1: **Θ(n)**.
- **T(n) = 6T(n/3) + n² log n**: n^(log₃6) ≈ n^1.63, and n² log n is bigger by n^0.37. Regularity: 6·(n/3)² log(n/3) = (2/3)n² log(n/3) ≤ (2/3)n² log n. Case 3: **Θ(n² log n)**.

::: warning Only when it says "master theorem"
This year's handout lists substitution only, and 2024 B and Oct 2025 both demanded substitution. Use the master theorem to check an answer, not to replace the steps.
:::

## Part B · Searching and recursion

### 7. Binary search {#binary-search}

Sorted array; compare with the middle; discard half. **T(n) = T(n/2) + c = O(log n).** Minimum comparisons **1** (the key is the middle element); maximum **⌈log₂(N + 1)⌉ = ⌊log₂ N⌋ + 1** ([Quiz I 2025 Q1](../quizzes/2025-theory-1#q1)).

::: code-group
<<< @/../code/ds/notes/u1-binary-search.cpp [Program]
<<< @/../code/ds/notes/u1-binary-search.out{txt} [Output]
:::

The first line is the slides' recursive version, which prints `a[mid]` **after** the recursive call, so the probes come out in reverse: 40 30 20 50. Binary search on a **linked list** is possible but no faster than linear search: reaching the middle already costs O(n).

### 8. Biased Search: mid = (2s + e) / 3 {#biased-search}

Not in any slide, asked on **Sep 2023 Q4** and **Oct 2025 Q4**. It is binary search with the split one third of the way in instead of halfway.

```text
BiasedSearch(A, n, key)
    s ← 0, e ← n − 1
    while s ≤ e
        mid ← (2·s + e) / 3            // integer division
        if A[mid] = key   return mid
        else if key > A[mid]   s ← mid + 1
        else   e ← mid − 1
    return −1                          // not found
```

Oct 2025 Q4: search 'X' in N O P Q R S T U V W X Y Z (indices 0–12).

| s | e | mid = (2s + e)/3 | A[mid] | Decision |
|---|---|---|---|---|
| 0 | 12 | (0 + 12)/3 = 4 | R | X > R: s = 5 |
| 5 | 12 | (10 + 12)/3 = 7 | U | X > U: s = 8 |
| 8 | 12 | (16 + 12)/3 = 9 | W | X > W: s = 10 |
| 10 | 12 | (20 + 12)/3 = 10 | X | **found at index 10** (4 comparisons) |

Sep 2023 Q4 (P…Z, indices 0–10): mid = 3 (S), then 6 (V), then 8 (**X found**), 3 comparisons. Checked by running:

::: code-group
<<< @/../code/ds/notes/u1-biased-search.cpp#answer [biasedSearch]
<<< @/../code/ds/notes/u1-biased-search.out{txt} [Output]
:::

::: tip Complexity, if asked
In the worst case the key is always in the larger part, about 2/3 of the range: **T(n) = T(2n/3) + 1 = O(log n)** (log base 3/2, about 1.71 log₂ n probes). The same order as binary search, with a worse constant, and better only when keys are known to sit near the start.
:::

::: danger Biased search traps
- Integer division: (2·10 + 12)/3 = 32/3 = **10**, not 10.67.
- After a miss it is mid **+ 1** or mid **− 1**, never mid itself, or the loop can stop moving.
- The list must be sorted. Letters compare alphabetically.
:::

### 9. Tracing recursion {#recursion}

**McCarthy's 91 function** (Oct 2022 Q1b): `fun(n) = n − 10` if n > 100, else `fun(fun(n + 11))`.

```text
fun(99)  = fun(fun(110))          110 > 100, so fun(110) = 100
         = fun(100) = fun(fun(111))   fun(111) = 101
         = fun(101) = 91
```

For every n ≤ 100 it returns **91**; above 100 it returns n − 10. More recursion traces (printing before vs after the call, the call stack, space) are in [Unit 3](./unit-3#recursion).

## Part C · Pointers and classes (what the quizzes test)

### 10. Pointers in one table {#pointers}

| Write | Means |
|---|---|
| `int *p = &x;` | p holds x's address |
| `*p = 20;` | changes x through p |
| `p + 2` | the address 2 **ints** further on, not 2 bytes |
| `p2 - p1` | how many ints lie between them |
| `vals[i]` | exactly `*(vals + i)`; no bounds check |
| `ptr->member` | `(*ptr).member` (the brackets are required) |
| `const int *p` | pointer to a constant: `*p = 5` is an error; `p = &y` is fine |
| `int *const p = &x;` | constant pointer: `p = &y` is an error; `*p = 5` is fine; must be initialised |
| `const int *const p` | neither may change |

::: code-group
<<< @/../code/ds/notes/u1-pointers.cpp [Program]
<<< @/../code/ds/notes/u1-pointers.out{txt} [Output]
:::

::: danger The slides' "??" line is a double delete
```cpp
p = new int; *p = 10;
q = new int; *q = *p;
q = p;          // q's own block is now unreachable: a memory leak
delete p;
delete q;       // ?? : the same block freed twice, undefined behaviour
```
Freed memory still pointed to is a **dangling pointer**; memory never freed is a **leak**. Fix both by setting a pointer to `nullptr` right after `delete`. `new` pairs with `delete`, `new[]` with `delete[]`.
:::

::: danger Returning the address of a local is undefined behaviour
```cpp
int* func() { int a = 10; return &a; }   // a dies when func returns
int main() { int *p = func(); cout << *p; }
```
The answer is **undefined behaviour**, not "prints 10" ([Quiz I 2025 Q6](../quizzes/2025-theory-1#q6)). GCC even replaces the returned address with null, so this crashes. A function may return a pointer only to data passed in or to memory from `new`.
:::

### 11. Classes: the rules the quizzes use {#classes}

- **Default access** in a `class` is **private**; in a `struct`, **public** ([Quiz I 2025 Q5](../quizzes/2025-theory-1#q5), [Practice sheet 1 Q1](../practice/sheet-1#q1)).
- A constructor has the class's name and no return type, and can be overloaded. **Once you write any constructor, the compiler stops providing the default one**, so `Box b;` is a compile error:

::: code-group
<<< @/../code/ds/notes/u1-no-default-ctor.cpp [Program]
<<< @/../code/ds/notes/u1-no-default-ctor.out{txt} [Compiler says]
:::

- `.` for an object, `->` for a pointer to one.
- A `const` member function (`int day() const`) cannot change the object, and is the only kind a `const` object may call.
- `enum class Month { jan = 1, feb, … }` is scoped and type-safe: `Month::feb`; no implicit conversion to or from `int`. A plain `enum` leaks its names into the surrounding scope and converts to `int`.
- A non-member "helper" like `operator==(const Date&, const Date&)` keeps the class interface small; it needs only the public getters, so it need not be a friend.

The full versions (Rectangle, BankAccount with nested exception classes, Schedule with an `enum class`) are on [Practice sheet 1](../practice/sheet-1).

### 12. Memory arithmetic: the recipe {#memory}

A theory-quiz question type this year (both 2026 theory quizzes had one), and the slides' sparse-matrix slide is one too. **Write each total as a formula before using numbers.**

| Structure | Bytes |
|---|---|
| array of capacity C, plus extra variables | C × size(element) + extras, **whether full or not** |
| linked list of n nodes, plus a head pointer | n × (data fields + pointer) + pointer |
| array of m linked lists (one per row or person) | m × pointer + nodes × (data fields + pointer) |

**TQ-1 2026 Q9** (int = 2 B, address = 4 B): 10⁴ researchers each get a list head: 10,000 × 4 = 40,000. Each co-authorship record stores a co-author ID and a count (2 + 2) plus a next pointer (4) = 8 bytes; 500 records = 4,000. **Total 44,000 bytes**, the official key. (If each record were stored in both researchers' lists there would be 1,000 nodes and 48,000 bytes; the key counts 500.)

**TQ-2 2026 Q4**: the array stack is 200 × 2 + 2 = 402 bytes regardless of occupancy; the linked stack is 6n + 4. Strictly more when 6n + 4 > 402 → n > 66.33 → **67**.

**Growing an array** ([TQ-2 2026 Q2](../quizzes/2026-theory-2#q2), [TQ-1 2026 Q2](../quizzes/2026-theory-1#q2)): grow by a constant c each time it fills and n pushes copy about n²/(2c) elements, **O(n²)**; double it and the copies stay under 2n, **O(n)**. Resizing by hand means allocate, copy, then `delete[]` the old block (or it leaks).

## Traps and the 5-minute checklist {#traps}

| # | Trap | Correct version |
|---|---|---|
| 1 | "two loops, so n²" | add up the inner loop's real work: halving gives 2n, `j += i` gives n log n |
| 2 | recursion is O(1) space | depth × frame: factorial is O(n) |
| 3 | leaving out the base-case step in substitution | write k from the base case, substitute, sum |
| 4 | log₄n confused with log₂n | 2^(log₄n) = √n |
| 5 | T(√n) without substituting | n = 2ᵐ turns √n into m/2 |
| 6 | biased mid with real division | integer division, then ±1 |
| 7 | `return &local;` "prints 10" | undefined behaviour |
| 8 | a class with only parameterised constructors, `X obj;` | compile error |
| 9 | struct members private | public by default; class members private |
| 10 | array memory counts only the elements in use | the whole capacity is allocated |

**The checklist:** for a loop, sum the inner work · for a recurrence, four steps and a check with a small n · for search, integer division and ±1 · for pointers, who owns the memory and when it dies.

## Quick check {#quick-check}

<Drill n="1" tag="Complexity">

`for (int i = n; i > 0; i /= 2) for (int j = 0; j < i; j++) cout << j;`

<Mcq :options="['O(n log n)', 'O(n)', 'O(n²)', 'O(log n)']" answer="b">

The inner loop runs n, n/2, n/4, … times: about 2n in total. O(n). Last year's class mostly answered O(n²).

</Mcq>

</Drill>

<Drill n="2" tag="Complexity">

<FillIn q="`for (int i = n; i > 1; i /= 2) for (int j = 1; j <= i; j *= 2) cout << j;` Time complexity?" answer="O((log n)^2)|O(log^2 n)|O((logn)^2)|O(log n)^2|O(log²n)|O((log n)²)">

The outer loop runs log n times; the inner runs about log i times. log n + log(n/2) + … ≈ (log n)²/2.

</FillIn>

</Drill>

<Drill n="3" tag="Recurrence">

Solve T(n) = T(n−1) + n, T(1) = 1.

<Mcq :options="['O(n log n)', 'O(n)', 'O(log n)', 'O(n²)']" answer="d">

1 + 2 + … + n = n(n+1)/2.

</Mcq>

</Drill>

<Drill n="4" tag="Recurrence">

<FillIn q="T(n) = 2T(n/4) + n, T(1) = 1. Exact closed form? (Write it in terms of n.)" answer="2n - √n|2n-√n|2n - sqrt(n)|2n-sqrt(n)|2n − √n">

Levels cost n, n/2, n/4…; with k = log₄n, 2ᵏ = √n, and T(n) = √n + 2n − 2√n = 2n − √n. O(n).

</FillIn>

</Drill>

<Drill n="5" tag="Search">

<FillIn q="Biased search, mid = (2s + e)/3, for X in N O P Q R S T U V W X Y Z (indices 0–12). Which indices are probed, in order? Separate with commas." answer="4, 7, 9, 10|4,7,9,10|4 7 9 10">

(0+12)/3 = 4 (R), (10+12)/3 = 7 (U), (16+12)/3 = 9 (W), (20+12)/3 = 10 (X).

</FillIn>

</Drill>

<Drill n="6" tag="Pointers">

`int* func() { int a = 10; return &a; }` then `int *p = func(); cout << *p;`

<Mcq :options="['Prints 10', 'Runtime error', 'Compilation error', 'Undefined behaviour']" answer="d">

`a` no longer exists after `func` returns. Reading it is undefined behaviour (with GCC it crashes). It does compile, with a warning.

</Mcq>

</Drill>

<Drill n="7" tag="Classes">

A class has only parameterised constructors. What happens on `Box b;`?

<Mcq :options="['The compiler provides a default constructor', 'The object gets garbage values', 'Compilation error', 'The object is created but uninitialised']" answer="c">

The free default constructor exists only when you write no constructor at all.

</Mcq>

</Drill>

<Drill n="8" tag="Memory">

<FillIn q="int = 2 B, address = 4 B. Array stack of capacity 200 plus an int `top`, vs a linked stack (int + next per node) plus a head pointer. Smallest number of elements for which the list takes strictly more memory?" answer="67">

402 bytes vs 6n + 4. 6n + 4 > 402 → n > 66.3 → 67.

</FillIn>

</Drill>
