---
title: Data Science and Machine Learning
---

# Data Science and Machine Learning

<PaperHeader :rows="[
  ['Course', 'AIN3003, 4 credits (3-0-2)'],
  ['Faculty', 'Dr. Shailendra Singh (course instructor); lecture slides by Dr. Poonam Saini'],
  ['Mid-semester', 'Units 1 to 4, 1.5 hours; past papers carried 25–30 marks'],
  ['Weightage', 'Mid-term 20 · Quizzes, assignments, tests and projects 10 · Lab work (quiz, viva, file) 30 · End-term 40'],
]" />

<Progress />

<div class="modes">
<div class="mode">

### Preparing for the mid-semester

Mostly calculations: gradient descent, metrics, KNN, scaling.

- [Past papers](./papers/), solved in exam layout
- [Numerical drills](./practice): 18 fresh calculations
- [Mock paper](./mock-mst), timed
- [How to answer](./how-to-answer) and the [formula sheet](./formulas)

</div>
<div class="mode quiz">

### Preparing for a quiz or the lab

10 minutes of definitions and traps; lab viva on the six assignments.

- [Timed quiz sets](./quiz-practice): two sets of 10 minutes
- **Quick check** at the end of each [notes](./notes/) unit
- [All six assignments](./assignments/), with real outputs

</div>
</div>

## What to study, in order {#order}

1. **[Gradient descent](./notes/unit-4a#gradient-descent).** On **both** mid-semesters: one iteration of w and b, and two iterations of three parameters. Learn the table layout, then do [Sep 2025 Q2](./papers/mst-2025#q2), [spring 2025 Q1](./papers/mst-2025-spring#q1) and [drills 6–8](./practice#gradient-descent).
2. **[Scaling and encoding](./notes/unit-2#scaling).** **Both** mid-semesters asked the same two questions word for word: *when do we prefer min-max over standardization?* and *two issues of one-hot encoding with high cardinality*. Learn the [two model answers](./papers/mst-2025#q1a) until you can write them in 8 minutes.
3. **[Evaluation](./notes/unit-3#confusion-matrix): confusion matrix, ROC and AUC, cross-validation.** On both mid-semesters, and the same confusion matrix came back in an end-semester. Then [drills 10–12](./practice#metrics).
4. **[KNN](./notes/unit-4b#knn) and [logistic regression](./notes/unit-4a#logistic).** KNN off a scatter plot (Sep 2025), a logistic probability (spring 2025), and KNN tables in both end-semesters.
5. **[Decision trees, Naive Bayes and SVM](./notes/unit-4b).** In your Units 1–4 syllabus and in both end-semesters (an 8-mark tree question), though not yet in a mid-semester. There are no slides for trees or Naive Bayes; the notes teach the standard method.
6. **[Unit 1](./notes/unit-1) and the theory of [Unit 3](./notes/unit-3).** Pearson r and chart choice (end-semester), definitions, paradigms, Q-learning (quiz material).
7. **Timed papers:** [Sep 2025](./papers/mst-2025), [spring 2025](./papers/mst-2025-spring), then the [mock](./mock-mst).
8. **The night before:** [most-trapped questions](./traps) and the [formula sheet](./formulas).

## How the papers are set {#pattern}

Four papers: two mid-semesters (55 marks) and two end-semesters (140 marks). Units 1–4 topics, by how many papers asked them:

| Topic | Papers | Where |
|---|---|---|
| Feature scaling: when to use which, the arithmetic, z-score outliers | **4 of 4** | [Unit 2](./notes/unit-2#scaling) |
| Categorical encoding, high cardinality | **4 of 4** | [Unit 2](./notes/unit-2#encoding) |
| Confusion matrix or ROC | **4 of 4** | [Unit 3](./notes/unit-3#confusion-matrix) |
| Gradient descent by hand | **3 of 4**, both mid-semesters | [Unit 4A](./notes/unit-4a#gradient-descent) |
| KNN by hand, choosing k | **3 of 4** | [Unit 4B](./notes/unit-4b#knn) |
| Cross-validation folds | 2 of 4 | [Unit 3](./notes/unit-3#cross-validation) |
| Decision tree by information gain | 2 of 4 (end-semesters) | [Unit 4B](./notes/unit-4b#decision-trees) |
| Naive Bayes | 2 of 4 (end-semesters) | [Unit 4B](./notes/unit-4b#naive-bayes) |
| Correlation, least-squares line | 2 of 4 (end-semesters) | [Unit 1](./notes/unit-1#correlation), [Unit 4A](./notes/unit-4a#simple-lr) |
| Logistic probability, ridge, SVM kernels, overfitting, chart choice | 1 each | |

Every paper also had **Unit 5** (k-means, PCA, DBSCAN), which is outside your mid-semester; last year's mid-semester gave it 6 of 30 marks. If yours stops at Unit 4, those marks move to the topics above. The full map is in [how often questions repeat](./repeats).

## About the quizzes and the lab {#quizzes}

No DSML quiz papers were available, so the [timed quiz sets](./quiz-practice) are built from what the slides stress and the traps in the notes, with long paragraph questions to practise reading under time. The **lab** is 30% of the course: the [assignments](./assignments/) show your six scripts with the output they really printed, and flag the leakage traps a viva is likely to probe.

## Where this comes from {#sources}

Built from the lecture slides (Units 1–4, including the borrowed decks on NumPy, KNN, SVM and Mitchell's chapters), the course handout, four past papers, the six assignment sheets with your lab scripts, and the earlier study documents (the Units 1–2 theory sheet and the Units 3–4 quiz notes). Every number in a solution, every worked example and every graph is produced by a script that CI re-runs; the assignment outputs are recorded runs of the lab scripts. Where the slides are wrong, the notes say so.
