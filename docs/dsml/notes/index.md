---
title: Notes
---

# Notes

Units 1 to 4, the whole mid-semester syllabus, in the format of the Stacks & Queues quiz-prep sheet. Each unit opens with a **one-screen toolkit**, then one numbered section per idea: the idea in plain words, a picture where one helps, the rule, the formula, a worked example laid out the way you would write it, and the traps. Each unit ends with a traps table, a checklist and a **Quick check** that marks itself.

Every number in a worked example and every graph comes from running a script, so none of it is typed by hand. The worked examples use **different data from the past papers**, so the papers stay fresh for timed practice. Where the slides are wrong or contradict themselves, a **Correction** box says so.

| Unit | Covers | Weight in the past papers |
|---|---|---|
| [1 · Data, Python and the maths underneath](./unit-1) | Data types, the data science process, the Python stack, NumPy and Pandas behaviour, choosing a chart, linear algebra, Pearson correlation | End-semester: chart choice and Pearson r (6 + 6). Quiz definitions |
| [2 · Data acquisition and preprocessing](./unit-2) | Sources and storage, missing data, binning and outliers, label / one-hot / dummy encoding, high cardinality, min-max vs z-score, splitting and leakage, reduction and discretization | **Both mid-semesters**, word for word: "prefer min-max over standardization?" and "two issues of one-hot with high cardinality" |
| [3 · Machine learning fundamentals](./unit-3) | Mitchell's T/P/E, paradigms, Q-learning, over- and underfitting, bias–variance, SSE and R², confusion matrix, ROC and AUC, cross-validation | **Both mid-semesters**: confusion-matrix metrics or an ROC table; fold sizes |
| [4A · Regression and gradient descent](./unit-4a) | Least squares, multiple regression, ridge, gradient descent (learning rate, variants, non-convex), logistic regression and odds | **Both mid-semesters**: gradient descent by hand; a logistic probability |
| [4B · KNN, SVM, Naive Bayes, decision trees](./unit-4b) | Distances and choosing k, the maximum margin and kernels, Bayes with Laplace smoothing, entropy, information gain and Gini | Mid-semester: KNN (Sep 2025). End-semester: trees (8 + 5), Naive Bayes (5 + 2), SVM kernels (5) |

::: tip Two ways to use the notes
**Before the mid-semester:** read each unit fully, then do the [papers](../papers/) with solutions hidden. Then do the [numerical drills](../practice) and the [mock](../mock-mst) against the clock.

**Before a quiz:** read each unit's toolkit table and traps table, do the Quick checks, or switch on **Traps only** in the top bar. Then do the [timed quiz sets](../quiz-practice).
:::

::: info Better than the old theory sheet
These notes replace the Units 1–2 theory HTML. They keep its face-offs and corrections, and add what it lacked: worked calculations for every numerical topic the papers ask (Pearson r, z-score outliers, both scalers, encoding a table), pictures for the visual ideas (gradient descent, ROC, k in KNN, the SVM margin, bias–variance), priorities taken from the papers instead of guesses, and an answer template for each kind of theory question in [How to answer](../how-to-answer).
:::
