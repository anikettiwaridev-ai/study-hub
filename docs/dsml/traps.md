---
title: Most-trapped questions
pageClass: trap-page
---

# Most-trapped questions

The mistakes that cost the most marks across the four papers, the slides and the assignments, roughly most costly first. Each one says what people write, what is right, and where it was asked.

::: tip Read this the night before
If a line surprises you, open the linked question. For how often each topic comes back, see [the repeat map](./repeats).
:::

## 1. The sign in a gradient-descent step

**People write:** $w_1 = 0 - 0.1 \times 18.67 = -1.87$, dropping the minus sign of the gradient.
**Right:** the gradient was **−18.67** (the line started too low), so $w_1 = 0 - 0.1 \times (-18.67) = +1.87$. Keep the sign of the gradient in brackets. And compute every gradient from the **old** values before updating any parameter.
**Asked:** <Src r="S25.Q2" /> <Src r="P25.Q1" /> <Src r="E24.Q4b" />

## 2. Missing data in the question

**People write:** nothing, and leave the question.
**Right:** papers leave out the learning rate and starting values ([spring 2025 Q1](./papers/mst-2025-spring#q1)) or the new point ([spring 2025 end-semester Q3a](./papers/endsem-2025#q3a)) and say "assume suitably". Write the assumption in your first line and solve.
**Asked:** <Src r="P25.Q1" /> <Src r="E25.Q3a" />

## 3. Precision and recall swapped

**People write:** precision = TP/(TP + FN).
**Right:** precision divides by everything **predicted** positive (TP + FP); recall by everything **actually** positive (TP + FN). Draw the labelled 2 × 2 table first, every time.
**Asked:** <Src r="P25.Q3" /> <Src r="E25.Q2a" /> <Src r="E24.Q3b" />

## 4. Standardisation scales to [0, 1]

**People write:** "standardisation scales the data between 0 and 1" (one slide says so).
**Right:** z-scores have mean 0 and standard deviation 1 and **no fixed range**; only min-max gives [0, 1]. The very next slide says "standardization does not have a bounding range".
**Asked:** <Src r="S25.Q1a" /> <Src r="P25.Q5a" /> <Src r="E25.Q1b" />

## 5. "Too many columns" is not an answer

**People write:** one-hot's problem: "it creates many columns".
**Right:** give the mechanism: 3,000 columns → curse of dimensionality, sparse memory-hungry data, overfitting on rare categories, the dummy-variable trap, unseen categories. Two of these with reasons is the full answer.
**Asked:** <Src r="S25.Q1b" /> <Src r="P25.Q5b" />

## 6. Label-encoding a nominal feature

**People write:** City → 0, 1, 2.
**Right:** that invents an order. Label encoding is for **ordinal** data (S < M < L). Nominal data needs one-hot (N columns) or dummy (N − 1). Exception: decision trees cope with label codes, and one-hot on 200 categories hurts them.
**Asked:** <Src r="E24.Q2c" /> <Src r="E25.Q1c" />

## 7. FPR divided by the wrong total

**People write:** FPR = FP/(FP + TP).
**Right:** FPR = FP/(FP + **TN**), over the actual negatives; TPR = TP/(TP + FN), over the actual positives. Add (0, 0) before measuring the AUC.
**Asked:** <Src r="S25.Q3" />

## 8. Large k in KNN is "more reliable"

**People write:** K = 11 is better because it has more votes.
**Right:** extra votes come from farther, less similar points. With k at least twice the smaller class, the smaller class can never win: KNN predicts the majority everywhere (high bias). Pick k by cross-validation.
**Asked:** <Src r="S25.Q5" /> <Src r="E24.Q3a" />

## 9. Bias and variance the wrong way round

**People write:** overfitting = high bias.
**Right:** overfitting = **low bias, high variance** (great on train, poor on test). Underfitting = high bias, low variance (poor on both). k = 1 in KNN overfits; LOOCV has low bias and high variance.
**Asked:** <Src r="P25.Q4a" /> <Src r="E24.Q3a" /> <Src r="E25.Q2b" />

## 10. k-fold sizes

**People write:** 10-fold on 100: train on 10, test on 90.
**Right:** k models; each trains on (k − 1)n/k = 90 and tests on n/k = 10. Check that N2 + N3 = n.
**Asked:** <Src r="P25.Q4b" />

## 11. Scale before the split

**People write:** standardise the whole dataset, then split.
**Right:** split first; fit the scaler on the training set; only transform the test set. Otherwise the test set leaks into training.
**Asked:** <Src r="A4.Q9" /> <Src r="A5.Q5" />

## 12. The z-score rule misses outliers

**People write:** "only 500 is an outlier" and stop.
**Right:** 500 inflates σ and hides −2 (masking). Recompute without 500, or use the IQR rule, and say so.
**Asked:** <Src r="E24.Q2b" />

## 13. e^β is a probability change

**People write:** "each extra unit raises the probability by e^0.0812".
**Right:** $e^{\beta}$ is the **odds ratio**: the odds are multiplied by it. Probability changes by different amounts depending on where you start.
**Asked:** <Src r="P25.Q2" />

## 14. Entropy with the wrong log, or unweighted children

**People write:** log base 10; or averages the child entropies equally.
**Right:** log base **2** (ln x / 0.6931). Weight each child by its share of the rows. Gain = parent − weighted children.
**Asked:** <Src r="E24.Q4c" /> <Src r="E25.Q3b" />

## 15. A zero in Naive Bayes

**People write:** carries on multiplying as if nothing happened, and is surprised two classes score 0.
**Right:** one zero count wipes out the class. Say so and mention Laplace smoothing (count + 1 over n + k).
**Asked:** <Src r="E25.Q4a" /> <Src r="E24.Q4d" />

## 16. The sklearn confusion matrix

**People write:** `[[48, 3], [10, 19]]`, so TP = 48.
**Right:** sklearn puts class 0 first: `[[TN, FP], [FN, TP]]`. TP = 19 here. Read the labels, not the positions.
**Asked:** <Src r="A5.Q9" />

## 17. Correlation is causation

**People write:** "r = 0.99, so X causes Y".
**Right:** correlation measures a straight-line association, symmetric and unitless; regression predicts a dependent variable. Neither proves cause. And r = 0 means no **linear** relationship, not no relationship.
**Asked:** <Src r="E24.Q1b" /> <Src r="E25.Q1a" />

## Mistakes in the material: state an assumption {#material-errors}

- **Spring 2025 Q1** gives no learning rate or starting values: assume them ([solution](./papers/mst-2025-spring#q1)).
- **Spring 2025 end-semester Q3a** never gives the new customer's Age and Income: assume them ([solution](./papers/endsem-2025#q3a)).
- **Sep 2025 Q1** gives 6 marks for two parts without a split: answer both fully.
- **Lec-4, "Feature scaling methods":** standardisation "scale range 0 to 1" is wrong; the deck corrects itself later ([Unit 2](./notes/unit-2#scaling)).
- **Lec-4, slide 48:** `y_test` labelled "independent variable"; it is the dependent variable.
- **LogReg deck:** 1 − 0.1001 written as 0.8889 (it is 0.8999); the final odds are right.
- **KNN deck (Dr. Saini):** "if n is even, adjust K to be odd": it is k that should be odd.
- **Gradient Descent deck:** calls a too-large learning rate "the exploding gradient problem" (it is divergence), and files weight initialisation under "regularisation".
- **Pandas deck:** mean removal leaves "standard deviation 1": it only centres the data.
- **Evaluation Measures deck:** R² "lies between 0 and 1": on new data it can be negative.
- **Linear Algebra deck:** lists translation as a linear transformation; it is affine.
- **SVM deck (Moore):** writes the classifier as sign(w·x − b) but the planes as w·x + b = ±1; use one convention.
- **Intro deck:** "decision trees (C5.4)" means C4.5.
