---
title: Unit 4B · KNN, SVM, Naive Bayes and decision trees
---

# Unit 4B · KNN, SVM, Naive Bayes and decision trees

Four classifiers, four different ideas: **vote** among the nearest examples (KNN), draw the **widest street** between the classes (SVM), multiply **probabilities** (Naive Bayes), ask the **most informative question** first (decision trees).

::: info How this unit is examined
- **Mid-semester:** KNN read off a scatter plot for K = 1, 3, 5, and whether K = 11 is wise ([Sep 2025 Q5](../papers/mst-2025#q5)). The rest of this unit had not been reached by the mid-semester in past years, but it is in your Units 1–4 syllabus, so expect it.
- **End-semester:** a KNN distance table (5), the effect of k on bias and variance (6), the root of a decision tree by information gain (8 and 5), Naive Bayes by hand (5) and its limits (2), an SVM kernel design (5).
- **Not in the slides:** Naive Bayes and decision trees have no deck in the course material. These notes use the standard methods (Bayes' rule with the naive independence assumption; ID3 with entropy and information gain), which is what the past papers' questions expect.
:::

## Read this first: the unit on one screen {#toolkit}

| Classifier | Idea | Learns | Key formula | Watch out for |
|---|---|---|---|---|
| **KNN** | majority vote of the k nearest training points | nothing (lazy): stores the data | $d = \sqrt{\sum (p_i - q_i)^2}$ | scale features; odd k; k by cross-validation |
| **SVM** | the boundary with the **maximum margin** | w and b (only support vectors matter) | margin = $2/\lVert w\rVert$ | needs a kernel for non-linear data |
| **Naive Bayes** | most probable class, features assumed independent | class priors and per-class frequencies | $P(c)\prod P(x_i \mid c)$ | a zero count kills the product (Laplace) |
| **Decision tree** | split on the most informative feature, recursively | a tree of questions | Gain = H(parent) − Σ weighted H(children) | log base 2; overfits if grown fully |

## 1. K-nearest neighbours {#knn}

"If it walks like a duck and quacks like a duck, it's probably a duck." To classify a new point, find the k training points closest to it and take a **majority vote** of their labels (for regression, **average** their values).

KNN is **instance-based** (it keeps the training records and compares new cases with them), **lazy** (no explicit training: `fit()` just stores the data, and all the work happens at prediction time) and **non-parametric** (no assumption about the data's distribution). The opposite, an **eager** learner such as a decision tree, builds a model up front. A **rote learner** is the extreme case: it classifies only exact matches; KNN uses the closest ones instead.

**KNN needs three things:** the stored records, a distance metric, and k. **The algorithm:** (1) choose k; (2) compute the distance from the new point to every training point; (3) sort and take the k nearest; (4) vote (or average).

### Distance metrics

<!--@include: @/../code/dsml/notes/u4b.out#distances-->

| Metric | Best for |
|---|---|
| Euclidean | continuous features in similar units (the default) |
| Manhattan | grid-like movement, or discrete features / features on different scales |
| Minkowski | the general family: r = 1 Manhattan, r = 2 Euclidean |
| Cosine | text and documents: direction matters, length does not |

### Worked example

<!--@include: @/../code/dsml/notes/u4b.out#knn-->

**Voting.** Majority: $y' = \arg\max_v \sum_{i \in D_z} I(v = y_i)$, where $D_z$ is the set of k nearest neighbours. **Distance-weighted:** each neighbour's vote counts $w = 1/d^2$, so close neighbours matter more. With 1-NN, the space is carved into a **Voronoi diagram**: each training point owns the region closer to it than to any other.

### Choosing k {#choosing-k}

| | Small k (k = 1) | Large k |
|---|---|---|
| Boundary | jagged; follows every point | smooth |
| Bias / variance | low bias, **high variance** | **high bias**, low variance |
| Failure mode | sensitive to noise: **overfits** (100% on training data) | the neighbourhood includes other classes: **underfits**; at the extreme, always predicts the majority class |

**How to pick k:** start from **k ≈ √n**; keep it **odd** for two classes so votes cannot tie; then choose by **cross-validation** (the k with the lowest validation error). In Assignment 6, √120 ≈ 11, but 5-fold cross-validation picked k = 5.

::: warning Correction: the slide says "if n is even, adjust K to be odd"
It is **k** that should be odd (to avoid ties in a two-class vote), whatever n is.
:::

**Scale the features first.** The slide's example: height varies from 1.5 to 1.8 m, weight from 60 to 100 kg, income from ₹10K to ₹2 lakh. Unscaled, income alone decides who is "near".

### The curse of dimensionality

<!--@include: @/../code/dsml/notes/u4b.out#curse-->

**Pros:** simple; no training phase; does classification and regression. **Cons:** slow at prediction (compares with every training point, O(n) per query); sensitive to noise and irrelevant features; struggles in high dimensions; needs scaling.

## 2. Support vector machines {#svm}

A linear classifier $f(x) = \text{sign}(w \cdot x + b)$. Many lines separate two clouds of points; which is best? The SVM picks the one with the **maximum margin**: the widest band (street) the boundary could be widened to before touching a point. The points the margin touches are the **support vectors**; every other point could move (or vanish) without changing the answer.

**Why maximum margin?** It is the safest choice (a small error in the boundary's position is least likely to cause a misclassification); LOOCV is easy, because removing a non-support vector changes nothing; there is theory (VC dimension) behind it; and it works very well in practice.

### The margin {#margin}

The boundary is $w\cdot x + b = 0$; the **plus-plane** $w \cdot x + b = +1$ and the **minus-plane** $w \cdot x + b = -1$ pass through the support vectors. w is perpendicular to the planes, and the distance between them is

$$ M = \frac{2}{\lVert w \rVert} = \frac{2}{\sqrt{w \cdot w}}. $$

(Take x⁻ on the minus-plane and x⁺ = x⁻ + λw on the plus-plane: subtracting the two plane equations gives λ w·w = 2, so M = λ‖w‖ = 2/‖w‖.)

<!--@include: @/../code/dsml/notes/u4b.out#svm-->

### Training an SVM

Maximising 2/‖w‖ is the same as minimising ‖w‖²:

$$ \min_{w, b}\ \tfrac{1}{2}\,w \cdot w \quad\text{subject to}\quad y_k\,(w \cdot x_k + b) \ge 1 \text{ for every training point } k. $$

That is a **quadratic programming (QP)** problem: a quadratic objective with linear constraints, solved by standard QP algorithms (more reliably than gradient ascent). There are R constraints, one per training point.

**Noisy data (soft margin).** If no line separates the classes perfectly, give each point a **slack** $\varepsilon_k \ge 0$ (how far it is on the wrong side) and minimise $\tfrac{1}{2}w\cdot w + C\sum_k \varepsilon_k$, subject to $y_k(w \cdot x_k + b) \ge 1 - \varepsilon_k$. Now there are 2R constraints. **C** trades a wide margin (small C) against fewer training errors (large C).

**The dual form** (why kernels work): the solution can be written $w = \sum_k \alpha_k y_k x_k$, where only the support vectors have $\alpha_k > 0$, and the training data appears **only through dot products** $x_k \cdot x_l$.

### Non-linear data: the kernel trick {#kernels}

<!--@include: @/../code/dsml/notes/u4b.out#kernel-->

Map each x to features φ(x) (polynomial terms, radial basis functions, sigmoids). Because the SVM only needs dot products, replace $\varphi(a)\cdot\varphi(b)$ by a **kernel** $K(a, b)$ computed directly from a and b:

| Kernel | Formula | Use |
|---|---|---|
| Linear | $a \cdot b$ | data already (nearly) linearly separable; many features (text) |
| Polynomial | $(a \cdot b + 1)^d$ | interactions between features up to degree d |
| **RBF (Gaussian)** | $\exp\!\left(-\dfrac{\lVert a - b\rVert^2}{2\sigma^2}\right)$ | the default for non-linear data; local, curved boundaries |
| Sigmoid (neural-net style) | $\tanh(\kappa\, a \cdot b - \delta)$ | rarely |

σ, κ, δ, d and C are chosen by **cross-validation**. **Multi-class:** an SVM separates two classes, so for N classes train N SVMs ("class i" vs "not class i") and pick the one that puts the point furthest into its positive side (one-vs-rest).

::: tip Why SVMs overfit less than you would expect
Whatever the kernel, there are at most R real parameters (the αs), and most are 0. Asking for a small w·w is the same idea as ridge regression's penalty and weight decay in neural networks: it smooths the boundary.
:::

::: warning Notation: the slides switch sign
Moore's slides write the classifier as sign(w·x − **b**) but the planes as w·x + **b** = ±1. Use **w·x + b** throughout your answer and say so.
:::

## 3. Naive Bayes {#naive-bayes}

**Bayes' theorem:** $P(c \mid x) = \dfrac{P(x \mid c)\,P(c)}{P(x)}$: the probability of class c after seeing the features x.

**The naive assumption:** the features are **independent of each other given the class**, so $P(x_1, x_2, \dots \mid c) = P(x_1 \mid c)\,P(x_2 \mid c)\cdots$. Then pick the class with the largest

$$ P(c)\,\prod_i P(x_i \mid c). $$

The denominator P(x) is the same for every class, so it can be skipped when you only need the winner (divide by the sum of the scores if you want a real probability).

<!--@include: @/../code/dsml/notes/u4b.out#nb-->

::: danger The zero-frequency problem
If a feature value never occurs with a class in training, its estimate is 0, and the whole product is 0 whatever the other features say. **Laplace smoothing** adds 1 to every count: $P(x_i = v \mid c) = \dfrac{\text{count} + 1}{n_c + k}$, where k is the number of values the feature can take. See [spring 2025 Q4a](../papers/endsem-2025#q4a), where two classes score exactly 0.
:::

**Continuous features** (Gaussian Naive Bayes): assume each feature is normal within each class and use the density $\frac{1}{\sqrt{2\pi}\sigma_c}e^{-(x - \mu_c)^2/2\sigma_c^2}$ in place of a count.

**Strengths:** very fast to train (one pass of counting) and to predict; works with little data; handles many features (spam filters, text classification); not hurt by irrelevant features much. **Limitations** ([autumn 2024 Q4d](../papers/endsem-2024#q4d)): the independence assumption is rarely true, so correlated features are double-counted; the zero-frequency problem; its probability estimates are poorly calibrated (good for ranking classes, poor as real probabilities); continuous features need an assumed distribution.

## 4. Decision trees {#decision-trees}

A tree of questions: each **internal node** tests one attribute, each **branch** is an outcome of the test, each **leaf** is a class. To classify, start at the root and follow the answers. It is an **eager** learner, and very **interpretable**: every path is an IF–THEN rule.

**ID3, the algorithm behind the papers' questions:**
1. Compute the entropy of the current set.
2. For each attribute, split the set by its values and compute the **information gain**.
3. Put the attribute with the **highest gain** at this node.
4. Repeat on each branch with the remaining attributes, until a branch is **pure** (one class), no attributes are left (use the majority class), or no examples are left.

$$ H(S) = -\sum_c p_c \log_2 p_c, \qquad \text{Gain}(S, A) = H(S) - \sum_{v} \frac{|S_v|}{|S|}\,H(S_v) $$

Entropy is 0 for a pure set and 1 for a 50/50 two-class set. Information gain is how much a split reduces it. **Gini impurity** $1 - \sum_c p_c^2$ is the alternative used by CART (scikit-learn's default); it usually picks the same attribute. **Gain ratio** (C4.5) divides the gain by the split's own entropy, so attributes with many values (like an ID column) are not unfairly favoured.

### Worked example

<!--@include: @/../code/dsml/notes/u4b.out#tree-->

### The Play Golf tree (autumn 2024 Q4c)

<!--@include: @/../code/dsml/notes/u4b.out#golftree-->

The root calculation (Outlook gain 0.247, Humidity 0.152, Wind 0.048, Temperature 0.029) is worked in full on the [paper page](../papers/endsem-2024#q4c).

::: tip Calculator trick for log₂
Most calculators have only ln and log: $\log_2 x = \dfrac{\ln x}{\ln 2} = \dfrac{\ln x}{0.6931}$. Remember these to save time: H(1/2, 1/2) = 1, H(1/4, 3/4) = 0.8113, H(1/3, 2/3) = 0.9183, H(2/5, 3/5) = 0.9710.
:::

**Overfitting and pruning.** A fully grown tree fits the training data perfectly, noise included. Limit it by **pre-pruning** (stop early: maximum depth, minimum samples per leaf, minimum gain) or **post-pruning** (grow fully, then cut back branches that do not help on validation data). **Continuous attributes** are split by a threshold ("Age ≤ 30?"), choosing the cut with the best gain. **Categorical attributes**: trees split on thresholds, so label encoding is usually fine for them ([spring 2025 Q1c](../papers/endsem-2025#q1c)).

**Strengths:** interpretable rules; no scaling needed; handles numeric and categorical data; implicit feature selection (the slides' golf example: the tree never used Temperature). **Weaknesses:** overfits if unpruned; unstable (a small change in the data can change the whole tree); greedy, so not guaranteed to find the best tree.

## 5. Choosing between them {#compare}

| | KNN | Logistic regression | SVM | Naive Bayes | Decision tree |
|---|---|---|---|---|---|
| Learner | lazy | eager | eager | eager | eager |
| Training cost | none | iterative | QP (slow for huge n) | one counting pass | greedy splitting |
| Prediction cost | **high** (all points) | tiny | depends on support vectors | tiny | tiny (one path) |
| Needs scaling | **yes** | yes (for gradient descent) | **yes** | no | no |
| Non-linear boundaries | yes | no (linear in z) | yes, with kernels | limited | yes |
| Interpretable | somewhat | weights and odds ratios | hard with kernels | probabilities | **very** (rules) |
| Outputs a probability | vote share | **yes** | no (a margin) | yes (poorly calibrated) | leaf class share |

## Traps and the 5-minute checklist {#traps}

| # | Trap | Correct version |
|---|---|---|
| 1 | KNN learns weights during `fit` | it only stores the data (lazy) |
| 2 | k = 1 is the most accurate | it overfits (memorises); pick k by cross-validation |
| 3 | Even k for two classes | odd k, so votes cannot tie |
| 4 | KNN without scaling | the largest-unit feature dominates every distance |
| 5 | SVM margin = 1/‖w‖ | the full margin is **2/‖w‖** |
| 6 | Every training point shapes the SVM | only the support vectors do |
| 7 | Linear SVM for interaction patterns | needs a kernel (RBF or polynomial) |
| 8 | Naive Bayes: a 0 probability is fine | it zeroes the whole product; use Laplace smoothing |
| 9 | Entropy with log base 10 or e | base **2** (convert: ln x / ln 2) |
| 10 | Information gain = weighted child entropy | gain = parent − weighted children |
| 11 | Unweighted average of child entropies | weight each child by its share of the rows |
| 12 | A deeper tree is always better | it overfits; prune |

**The checklist:**
1. KNN: distance table (all points) → sort → take k → vote → state the class. Mention scaling.
2. Decision tree: parent entropy → one small table per attribute (counts, entropy, weighted) → gains → pick the largest → say why (purity).
3. Naive Bayes: the count table per class → multiply P(c) × each P(feature ∣ c) → compare → watch for zeros.
4. SVM: margin = 2/‖w‖; a point's side = sign of w·x + b; support vectors give ±1.

## Quick check {#quick-check}

<Drill n="1" tag="KNN">

Why is KNN called a lazy learner?

<Mcq :options="['It uses few features', 'It builds no model during training; all work happens at prediction time', 'It converges slowly', 'It ignores distant points']" answer="b">

`fit()` only stores the training data. Every prediction then computes the distance to all of it, which is why prediction is the slow part.

</Mcq>

</Drill>

<Drill n="2" tag="KNN">

<FillIn q="Manhattan distance between (2, 5) and (6, 2)?" answer="7">

∣2 − 6∣ + ∣5 − 2∣ = 4 + 3 = 7. The Euclidean distance would be √(16 + 9) = 5.

</FillIn>

</Drill>

<Drill n="3" tag="KNN">

As k grows very large, a KNN classifier…

<Mcq :options="['overfits more', 'tends to predict the majority class everywhere', 'becomes a decision tree', 'needs no scaling']" answer="b">

With huge k the vote is taken over most of the data, so the majority class always wins: high bias, underfitting.

</Mcq>

</Drill>

<Drill n="4" tag="SVM">

<FillIn q="An SVM has w = (6, 8). What is the margin width 2/‖w‖?" answer="0.2|.2|1/5">

‖w‖ = √(36 + 64) = 10, so the margin is 2/10 = 0.2.

</FillIn>

</Drill>

<Drill n="5" tag="SVM">

What is the kernel trick?

<Mcq :options="['Removing outliers before training', 'Computing dot products in a high-dimensional feature space without building the features', 'Choosing C by cross-validation', 'Training one SVM per class']" answer="b">

K(a, b) equals φ(a)·φ(b), computed directly from a and b. Since the SVM only needs dot products, it works in the big space for the price of a small one.

</Mcq>

</Drill>

<Drill n="6" tag="Naive Bayes">

What does the "naive" in Naive Bayes refer to?

<Mcq :options="['It uses no training data', 'It assumes the features are independent given the class', 'It ignores the class prior', 'It only handles two classes']" answer="b">

That assumption lets the joint likelihood factor into a product of one-feature probabilities. It is rarely exactly true, which is its main limitation.

</Mcq>

</Drill>

<Drill n="7" tag="Naive Bayes">

<FillIn q="P(c) = 0.4, P(x₁ | c) = 0.5, P(x₂ | c) = 0.25. What is the Naive Bayes score for c?" answer="0.05|.05|1/20">

0.4 × 0.5 × 0.25 = 0.05. Compare it with the other classes' scores; the largest wins.

</FillIn>

</Drill>

<Drill n="8" tag="Decision tree">

<FillIn q="A node has 4 Yes and 4 No examples. What is its entropy?" answer="1|1.0">

H = −(1/2)log₂(1/2) − (1/2)log₂(1/2) = 1: the maximum for two classes.

</FillIn>

</Drill>

<Drill n="9" tag="Decision tree">

A split sends 6 rows (entropy 0) and 4 rows (entropy 1) from a parent with entropy 0.971. What is the information gain?

<Mcq :options="['0.571', '0.471', '0.971', '0.4']" answer="a">

Weighted children = 6/10 × 0 + 4/10 × 1 = 0.4; gain = 0.971 − 0.4 = 0.571.

</Mcq>

</Drill>

<Drill n="10" tag="Comparison">

Which classifier needs no feature scaling?

<Mcq :options="['KNN', 'SVM with an RBF kernel', 'Decision tree', 'Logistic regression trained by gradient descent']" answer="c">

A tree splits one feature at a time on a threshold, so units do not matter. KNN and RBF-SVM use distances; gradient descent behaves badly on unscaled features.

</Mcq>

</Drill>
