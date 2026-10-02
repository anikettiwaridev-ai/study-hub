---
title: Timed quiz sets
---

# Timed quiz sets

Two 10-minute sets in the style of a theory quiz: one for Units 1–2, one for Units 3–4. No DSML quiz papers were available, so these are built from what the slides stress, the past papers' wording, and the traps in the notes. Each set has a couple of long "paragraph" questions, because reading time is what costs marks in a 10-minute quiz.

::: tip The routine for a 10-minute quiz
1. **First pass, 4 minutes:** answer every short question you know at once. Skip anything that needs more than 20 seconds.
2. **Long questions:** read the **last sentence first** (what is actually asked), then skim the paragraph only for the numbers or the one fact you need. Most paragraphs reduce to one line: the skeleton under each long question shows that line. Open it only after you have tried.
3. **Second pass:** the skipped ones. Never leave a blank in an MCQ.
:::

## Set A · Units 1 and 2 {#set-a}

<div class="timed-set">

<QuizTimer :minutes="10" label="Set A" />

<Drill n="1" tag="Data">

Which of these is **unstructured** data?

<Mcq :options="['A SQL table of hotel bookings', 'Web-server logs', 'A folder of customer emails', 'GPS sensor readings']" answer="c">

Emails, documents and PDFs are the slides' unstructured sources. Logs and GPS readings are structured: they fit rows and columns.

</Mcq>

</Drill>

<Drill n="2" tag="Data">

<FillIn q="Structured data reveals patterns that show what is happening; unstructured data reveals ____ it is happening." answer="why">

The slides' one-liner: structured tells you **what**, unstructured tells you **why**.

</FillIn>

</Drill>

<Drill n="3" tag="Types">

"Beginner, intermediate, advanced" is an example of which type of data?

<Mcq :options="['Numerical', 'Nominal', 'Ordinal', 'Time series']" answer="c">

Categories with a natural order: ordinal (a mix of numerical and categorical, as the slide puts it).

</Mcq>

</Drill>

<Drill n="4" tag="NumPy">

How many values do `np.arange(0, 1, 0.25)` and `np.linspace(0, 1, 5)` produce?

<Mcq :options="['4 and 5', '5 and 5', '4 and 4', '5 and 4']" answer="a">

`arange` excludes the stop: 0, 0.25, 0.5, 0.75 (4 values). `linspace` gives exactly the count asked for, stop included: 0, 0.25, 0.5, 0.75, 1 (5 values).

</Mcq>

</Drill>

<Drill n="5" tag="NumPy">

`A = np.zeros((2, 2)); C = A; C[0, 0] = 5`. What is `A[0, 0]`?

<Mcq :options="['0.0', '5.0', 'An error', 'It depends on the dtype']" answer="b">

`C = A` makes a second name for the same array, not a copy. Use `A.copy()` for an independent array.

</Mcq>

</Drill>

<Drill n="6" tag="Pandas">

Which statement is **false**?

<Mcq :options="['A Series is value mutable', 'A Series is size mutable', 'A DataFrame is size mutable', 'Pandas structures are built on NumPy arrays']" answer="b">

The slide: all Pandas structures are value mutable; all except Series are size mutable. Series is size **immutable**.

</Mcq>

</Drill>

<Drill n="7" tag="Pandas">

<FillIn q="`df.groupby('rank')['salary'].mean()` returns a Series. What change returns a DataFrame instead?" answer="double brackets|[['salary']]|use double brackets">

`df.groupby('rank')[['salary']].mean()`: double brackets keep it a DataFrame, just as in plain column selection.

</FillIn>

</Drill>

<Drill n="8" tag="Missing data">

What does `df.dropna(thresh=5)` do?

<Mcq :options="['Drops rows with more than 5 missing values', 'Drops rows with fewer than 5 non-missing values', 'Drops the first 5 rows with NaN', 'Fills up to 5 missing values']" answer="b">

It keeps a row only if it has at least 5 real values. `how='any'` (the default) drops a row with even one NaN; `how='all'` only completely empty rows.

</Mcq>

</Drill>

<Drill n="9" tag="Encoding">

<FillIn q="Dummy encoding of a feature with 6 categories creates how many columns?" answer="5|five">

N − 1 = 5. One-hot would create 6; label encoding 1.

</FillIn>

</Drill>

<Drill n="10" tag="Scaling">

After standardisation (z-score), a feature's values…

<Mcq :options="['lie in [0, 1]', 'lie in [−1, 1]', 'have mean 0 and standard deviation 1, with no fixed range', 'are all positive']" answer="c">

Only min-max gives [0, 1]. The slide that says standardisation scales to 0–1 contradicts the next slide; the second one is right.

</Mcq>

</Drill>

<Drill n="11" tag="Reduction">

Discretization is classified as part of…

<Mcq :options="['data cleaning', 'data integration', 'data transformation', 'data reduction']" answer="d">

"Data discretization: part of data reduction, replacing numerical attributes with nominal ones."

</Mcq>

</Drill>

<Drill n="12" tag="Long question">

A hospital collects patient records: age (a few blanks, ages spread fairly evenly), blood group (A, B, AB, O; some blanks), annual income in rupees (skewed by a few very wealthy patients; some blanks), and a 0/1 label for a disease. A student plans to (1) standardise all numeric columns, (2) split 80:20, (3) fill missing values, and (4) label-encode blood group, in that order, before training a KNN classifier. Which correction is needed?

<details class="skeleton"><summary>Skeleton: open it after you try</summary>

Order should be missing → encode → split → scale. Blood group is nominal. Income is skewed.

</details>

<Mcq :options="['Only swap steps 1 and 2', 'Fill missing first (median for income, mode for blood group), one-hot blood group, then split, then scale using the training set only', 'Drop all rows with missing values, then follow the same order', 'Nothing; KNN does not need preprocessing']" answer="b">

Three fixes: the steps are in the wrong order (scaling before the split leaks test data); blood group is **nominal**, so one-hot, not label encoding; and skewed income wants the **median**, categorical blood group the **mode**.

</Mcq>

</Drill>

<Drill n="13" tag="Long question">

A data scientist has two features for a distance-based model: `height_cm` (150–190) and `annual_income` (₹2 lakh to ₹80 lakh, with a handful of incomes above ₹5 crore). The model's predictions seem to depend on income alone. She also notices a third column, `height_inches`, which is just `height_cm / 2.54`. What are the two problems, and the two fixes?

<details class="skeleton"><summary>Skeleton: open it after you try</summary>

Unscaled income dominates the distance; an exact duplicate feature is redundant.

</details>

<Mcq :options="['Overfitting; use more data', 'Income dominates the unscaled distance, so scale (standardise, given the outliers); height_inches is redundant, so drop it (feature selection)', 'Too few features; add more columns', 'Height should be label-encoded']" answer="b">

Distances are dominated by the feature with the largest range, so scale; with extreme incomes, standardisation is safer than min-max. A feature that is an exact copy of another adds nothing and double-counts the same evidence; feature selection removes it.

</Mcq>

</Drill>

</div>

## Set B · Units 3 and 4 {#set-b}

<div class="timed-set">

<QuizTimer :minutes="10" label="Set B" />

<Drill n="1" tag="Definition">

In Mitchell's definition, "the percentage of games won" in checkers is…

<Mcq :options="['the task T', 'the performance measure P', 'the experience E', 'the target function']" answer="b">

P is always a measurement. T is playing checkers; E is the games played against itself.

</Mcq>

</Drill>

<Drill n="2" tag="Fitting">

Low bias and high variance describe…

<Mcq :options="['underfitting', 'overfitting', 'a well-generalised model', 'a model with no features']" answer="b">

Overfitting: very flexible (low bias) and over-sensitive to the training sample (high variance). Underfitting is the reverse.

</Mcq>

</Drill>

<Drill n="3" tag="Metrics">

<FillIn q="TP = 45, FP = 5, FN = 15. What is the recall? Give a decimal." answer="0.75|.75|3/4">

Recall = TP/(TP + FN) = 45/60 = 0.75. (Precision = 45/50 = 0.9.)

</FillIn>

</Drill>

<Drill n="4" tag="Metrics">

For a cancer-screening test, which metric should be kept highest?

<Mcq :options="['Precision', 'Recall', 'Specificity', 'Accuracy']" answer="b">

A missed cancer (false negative) is far worse than a false alarm, so recall (sensitivity) matters most. Spam filtering is the opposite case: precision.

</Mcq>

</Drill>

<Drill n="5" tag="ROC">

A ROC curve plots…

<Mcq :options="['precision against recall', 'TPR against FPR', 'accuracy against threshold', 'FPR against TNR']" answer="b">

y = TPR (recall), x = FPR (1 − specificity), one point per threshold.

</Mcq>

</Drill>

<Drill n="6" tag="Cross-validation">

<FillIn q="8-fold cross-validation on 400 examples: how many examples does each model train on?" answer="350">

(k − 1)/k × n = 7/8 × 400 = 350; each test fold has 50; 8 models are built.

</FillIn>

</Drill>

<Drill n="7" tag="Gradient descent">

<FillIn q="Minimise f(w) = (w − 2)² from w = 0 with learning rate 0.25. What is w after one step?" answer="1|1.0">

f′(w) = 2(w − 2) = −4 at w = 0; w ← 0 − 0.25 × (−4) = 1.

</FillIn>

</Drill>

<Drill n="8" tag="Logistic">

A logistic-regression model gives z = 2 for a customer. What is the predicted probability (to 2 decimals)?

<Mcq :options="['0.12', '0.50', '0.73', '0.88']" answer="d">

σ(2) = 1/(1 + e⁻²) = 1/(1 + 0.1353) = 0.88. (0.73 is σ(1); 0.12 is σ(−2).)

</Mcq>

</Drill>

<Drill n="9" tag="KNN">

Why is KNN called a lazy learner?

<Mcq :options="['It uses few neighbours', 'It builds no model during training and does all its work at prediction time', 'It needs no distance metric', 'It converges slowly']" answer="b">

`fit` only stores the data; each prediction then measures the distance to every stored point.

</Mcq>

</Drill>

<Drill n="10" tag="SVM">

<FillIn q="A linear SVM has w = (3, 4). What is the margin width 2/‖w‖?" answer="0.4|.4|2/5">

‖w‖ = √(9 + 16) = 5, so the margin is 2/5 = 0.4.

</FillIn>

</Drill>

<Drill n="11" tag="Naive Bayes">

In Naive Bayes, one feature value never appeared with a class in training. What happens, and what is the fix?

<Mcq :options="['Nothing; it is ignored', 'That class gets probability 0 whatever the other features say; use Laplace smoothing', 'The class prior becomes 1', 'The model switches to KNN']" answer="b">

A zero factor makes the whole product zero. Laplace smoothing adds 1 to every count.

</Mcq>

</Drill>

<Drill n="12" tag="Trees">

<FillIn q="A node holds 3 Yes and 1 No. What is its entropy (4 decimals)?" answer="0.8113|.8113">

−(3/4)log₂(3/4) − (1/4)log₂(1/4) = 0.3113 + 0.5 = 0.8113.

</FillIn>

</Drill>

<Drill n="13" tag="Long question">

A team trains a model to flag fraudulent transactions. In the test set of 10,000 transactions, only 100 are fraud. The model labels every transaction "genuine" and the team reports 99% accuracy. A manager asks whether this model is ready. Using the confusion matrix, which statement is right?

<details class="skeleton"><summary>Skeleton: open it after you try</summary>

Predict-all-negative on 1% positives: TP = 0, so recall = 0.

</details>

<Mcq :options="['Ready: 99% accuracy is excellent', 'Not ready: TP = 0, so recall is 0 and it catches no fraud; accuracy misleads on imbalanced data', 'Not ready: precision is 99%, which is too high', 'Ready, if the threshold is raised']" answer="b">

TN = 9,900, FN = 100, TP = FP = 0: accuracy 99%, recall 0. The accuracy paradox. Report recall, precision and F1 (or a PR curve) for rare positives.

</Mcq>

</Drill>

<Drill n="14" tag="Long question">

A student tunes k for a KNN classifier by training on the training set and trying k = 1 to 15, keeping the k with the best accuracy on the **test** set. k = 1 wins with 96.7%. She reports 96.7% as the model's expected accuracy on new data. What is wrong, and what should she do?

<details class="skeleton"><summary>Skeleton: open it after you try</summary>

Choosing on the test set leaks it; k = 1 overfits; use cross-validation on the training set.

</details>

<Mcq :options="['Nothing is wrong', 'The test set was used to choose k, so 96.7% is optimistic, and k = 1 is the most overfit choice; choose k by cross-validation on the training data and touch the test set once at the end', 'She should have used k = 15', 'KNN cannot be tuned']" answer="b">

This is exactly Assignment 6's set-up: test accuracy picked k = 1, while 5-fold cross-validation on the training set picked k = 5, whose honest test score was 93.3%.

</Mcq>

</Drill>

</div>
