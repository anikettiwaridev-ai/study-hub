// Single source of truth for Data Science and Machine Learning repeat tracking.
// Every badge, count and mark total on the site is computed from this file.
// Refs look like "S25.Q2" or "E24.Q4c": <source id>.<part>.

const range = (n, marks = null) =>
  Object.fromEntries(Array.from({ length: n }, (_, i) => [`Q${i + 1}`, marks]))

export const labels = {
  column: ['In assignments', 'In A1–A6'],
  word: 'assignments',
  uncovered: 'Not in the slides. Learn it from the notes, which use the standard method.',
}

export const sources = {
  S25: {
    title: 'Mid-semester, September 2025',
    note: 'Last year’s paper for this course (CSN3002 / AIN3003): the closest model for yours',
    short: 'Sep 2025',
    kind: 'mst', maxMarks: 30, time: '1.5 hours',
    href: '/dsml/papers/mst-2025',
    // The paper gives Q1 6 marks without splitting them; 3 + 3 is assumed.
    parts: { Q1a: 3, Q1b: 3, Q2: 6, Q3: 6, Q4: 6, Q5: 6 },
  },
  P25: {
    title: 'Mid-semester, spring 2025 (DSN4005)',
    note: 'B.Tech CSE (Data Science), 4th semester: a sibling course with the same Units 1–4',
    short: 'Spring 2025',
    kind: 'mst', maxMarks: 25, time: '1.5 hours',
    href: '/dsml/papers/mst-2025-spring',
    parts: { Q1: 5, Q2: 5, Q3: 5, Q4a: 2, Q4b: 2, Q5a: 2, Q5b: 2, Q5c: 2 },
  },
  E24: {
    title: 'End-semester, autumn 2024',
    note: 'CSN3002 / ES1701 / AIN3003, this course. Units 1–4 solved; Unit 5 (Q5) waits for the end-semester build.',
    short: 'End-sem 2024',
    kind: 'endsem', maxMarks: 80, time: '3 hours',
    href: '/dsml/papers/endsem-2024',
    parts: { Q1a: 6, Q1b: 6, Q2a: 4, Q2b: 5, Q2c: 5, Q3a: 6, Q3b: 6, Q4a: 6, Q4b: 6, Q4c: 8, Q4d: 2, Q5a: 7, Q5b: 7, Q5c: 6 },
  },
  E25: {
    title: 'End-semester, spring 2025 (DSN4005)',
    note: 'The sibling course’s backlog paper. Units 1–4 solved; Unit 5 (Q5) waits for the end-semester build.',
    short: 'End-sem 2025',
    kind: 'endsem', maxMarks: 60, time: '3 hours',
    href: '/dsml/papers/endsem-2025',
    parts: { Q1a: 5, Q1b: 5, Q1c: 5, Q2a: 5, Q2b: 5, Q3a: 5, Q3b: 5, Q4a: 5, Q4b: 5, Q5a: 5, Q5b: 5, Q5c: 5 },
  },
  MK: {
    title: 'Mock mid-semester paper',
    note: 'Written for this site in the shape of the two real mid-semesters, Units 1–4 only. Not a real paper.',
    short: 'Mock MST',
    kind: 'mock', maxMarks: 30, time: '1.5 hours',
    href: '/dsml/mock-mst',
    parts: { Q1a: 3, Q1b: 3, Q2: 6, Q3a: 3, Q3b: 3, Q4: 6, Q5a: 3, Q5b: 3 },
  },
  A1: { title: 'Assignment 1 · NumPy', href: '/dsml/assignments/a1', topic: 'Arrays: create, reshape, index, split, stack, dot and cross', short: 'A1', kind: 'assignment', parts: range(10) },
  A2: { title: 'Assignment 2 · Pandas and Matplotlib', href: '/dsml/assignments/a2', topic: 'Series, DataFrames, missing values, groupby, four chart types', short: 'A2', kind: 'assignment', parts: range(10) },
  A3: { title: 'Assignment 3 · Linear regression', href: '/dsml/assignments/a3', topic: 'Salary_Data.csv: split, fit, slope and intercept, MSE and R²', short: 'A3', kind: 'assignment', parts: range(10) },
  A4: { title: 'Assignment 4 · Data preprocessing', href: '/dsml/assignments/a4', topic: 'Imputation, duplicates, label and one-hot encoding, scaling', short: 'A4', kind: 'assignment', parts: range(10) },
  A5: { title: 'Assignment 5 · Logistic regression', href: '/dsml/assignments/a5', topic: 'Social_Network_Ads.csv: scale, fit, probabilities, confusion matrix', short: 'A5', kind: 'assignment', parts: range(10) },
  A6: { title: 'Assignment 6 · K-nearest neighbours', href: '/dsml/assignments/a6', topic: 'Iris.csv: k = 5, evaluation, choosing k', short: 'A6', kind: 'assignment', parts: range(10) },
}

export const clusters = [
  {
    id: 'gradient-descent',
    title: 'Gradient descent iterations by hand',
    trap: 'Write the update rule and the gradient formula before any number, and state the convention: MSE with 2/n or 1/(2n). If the paper gives no learning rate or starting point, assume them in the first line. Update every parameter from the OLD values (simultaneous update).',
    groups: [
      { kind: 'single', refs: ['S25.Q2'] },
      { kind: 'single', refs: ['P25.Q1'] },
      { kind: 'single', refs: ['E24.Q4b'] },
      { kind: 'single', refs: ['MK.Q2'] },
    ],
    notes: {
      'S25.Q2': 'One iteration of w and b on three points, η = 0.1',
      'P25.Q1': 'Two iterations of θ₀, θ₁, θ₂ with no learning rate given',
      'E24.Q4b': 'Two iterations on f(x, y, z) = 2x² − y + z³/3, plus why non-convex functions break it',
    },
  },
  {
    id: 'scaling',
    title: 'Feature scaling: min-max or standardisation, and the arithmetic',
    trap: 'Standardisation is NOT bounded to [0, 1] (the slide that says so contradicts the next slide). Min-max is ruined by one outlier. Say which standard deviation you use (population ÷n or sample ÷(n − 1)).',
    groups: [
      { kind: 'exact', refs: ['S25.Q1a', 'P25.Q5a'] },
      { kind: 'single', refs: ['E25.Q1b'] },
      { kind: 'single', refs: ['E24.Q2b'] },
      { kind: 'single', refs: ['MK.Q1a'] },
      { kind: 'single', refs: ['A4.Q7'] },
    ],
    notes: {
      'S25.Q1a': '“When do we prefer min-max scaling over standardization? Justify with an example.”',
      'E25.Q1b': 'Both methods on the marks 8, 10, 15, 20',
      'E24.Q2b': 'Find outliers with z-scores: one huge value hides the other outlier',
    },
  },
  {
    id: 'encoding',
    title: 'Categorical encoding: label, one-hot, dummy, and high cardinality',
    trap: 'Label encoding invents an order, so it is only for ordinal data (or trees). One-hot on a high-cardinality column has at least five problems; name two with a reason each, not just “too many columns”.',
    groups: [
      { kind: 'exact', refs: ['S25.Q1b', 'P25.Q5b'] },
      { kind: 'single', refs: ['E24.Q2c'] },
      { kind: 'single', refs: ['E25.Q1c'] },
      { kind: 'single', refs: ['MK.Q1b'] },
      { kind: 'single', refs: ['A4.Q5'] },
      { kind: 'single', refs: ['A4.Q6'] },
    ],
    notes: {
      'S25.Q1b': '“Assess any two potential issues of applying one-hot encoding to a dataset with high cardinality.”',
      'E24.Q2c': 'Why encode at all, and the encoding techniques',
      'E25.Q1c': '200 product categories: label or one-hot for a decision tree? Then one-hot a Weather column',
    },
  },
  {
    id: 'knn',
    title: 'K-nearest neighbours: classify by hand, and choose k',
    trap: 'Make the distance table first and sort it. Small k overfits (high variance), large k underfits (high bias); once k is at least twice the size of the smaller class, KNN predicts the majority class everywhere. Scale the features before measuring distance.',
    groups: [
      { kind: 'single', refs: ['S25.Q5'] },
      { kind: 'single', refs: ['E24.Q3a'] },
      { kind: 'single', refs: ['E25.Q3a'] },
      { kind: 'single', refs: ['MK.Q4'] },
      { kind: 'single', refs: ['A6.Q6'] },
      { kind: 'single', refs: ['A6.Q9'] },
    ],
    notes: {
      'S25.Q5': 'Read the class off a scatter plot for k = 1, 3, 5; is k = 11 wise?',
      'E24.Q3a': 'Effect of k on bias and variance, and how to pick k',
      'E25.Q3a': 'Euclidean distances, k = 3 (the new customer’s values are missing from the paper)',
    },
  },
  {
    id: 'confusion-matrix',
    title: 'Confusion matrix: accuracy, precision, recall, F1, specificity',
    trap: 'Precision divides by everything PREDICTED positive; recall by everything ACTUALLY positive. Build the 2 × 2 table before any formula. A false positive is a Type I error.',
    groups: [
      { kind: 'exact', refs: ['P25.Q3', 'E25.Q2a'] },
      { kind: 'single', refs: ['E24.Q3b'] },
      { kind: 'single', refs: ['MK.Q3a'] },
      { kind: 'single', refs: ['A5.Q9'] },
    ],
    notes: {
      'P25.Q3': 'The 50 / 10 / 5 / 35 matrix; the end-semester reuses it',
      'E24.Q3b': 'Build the matrix from a story about a packet filter first',
    },
  },
  {
    id: 'cross-validation',
    title: 'Cross-validation: fold sizes, LOOCV, and the bias–variance effect of k',
    trap: 'k-fold on n examples: k models, each trained on (k − 1)n/k and tested on n/k. More folds: lower bias, higher variance, more computation. LOOCV is k = n.',
    groups: [
      { kind: 'single', refs: ['P25.Q4a'] },
      { kind: 'single', refs: ['P25.Q4b'] },
      { kind: 'single', refs: ['E24.Q2a'] },
      { kind: 'single', refs: ['MK.Q5b'] },
    ],
    notes: {
      'P25.Q4a': 'Many folds vs few: bias, variance, computation',
      'P25.Q4b': '10-fold on 100 examples: N1, N2, N3',
      'E24.Q2a': 'LOOCV vs 5-fold: time and effectiveness',
    },
  },
  {
    id: 'trees-bayes',
    title: 'Decision trees (entropy and information gain) and Naive Bayes',
    trap: 'Entropy uses log base 2. Information gain = parent entropy − weighted child entropy. In Naive Bayes, one zero count wipes out the whole product: say so, and mention Laplace smoothing.',
    uncovered: true,
    groups: [
      { kind: 'single', refs: ['E24.Q4c'] },
      { kind: 'single', refs: ['E25.Q3b'] },
      { kind: 'single', refs: ['E25.Q4a'] },
      { kind: 'single', refs: ['E24.Q4d'] },
    ],
    notes: {
      'E24.Q4c': 'The Play Golf table: which feature at the root? (8 marks)',
      'E25.Q3b': 'Entropy, gain for three attributes, root node',
      'E25.Q4a': 'Naive Bayes on Colour and Shape: Apple, Chilli or Cucumber',
      'E24.Q4d': 'Two reasons Naive Bayes is limited in practice',
    },
  },
  {
    id: 'logistic',
    title: 'Logistic regression: sigmoid, probability, odds',
    trap: 'Compute z first, then σ(z) = 1/(1 + e^(−z)). e^β is an odds ratio, not a change in probability. The training table printed beside the equation is usually not needed.',
    groups: [
      { kind: 'single', refs: ['P25.Q2'] },
      { kind: 'single', refs: ['MK.Q5a'] },
      { kind: 'single', refs: ['A5.Q8'] },
    ],
    notes: { 'P25.Q2': 'Age 38, income $62,000: p = 0.87' },
  },
  {
    id: 'regression-line',
    title: 'Correlation and the least-squares line',
    trap: 'Correlation is one symmetric number in [−1, 1]; regression is an equation with a dependent variable. Neither proves causation. Code years as 0, ±1, ±2 to keep the sums small.',
    groups: [
      { kind: 'single', refs: ['E24.Q1b'] },
      { kind: 'single', refs: ['E25.Q1a'] },
      { kind: 'single', refs: ['A3.Q8'] },
    ],
    notes: {
      'E24.Q1b': 'Pearson r for five points, and what it means',
      'E25.Q1a': 'Correlation vs regression; the line for sales by year; predict 2012',
    },
  },
  {
    id: 'roc',
    title: 'ROC curve and AUC from a threshold table',
    trap: 'One threshold gives one confusion matrix gives one point (FPR, TPR). Predict positive when p ≥ threshold. Add (0, 0) and (1, 1) before measuring the area.',
    groups: [
      { kind: 'single', refs: ['S25.Q3'] },
      { kind: 'single', refs: ['MK.Q3b'] },
    ],
    notes: { 'S25.Q3': 'Six samples, six thresholds, AUC ≈ 0.67' },
  },
  {
    id: 'unit-5',
    title: 'Unit 5: clustering and PCA (outside the Units 1–4 mid-semester)',
    trap: 'Every paper had some Unit 5. Your mid-semester stops at Unit 4, so these are here for the record. The two short mid-semester ones are solved; the end-semester ones wait for the end-semester build.',
    groups: [
      { kind: 'single', refs: ['S25.Q4'] },
      { kind: 'single', refs: ['P25.Q5c'] },
      { kind: 'single', refs: ['E24.Q5a'] },
      { kind: 'single', refs: ['E24.Q5b'] },
      { kind: 'single', refs: ['E24.Q5c'] },
      { kind: 'single', refs: ['E25.Q5a'] },
      { kind: 'single', refs: ['E25.Q5b'] },
      { kind: 'single', refs: ['E25.Q5c'] },
    ],
    notes: {
      'S25.Q4': 'k-means on {0, 2, 4, 6, 24, 26}, two iterations',
      'P25.Q5c': 'PCA: how many components keep 90% of the variance',
      'E24.Q5a': 'DBSCAN core points and outliers',
      'E24.Q5b': 'Minimum number of PCA components',
      'E24.Q5c': 'Chi-square feature selection',
      'E25.Q5a': 'DBSCAN and the effect of ε',
      'E25.Q5b': 'Hierarchical clustering on a distance matrix',
      'E25.Q5c': 'PCA on two highly correlated variables',
    },
  },
]

export const singles = [
  { ref: 'E24.Q1a', topic: 'Choose a chart: categories, change over time, a distribution' },
  { ref: 'E24.Q4a', topic: 'Ridge vs linear regression, then ridge weights with λ = 10' },
  { ref: 'E25.Q2b', topic: 'Three spam models (99/72, 68/68, 88/85): which overfits, which underfits' },
  { ref: 'E25.Q4b', topic: 'SVM for fraud: is a linear SVM enough, which kernel?' },
]

export default { sources, clusters, singles, labels }
