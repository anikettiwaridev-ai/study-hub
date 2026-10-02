---
title: End-semester, spring 2025 (DSN4005)
---

# End-semester, spring 2025 (DSN4005)

<PaperHeader :rows="[
  ['Programme', 'B.Tech CSE (Data Science), 4th semester (24252); also the AIML backlog paper'],
  ['Course code', 'DSN4005 / ES1701'],
  ['Maximum marks', '60'],
  ['Time allowed', '3 hours'],
]" />

::: info What this paper adds
Short 5-mark questions, almost all calculations: a least-squares line, both scalers by hand, a KNN table, entropy and information gain, and Naive Bayes. Q2(a) is the same confusion matrix as the [spring 2025 mid-semester](./mst-2025-spring#q3). Q5 is Unit 5 and waits for the end-semester build.
:::

<Q id="E25.Q1a" title="Correlation vs regression; least-squares line">

Differentiate between correlation and regression with respect to their purpose, causation and variables. Then, for the sales of a company (in million dollars):

| x (year) | 2005 | 2006 | 2007 | 2008 | 2009 |
|---|:-:|:-:|:-:|:-:|:-:|
| y (sales) | 12 | 19 | 29 | 37 | 45 |

(i) find the least-squares regression line y = ax + b; (ii) use it to estimate the sales in 2012.

::::: details Solution

| | Correlation | Regression |
|---|---|---|
| **Purpose** | Measures the **strength and direction** of a linear relationship, as one number r in [−1, 1] | Gives an **equation** to **predict** one variable from another |
| **Variables** | Symmetric: no dependent or independent; r(x, y) = r(y, x) | Asymmetric: y is **dependent** (target), x **independent** (predictor); regressing x on y gives a different line |
| **Causation** | Does not imply causation | Does not prove causation either; it only describes how y changes with x |
| **Output** | A unitless number | Coefficients in the units of the data (sales per year) |

<!--@include: @/../code/dsml/papers/e25.out#q1a-->

::: danger Where marks go
Extrapolating three years past the data assumes the trend continues; say so in a few words. And give a and b for the line in **years** as asked, not only in coded u.
:::

:::::

</Q>

<Q id="E25.Q1b" title="Min-max and z-score by hand">

Use the two methods to normalize the following group of data: Marks = 8, 10, 15, 20. (i) min-max normalization with min = 0 and max = 1; (ii) z-score normalization.

::::: details Solution

<!--@include: @/../code/dsml/papers/e25.out#q1b-->

:::::

</Q>

<Q id="E25.Q1c" title="Encoding for a decision tree">

You have a "Product Category" feature with 200 unique categories. Which encoding method, label encoding or one-hot encoding, is better for decision trees, and why? Then one-hot encode the "Weather" feature (categories Sunny, Rainy, Cloudy) for this data:

| ID | 1 | 2 | 3 | 4 |
|---|:-:|:-:|:-:|:-:|
| Weather | Sunny | Rainy | Cloudy | Rainy |

::::: details Solution

**Label encoding is better for a decision tree here.**
- A tree splits on one feature at a time with a threshold ("code ≤ 57?"). It never multiplies or adds the codes, so the invented order does far less harm than in a linear model: the tree can still carve out groups of categories with a few splits.
- One-hot would create **200 sparse columns**. Each split can only separate **one** category from all the rest, so the tree needs many more, deeper splits, trains more slowly, and each column has few rows behind it (overfitting). Many tree implementations also handle categories natively.

(For a **linear** model or KNN the answer flips: there, label codes would be treated as real distances, so one-hot is the right choice.)

**One-hot encoding of Weather** (one column per category, alphabetical order):

| ID | Weather | Weather_Cloudy | Weather_Rainy | Weather_Sunny |
|:-:|---|:-:|:-:|:-:|
| 1 | Sunny | 0 | 0 | 1 |
| 2 | Rainy | 0 | 1 | 0 |
| 3 | Cloudy | 1 | 0 | 0 |
| 4 | Rainy | 0 | 1 | 0 |

Exactly one 1 per row. Dummy encoding would drop one column (say Cloudy), which is implied when the other two are 0.

:::::

</Q>

<Q id="E25.Q2a" title="Precision, recall, F1">

A confusion matrix for a binary classification problem: Actual Yes → Predicted Yes 50, Predicted No 10; Actual No → Predicted Yes 5, Predicted No 35. What are the precision, recall and F1 score for the class "Yes"?

::::: details Solution

The same matrix as the [spring 2025 mid-semester Q3](./mst-2025-spring#q3), with "Yes" as the positive class:

<!--@include: @/../code/dsml/papers/p25.out#q3-->

**Precision 0.909, recall 0.833, F1 0.870.**

:::::

</Q>

<Q id="E25.Q2b" title="Overfitting or underfitting?">

A company is building a model to classify emails as spam or not spam. Model X achieves 99% accuracy on the training set but only 72% on the test set. Model Y achieves 68% on both. Model Z achieves 88% on the training set and 85% on the test set. (i) Identify which model is overfitting, which is underfitting and which generalises well. (ii) Explain the reason for each.

::::: details Solution

| Model | Train | Test | Verdict | Reason |
|---|:-:|:-:|---|---|
| X | 99% | 72% | **Overfitting** | A huge train–test gap (27 points): it has memorised the training emails, noise included, and does not transfer. Low bias, high variance. |
| Y | 68% | 68% | **Underfitting** | No gap, but low on both: it has not learned the pattern even on data it has seen. Too simple, or too heavily regularised. High bias, low variance. |
| Z | 88% | 85% | **Generalises well** | High on both with a small gap (3 points): it learned the real pattern. |

**The two-check rule:** (1) is training accuracy high (is it learning at all)? (2) is the train–test gap small (does the learning transfer)? Fixes: X needs more data, a simpler model or regularisation; Y needs a more complex model, better features or less regularisation.

:::::

</Q>

<Q id="E25.Q3a" title="KNN by hand">

You are given a dataset of customers with two features, Age and Income, and a binary label Buys_Product:

| ID | Age | Income | Buys_Product |
|:-:|:-:|:-:|:-:|
| 1 | 25 | 40 | No |
| 2 | 30 | 60 | No |
| 3 | 35 | 65 | Yes |
| 4 | 40 | 80 | Yes |
| 5 | 45 | 60 | Yes |
| 6 | 50 | 50 | No |
| 7 | 55 | 90 | Yes |

(i) Compute the Euclidean distance from a new customer to each of the 7 existing points. (ii) Use K = 3 to find the 3 nearest neighbours. (iii) By majority voting, predict whether the new customer will buy the product.

::::: details Solution

::: warning The paper never gives the new customer's values
State an assumption in your first line. Here: **Age = 42, Income = 70**. The method is the same for any values, and the paper says "assume suitably".
:::

<!--@include: @/../code/dsml/papers/e25.out#q3a-->

A remark worth a line: Age and Income here are on similar scales, so unscaled distances are fair. If Income were in rupees (70,000), it would swamp Age, and you would scale both first.

:::::

</Q>

<Q id="E25.Q3b" title="Entropy and information gain">

A dataset has 7 rows and 3 attributes; the goal is to classify whether a person will buy a laptop.

| ID | Age | Income | Student | Buy_Laptop |
|:-:|---|---|---|---|
| 1 | ≤30 | High | No | No |
| 2 | ≤30 | High | Yes | Yes |
| 3 | 31–40 | High | No | Yes |
| 4 | >40 | Medium | No | Yes |
| 5 | >40 | Low | Yes | No |
| 6 | >40 | Low | Yes | Yes |
| 7 | 31–40 | Low | Yes | Yes |

(i) What is the entropy of the entire dataset? (ii) Calculate the information gain for Age, Income and Student. (iii) Which attribute would be selected as the root node?

::::: details Solution

<!--@include: @/../code/dsml/papers/e25.out#q3b-->

The 31–40 branch of Age is pure (both Yes), which is a large part of why Age wins.

:::::

</Q>

<Q id="E25.Q4a" title="Naive Bayes">

Consider the dataset below. A new object has Colour = Red and Shape = Long. Predict its class (Apple, Chilli or Cucumber) using the Naive Bayes classifier.

| Colour | Shape | Class |
|---|---|---|
| Red | Round | Apple |
| Red | Long | Chilli |
| Green | Round | Apple |
| Green | Long | Cucumber |
| Red | Round | Apple |

::::: details Solution

Naive Bayes picks the class c with the largest $P(c)\,P(\text{Red} \mid c)\,P(\text{Long} \mid c)$, treating Colour and Shape as independent given the class (the "naive" part). The denominator P(Red, Long) is the same for every class, so it is skipped.

<!--@include: @/../code/dsml/papers/e25.out#q4a-->

:::::

</Q>

<Q id="E25.Q4b" title="SVM and the kernel trick">

You are designing an SVM-based system to detect **fraudulent credit card transactions**. The features are transaction amount, merchant type, time of transaction, device used and location (latitude/longitude). Some patterns are non-linear: certain frauds happen only at specific times and locations together. (i) Would a linear SVM be sufficient? Why or why not? (ii) Design a kernel-trick idea that could help the SVM here. (iii) Name a specific kernel and briefly justify it.

::::: details Solution

**(i) No.** A linear SVM separates the classes with one flat hyperplane w·x + b = 0, so it can only say "more of this feature means more (or less) fraud". The fraud here is an **interaction**: a transaction is risky only when a particular time **and** a particular place occur together, for example 3 a.m. in a city the customer has never used. That region is a pocket in feature space, not one side of a plane, so no single hyperplane separates it.

**(ii) The kernel trick.** Map each transaction x into a higher-dimensional space φ(x) that contains products of features (time × latitude, time × longitude, amount × hour…). In that space the fraud pocket **does** become linearly separable, so a linear SVM there gives a curved boundary back in the original space. The trick is that the SVM only ever needs dot products φ(a)·φ(b), and a **kernel function** K(a, b) gives that dot product directly from a and b, without ever building φ(x). The slides' example: $(a\cdot b + 1)^2$ equals the dot product of all quadratic terms, at the cost of one ordinary dot product.

**(iii) The RBF (Gaussian) kernel**, $K(a, b) = \exp\!\left(-\dfrac{\|a - b\|^2}{2\sigma^2}\right)$. It scores similarity by closeness, so it naturally draws boundaries around **local clusters**, such as "near this place at this time". Choose σ (and the penalty C) by cross-validation. A degree-2 **polynomial kernel** is also defensible, because it builds exactly the pairwise interaction terms the problem describes. Before either, **scale** the features and **encode** merchant type and device (one-hot), because SVM distances depend on units.

:::::

</Q>

<Q id="E25.Q5a" title="DBSCAN and ε (Unit 5)">

You apply DBSCAN to 1,000 points. With ε = 0.5 you get 10 clusters and 200 noise points; with ε = 1.5, 2 clusters and 10 noise points. (i) Explain why increasing ε decreases the number of clusters. (ii) Which ε would better capture small dense clusters?

::: warning Unit 5: not solved yet
Outside the Units 1–4 mid-semester. It will be solved in the end-semester build.
:::

</Q>

<Q id="E25.Q5b" title="Hierarchical clustering (Unit 5)">

Given a distance matrix for six objects A–F, show the final result of either k-means or dendrogram clustering (HAC), explaining each step.

::: warning Unit 5: not solved yet
Outside the Units 1–4 mid-semester. It will be solved in the end-semester build.
:::

</Q>

<Q id="E25.Q5c" title="PCA on correlated variables (Unit 5)">

A company records Age (V1) and Annual Spending (V2) for 1,000 customers. The two are highly positively correlated (≈ 0.95), and V1 has a much larger variance than V2. If you perform PCA, (i) how many principal components will you need to explain most of the variance? (ii) Will the first principal component be closer to V1, V2, or a mix?

::: warning Unit 5: not solved yet
Outside the Units 1–4 mid-semester. It will be solved in the end-semester build.
:::

</Q>
