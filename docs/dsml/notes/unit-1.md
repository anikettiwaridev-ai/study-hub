---
title: Unit 1 · Data, Python and the maths underneath
---

# Unit 1 · Data, Python and the maths underneath

Before any model: what data is, the process that turns it into a result, the Python tools that hold it, and the two pieces of maths every later unit leans on, linear algebra and correlation.

::: info How this unit is examined
- **Mid-semester:** neither past mid-semester asked Unit 1 directly, but its tools appear inside other questions (dot products in every model, matrix sizes in ridge regression, correlation as multicollinearity).
- **End-semester:** choose a chart for each kind of data (6 marks), **Pearson correlation by hand** (6 marks), correlation vs regression (part of 5 marks). See [autumn 2024 Q1](../papers/endsem-2024#q1a).
- **Theory quiz:** definitions and face-offs: structured vs unstructured, the five data types, which library is built on which, and what NumPy and Pandas actually do (copy vs view, `shape` vs `size`, `loc` vs `iloc`).
:::

## Read this first: the unit on one screen {#toolkit}

| Topic | The one thing to remember |
|---|---|
| Data | An **unprocessed, uninterpreted** fact, value, text, sound or picture. Interpret it and it becomes information. |
| Structured vs unstructured | Structured = quantitative, predefined schema, SQL; tells you **what**. Unstructured = qualitative, no schema, NoSQL; tells you **why**. |
| Data types | Numerical, categorical, **ordinal** (ordered categories), time series, text. Ordinal vs nominal decides the encoding in Unit 2. |
| Process | Collection → cleaning → EDA → model building and deployment. |
| NumPy | One dtype, contiguous memory, **vectorised**. `a * b` is element-wise; `@` or `np.dot` is matrix multiplication. |
| Pandas | Series (1-D, size **immutable**), DataFrame (2-D). `df['x']` is a Series, `df[['x']]` a DataFrame. `loc` = labels, `iloc` = positions. |
| Charts | Categories → bar. Time → line. Distribution → histogram. Spread and outliers → box plot. Two numbers → scatter. |
| Matrices | (m × **n**)(**n** × p) = m × p. Not commutative. det = 0 means no inverse. |
| Correlation | $r = \dfrac{\sum(x-\bar x)(y-\bar y)}{\sqrt{\sum(x-\bar x)^2\sum(y-\bar y)^2}}$, between −1 and 1, unitless, says nothing about cause. |

## 1. What data is, and its types {#data-types}

**Data** (the slide's definition, learn it word for word): *any unprocessed fact, value, text, sound or picture that is not being interpreted and analysed.* The second half is the part people drop. Without data no model can be trained, which is why companies spend heavily to collect it.

### Structured vs unstructured

| | Structured | Unstructured |
|---|---|---|
| Category | Quantitative | Qualitative |
| Model | Predefined data model (schema) | No predefined model; stays undefined until needed |
| Database | Relational, **SQL** (developed by IBM, 1974) | Non-relational, **NoSQL** |
| Sources | GPS sensors, online forms, network and web-server logs | Email, word-processing documents, PDFs |
| Forms | Numbers and values | Text, audio, video, sensor files |
| Storage | Tables (Excel, SQL), **data warehouses**; less space, scalable | Media files, NoSQL; more space |
| Used in | **Machine learning** algorithms | **NLP** and text mining |
| Reveals | **What** is happening | **Why** it is happening |
| Tools | SQLite, MySQL, PostgreSQL | MongoDB, Hadoop, Azure |
| Advantages | Easy for ML algorithms; easy for business users; more tools (it came first) | Native format keeps the pool wide; fast to collect (nothing to predefine) |
| Disadvantages | **Limited usage** (only its intended purpose); **rigid schemas**: a change means updating all the data | Needs **data science expertise**; needs **specialised tools** |
| Use cases | CRM, online booking, accounting | Data mining (sentiment, purchasing patterns), predictive analytics, chatbots |

::: tip The one-liner
Structured data tells you **what** is happening; unstructured data tells you **why**.
:::

### The five types of data

| Type | Definition | Example | Marker |
|---|---|---|---|
| **Numerical** (quantitative) | Measurable; exact numbers that mean a measurement or a count | Height, house price, houses sold | Arithmetic means something |
| **Categorical** | Characteristics; may be stored as numbers but they carry no maths | Gender (0 = Male, 1 = Female), hometown | You cannot average it |
| **Ordinal** | Categories with a natural **order** (numerical + categorical) | Beginner < intermediate < advanced; age bands | Order is real, gaps are not |
| **Time series** | Numbers collected at **regular intervals** over time | Monthly home sales | Has a date or timestamp |
| **Text** | Words, sentences, paragraphs | Reviews | Turned into numbers first (bag of words, word frequency) |

::: danger Three face-offs that are quiz questions
- **Stored as a number ≠ numerical.** The test is "can you average it and get something meaningful?". 0/1 for gender averages to 0.4, which is nonsense: categorical.
- **Time series vs numerical.** Both are numbers; time series is anchored to time, with a start, an end and a regular interval, so week-to-week comparison means something.
- **Ordinal vs nominal.** Ordinal has an order (small/medium/large); nominal does not (Delhi/Mysore). This one fact decides label vs one-hot encoding in [Unit 2](./unit-2#encoding).
:::

## 2. The data science process {#process}

| Stage | What happens |
|---|---|
| 1. **Data collection** | After stating the problem, gather data that supports the analysis: surveys, web scraping, sensors, public datasets. |
| 2. **Data cleaning** | Most real data is not structured; clean it and convert it to structured form **before** any analysis. |
| 3. **Exploratory data analysis (EDA)** | Find hidden patterns; which factors affect the target and how much; how the features relate to each other. Gives the direction for modelling. |
| 4. **Model building and deployment** | Fit models; if they hold up on held-out (real-world) data, deploy and monitor them. |

**Components of data science:** data analysis, statistics, data engineering (ML and DL).

The slides' **ML pipeline** adds the loop: datasets → data retrieval → **data preparation** (processing and wrangling; feature extraction and engineering; feature scaling and selection) → modelling → **evaluation and tuning** → deployment and monitoring, and back to preparation until the performance is good enough.

**Which metric for which problem** (a slide that appears in two decks):

| Problem | Metrics |
|---|---|
| Classification | Precision, recall, F-measure, error rate |
| Regression | Root mean squared error, correlation, R² |
| Clustering | Compare clusters with class labels if labels exist; otherwise **expert evaluation** |
| Association | **Expert evaluation** |

Clustering and association fall back on an expert because there is no ground truth to score against.

## 3. The Python stack {#libraries}

| Library | What it adds | Built on |
|---|---|---|
| **NumPy** | N-dimensional arrays and matrices; maths and statistics on them; **vectorisation**, which greatly improves performance | (the base) |
| **SciPy** | Algorithms: linear algebra, differential equations, integration, optimisation, statistics (`scipy.stats` has Pearson's r) | NumPy |
| **Pandas** | Table-like structures (Series, DataFrame, "similar to R"); reshaping, merging, sorting, slicing, aggregation; **handles missing data** | NumPy |
| **scikit-learn** | ML algorithms: classification, regression, clustering, model validation | NumPy, SciPy and matplotlib |
| **matplotlib** | 2-D plotting, publication quality, MATLAB-like; **relatively low-level** | – |
| **Seaborn** | **High-level** attractive statistical graphics, styled like R's ggplot2 | matplotlib |

::: tip Two face-offs
**matplotlib vs Seaborn:** low-level and general vs a high-level layer for statistical plots. **statsmodels vs scikit-learn:** statistical analysis with R-style formulas (regression, ANOVA, hypothesis tests) vs machine learning (k-means, SVM, random forests). Same maths, different intent: inference vs prediction.
:::

## 4. NumPy for the theory quiz {#numpy}

**Why an array and not a Python list?** (1) **Homogeneous**: one dtype, stored in one contiguous block; a list holds pointers to separate objects. (2) **Vectorised**: operations run element-wise in compiled code, not a Python loop. (3) **Broadcasting**: shape-aware arithmetic a list cannot do. (4) Fixed size: an array does not grow the way a list appends.

| Attribute | Gives | For `np.arange(10).reshape(2, 5)` |
|---|---|---|
| `a.ndim` | number of axes | 2 |
| `a.shape` | size along each axis (a tuple) | (2, 5) |
| `a.size` | total number of elements | 10 |
| `a.dtype` | element type | int64 |
| `a.T` | transpose | shape (5, 2) |

| Routine | You give | Note |
|---|---|---|
| `np.arange(start, stop, step)` | a **step** | stop **excluded**: `np.arange(0, 1, 0.2)` → 0, 0.2, 0.4, 0.6, 0.8 |
| `np.linspace(start, stop, n)` | a **count** | stop **included**: `np.linspace(0, 2π, 4)` → 4 values ending at 6.28 |
| `np.zeros`, `np.ones`, `np.eye(n)` | a shape | floats by default; `eye` is the identity |
| `np.random.random(shape)` | a shape | uniform in [0, 1) |
| `np.random.randint(lo, hi, size)` | a range | hi excluded |

::: danger Assignment is not a copy
```python
A = np.zeros((2, 2))
C = A          # another name for the SAME array
C[0, 0] = 1
print(A)       # [[1. 0.] [0. 0.]]  A changed too
```
The slide calls this "arrays are mutable". Basic slicing also gives a **view**. Use `A.copy()` for an independent array (Assignment 1 Q8a does exactly this).
:::

**Broadcasting rule** (guaranteed question): compare shapes from the **last** dimension backwards; two dimensions are compatible when they are **equal** or **one of them is 1**. Otherwise it is an error.

| Shapes | Result |
|---|---|
| (3, 3) and a scalar | (3, 3): the scalar is stretched, so `3 * A - 1` works |
| (2, 3) and (3,) | (2, 3): the row is added to every row |
| (3, 1) and (1, 4) | (3, 4): both stretch |
| (2, 3) and (2,) | **error**: last dimensions 3 and 2 differ and neither is 1 |

| Call | Inputs | Output |
|---|---|---|
| `np.dot(u, v)`, `np.inner(u, v)` | two 1-D vectors | a scalar: [1, 2, 3]·[1, 1, 1] = 6 |
| `np.outer(u, v)` | lengths m and n | an m × n matrix |
| `np.dot(A, B)` or `A @ B` | matrices | the matrix product |
| `np.cross(u, v)` | two 3-D vectors | a vector perpendicular to both |
| `a * b` | same shape | **element-wise** product, not matrix multiplication |

For `np.dot(A, B)`, A's **last** dimension must equal B's **first**: two (3, 2) matrices give "shapes (3,2) and (3,2) not aligned".

::: tip The axis rule
**The axis you name is the axis that disappears.** `a.sum(axis=0)` collapses down the rows and leaves one value per **column**; `axis=1` leaves one value per **row**; no axis gives one number. Pandas follows the same rule.
:::

| Pair | Difference |
|---|---|
| `reshape` vs `resize` | reshape must keep the total size (else error); resize always works, chopping or padding with zeros |
| `vstack` vs `hstack` | two length-3 arrays: vstack gives shape (2, 3); hstack gives (6,) |
| `split` vs `array_split` | split needs an even division (4 rows into 3 is an error); array_split allows uneven pieces |
| `save/load` vs `savetxt/loadtxt` | binary `.npy` keeps dtype and shape exactly; text is readable but loses fidelity |
| `shuffle` vs `permutation` | shuffle changes the array in place; permutation returns a new one |

## 5. Pandas for the theory quiz {#pandas}

| Structure | Dimensions | Data | Size |
|---|---|---|---|
| **Series** | 1 | homogeneous | **immutable** |
| **DataFrame** | 2 | heterogeneous columns | mutable |
| **Panel** | 3 | heterogeneous ("a container of DataFrames") | mutable; rarely used |

::: tip The mutability sentence (stated on the slide)
All Pandas data structures are **value mutable**. All except Series are **size mutable**. All are built on NumPy arrays.
:::

- **dtypes:** `object` is the most general (mixed numbers and strings); `int64`, `float64`, `datetime64`. **A numeric column with NaN becomes float64**, because NaN is a float.
- **Attributes have no parentheses, methods do.** `df.shape`, `df.dtypes`, `df.columns`, `df.size` are attributes; `df.head()`, `df.describe()` (numeric columns only), `df.dropna()` are methods. `dir(df)` lists both.
- **Selecting:** `df['sex']` or `df.sex`, except when the name clashes with a method: a column called `rank` must be `df['rank']`. Single brackets give a **Series**, double brackets a **DataFrame**.
- **`loc` vs `iloc`:** `loc` uses **labels** and its slice end is **included**; `iloc` uses **positions**, its slice end is **excluded**, and it allows negative indices (`df.iloc[-1]` is the last row).
- **Filtering** is Boolean indexing: `df[df['salary'] > 120000]`.
- **GroupBy** = split → apply → combine (like `dplyr` in R). It is **lazy** (creating the object computes nothing) and **sorts group keys** by default (`sort=False` is faster).
- **Missing values:** `isnull()`, `notnull()`, `dropna()` (any NaN drops the row), `dropna(how='all')`, `dropna(thresh=5)` (keep rows with at least 5 real values), `fillna(0)`, `fillna(df.mean())`. When summing, NaN counts as 0; an all-NaN column sums to NaN; GroupBy excludes NaN; `skipna=True` by default (unlike R).

## 6. Visualising data: which chart {#charts}

Visualisation turns a table into a pattern the eye sees at once. It is the main tool of EDA, and it decides preprocessing choices (a skewed histogram means median imputation, not mean).

| Data or question | Chart | Why |
|---|---|---|
| Compare categories | **Bar chart** | one separated bar per category |
| Change over time | **Line chart** | ordered x-axis, points joined |
| Distribution of one numeric variable | **Histogram** | values binned, bars touch, shape (skew) visible |
| Spread and outliers; compare groups | **Box plot** | median, quartiles, whiskers, outlier points |
| Relationship between two numeric variables | **Scatter plot** | the picture of correlation |
| Parts of a whole | **Pie chart** | needs counts per category (`value_counts()`) |
| Distribution with density | Violin plot (Seaborn) | a box plot plus the density shape |

Seaborn names from the slides: `distplot` (histogram), `barplot`, `boxplot`, `violinplot`, `jointplot` (scatter), `regplot` (scatter with a regression line), `pairplot` (every pair of features), `swarmplot` (categorical scatter).

::: danger Bar chart or histogram?
A **bar chart** compares **categories** and its bars have gaps. A **histogram** shows the distribution of **one numeric variable** in bins and its bars touch. "Shape of the salary data" wants a histogram; "salary per department" wants a bar chart.
:::

## 7. Linear algebra {#linear-algebra}

A dataset **is** a matrix: n rows (examples) by d columns (features). Every model in this course is a set of operations on that matrix.

| Object | What it is | Example |
|---|---|---|
| **Scalar** | one number: magnitude only | k = 3 |
| **Vector** | magnitude and direction; one row of data | v = (2, −1, 4) |
| **Matrix** | rectangular array; represents a transformation, a system of equations, or a whole dataset | 3 × 3, 1000 × 5 |

### Vector operations, worked

<!--@include: @/../code/dsml/notes/u1.out#vectors-->

The **dot product** measures how much two vectors point the same way: $u \cdot w = \|u\|\|w\|\cos\theta$. It is zero for perpendicular vectors. The **cross product** exists only for 3-D vectors and is used less in ML than the dot product.

### Matrix multiplication

<!--@include: @/../code/dsml/notes/u1.out#matmul-->

**Transpose** $A^T$ swaps rows and columns: (m × n) becomes (n × m). The **identity** I has 1s on the diagonal, and AI = A.

### Determinant, inverse and eigenvalues (2 × 2)

<!--@include: @/../code/dsml/notes/u1.out#eigen-->

An **eigenvector** of M is a direction that M only stretches: $Mv = \lambda v$; the stretch factor λ is the **eigenvalue**. In PCA (Unit 5) the eigenvectors of the covariance matrix are the principal components, and each eigenvalue is the variance along one.

::: danger det = 0 means no inverse
If two columns are dependent (one is a multiple or combination of others), the determinant is 0 and the matrix cannot be inverted. In regression this is **multicollinearity**: $X^TX$ has no inverse, so least squares has no unique answer. Ridge regression fixes it ([autumn 2024 Q4a](../papers/endsem-2024#q4a)).
:::

### Linear transformations

A transformation T is **linear** if it has **additivity**, T(u + v) = T(u) + T(v), and **homogeneity**, T(kv) = kT(v). Every linear transformation can be written as a matrix. The slides' three in ML:
- **Scaling**: stretch or compress each dimension; feature scaling is this.
- **Rotation**: turn vectors about a point; used in computer vision and robotics.
- **Translation**: shift every vector by the same amount; centring data (subtracting the mean) is this.

::: warning Correction: translation is not strictly linear
x ↦ x + c sends 0 to c, so T(u + v) = u + v + c ≠ T(u) + T(v) = u + v + 2c. It is an **affine** map. Name it as the slide does if asked for "linear transformations used in ML", but do not claim it satisfies additivity.
:::

### Solving linear systems

Systems Ax = b appear in parameter estimation and model fitting.
- **Gaussian elimination**: (1) **forward elimination**: row operations turn the augmented matrix into upper-triangular form; (2) **back substitution**: solve from the last equation up; (3) **pivoting**: swap rows so no pivot is 0 (numerical stability).
- **LU decomposition**: factor A = LU (lower × upper triangular), then solve with one forward and one back substitution. Reusable for many right-hand sides, and gives the determinant cheaply.

### Where it is used

| ML method | Linear algebra inside it |
|---|---|
| **PCA** | covariance matrix → eigen-decomposition → project the data onto the top eigenvectors |
| **Linear regression** | matrix form $Y = X\beta + \varepsilon$; the **normal equation** $X^TX\beta = X^TY$ |
| **SVM** | the kernel trick (dot products in a higher-dimensional space); a quadratic-programming optimisation |
| **Neural networks** | matrix multiplication in every layer; gradients by backpropagation; weight initialisation (Xavier, He) |

## 8. Features and correlation {#correlation}

A **feature** is one measurable input attribute: a column. The model sees the features and predicts the **target** (label). Two features that move together are **correlated**, and correlation is how you spot a redundant feature.

**Covariance** $\text{cov}(x, y) = \frac{1}{n-1}\sum (x - \bar x)(y - \bar y)$ gives the direction of the relationship, but its size depends on the units. **Pearson's r** divides the units out:

$$ r = \frac{\sum (x - \bar x)(y - \bar y)}{\sqrt{\sum (x - \bar x)^2 \; \sum (y - \bar y)^2}}, \qquad -1 \le r \le 1 $$

### Worked example: always use this table

<!--@include: @/../code/dsml/notes/u1.out#pearson-->

| r | Meaning |
|---|---|
| +1 / −1 | perfect positive / negative straight line |
| about ±0.9 | very strong |
| about ±0.7 | strong |
| about ±0.5 | moderate |
| about ±0.3 | weak |
| 0 | **no linear** relationship |

::: danger r = 0 does not mean "no relationship"
For x = −2, −1, 0, 1, 2 and y = x², r = 0 exactly, yet y is completely determined by x. Pearson's r measures **straight-line** relationships only.
:::

**Correlation vs regression** (asked in [spring 2025 end-semester Q1a](../papers/endsem-2025#q1a)): correlation is one symmetric number with no dependent variable; regression is an equation that predicts a dependent variable from independent ones. **Neither proves causation**: ice-cream sales and drownings are correlated because both rise in summer.

## Traps and the 5-minute checklist {#traps}

| # | Trap | Correct version |
|---|---|---|
| 1 | "Data is any fact or value" | add *unprocessed, not interpreted or analysed* |
| 2 | 0/1-coded gender is numerical | categorical: averaging it is meaningless |
| 3 | `a * b` multiplies matrices | element-wise; matrix product is `a @ b` or `np.dot` |
| 4 | `size` and `shape` swapped | `size` is a number (10); `shape` is a tuple (2, 5) |
| 5 | `C = A` copies an array | it aliases; use `A.copy()` |
| 6 | `axis=0` means "per row" | axis 0 collapses the rows: one value **per column** |
| 7 | `df.shape()` | `shape` is an attribute: no parentheses |
| 8 | `loc` slice end excluded | `loc` includes the end label; `iloc` excludes the end position |
| 9 | Series is size mutable | value mutable, **size immutable** |
| 10 | AB = BA | not commutative; even the shapes may differ |
| 11 | r = 0.95, so X causes Y | correlation ≠ causation |
| 12 | Histogram for categories | bar chart for categories; histogram for one numeric variable |

**The checklist:**
1. For a definition, give the slide's exact phrase plus one example.
2. For a face-off, give the one-line difference first, then a table.
3. For Pearson, draw the 7-column table, then substitute once, then interpret (strength, direction, no causation).
4. For any matrix product, write the shapes first: inner numbers must match.

## Quick check {#quick-check}

<Drill n="1" tag="Data types">

A dataset stores Education as 1 = High school, 2 = Bachelor's, 3 = Master's, 4 = PhD. What type of data is it?

<Mcq :options="['Numerical', 'Nominal categorical', 'Ordinal', 'Time series']" answer="c">

The categories have a real order (more education), but the gaps are not equal: PhD − Master's is not "1 unit" of anything. That is ordinal, and it is why label encoding suits it.

</Mcq>

</Drill>

<Drill n="2" tag="Structured data">

Which statement about unstructured data is correct?

<Mcq :options="['It is stored in relational SQL databases', 'It reveals why something is happening', 'It needs less storage than structured data', 'It drives most ML algorithms directly']" answer="b">

Unstructured data (emails, reviews, audio) explains **why**; structured data shows **what**. It lives in NoSQL stores, needs more space, and feeds NLP and text mining.

</Mcq>

</Drill>

<Drill n="3" tag="NumPy">

<FillIn q="`a = np.arange(12).reshape(3, 4)`. What is `a.sum(axis=0).shape`? Type it as a tuple." answer="(4,)|(4, )|4">

The axis you name disappears: axis 0 (length 3) collapses, leaving the 4 columns. Output: `[12 15 18 21]`.

</FillIn>

</Drill>

<Drill n="4" tag="NumPy">

Which pair of shapes **cannot** be broadcast together?

<Mcq :options="['(4, 3) and (3,)', '(4, 1) and (1, 5)', '(4, 3) and (4,)', '(4, 3) and a scalar']" answer="c">

Compare from the right: 3 vs 4 are unequal and neither is 1, so it fails. (4, 3) with (4, 1) would have worked.

</Mcq>

</Drill>

<Drill n="5" tag="Pandas">

Why does an integer column become `float64` after a value goes missing?

<Mcq :options="['Pandas converts every column to float', 'NaN is a float, so the column must hold floats', 'Missing values are stored as 0.0', 'It is a bug in older versions']" answer="b">

The missing marker NaN is a floating-point value; there is no integer NaN, so the whole column is upcast to float64. This is on the dtypes slide almost word for word.

</Mcq>

</Drill>

<Drill n="6" tag="Pandas">

<FillIn q="`df.groupby('rank')` has just run. What has it computed?" answer="nothing|nothing yet|nothing until needed">

GroupBy is lazy: creating the object only checks that the mapping is valid. The splitting happens when you call an aggregation such as `.mean()`.

</FillIn>

</Drill>

<Drill n="7" tag="Charts">

You want to see whether a salary column is skewed before choosing mean or median imputation. Which chart?

<Mcq :options="['Bar chart', 'Line chart', 'Histogram', 'Pie chart']" answer="c">

The distribution of one numeric variable is a histogram. A long right tail means skew, so use the median.

</Mcq>

</Drill>

<Drill n="8" tag="Linear algebra">

<FillIn q="A is 4 × 3 and B is 3 × 2. What is the shape of AB? Type it like 4x2." answer="4x2|4 x 2|4×2|(4, 2)|(4,2)">

Inner numbers (3 and 3) match, so the product exists; it takes the outer numbers, 4 × 2. BA would be (3 × 2)(4 × 3), which does not exist.

</FillIn>

</Drill>

<Drill n="9" tag="Linear algebra">

<FillIn q="The eigenvalues of a 2 × 2 matrix are 6 and 1. What is its determinant?" answer="6">

The determinant is the product of the eigenvalues: 6 × 1 = 6. (Their sum, 7, is the trace.)

</FillIn>

</Drill>

<Drill n="10" tag="Correlation">

For five points, Σ(x − x̄)(y − ȳ) = −24, Σ(x − x̄)² = 10 and Σ(y − ȳ)² = 90. What is Pearson's r?

<Mcq :options="['−0.8', '−0.24', '0.8', '−2.4']" answer="a">

r = −24 / √(10 × 90) = −24 / 30 = −0.8: a strong negative relationship. The sign comes from the numerator.

</Mcq>

</Drill>
