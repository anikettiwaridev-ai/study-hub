---
title: Mid-semester, spring 2025 (DSN4005)
---

# Mid-semester, spring 2025 (DSN4005)

<PaperHeader :rows="[
  ['Programme', 'B.Tech CSE (Data Science), 4th semester (24252)'],
  ['Course code', 'DSN4005'],
  ['Maximum marks', '25'],
  ['Time allowed', '1 hour 30 minutes'],
]" />

::: info Why this paper matters
It is the sibling Data Science course's paper, but two of its questions reappeared **word for word** in your course's September 2025 paper (Q5a and Q5b here are Sep 2025 Q1a and Q1b), and its confusion matrix (Q3) reappeared in an end-semester. Four of its five questions are calculations. Only Q5c (PCA) is outside Units 1–4.
:::

<Q id="P25.Q1" title="Gradient descent, two iterations, three parameters">

A company wants to predict the salary of its employees based on their years of experience and education level:

| Years of experience (X₁) | Education level (X₂) | Salary (Y) |
|:-:|:-:|:-:|
| 1 | 2 | 40,000 |
| 2 | 3 | 45,000 |
| 3 | 4 | 50,000 |
| 4 | 5 | 60,000 |
| 5 | 6 | 70,000 |

Education is on a scale where 1 = High School, 2 = Associate's degree, 3 = Bachelor's, 4 = Master's and 5 = Ph.D. The cost function is the mean squared error, and the model is Y = θ₀ + θ₁X₁ + θ₂X₂. Find θ₀, θ₁ and θ₂ to predict salary after two iterations.

::::: details Solution

::: warning The paper leaves out the learning rate and the starting values
State your assumption in the first line: **α = 0.01, θ₀ = θ₁ = θ₂ = 0**, and $J = \frac{1}{n}\sum(\hat Y - Y)^2$, so the gradients are $\frac{\partial J}{\partial \theta_j} = \frac{2}{n}\sum(\hat Y - Y)\,x_j$ with $x_0 = 1$. The paper says "assume suitably", so any reasonable choice that you state is marked on method.
:::

<!--@include: @/../code/dsml/papers/p25.out#q1-->

**Answer (α = 0.01, starting from 0):** after two iterations **θ₀ = 1526.8, θ₁ = 4859.6, θ₂ = 6386.4**.

::: info Something the paper does not tell you
Education here is always experience + 1 (X₂ = X₁ + 1), so the two features carry the same information. That is perfect **multicollinearity**: many different (θ₁, θ₂) pairs give exactly the same predictions, so the individual weights cannot be trusted, even though gradient descent still lowers the cost. A one-line remark like this shows you understand the model.
:::

:::::

</Q>

<Q id="P25.Q2" title="Logistic regression probability">

A company predicts whether a customer will subscribe (1) or not (0) from age and annual income, using logistic regression with the sigmoid activation:

| Age | Income (USD) | Subscribed |
|:-:|:-:|:-:|
| 25 | 45,000 | 0 |
| 30 | 50,000 | 1 |
| 35 | 60,000 | 1 |
| 40 | 65,000 | 1 |
| 45 | 70,000 | 0 |

The learned equation is P(subscribed) = σ(b₀ + b₁ × Age + b₂ × Income), with b₀ = −5, b₁ = 0.1 and b₂ = 0.00005. Predict the probability that a customer who is **38 years old** and earns **62,000 dollars** will subscribe.

::::: details Solution

<!--@include: @/../code/dsml/papers/p25.out#q2-->

::: danger Where marks go
- The data table is a distractor: the coefficients are already given. Do not try to fit anything.
- Compute z first and write it down, then apply the sigmoid. $e^{-1.9}$ needs a calculator: 0.1496.
- End with the class (subscribe) as well as the probability.
:::

:::::

</Q>

<Q id="P25.Q3" title="Confusion-matrix metrics">

You are evaluating a binary classification model with this confusion matrix for the test set:

| | Predicted 1 | Predicted 0 |
|---|:-:|:-:|
| **Actual 1** | 50 | 10 |
| **Actual 0** | 5 | 35 |

Calculate (a) accuracy, (b) precision, (c) recall and (d) F1 score.

::::: details Solution

<!--@include: @/../code/dsml/papers/p25.out#q3-->

::: danger Where marks go
Precision divides by the **predicted-1 column** (50 + 5). Recall divides by the **actual-1 row** (50 + 10). Swapping them is the most common mistake on this question, and the two answers (0.91 and 0.83) are close enough that you will not notice.
:::

:::::

</Q>

<Q id="P25.Q4a" title="Number of folds">

Analyse the impact of using a large number of folds and a small number of folds on bias, variance and computational complexity in cross-validation.

::::: details Solution

| | Small k (2–3 folds) | Large k (→ n, i.e. LOOCV) |
|---|---|---|
| **Bias** | **Higher.** Each model trains on only half or two-thirds of the data, so it is weaker than the final model and the error estimate is pessimistic. | **Lower.** Each model trains on almost all the data, so the estimate is close to the real model's error. |
| **Variance** | **Lower.** Big test folds give stable error estimates. | **Higher.** Each test fold is tiny (one point in LOOCV), and the training sets overlap almost completely, so the estimates swing with every outlier. |
| **Computation** | **Low.** Only k models are trained. | **High.** k models; LOOCV trains n models. |

**Conclusion:** k = 5 or 10 is the usual compromise. The slides recommend 10: lower k drifts towards a single holdout split, higher k towards LOOCV.

:::::

</Q>

<Q id="P25.Q4b" title="10-fold cross-validation sizes">

Suppose we want to compute the 10-fold cross-validation error on 100 training examples. We need to compute the error N1 times, and the cross-validation error is the average of the errors. To compute each error, we build a model with data of size N2 and test it on data of size N3. What are N1, N2 and N3?

::::: details Solution

<!--@include: @/../code/dsml/papers/p25.out#q4b-->

:::::

</Q>

<Q id="P25.Q5a" title="Feature scaling">

When do we prefer min-max scaling over standardization? Justify with an example.

::::: details Solution

The same question, word for word, as [Sep 2025 Q1a](./mst-2025#q1a); the full answer is there. In two marks: prefer **min-max** when the data is not Gaussian, has no big outliers, and the model wants a fixed range (KNN, neural networks), or the feature has hard limits. Example: pixel values 0–255 → x/255, so 51 → 0.2. Prefer **standardization** for roughly Gaussian data, data with outliers, or when min and max are unknown.

:::::

</Q>

<Q id="P25.Q5b" title="One-hot encoding">

Assess any two potential issues of applying one-hot encoding to a dataset with high cardinality.

::::: details Solution

Word for word [Sep 2025 Q1b](./mst-2025#q1b). Two issues, each with its reason: (1) **dimensionality explosion**: 3,000 categories become 3,000 columns, so the model needs far more data and distances lose meaning; (2) **sparse, memory-heavy data**: every row is one 1 and thousands of zeros, slowing training. (Also valid: overfitting on rare categories, the dummy-variable trap, unseen categories at test time.)

:::::

</Q>

<Q id="P25.Q5c" title="PCA (Unit 5)">

A dataset has eigenvalues [5.2, 3.8, 1.5, 0.6, 0.2] after PCA. How many principal components should be retained to capture at least 90% of the variance?

::::: details Solution

::: warning Outside your syllabus
PCA is Unit 5. It is solved because it is two marks and quick.
:::

<!--@include: @/../code/dsml/papers/p25.out#q5c-->

:::::

</Q>
