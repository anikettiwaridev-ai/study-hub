---
title: Numerical drills
---

# Numerical drills

Eighteen fresh calculations, one or two of every kind the papers ask, with new numbers. Do them on paper with a calculator, then open the answer. Every answer comes from running a script.

::: tip How to use this page
Keep **Hide solutions** on (the default). Give each drill 4–6 minutes, the pace of a 6-mark question in a 90-minute paper. If one takes longer, read its section in the notes, then come back the next day and do it again from scratch.
:::

## Preprocessing {#preprocessing}

<Drill n="1" tag="Scaling">

Apply min-max scaling and z-score standardisation (population σ) to: **5, 10, 15, 30**.

::: details Answer

<!--@include: @/../code/dsml/practice/drills.out#d1-->

:::

</Drill>

<Drill n="2" tag="Scaling">

Temperatures −10, 0, 10, 20, 30 must be scaled to the range **[−1, 1]**. Give the formula and the scaled values.

::: details Answer

<!--@include: @/../code/dsml/practice/drills.out#d2-->

:::

</Drill>

<Drill n="3" tag="Outliers">

Find the outliers in **12, 14, 15, 13, 16, 14, 13, 60** using z-scores. Try the cut-offs 2 and 3.

::: details Answer

<!--@include: @/../code/dsml/practice/drills.out#d3-->

:::

</Drill>

## Correlation and regression {#regression}

<Drill n="4" tag="Pearson r">

Compute Pearson's r for x = 10, 20, 30, 40, 50 and y = 40, 35, 30, 22, 18, and interpret it.

::: details Answer

<!--@include: @/../code/dsml/practice/drills.out#d4-->

:::

</Drill>

<Drill n="5" tag="Least squares">

The slides' advertising example: spend (x) 90, 120, 150, 100, 130 and sales (y) 1000, 1300, 1800, 1200, 1380. Fit y = ax + b by least squares and predict the sales for a spend of 200.

::: details Answer

<!--@include: @/../code/dsml/practice/drills.out#d5-->

:::

</Drill>

## Gradient descent {#gradient-descent}

<Drill n="6" tag="One variable">

Minimise f(w) = w² − 4w + 5 by gradient descent from w = 0 with α = 0.25. Give w after three iterations.

::: details Answer

<!--@include: @/../code/dsml/practice/drills.out#d6-->

:::

</Drill>

<Drill n="7" tag="Linear regression">

Data (2, 5), (4, 9), (6, 13); model ŷ = wx + b; cost J = (1/2n)Σ(ŷ − y)²; start from w = b = 0 with α = 0.01. Perform one iteration.

::: details Answer

<!--@include: @/../code/dsml/practice/drills.out#d7-->

:::

</Drill>

<Drill n="8" tag="Two features">

Data (x₁, x₂, y) = (1, 1, 4), (2, 0, 5), (0, 2, 6); model ŷ = θ₀ + θ₁x₁ + θ₂x₂; MSE cost with the 2/n gradient; all θ start at 0; α = 0.1. Perform one iteration.

::: details Answer

<!--@include: @/../code/dsml/practice/drills.out#d8-->

:::

</Drill>

## Classification metrics {#metrics}

<Drill n="9" tag="Logistic">

A model predicts passing an exam from hours of study: P(pass) = σ(−4 + 0.05 × hours). Find the probability for 60 hours, the odds, the odds ratio per extra hour, and the hours needed for a 50% chance.

::: details Answer

<!--@include: @/../code/dsml/practice/drills.out#d9-->

:::

</Drill>

<Drill n="10" tag="Confusion matrix">

A spam filter sees 1,000 emails, 200 of them spam. It flags 180 emails, of which 150 really are spam. Build the confusion matrix and find accuracy, precision, recall, F1 and specificity. Which metric matters most here?

::: details Answer

<!--@include: @/../code/dsml/practice/drills.out#d10-->

:::

</Drill>

<Drill n="11" tag="ROC">

Scores and true labels: 0.9 (1), 0.75 (1), 0.7 (0), 0.5 (1), 0.4 (0), 0.2 (0). Build the ROC table using each score as a threshold, and find the AUC.

::: details Answer

<!--@include: @/../code/dsml/practice/drills.out#d11-->

:::

</Drill>

<Drill n="12" tag="Cross-validation">

Give N1 (number of models), N2 (training size) and N3 (test size) for: 4-fold on 60 examples; LOOCV on 25; 10-fold on 250.

::: details Answer

<!--@include: @/../code/dsml/practice/drills.out#d12-->

:::

</Drill>

## Classifiers {#classifiers}

<Drill n="13" tag="KNN">

Training points: A(1, 1) Red, B(2, 1) Red, C(4, 3) Blue, D(5, 4) Blue, E(3, 5) Blue, F(1, 3) Red. Classify the query (3, 2) with k = 3 and k = 5 (Euclidean). Also give the Manhattan distances.

::: details Answer

<!--@include: @/../code/dsml/practice/drills.out#d13-->

:::

</Drill>

<Drill n="14" tag="KNN regression">

The 3 nearest houses to a new one are at distances 2, 3 and 4, priced 52, 48 and 60 lakh. Predict the price by plain KNN regression and by distance-weighted KNN (w = 1/d²).

::: details Answer

<!--@include: @/../code/dsml/practice/drills.out#d14-->

:::

</Drill>

<Drill n="15" tag="Decision tree">

Six days (Weather, Wind → Play): (Sunny, Low → Yes), (Sunny, High → No), (Rainy, High → No), (Rainy, Low → No), (Sunny, Low → Yes), (Rainy, Low → Yes). Which attribute is the root by information gain?

::: details Answer

<!--@include: @/../code/dsml/practice/drills.out#d15-->

:::

</Drill>

<Drill n="16" tag="Naive Bayes">

Eight emails (contains "free", has a link → class): (Yes, Yes → Spam), (Yes, No → Spam), (Yes, Yes → Spam), (No, Yes → Spam), (No, No → Ham), (No, No → Ham), (Yes, No → Ham), (No, No → Ham). Classify an email with "free" and a link, with and without Laplace smoothing.

::: details Answer

<!--@include: @/../code/dsml/practice/drills.out#d16-->

:::

</Drill>

<Drill n="17" tag="SVM">

A linear SVM has w = (2, −1) and b = −1. Find the margin width and classify (1, 0), (0, 1), (2, 1) and (1, 1). Which are support vectors?

::: details Answer

<!--@include: @/../code/dsml/practice/drills.out#d17-->

:::

</Drill>

<Drill n="18" tag="Q-learning">

γ = 0.8. An agent in state s takes action a, receives reward 10 and lands in s′, whose current Q̂-values are 20, 35 and 5. What is the updated Q̂(s, a)?

::: details Answer

<!--@include: @/../code/dsml/practice/drills.out#d18-->

:::

</Drill>
