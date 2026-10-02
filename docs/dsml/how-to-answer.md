---
title: How to answer the mid-semester
---

# How to answer the mid-semester

The paper is about 80% calculation, and calculations are marked on the **working**, not just the final number. Every question type the papers have used is below, with the layout that collects the marks and a link to a solved example.

::: info The paper at a glance
Five questions of 5–6 marks, 25–30 marks in all, 1 hour 30 minutes, **all compulsory** (the handout: no choice in the mid-term or end-term). A non-programmable calculator is allowed. Budget about **16 minutes a question** and keep 10 minutes at the end to check arithmetic.
:::

## Four habits that apply to every question {#habits}

1. **State assumptions in the first line.** Papers leave things out (no learning rate, no new customer's values) and say "assume suitably". Write "Assume α = 0.01 and θ = 0" and carry on; method marks are safe.
2. **Formula, then substitution, then value.** Write the symbolic formula, then the same formula with numbers, then the result to 4 decimal places. A wrong final number with a right substitution still earns most of the marks.
3. **Use a table** for anything repeated over rows (errors in gradient descent, distances in KNN, thresholds in ROC). Tables are faster to write and easier to mark.
4. **End with one sentence of meaning**: "r = 0.99, a very strong positive linear relationship", "the cost fell, so the step went the right way", "precision matters more here because…".

**Calculator:** $e^{x}$ for the sigmoid, ln for the logit; $\log_2 x = \ln x / 0.6931$ for entropy. Keep 4 decimals in intermediate values; round only the final answer.

## Calculation questions {#calculations}

### Gradient descent iterations

> **Assume** (if not given) α and starting values. **Write** the cost $J$, the gradient formulas and the update rule. **Table:** $x$, $y$, $\hat y$, $e = \hat y - y$, $e \cdot x$, with column sums. **Gradients** from the sums. **Update** all parameters from the old values. **Repeat** for the next iteration. **Box** the final values; optionally show the cost fell.

Examples: [Sep 2025 Q2](./papers/mst-2025#q2) (one iteration), [spring 2025 Q1](./papers/mst-2025-spring#q1) (three parameters, two iterations), [autumn 2024 Q4b](./papers/endsem-2024#q4b) (a function of three variables).

### Confusion matrix and metrics

> **Draw** the 2 × 2 table with labels (actual rows, predicted columns) and fill TP, FN, FP, TN; check the totals against the story. **Table** of metric → formula → substitution → value. **One line** on which metric matters for this problem.

Examples: [spring 2025 Q3](./papers/mst-2025-spring#q3), [autumn 2024 Q3b](./papers/endsem-2024#q3b) (built from a story).

### ROC table and AUC

> **Count** positives P and negatives N. **One row per threshold** (positive if p ≥ t): TP, FP, FN, TN, TPR = TP/P, FPR = FP/N. **List** the points, adding (0, 0). **Sketch** the curve with the diagonal. **AUC** by rectangles or trapezoids (check by counting correctly ordered pairs). **Interpret** with the AUC scale.

Example: [Sep 2025 Q3](./papers/mst-2025#q3).

### KNN by hand

> **Table** of every training point with its distance (show √(Δx² + Δy²)). **Sort.** **Take k**, count the votes, state the class. **Mention** scaling if the units differ, and how you would choose k.

Examples: [spring 2025 end-semester Q3a](./papers/endsem-2025#q3a), [Sep 2025 Q5](./papers/mst-2025#q5) (read off a plot).

### Scaling and outliers

> **Compute** min, max, mean and σ (say population or sample). **Table** of x → min-max → z-score. For outliers, **state the cut-off** (|z| > 3 or 2), flag the points, and note masking or the IQR alternative.

Examples: [spring 2025 end-semester Q1b](./papers/endsem-2025#q1b), [autumn 2024 Q2b](./papers/endsem-2024#q2b).

### Correlation and the least-squares line

> **Table:** x, y, x − x̄, y − ȳ, products, squares, with sums. **Substitute** into r (or a and b). **Interpret** strength and direction, and add "correlation is not causation". For a line, **predict** with it and note extrapolation.

Examples: [autumn 2024 Q1b](./papers/endsem-2024#q1b), [spring 2025 end-semester Q1a](./papers/endsem-2025#q1a).

### Logistic-regression probability

> **z** = b₀ + b₁x₁ + … with numbers. **p** = 1/(1 + e^(−z)), showing $e^{-z}$. **Class** at threshold 0.5. Optionally odds = p/(1 − p) = $e^{z}$.

Example: [spring 2025 Q2](./papers/mst-2025-spring#q2).

### Decision tree root, Naive Bayes

> **Tree:** parent entropy → for each attribute a small table (value, Yes, No, entropy, weighted) → gain → pick the largest → say why (a pure branch). **Naive Bayes:** count table per class → score = P(c) × each P(feature ∣ c) → compare → mention Laplace smoothing if a count is 0.

Examples: [autumn 2024 Q4c](./papers/endsem-2024#q4c), [spring 2025 end-semester Q3b and Q4a](./papers/endsem-2025#q3b).

## Theory questions {#theory}

The theory parts are short and come in four shapes. Each needs a structure, not an essay.

### "When do we prefer X over Y? Justify with an example."

> **One line** defining each. **Prefer X when** (2–3 conditions, each with a reason). **Example with numbers.** **Prefer Y when** (1–2 conditions). Never only a list of names.

Model answer: [Sep 2025 Q1a](./papers/mst-2025#q1a) (min-max vs standardisation).

### "Assess any two issues of…"

> **Two bold headings**, each with the mechanism in one sentence and the example quantified ("3,000 categories → 3,000 columns"). **One remedy** for a bonus mark.

Model answer: [Sep 2025 Q1b](./papers/mst-2025#q1b) (one-hot with high cardinality).

### "Analyse the impact of A on bias, variance and computation"

> **A table** with the two extremes as columns (small k / large k) and bias, variance and computation as rows, each cell with a reason. **A conclusion** naming the usual compromise.

Model answers: [spring 2025 Q4a](./papers/mst-2025-spring#q4a) (number of folds), [autumn 2024 Q3a](./papers/endsem-2024#q3a) (k in KNN).

### "Differentiate / compare A and B"

> **The one-sentence difference first**, then a **table** of 4–5 rows (purpose, how, when, strength, weakness), then an example of each.

Model answers: [spring 2025 end-semester Q1a](./papers/endsem-2025#q1a) (correlation vs regression), [autumn 2024 Q4a](./papers/endsem-2024#q4a) (ridge vs linear), [autumn 2024 Q2a](./papers/endsem-2024#q2a) (LOOCV vs 5-fold).

::: danger The mistakes that cost the most
- **Skipping the formula line** and writing only numbers: the examiner cannot give method marks.
- **No assumption written** when the paper left data out.
- **Swapping precision and recall**, or dividing FPR by the positives.
- **Updating w and then using the new w** for b's gradient.
- In theory parts, **a list of keywords without reasons**. "Curse of dimensionality" earns nothing on its own; "3,000 columns, so the model needs far more data and distances lose meaning" earns the mark.
:::
