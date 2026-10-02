---
title: End-semester, autumn 2024
---

# End-semester, autumn 2024

<PaperHeader :rows="[
  ['Programme', 'B.Tech (CSE / AI), 3rd semester, 2024'],
  ['Course code', 'CSN3002 / ES1701 / AIN3003'],
  ['Maximum marks', '80'],
  ['Time allowed', '3 hours'],
  ['Note on the paper', 'All questions are compulsory. Assume suitably and state additional data required, if any. A non-programmable scientific calculator is allowed.'],
]" />

::: info How to use an end-semester paper before the mid-semester
This is your course's own end-semester paper, so it shows how the Units 1–4 topics are asked at full length. 60 of its 80 marks are Units 1–4, and every one of those questions is solved here. Q5 (DBSCAN, PCA, chi-square) is Unit 5 and waits for the end-semester build.
:::

<Q id="E24.Q1a" title="Choosing a visualisation">

What is the use of visualization of data? Choose the best visualization method (out of bar chart, line chart, histogram, box plot) for: (a) data that consists of categories or labels; (b) data that is collected over time, showing trends and changes; (c) data that consists of numeric values representing quantities, showing the distribution of data.

::::: details Solution

**Use of visualisation.** It turns a table into a picture the eye can read at once: it shows patterns, trends, outliers and relationships that are invisible in raw numbers; it is the main tool of **exploratory data analysis** (the third stage of the data science life cycle); it guides preprocessing (a histogram shows skew, so you pick median over mean imputation); and it communicates results to people who will not read the numbers.

| Data | Best chart | Why |
|---|---|---|
| (a) Categories or labels | **Bar chart** | One bar per category, bars separated, height = count or value. Easy to compare categories. |
| (b) Collected over time | **Line chart** | The x-axis is ordered time and the line joins consecutive points, so rises, falls and trends are visible. |
| (c) Numeric values, distribution | **Histogram** | Values are grouped into bins and the bars touch, so the shape (skew, peaks, spread) is visible. |

The **box plot** is the fourth option: it summarises a numeric distribution in five numbers (minimum, Q1, median, Q3, maximum) and marks outliers beyond the whiskers. It is the best choice when the question says "spread" or "outliers", or compares distributions across groups. For (c), a histogram is the standard answer; mention the box plot as the alternative.

::: danger Bar chart or histogram?
Bar chart: **categories**, gaps between bars, compares groups. Histogram: **one numeric variable** in bins, bars touch, shows a distribution. Mixing these up is the trap.
:::

:::::

</Q>

<Q id="E24.Q1b" title="Pearson correlation">

Given the data points with features X and Y, find the correlation between X and Y using the Pearson correlation coefficient, and interpret it.

| Data point | X | Y |
|:-:|:-:|:-:|
| 1 | 2 | 3 |
| 2 | 4 | 6 |
| 3 | 5 | 8 |
| 4 | 7 | 11 |
| 5 | 8 | 14 |

::::: details Solution

<!--@include: @/../code/dsml/papers/e24.out#q1b-->

**Interpretation.** r = 0.99 is a **very strong positive linear correlation**: as X increases, Y increases almost exactly along a straight line. It says nothing about cause: X need not cause Y.

| \|r\| | Strength (a common scale) |
|---|---|
| 0.9–1 | very strong |
| 0.7–0.9 | strong |
| 0.5–0.7 | moderate |
| 0.3–0.5 | weak |
| below 0.3 | negligible |

The sign gives the direction: positive means both rise together, negative means one falls as the other rises.

:::::

</Q>

<Q id="E24.Q2a" title="LOOCV vs 5-fold">

Compare LOOCV and 5-fold CV based on their time complexity and effectiveness, and analyse in which situation each is preferable.

::::: details Solution

| | LOOCV (leave one out) | 5-fold CV |
|---|---|---|
| How | n rounds: train on n − 1 points, test on the 1 left out | 5 rounds: train on 4/5 of the data, test on the other 1/5 |
| **Time** | **n model fits**: 1,000 points means 1,000 fits. Very slow for large n or slow models | **5 fits**, whatever n is |
| **Bias** of the error estimate | **Low**: each model sees almost all the data | Slightly higher: each model sees 80% |
| **Variance** of the estimate | **High**: each test is a single point (one outlier swings it), and the n training sets are nearly identical | Lower: each test fold is large |
| Randomness | None: the result is the same every run | Depends on how the folds are drawn (shuffle with a fixed `random_state`) |

**When to prefer which.** **LOOCV** for **small** datasets (a few dozen rows), where every training point matters and n fits are cheap. **5-fold** (or 10-fold) for medium and large datasets, or expensive models, where n fits would take too long and the lower variance gives a more stable estimate. For imbalanced classes use **stratified** k-fold.

:::::

</Q>

<Q id="E24.Q2b" title="Z-score normalisation and outliers">

What is Z-score normalization? Find the outliers in the following set of data points using Z-score normalization: X = [55, 57, 500, 61, 62, 65, 67, 70, 72, 73, 95, −2].

::::: details Solution

**Z-score normalisation** (standardisation) rescales a feature to mean 0 and standard deviation 1: $z = \dfrac{x - \mu}{\sigma}$. A z-score says how many standard deviations a point is from the mean. As an outlier test, a point with **|z| > 3** is usually called an outlier (some texts use 2).

<!--@include: @/../code/dsml/papers/e24.out#q2b-->

**Answer:** with the usual cut-off of 3, **500** is the outlier (z ≈ 3.27). −2 is also an outlier but is **masked** by 500; it shows up (z ≈ −2.8) once 500 is removed and the z-scores are recomputed, if you use a cut-off of 2.

::: tip The mark-winning remark
The z-score method uses the mean and standard deviation, and both are pulled by the very outliers it is hunting. The robust alternative is the **IQR rule**: anything below Q1 − 1.5·IQR or above Q3 + 1.5·IQR, where the quartiles are not moved by extremes. One sentence on this shows judgement.
:::

:::::

</Q>

<Q id="E24.Q2c" title="Feature encoding">

What is the need for feature encoding when developing a machine learning model for real-life applications? Explain the different feature encoding techniques.

::::: details Solution

**Need.** Real data contains categorical columns: city, colour, education level, product type. Almost every ML algorithm (linear and logistic regression, KNN, SVM, neural networks) computes with numbers: weighted sums, distances, gradients. Text labels cannot go into those formulas, so they must be **encoded as numbers** before a model can be fitted, and the encoding must not invent information that is not there.

**Techniques.**

| Technique | How | Columns for N categories | Use for | Problem |
|---|---|---|---|---|
| **Label / ordinal encoding** | Each category gets an integer: Small 0, Medium 1, Large 2 | 1 | **Ordinal** data, where the order is real | On nominal data it invents an order (Delhi > Chandigarh?) |
| **One-hot encoding** | One 0/1 column per category; exactly one is 1 in each row | N | **Nominal** data with no order | Many columns when N is large |
| **Dummy encoding** | One-hot with one column dropped (it is implied when all others are 0) | N − 1 | Nominal data in linear models | Same as one-hot, slightly leaner |

Example, `City` = Chandigarh, Delhi, Mysore:

| City | Label | City_Chandigarh | City_Delhi | City_Mysore | Dummy (drop Chandigarh) |
|---|:-:|:-:|:-:|:-:|:-:|
| Chandigarh | 0 | 1 | 0 | 0 | 0 0 |
| Delhi | 1 | 0 | 1 | 0 | 1 0 |
| Mysore | 2 | 0 | 0 | 1 | 0 1 |

**Rule from the slides:** label encoding when the order of categories matters; one-hot when it does not and you want to represent presence or absence.

Beyond the slides (worth one line each if you have time): **frequency encoding** (replace a category by how often it occurs), **target encoding** (by the mean of the target for that category), **binary encoding** (the integer code written in binary bits) and **hashing**: all keep the column count small for high-cardinality features.

:::::

</Q>

<Q id="E24.Q3a" title="k in KNN">

What is the effect of the hyperparameter k on the bias–variance trade-off in KNN classification? How do you decide the optimal value of k, and what needs to be considered?

::::: details Solution

| | Small k (e.g. 1) | Large k (e.g. 50) |
|---|---|---|
| Decision boundary | Jagged, follows every point | Smooth |
| Bias | **Low**: adapts to local detail | **High**: averages over a wide region, misses local patterns |
| Variance | **High**: one noisy neighbour flips the answer | **Low**: stable |
| Failure | **Overfitting** (k = 1 gets 100% on training data) | **Underfitting**: in the limit, predicts the majority class everywhere |

**Choosing k.**
1. **Cross-validation**: try k = 1, 3, 5, …, compute the validation error for each, and pick the k with the lowest error (the elbow of the error curve). Never pick k by looking at the test set.
2. **Rule of thumb**: k ≈ √n as a starting point.
3. **Odd k** for two classes, so a vote can never tie.

**Also consider:** **scale** the features first (otherwise the feature with the biggest units decides the distance), the **distance metric** (Euclidean, Manhattan, cosine for text), **class imbalance** (a large k favours the majority class) and **distance-weighted voting** (w = 1/d²) if near neighbours should count more.

:::::

</Q>

<Q id="E24.Q3b" title="Confusion matrix from a scenario">

A network security filter is designed to identify and block malicious packets. In a test, the filter processes 10,000 packets, of which 1,000 are actually malicious and 9,000 benign. Of the 1,000 malicious packets, 850 are correctly identified as malicious and 150 are missed. Of the 9,000 benign packets, 8,500 are correctly identified as benign but 500 are mistakenly flagged as malicious. Construct the confusion matrix and calculate precision, recall, F1 score, specificity and false negative rate.

::::: details Solution

<!--@include: @/../code/dsml/papers/e24.out#q3b-->

**Reading it:** the filter catches 85% of attacks (recall), but only 63% of what it blocks is really malicious (precision): 500 good packets are blocked. Accuracy (93.5%) flatters it because benign packets outnumber malicious ones 9 to 1.

:::::

</Q>

<Q id="E24.Q4a" title="Ridge regression">

Differentiate between ridge regression and linear regression. For the dataset

$$X = \begin{bmatrix} 1 & 2 & 3 \\ 4 & 5 & 6 \\ 7 & 8 & 9 \end{bmatrix},\qquad y = \begin{bmatrix} 1 \\ 2 \\ 3 \end{bmatrix},$$

find the coefficients (weights) of ridge regression using λ = 10, and predict the values of all three training examples.

::::: details Solution

| | Linear regression (least squares) | Ridge regression |
|---|---|---|
| Minimises | $\sum (y - \hat y)^2$ | $\sum (y - \hat y)^2 + \lambda \sum w_j^2$ |
| Closed form | $w = (X^TX)^{-1}X^Ty$ | $w = (X^TX + \lambda I)^{-1}X^Ty$ |
| Weights | Unrestricted; can be huge when features are correlated | **Shrunk towards 0** (never exactly 0) |
| Correlated features (multicollinearity) | $X^TX$ is (nearly) singular: no unique or no stable solution | Adding λI always makes it invertible |
| Bias / variance | Low bias, can have high variance (overfits) | A little bias, much lower variance |

<!--@include: @/../code/dsml/papers/e24.out#q4a-->

::: warning Assumption to state
The question gives no intercept, so the model is ŷ = w₁x₁ + w₂x₂ + w₃x₃ with every weight penalised. With an unpenalised intercept the answer would differ; write which version you use.
:::

:::::

</Q>

<Q id="E24.Q4b" title="Gradient descent on a non-convex function">

Why is gradient descent not applicable to non-convex functions? Explain with a suitable diagram. Suppose the objective function of a learner is $f(x, y, z) = 2x^2 - y + \dfrac{z^3}{3}$ with initial values x = 0.1, y = 0.2, z = 0.3. What are (x, y, z) after two iterations of gradient descent with learning rate γ = 0.01?

::::: details Solution

**Why.** Gradient descent only looks at the local slope and steps downhill. On a **convex** function (one bowl) the only place the slope is zero is the global minimum, so it always gets there. A **non-convex** function has several valleys and flat points, and the slope is also zero at:
- a **local minimum**, where it gets stuck in a valley that is not the lowest;
- a **saddle point** or plateau, where it slows to a stop although it is not at a minimum.

Which one it ends in depends on the starting point, so the result is not guaranteed to be the best. (It is still used, for neural networks, with tricks such as random restarts and momentum; it just loses its guarantee.)

<!--@include: @/../code/dsml/notes/u4a.out#nonconvex-->

<!--@include: @/../code/dsml/papers/e24.out#q4b-->

**After two iterations: x = 0.09216, y = 0.22, z ≈ 0.2982.**

::: info A point the examiner may be fishing for
This f has **no minimum at all**: it falls forever as y grows (−y) or as z goes negative (z³). Gradient descent will keep increasing y by 0.01 every step and never converge. That is the first half of the question in miniature.
:::

:::::

</Q>

<Q id="E24.Q4c" title="Decision tree root node">

Suppose there are four features (Outlook, Temperature, Humidity, Wind) and the class label Play Golf in the dataset below. Which feature is most suitable for splitting at the root node, and why?

| Day | Outlook | Temperature | Humidity | Wind | Play Golf |
|:-:|---|---|---|---|---|
| 1 | Sunny | Hot | High | Weak | No |
| 2 | Sunny | Hot | High | Strong | No |
| 3 | Overcast | Hot | High | Weak | Yes |
| 4 | Rainy | Mild | High | Weak | Yes |
| 5 | Rainy | Cool | Normal | Weak | Yes |
| 6 | Rainy | Cool | Normal | Strong | No |
| 7 | Overcast | Cool | Normal | Strong | Yes |
| 8 | Sunny | Mild | High | Weak | No |
| 9 | Sunny | Cool | Normal | Weak | Yes |
| 10 | Rainy | Mild | Normal | Weak | Yes |
| 11 | Sunny | Mild | Normal | Strong | Yes |
| 12 | Overcast | Mild | High | Strong | Yes |
| 13 | Overcast | Hot | Normal | Weak | Yes |
| 14 | Rainy | Mild | High | Strong | No |

::::: details Solution

Use ID3: pick the attribute with the highest **information gain**, $\text{Gain}(S, A) = H(S) - \sum_v \frac{|S_v|}{|S|} H(S_v)$, where $H = -\sum p \log_2 p$.

<!--@include: @/../code/dsml/papers/e24.out#q4c-->

<!--@include: @/../code/dsml/notes/u4b.out#golftree-->

**Why Outlook:** splitting on it removes the most uncertainty about the label. Its *Overcast* branch is **pure** (4 Yes, 0 No), so it is a leaf straight away, and the other two branches are still mixed and will be split further (Sunny on Humidity, Rainy on Wind).

:::::

</Q>

<Q id="E24.Q4d" title="Limits of Naive Bayes">

The Naive Bayes classifier has the smallest prediction time among all classifiers, yet it is very limited in real-world applications. Give two reasons for its limited use.

::::: details Solution

1. **The independence assumption is rarely true.** It assumes every feature is independent of every other given the class. Real features are correlated (height and weight, or words that appear together), so the probabilities it multiplies are wrong, and redundant features are counted twice.
2. **The zero-frequency problem.** If a feature value never occurs with a class in training, its probability is 0 and the whole product becomes 0, whatever the other features say. It needs Laplace smoothing to work at all.

Also accepted: its probability estimates are poorly calibrated (fine for ranking classes, bad as real probabilities), and continuous features need an assumed distribution (usually Gaussian) that may not fit.

:::::

</Q>

<Q id="E24.Q5a" title="DBSCAN (Unit 5)">

In which situations is DBSCAN not suitable? How does DBSCAN determine clusters? Given the points A(3, 7), B(4, 6), C(5, 5), D(6, 4), E(7, 3), F(6, 2), G(7, 2) and H(8, 4), find the core points and outliers using DBSCAN with Euclidean distance, Eps = 2.5 and MinPts = 3.

::: warning Unit 5: not solved yet
Outside the Units 1–4 mid-semester. It will be solved in the end-semester build.
:::

</Q>

<Q id="E24.Q5b" title="PCA components (Unit 5)">

What is the minimum number of PCA components required to reduce the dimensionality of this dataset without significant information loss? (X1 in [0, 10]: 1, 3, 5, 7, 10; X2 in [0, 1]: 0.1, 0.2, 0.4, 0.7, 1.0; X3 in [−5, −10]: −5, −6, −7, −8, −9.)

::: warning Unit 5: not solved yet
Outside the Units 1–4 mid-semester. It will be solved in the end-semester build.
:::

</Q>

<Q id="E24.Q5c" title="Chi-square feature selection (Unit 5)">

How does correlation-based feature selection work in the filter method? For a binary classification problem with a categorical feature X and target Y (Yes/No): A has 30 Yes and 10 No, B has 15 Yes and 25 No, C has 25 Yes and 15 No (total 70 Yes, 50 No, 120). Determine whether X has a significant relationship with Y using the chi-square statistic, given the critical value 5.99 for df = 2 at α = 0.05.

::: warning Unit 5: not solved yet
Feature selection is in Unit 5 of your syllabus. It will be solved in the end-semester build.
:::

</Q>
