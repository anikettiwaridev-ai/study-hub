---
title: Mock mid-semester paper
---

# Mock mid-semester paper

<PaperHeader :rows="[
  ['Course', 'Data Science and Machine Learning (AIN3003)'],
  ['Maximum marks', '30'],
  ['Time allowed', '1 hour 30 minutes'],
  ['Note', 'All questions are compulsory. Assume suitably and state additional data required, if any. A non-programmable calculator is allowed.'],
]" />

::: info Written for this site, not a real paper
Built in the shape of the two real mid-semesters ([September 2025](./papers/mst-2025), [spring 2025](./papers/mst-2025-spring)): five questions of 6 marks, about 80% calculation, Units 1–4 only. Every number in the solutions comes from running a script. Hide the solutions, start the timer, and write on paper.
:::

<QuizTimer :minutes="90" label="Mid-semester" />

<Q id="MK.Q1a" title="Feature scaling">

Annual incomes (in thousands) are 20, 25, 30, 35 and 90. (i) Scale them with min-max scaling and with z-score standardisation. (ii) Which scaler is safer for this column, and why?

::::: details Solution

<!--@include: @/../code/dsml/mock/mock.out#q1a-->

**(ii) Standardisation.** The 90 is an outlier and becomes the min-max maximum, which squeezes the four ordinary incomes into 0 to 0.21: their differences almost vanish. Standardisation uses the mean and standard deviation; the outlier still has an effect (it widens σ), but the ordinary values keep a usable spread, and future incomes above 90 do not break the [0, 1] range. (Removing or capping the outlier first is also a good answer.)

:::::

</Q>

<Q id="MK.Q1b" title="Encoding">

A dataset has a **Size** feature (S, M, L, XL) and a **City** feature with 3,000 distinct values. Choose an encoding for each, and give two problems you would face if you one-hot encoded City.

::::: details Solution

- **Size → label (ordinal) encoding**: S = 0, M = 1, L = 2, XL = 3. The categories have a real order, so the integers carry true information in one column.
- **City → not plain one-hot.** City is nominal, so label encoding would invent an order (city 2,999 is not "greater" than city 1). But one-hot gives:
  1. **3,000 new columns**: the curse of dimensionality; the model needs far more data, and distances stop meaning much.
  2. **Sparse, slow data**: each row is one 1 and 2,999 zeros (and rare cities have too few rows to learn from: overfitting).

  Better: group rare cities into "Other", **generalise** to state or region first, or use frequency or target encoding (one column).

:::::

</Q>

<Q id="MK.Q2" title="Gradient descent">

For the data (1, 3), (2, 5), (3, 7), fit ŷ = wx + b by gradient descent on the MSE cost $J = \frac{1}{n}\sum(\hat y - y)^2$, starting from w = b = 0 with learning rate 0.05. Perform two iterations.

::::: details Solution

Gradients: $\dfrac{\partial J}{\partial w} = \dfrac{2}{n}\sum(\hat y - y)x$, $\dfrac{\partial J}{\partial b} = \dfrac{2}{n}\sum(\hat y - y)$; update $w \leftarrow w - \alpha\,\partial J/\partial w$ and $b \leftarrow b - \alpha\,\partial J/\partial b$, both from the old values.

<!--@include: @/../code/dsml/mock/mock.out#q2-->

**After two iterations: w = 1.6378, b = 0.7233.**

:::::

</Q>

<Q id="MK.Q3a" title="Confusion matrix">

A fraud model checks 500 transactions, 50 of which are fraudulent. It flags 60 transactions, and 40 of the flagged ones really are fraud. Build the confusion matrix and compute precision, recall, F1 and specificity.

::::: details Solution

<!--@include: @/../code/dsml/mock/mock.out#q3a-->

Accuracy (0.94) looks excellent only because 90% of transactions are genuine; precision says a third of the alarms are false.

:::::

</Q>

<Q id="MK.Q3b" title="ROC and AUC">

Five samples have predicted probabilities and true labels: 0.9 (1), 0.7 (1), 0.6 (0), 0.4 (1), 0.2 (0). Using each probability as a threshold, compute TPR and FPR, list the ROC points, and estimate the AUC.

::::: details Solution

<!--@include: @/../code/dsml/mock/mock.out#q3b-->

AUC ≈ 0.83: "considerable" on the slides' scale. The only mis-ordering is the negative at 0.6 scoring above the positive at 0.4.

:::::

</Q>

<Q id="MK.Q4" title="KNN">

Training points: P1(1, 2) A, P2(2, 3) A, P3(3, 1) A, P4(5, 5) B, P5(6, 5) B, P6(7, 7) B, P7(8, 6) B. (a) Classify the query (4, 4) with Euclidean distance for k = 1, 3, 5 and 7. (b) What does the result tell you about choosing k, and how should k be chosen?

::::: details Solution

<!--@include: @/../code/dsml/mock/mock.out#q4-->

**(b)** The answer flips with k: B, B, A, B. Small k follows the single nearest point (high variance, sensitive to noise); large k takes in points from far away (high bias; with k = 7 every point votes, so it is simply the majority class). There is no "correct" k from the data alone: choose it by **cross-validation** (lowest validation error), starting near √n and keeping it odd for two classes. Scale the features first if their units differ.

:::::

</Q>

<Q id="MK.Q5a" title="Logistic regression">

A model gives P(buy) = σ(−2.5 + 0.8 × past purchases). Find the probability and the predicted class for customers with 2 and with 5 past purchases, and interpret the coefficient 0.8.

::::: details Solution

<!--@include: @/../code/dsml/mock/mock.out#q5a-->

:::::

</Q>

<Q id="MK.Q5b" title="Cross-validation">

A dataset has 300 examples. Give the number of models, the training size and the test size for 6-fold cross-validation and for LOOCV. Which would you choose here, and why?

::::: details Solution

<!--@include: @/../code/dsml/mock/mock.out#q5b-->

**6-fold.** LOOCV trains 300 models (50 times the work) for an estimate with lower bias but higher variance: each test is a single point. With 300 examples, each 6-fold test set (50) is large enough to be stable. LOOCV is worth it only for very small datasets. If the classes are imbalanced, use **stratified** 6-fold.

:::::

</Q>
