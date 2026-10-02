---
title: Unit 2 · Data acquisition and preprocessing
---

# Unit 2 · Data acquisition and preprocessing

"There can be no knowledge discovery on bad data." This unit turns raw data into something a model can use: fill the gaps, tame the noise, turn categories into numbers, put features on one scale, and split without leaking the test set.

::: info How this unit is examined
- **Mid-semester:** **both** past mid-semesters asked the same two questions, word for word: *when do we prefer min-max scaling over standardization?* and *assess two issues of one-hot encoding with high cardinality* ([Sep 2025 Q1](../papers/mst-2025#q1a), [spring 2025 Q5](../papers/mst-2025-spring#q5a)). Learn both answers cold.
- **End-semester:** z-score outliers (5), why encode and the techniques (5), min-max and z-score by hand (5), label vs one-hot for a decision tree (5).
- **Theory quiz:** the seven steps and their order, the missing-data ladder, label vs one-hot vs dummy, the two scaling slides that contradict each other.
- **Lab:** [Assignment 4](../assignments/a4) is this unit in code.
:::

## Read this first: the unit on one screen {#toolkit}

| Problem | Fix | Trade-off |
|---|---|---|
| Missing values, few rows affected | delete the rows | loses information |
| Missing numeric values | mean (median if skewed) | mean is dragged by outliers |
| Missing categorical values | mode (most frequent) | ties are arbitrary |
| Noise and outliers | binning, z-score or IQR, clustering, regression | each rule flags different points |
| Ordinal categories | **label** encoding | invents an order if used on nominal data |
| Nominal categories | **one-hot** (N columns) or **dummy** (N − 1) | many columns when there are many categories |
| Features on different scales | **min-max** to [0, 1] or **z-score** to mean 0, sd 1 | min-max breaks on outliers |
| Honest evaluation | split **before** scaling; fit the scaler on train only | – |

**The order of the seven steps:** get the dataset → import libraries → import the dataset → **missing data → encode → split → scale**.

## 1. Where data comes from, and where it lives {#sources}

**Collection:** surveys, web scraping, sensors and logs, APIs, and public repositories. The slides' repositories: **Kaggle** and **IEEE DataPort**, plus Google Dataset Search, Microsoft Research Open Data, Amazon datasets, the **UCI Machine Learning Repository** and government data portals. Good data is **representative** of each concept, **balanced** across classes, and accurately **labelled**: emotion tags for songs are hard to get right because emotion is ambiguous.

**Storage and management:** save the dataset as **CSV** (usual), XLSX or HTML and load it with `pd.read_csv`. Structured data goes in relational (SQL) databases and data warehouses; unstructured data in NoSQL stores and file systems ([Unit 1](./unit-1#data-types)). Data gathered from many sources arrives raw and inconsistent, which is why preprocessing exists.

## 2. Why preprocess, and the steps {#steps}

**Definition (learn it):** data preprocessing is the process of preparing raw data and making it suitable for a machine learning model. It is the **first and crucial step** in creating a model: the transformations applied to the data before feeding it to the algorithm, converting a raw dataset into a clean one.

**Real-world data is:**
- **Incomplete**: missing values, missing attributes, or only aggregate data.
- **Noisy**: errors and outliers.
- **Inconsistent**: discrepancies in codes or names ("Delhi", "New Delhi", "DEL").

| Task | Covers |
|---|---|
| **Data cleaning** | fill missing values, smooth noise, find and remove outliers, resolve inconsistencies |
| **Data integration** | combine several databases, data cubes or files |
| **Data transformation** | normalisation and aggregation |
| **Data reduction** | less volume, same (or similar) analytical result |
| **Data discretization** | part of reduction: replace numeric attributes with nominal ones (bins) |

The **seven steps** (Lec-4): (1) get or generate the dataset, (2) import libraries (NumPy, Matplotlib, Pandas), (3) import the dataset, (4) find missing data, (5) encode categorical data, (6) split into training and test sets, (7) feature scaling.

::: tip Why split comes before scaling
The scaler learns numbers from the data it is fitted on: min and max, or mean and standard deviation. Fit it on everything and the test rows have leaked into training, so the test score is optimistic. Split first, `fit_transform` on the training set, `transform` on the test set.
:::

## 3. Missing data {#missing}

Missing values appear as **NaN, NA, None, " " or ?**. Causes: human error in data entry, faulty sensor readings, software bugs in the pipeline. Visualise them with `missingno` (`msno.matrix(df)`); count them with `df.isnull().sum()`.

| Situation | Do this | Because |
|---|---|---|
| Few rows have a missing value | **Delete** those rows | cheap; you lose little |
| Numeric column, roughly symmetric | **Mean** | keeps the column's average (the slides' default for age, salary, year) |
| Numeric column, **skewed or with outliers** | **Median** | the mean is dragged by the extremes; the median is not |
| Categorical column | **Mode** (most frequent) | a mean of categories is meaningless |
| The value is predictable from other columns | **Predict it** with a model (Bayes, decision tree) | keeps the most information, costs the most |
| The **class label** is missing | **Ignore the tuple** | you cannot invent the answer for supervised learning |

::: danger The cost of deleting
The slides say it plainly: deleting rows "is not so efficient", and removing data "may lead to loss of information which will not give the accurate output". Set that against the rule of thumb that more data trains better models: delete only when the missing proportion is small.
:::

### Worked example: Assignment 4's data

<!--@include: @/../code/dsml/notes/u2.out#impute-->

**Tools, by name:** `SimpleImputer(missing_values=np.nan, strategy='mean')` from `sklearn.impute` (also `'median'`, `'most_frequent'`), used with `fit` then `transform`. In NumPy, `np.nan_to_num(arr, nan=0)` fills a constant and `np.nanmean(arr)` is the mean ignoring NaN (a plain mean of an array containing NaN is NaN). In Pandas, `dropna()` (any NaN drops the row), `dropna(how='all')`, `dropna(thresh=n)` (keep rows with at least n real values) and `fillna(...)`.

## 4. Noise, outliers and duplicates {#outliers}

| Technique | How |
|---|---|
| **Binning** | sort the values, split them into bins, then smooth each value by its bin **mean**, **median** or **boundaries** |
| **Clustering** | group the values; points that fall outside every cluster are outliers |
| **Regression** | fit a function and replace values by the fitted ones |
| **Inconsistent data** | no algorithm: use domain knowledge or an expert |

### Worked example: binning

<!--@include: @/../code/dsml/notes/u2.out#binning-->

### Finding outliers: the z-score rule and the IQR rule

**Z-score rule:** compute $z = (x - \mu)/\sigma$ for every value; |z| > 3 (or 2) is an outlier. Weakness: μ and σ are themselves pulled by the outliers, so a big outlier can **mask** a smaller one. The [autumn 2024 Q2b](../papers/endsem-2024#q2b) data shows this exactly: 500 hides −2.

**IQR rule:** values below Q1 − 1.5·IQR or above Q3 + 1.5·IQR, where IQR = Q3 − Q1. Quartiles barely move for extreme values, so this rule is robust. It is also what the whiskers of a **box plot** show.

<!--@include: @/../code/dsml/notes/u2.out#iqr-->

**Duplicates** (Assignment 4 Q4): `df.duplicated()` flags a row only if an identical row appeared earlier; `drop_duplicates()` removes them. Impute **before** de-duplicating: NaN ≠ NaN, so two otherwise identical rows with a missing value would not match.

## 5. Encoding categorical data {#encoding}

Models compute with numbers (weighted sums, distances, gradients), so every categorical column must be encoded before fitting, without inventing information that is not there.

| | Label / ordinal | One-hot | Dummy |
|---|---|---|---|
| Does | one integer per category | one 0/1 column per category; exactly one is 1 in each row | one-hot minus one column |
| Columns for N categories | 1 | N | **N − 1** |
| Use for | **ordinal** data (order matters) | **nominal** data (no order) | nominal data, the compact form |
| Problem | the model may treat the codes as ordered ("one value is greater than another") | can greatly increase dimensionality | as one-hot |

**The slides' rule:** use label encoding when the order of categories matters; use one-hot when it does not and you want to represent presence or absence. Their example: `city` = Chandigarh, Delhi, Mysore is nominal (Delhi is not "greater" than Chandigarh), so one-hot. Education level or small/medium/large is ordinal, so label encoding.

| City | Label | One-hot: Chandigarh, Delhi, Mysore | Dummy: Delhi, Mysore |
|---|:-:|:-:|:-:|
| Chandigarh | 0 | 1 0 0 | 0 0 |
| Delhi | 1 | 0 1 0 | 1 0 |
| Mysore | 2 | 0 0 1 | 0 1 |

In the dummy version Chandigarh is the row with all zeros: the dropped column is implied, which is why it is "a more compact version of one-hot by dropping a redundant column".

### High cardinality: the mid-semester question {#high-cardinality}

A feature with many distinct values (3,000 PIN codes, 200 product types). One-hot encoding it causes:

1. **Dimensionality explosion**: 3,000 new columns; the model needs far more data, and distances lose meaning (the curse of dimensionality).
2. **Sparse data, memory and time**: each row is one 1 and thousands of zeros.
3. **Overfitting on rare categories**: many columns have only a few rows behind them.
4. **Multicollinearity (dummy-variable trap)**: the columns always sum to 1, so a linear model cannot separate their effects; drop one (dummy encoding).
5. **Unseen categories** at test time have no column (`OneHotEncoder(handle_unknown='ignore')`).

**Remedies:** group rare values into "Other"; **generalise** up the hierarchy first (PIN code → city → state); or use an encoding that keeps one column: frequency encoding (how often the value occurs), target encoding (the mean of the target for that value), or binary encoding.

::: tip Trees are different
A decision tree splits on one feature at a time with thresholds and never adds or multiplies the codes, so **label encoding is usually fine for trees**, and one-hot on 200 categories makes them deep and slow ([spring 2025 Q1c](../papers/endsem-2025#q1c)). For linear models and KNN, use one-hot.
:::

**Tools, by name:** `LabelEncoder` (`sklearn.preprocessing`); `OneHotEncoder`, often inside `make_column_transformer(..., remainder='passthrough')` from `sklearn.compose`; `pd.get_dummies(df['City'])`.

## 6. Feature scaling {#scaling}

**Why:** features measured in large numbers dominate any distance. The slides' example is Age (tens) and Salary (tens of thousands): in a Euclidean distance, salary decides everything and age contributes almost nothing. **Definition:** a method to standardise the **independent** variables within a specific range, so they can be compared on common ground. (Scale the features x, not the target.)

| Method | Formula | Range | Use when |
|---|---|---|---|
| **Min-max** (normalisation) | $x' = \dfrac{x - \min}{\max - \min}$ | [0, 1] (sometimes [−1, 1]) | data **not Gaussian**; no big outliers; models that assume no distribution (KNN, neural networks); hard limits (pixels 0–255) |
| **Standardisation** (z-score) | $z = \dfrac{x - \mu}{\sigma}$ | **unbounded**; mean 0, sd 1 | data roughly **Gaussian**; outliers present; min and max unknown |
| Mean normalisation | $x' = \dfrac{x - \mu}{\max - \min}$ | [−1, 1], mean 0 | – |
| Unit vector | $x' = x / \lVert x \rVert$ | [0, 1] | data with hard boundaries, e.g. colour codes 0–255 |

<!--@include: @/../code/dsml/notes/u2.out#scaling-->

### Why one outlier ruins min-max

<!--@include: @/../code/dsml/notes/u2.out#outlier-effect-->

::: warning Correction: the slides contradict themselves
Lec-4's "Feature scaling methods" slide says standardisation has "scale range: 0 to 1". Two slides later it says "standardization does not have a bounding range". **The second is right**: z-scores are routinely negative and can exceed 1. Only min-max gives 0 to 1. If a fill-in-the-blank quotes the first slide, recognise where it came from, but never write "standardisation scales to [0, 1]" in an explanation.
:::

### The mid-semester answer, in short

> **Prefer min-max** when the data is not Gaussian, has no big outliers, and the model needs a bounded range or assumes no distribution (KNN, neural networks), or when the feature has natural limits. *Example:* pixels 0–255 → x/255, so 51 becomes 0.2. **Prefer standardisation** when the data is roughly Gaussian, contains outliers, or min and max are unknown.

The full 6-mark version is [Sep 2025 Q1a](../papers/mst-2025#q1a).

### L1 and L2 normalisation (the Pandas deck's other meaning of "normalisation")

<!--@include: @/../code/dsml/notes/u2.out#l1l2-->

::: danger Two things called "normalisation"
Min-max and z-score work **down a column** (per feature). L1 and L2 normalisation work **across a row** (per sample). If asked to compare normalisation with scaling, this row-vs-column difference is the deeper point.
:::

::: warning Correction: mean removal does not make the standard deviation 1
The Pandas deck says mean removal leaves "mean almost 0 and standard deviation 1". Subtracting the mean only centres the data: mean 0, spread unchanged. The deck's example used `preprocessing.scale`, which also divides by σ. Mean removal = centring; centring + dividing by σ = standardisation.
:::

## 7. Splitting: training, validation and test {#split}

| Set | Role |
|---|---|
| **Training** | the model learns its parameters here; the outputs are known |
| **Validation** | used during development to tune choices (k in KNN, λ in ridge) and compare models; you may look at it many times |
| **Test** | touched **once**, at the end, to estimate real-world performance |

The usual split is **70:30** or **80:20**. `train_test_split(X, y, test_size=0.2, random_state=0)` returns `X_train, X_test, y_train, y_test` in that order.

- **`random_state`** controls the random shuffle before the split, so the **same split is reproduced** every run. It is about reproducibility, not accuracy.
- **`stratify=y`** keeps the class proportions the same in both halves (Assignment 5 used it for a 64/36 target).

::: warning Correction: slide 48 mislabels y_test
It calls `y_test` the "independent variable for testing data". **x** holds the independent variables (features); **y** is the dependent variable (target). So `y_train` and `y_test` are both dependent.
:::

::: danger Two kinds of leakage
- **Data leakage:** information from the test set reaches training, e.g. fitting the scaler before splitting. The fix is the order above.
- **Target leakage:** a feature that encodes the answer. Assignment 4 built its target `Senior` from `Experience` and kept `Experience` as a feature, so any model would score 100% while learning nothing. Iris's `Id` column (Assignment 6) secretly encodes the species because the file is sorted. Drop such columns.
:::

## 8. Transformation, reduction and discretization {#transform}

| Transformation | Meaning |
|---|---|
| Normalisation | scale values into a range |
| **Aggregation** | move up a concept hierarchy on **numeric** data (daily sales → monthly) |
| **Generalisation** | move up a concept hierarchy on **nominal** data (city → state) |
| Attribute construction | build new attributes from existing ones (feature engineering, Assignment 4 Q8: salary per year of experience) |

| Reduce the number of… | How |
|---|---|
| attributes | data cube aggregation (roll-up, slice, dice); attribute selection (filter and wrapper methods); **PCA** (numeric attributes only) |
| attribute values | binning or histograms; clustering; aggregation or generalisation |
| tuples (rows) | sampling |

**Discretization** turns a numeric attribute into intervals, and counts as **reduction** (not transformation): a likely quiz question.
- **Unsupervised** (the class is not used): **equal-width** (equal-sized intervals) and **equal-frequency / equal-depth** (equal counts per interval). See the binning example above.
- **Supervised** (uses the class): sort the values → put breakpoints between values of different classes → merge neighbouring intervals with similar class distributions if there are too many. **Entropy-based** discretization is the other named method.

Concept hierarchies are generated by applying partitioning or discretization recursively.

## 9. Feature extraction vs feature selection {#features}

| | Feature extraction | Feature selection |
|---|---|---|
| Does | **creates** new features from raw data | **removes** irrelevant or redundant features from the existing set |
| Example | musical tempo computed from audio | dropping `height_inches` when `height_cm` exists |
| Catch | extraction algorithms are not 100% accurate | – |

**Redundant features decrease accuracy** (the slide says so): Naive Bayes, for instance, assumes features are independent, so two copies of the same evidence are counted twice. Selection gives simpler, faster, more interpretable models.

## Traps and the 5-minute checklist {#traps}

| # | Trap | Correct version |
|---|---|---|
| 1 | Standardisation gives [0, 1] | unbounded, mean 0, sd 1; only min-max gives [0, 1] |
| 2 | Scale, then split | split, then fit the scaler on the training set only |
| 3 | Label-encode a nominal column (City) | one-hot; label encoding is for ordinal data (or trees) |
| 4 | "One-hot's problem is too many columns" | name the mechanism: sparsity, curse of dimensionality, overfitting, dummy trap |
| 5 | Mean imputation on skewed data | median |
| 6 | Mean imputation on a categorical column | mode |
| 7 | Delete every row with a NaN | only if few rows are affected; otherwise impute |
| 8 | Z-score finds every outlier | big outliers mask small ones; say so, or use IQR |
| 9 | Discretization is a transformation | it is part of **reduction** |
| 10 | Aggregation and generalisation are the same | numeric vs nominal hierarchy |
| 11 | `random_state` improves accuracy | it makes the split reproducible |
| 12 | Mean removal makes sd 1 | it only centres the data |

**The checklist for a scenario question:**
1. Name the flaw (missing, noisy, inconsistent, unscaled, categorical, redundant).
2. Classify the column: numeric or categorical; if categorical, ordinal or nominal.
3. Name the technique precisely ("one-hot encoding", not "convert to numbers").
4. State its trade-off.
5. Check the order: missing → encode → split → scale.

## Quick check {#quick-check}

<Drill n="1" tag="Order">

A student scales the whole dataset, then splits it 80:20. What is wrong?

<Mcq :options="['Nothing; the order does not matter', 'Test information leaks into training through the scaler', 'Scaling must come before handling missing values', 'The split should be 70:30']" answer="b">

The scaler's min, max, mean and standard deviation were computed using the test rows, so the test score is optimistic. Split first and fit the scaler on the training set only.

</Mcq>

</Drill>

<Drill n="2" tag="Missing data">

A house-price column is missing 8% of its values, and a histogram shows a long right tail (a few mansions). How should you fill it?

<Mcq :options="['Mean', 'Median', 'Mode', 'Delete the column']" answer="b">

The mansions drag the mean up, so mean imputation would insert prices higher than most real houses. The median ignores how extreme the tail is.

</Mcq>

</Drill>

<Drill n="3" tag="Encoding">

<FillIn q="How many columns does dummy encoding create for a feature with 5 categories?" answer="4|four">

Dummy encoding uses N − 1 columns; the dropped category is the row of all zeros. One-hot would use 5.

</FillIn>

</Drill>

<Drill n="4" tag="Encoding">

Size has values S, M, L and Colour has Red, Blue, Green. A student label-encodes both. What breaks?

<Mcq :options="['Both are fine', 'Size is fine; Colour gets a fake order', 'Colour is fine; Size gets a fake order', 'Both get a fake order']" answer="b">

Size is ordinal (S < M < L), so 0/1/2 keeps real information. Colour is nominal: coding Green = 2 tells the model Green is "twice" Blue. One-hot (or dummy) encode Colour.

</Mcq>

</Drill>

<Drill n="5" tag="Scaling">

<FillIn q="Min-max scale the value 30 from the column 10, 20, 30, 50." answer="0.5|1/2">

(30 − 10)/(50 − 10) = 20/40 = 0.5.

</FillIn>

</Drill>

<Drill n="6" tag="Scaling">

You are building a KNN classifier; the feature histograms are lumpy and clearly not bell-shaped, with no extreme outliers. Which scaler does the slide recommend?

<Mcq :options="['Standardisation, because KNN assumes Gaussian data', 'Min-max normalisation', 'No scaling: KNN does not need it', 'L1 normalisation of each feature']" answer="b">

Normalisation suits data that is not Gaussian and algorithms that assume no distribution, and the slide names KNN and neural networks. Scaling matters for KNN because it is entirely distance-based.

</Mcq>

</Drill>

<Drill n="7" tag="Reduction">

Rolling daily sales up to monthly sales is…

<Mcq :options="['generalisation', 'aggregation', 'discretization', 'attribute construction']" answer="b">

Moving up a hierarchy on **numeric** data is aggregation. On nominal data (city → state) it would be generalisation.

</Mcq>

</Drill>

<Drill n="8" tag="Binning">

<FillIn q="Equal-width binning of values from 0 to 100 into 4 bins: what is the width of each bin?" answer="25">

(max − min)/number of bins = (100 − 0)/4 = 25. Equal-depth binning would instead put the same number of values in each bin.

</FillIn>

</Drill>

<Drill n="9" tag="Split">

What does `random_state=42` do in `train_test_split`?

<Mcq :options="['Puts 42% of rows in the test set', 'Makes the same split happen on every run', 'Improves model accuracy', 'Keeps class proportions equal in both sets']" answer="b">

It seeds the shuffle, so the split is reproducible. Keeping class proportions is `stratify=y`.

</Mcq>

</Drill>

<Drill n="10" tag="Outliers">

Values: 10, 12, 11, 13, 12, 100. Which is true of the z-score test with cut-off 2?

<Mcq :options="['100 is flagged, because z(100) ≈ 2.2', 'Nothing is flagged', '10 and 100 are both flagged', '100 is not flagged, because σ is huge']" answer="a">

μ = 26.33, population σ ≈ 32.96, so z(100) = 73.67/32.96 ≈ 2.24 > 2: flagged. With a cut-off of 3 it would not be, which is exactly how one big value inflates σ.

</Mcq>

</Drill>
