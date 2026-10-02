---
title: Unit 4A · Regression and gradient descent
---

# Unit 4A · Regression and gradient descent

Fitting a line by least squares, adding more inputs, keeping the weights in check with ridge, finding the weights by **gradient descent** when there is no formula, and bending the line into a probability with **logistic regression**.

::: info How this unit is examined
- **Mid-semester:** **gradient descent by hand was on both papers**: one iteration of w and b ([Sep 2025 Q2](../papers/mst-2025#q2)), two iterations of θ₀, θ₁, θ₂ ([spring 2025 Q1](../papers/mst-2025-spring#q1)). A logistic-regression probability ([spring 2025 Q2](../papers/mst-2025-spring#q2)).
- **End-semester:** gradient descent on a 3-variable function and why non-convex functions break it (6), ridge weights with λ = 10 (6), a least-squares line and a prediction (5).
- **Lab:** [Assignment 3](../assignments/a3) (linear regression) and [Assignment 5](../assignments/a5) (logistic regression).
:::

## Read this first: the unit on one screen {#toolkit}

| Topic | The one thing to remember |
|---|---|
| Least squares | $a = \dfrac{n\sum xy - \sum x\sum y}{n\sum x^2 - (\sum x)^2}$, $b = \bar y - a\bar x$ |
| Multiple regression | $y = \theta_0 + \theta_1x_1 + \dots$; closed form $\theta = (X^TX)^{-1}X^Ty$ |
| Ridge | add $\lambda\sum w^2$; closed form $(X^TX + \lambda I)^{-1}X^Ty$; weights shrink, never to 0 |
| Gradient descent | $\theta \leftarrow \theta - \alpha \dfrac{\partial J}{\partial \theta}$, all parameters from the OLD values |
| MSE gradient | $\dfrac{\partial J}{\partial \theta_j} = \dfrac{2}{n}\sum(\hat y - y)x_j$, with $x_0 = 1$ for the intercept |
| Learning rate | too small: slow; too large: overshoots and can diverge |
| Sigmoid | $\sigma(z) = \dfrac{1}{1 + e^{-z}}$; σ(0) = 0.5 |
| Odds, logit | odds = p/(1 − p); ln(odds) = z, so $e^{\theta_1}$ is the odds ratio per unit of $x_1$ |
| Logistic gradient | $\dfrac{\partial J}{\partial w_j} = \dfrac{1}{m}\sum(p - y)x_j$ |

## 1. Regression basics {#regression}

**Regression** models the relationship between a **dependent** (target) variable and one or more **independent** (predictor) variables: how the target changes when one predictor changes and the others are held fixed. It predicts a **continuous** value: sales, salary, temperature.

| Term | Meaning |
|---|---|
| Dependent variable | what we predict (the target) |
| Independent variable | what we predict from (the predictor) |
| **Outlier** | an observation far from the rest; it can drag the line, so it may need to be handled |
| **Multicollinearity** | independent variables strongly correlated with each other; it "creates problems while ranking the most affecting variable", because the model cannot tell which one deserves the credit |
| Overfitting / underfitting | good on training but not test / poor even on training ([Unit 3](./unit-3#bias-variance)) |

**Types on the slides:** linear, logistic, polynomial, support vector, decision tree and random forest regression. **Uses:** trends and sales forecasts, salary forecasting, real-estate prices, ETAs in traffic, and finding the most and least important factors.

## 2. Simple linear regression by least squares {#simple-lr}

One input x and one output y: **ŷ = ax + b**, where a is the slope (change in y per unit of x) and b the intercept (y at x = 0). For each point the **residual** is y − ŷ. **Least squares** picks the a and b that make the SSE, Σ(y − ŷ)², as small as possible. There is an exact formula, so no iterations are needed:

$$ a = \frac{n\sum xy - \sum x\sum y}{n\sum x^2 - (\sum x)^2} = \frac{\sum (x - \bar x)(y - \bar y)}{\sum (x - \bar x)^2}, \qquad b = \bar y - a\,\bar x $$

### Worked example: the slides' seven points

<!--@include: @/../code/dsml/notes/u4a.out#ls-->

::: tip Shortcut for years
When x is a run of years, code it as u = year − middle year (−2, −1, 0, 1, 2). Then Σu = 0, so a = Σuy/Σu² and b = ȳ. Shifting x never changes the slope. [Spring 2025 end-semester Q1a](../papers/endsem-2025#q1a) is solved this way.
:::

**In the lab** ([Assignment 3](../assignments/a3)): `LinearRegression().fit(X_train, y_train)` computes exactly this formula in one step (there is no `n_iter_`, because nothing iterates). On Salary_Data.csv it found slope 9423.82 and intercept 25321.58: each extra year of experience adds about ₹9,424.

## 3. Multiple linear regression {#multiple-lr}

Several inputs: $\hat y = \theta_0 + \theta_1x_1 + \theta_2x_2 + \dots + \theta_nx_n$. Each θ is the change in y per unit of that feature **with the other features held fixed**.

In matrix form $Y = X\beta + \varepsilon$, where X has a column of 1s for the intercept. Least squares has the **normal equation**:

$$ X^TX\,\beta = X^TY \quad\Rightarrow\quad \beta = (X^TX)^{-1}X^TY. $$

::: danger Multicollinearity breaks the formula
If one feature is a combination of others, the columns of X are dependent, $\det(X^TX) = 0$, and the inverse does not exist: there are infinitely many equally good β. In the spring 2025 mid-semester data, Education is always Experience + 1, so the individual θ₁ and θ₂ mean nothing (only their sum does). Ridge regression, or dropping one of the features, fixes it.
:::

**R² never goes down when you add a feature**, even a useless one, because least squares can always set its weight to 0. That is why adjusted R² exists: $R^2_{\text{adj}} = 1 - (1 - R^2)\dfrac{n - 1}{n - p - 1}$ for p features (not on your slides; a common follow-up).

## 4. Ridge regression: regularisation {#ridge}

Ridge adds a penalty on large weights to the least-squares cost:

$$ J(w) = \sum (y - \hat y)^2 + \lambda\sum_j w_j^2, \qquad w = (X^TX + \lambda I)^{-1}X^Ty. $$

- **λ = 0** is ordinary least squares; larger λ shrinks the weights more.
- Adding λI makes $X^TX + \lambda I$ **always invertible**, so ridge gives a unique answer even with multicollinearity.
- The weights get small but **never exactly 0**. (**Lasso** uses $\lambda\sum|w_j|$, the L1 penalty, and can set weights exactly to 0, which selects features.)
- It is the "regularisation (L1/L2)" that the overfitting slides list: a little more bias, much less variance.

<!--@include: @/../code/dsml/notes/u4a.out#ridge-->

The full 3 × 3 version, solved by elimination, is [autumn 2024 Q4a](../papers/endsem-2024#q4a).

## 5. Gradient descent {#gradient-descent}

Gradient descent is an **iterative** way to find the parameters that minimise a cost function. The slides' picture: you are in a valley, blindfolded. Feel which way the ground slopes (the **gradient**, which points uphill: the direction of steepest increase), step the other way, and repeat.

| Concept | Meaning |
|---|---|
| **Cost (loss) function** | how wrong the model is: MSE for regression, log loss for logistic regression |
| **Parameters** | what is being adjusted: weights and biases, regression coefficients |
| **Gradient** | the vector of partial derivatives; points to steepest **increase** |
| **Learning rate** (α or η) | the step size: a hyperparameter you choose |
| **Convergence** | further steps no longer lower the cost meaningfully |

**The algorithm:** (1) start from some θ (zeros or random); (2) predict with the current θ; (3) compute the cost; (4) compute the gradient $\partial J/\partial \theta_j$ for every parameter; (5) update **all** of them at once, $\theta_j \leftarrow \theta_j - \alpha\,\partial J/\partial\theta_j$; (6) repeat until convergence.

### The slides' example: f(w) = (w − 3)²

<!--@include: @/../code/dsml/notes/u4a.out#gd1-->

### Choosing the learning rate

<!--@include: @/../code/dsml/notes/u4a.out#lr-cases-->

| Learning rate | What happens |
|---|---|
| **Too small** | tiny steps; converges very slowly; training takes much longer |
| **Too large** | overshoots the minimum; oscillates and may **diverge** (the cost grows every step) |
| **Right** | big steps far away, small steps near the bottom (the gradient shrinks by itself) |

::: warning Correction: overshooting is not the "exploding gradient problem"
The slides call a too-large learning rate "the exploding gradient problem". It is **divergence**: the steps are too big. Exploding gradients is a deep-network problem where the gradients themselves become huge during backpropagation. The same slide's fix "weights regularization: initialization of weights…" is **weight initialisation**, not regularisation. The other fixes it lists (ReLU against vanishing gradients, gradient clipping against exploding ones, batch normalisation) are about deep networks.
:::

### Three kinds of gradient descent

| Variant | Gradient computed from | Trade-off |
|---|---|---|
| **Batch** | the whole training set, every step | stable; guaranteed to reach the global minimum of a **convex** cost; slow on big data |
| **Stochastic (SGD)** | **one** random example per step | fast, but the path oscillates (the LMS rule in [Unit 3](./unit-3#what-is-ml) is this) |
| **Mini-batch** | a small batch (say 32 or 64) per step | the balance between speed and stability; standard for neural networks |

### Linear regression by gradient descent

For $\hat y = wx + b$ and $J = \frac{1}{n}\sum(\hat y - y)^2$:

$$ \frac{\partial J}{\partial w} = \frac{2}{n}\sum (\hat y_i - y_i)\,x_i, \qquad \frac{\partial J}{\partial b} = \frac{2}{n}\sum (\hat y_i - y_i), \qquad w \leftarrow w - \alpha\frac{\partial J}{\partial w},\ \ b \leftarrow b - \alpha\frac{\partial J}{\partial b}. $$

The papers sometimes write the same thing with $(y - \hat y)$ and a minus sign in front: $-\frac{2}{n}\sum x(y - \hat y)$. It is identical. Some books use $J = \frac{1}{2n}\sum(\cdot)^2$, which removes the 2 and halves every step; **state which one you use**.

<!--@include: @/../code/dsml/notes/u4a.out#gd-lr-->

::: danger Where marks go in a gradient-descent question
1. Write the cost and the update rule first, then the gradient formula.
2. Draw the table: x, y, ŷ, error, error × x, with the sums.
3. Compute **every** gradient from the **old** parameters, then update them all.
4. If the paper gives no α or starting values, assume them in your first line ("assume suitably").
5. Optional but impressive: show the cost went down.
:::

### Gradient descent fails on non-convex functions {#non-convex}

<!--@include: @/../code/dsml/notes/u4a.out#nonconvex-->

A **convex** cost (one bowl, like MSE for linear regression) has a single place where the slope is zero: the global minimum. A **non-convex** cost has several: **local minima**, local maxima and **saddle points**, where gradient descent stops or crawls. The result then depends on the starting point. (Neural networks are trained this way anyway, with tricks such as momentum and random restarts.)

**Closed form or gradient descent?** Least squares has an exact formula, so `LinearRegression` uses it. Gradient descent exists for models with **no** formula (logistic regression, neural networks) and for data too large to invert $X^TX$. **Scale the features first**: with features on wildly different scales, one learning rate is too big for one feature and too small for another.

## 6. Logistic regression {#logistic}

A **classification** algorithm despite its name: it predicts the probability that y = 1 (spam, purchase, survival).

**Why not a straight line?** Extend the line a little and it predicts "probabilities" below 0 or above 1. So the linear score $z = \theta_0 + \theta_1x_1 + \dots$ is passed through the **sigmoid**, which squashes any real number into (0, 1):

$$ p = \sigma(z) = \frac{1}{1 + e^{-z}}. $$

<!--@include: @/../code/dsml/notes/u4a.out#sigmoid-->

**Class** = 1 if p ≥ threshold (usually 0.5), else 0. Because σ(0) = 0.5, the decision boundary is where z = 0, a straight line (or plane) in feature space.

### Odds, logit and the odds ratio

$$ \text{odds} = \frac{p}{1 - p}, \qquad \text{logit}(p) = \ln\frac{p}{1 - p} = z = \theta_0 + \theta_1x_1 + \dots $$

**Logistic regression is linear regression on the log-odds.** Add 1 to $x_1$ and the log-odds go up by $\theta_1$, so the odds are **multiplied by $e^{\theta_1}$**: that is the **odds ratio**. It is a multiplier on the odds, not a change in probability.

<!--@include: @/../code/dsml/notes/u4a.out#odds-->

::: warning Correction: a slip on the LogReg slides
The delinquency slide writes 1 − 0.1001 as 0.8889. It is **0.8999**; the slide's final odds (0.111) are right anyway.
:::

### Fitting it: log loss and gradient descent

There is no closed form, so the weights are found iteratively by minimising the **log loss** (binary cross-entropy):

$$ J(w, b) = -\frac{1}{m}\sum\Big[y\log p + (1 - y)\log(1 - p)\Big], \qquad \frac{\partial J}{\partial w_j} = \frac{1}{m}\sum (p - y)\,x_j, \qquad \frac{\partial J}{\partial b} = \frac{1}{m}\sum (p - y). $$

<!--@include: @/../code/dsml/notes/u4a.out#logistic-gd-->

**Three types:** binary (pass/fail), multinomial (cat/dog/lion), ordinal (low/medium/high).

**In the lab** ([Assignment 5](../assignments/a5)): `LogisticRegression().fit` really iterates (with lbfgs, a smarter relative of gradient descent), and `n_iter_` reports how many steps it took. `predict_proba` gives p; `predict` is just p ≥ 0.5. Scaling the features first (StandardScaler) matters here, for the reason above.

## Traps and the 5-minute checklist {#traps}

| # | Trap | Correct version |
|---|---|---|
| 1 | Subtracting a negative gradient makes θ smaller | θ − α(−g) = θ + αg: it goes **up** |
| 2 | Updating w, then using the new w to compute b's gradient | compute all gradients from the old values, then update together |
| 3 | Mixing the 2/n and 1/(2n) conventions mid-answer | pick one, state it, stick to it |
| 4 | A bigger learning rate is always faster | past a point it overshoots and diverges |
| 5 | Gradient descent always finds the best minimum | only for convex costs; otherwise local minima and saddles |
| 6 | Logistic regression is a regression model | it is a classifier; it outputs a probability |
| 7 | e^θ₁ is the change in probability | it is the **odds ratio** per unit of x₁ |
| 8 | Ridge sets useless weights to 0 | ridge shrinks; **lasso** can set to 0 |
| 9 | Adding features raised R², so the model improved | training R² always rises; check adjusted R² or test error |
| 10 | Forgetting the intercept column $x_0 = 1$ | the intercept's gradient uses Σ(ŷ − y) with no x |

**The checklist for a gradient-descent question:** state the assumptions → write the update rule → table of x, y, ŷ, error, error × x → gradients → updates → (cost check) → box the answer.

## Quick check {#quick-check}

<Drill n="1" tag="Least squares">

For points with Σx = 10, Σy = 30, Σxy = 80, Σx² = 30 and n = 5, what is the slope a?

<Mcq :options="['1', '2', '3', '0.5']" answer="b">

a = (5·80 − 10·30)/(5·30 − 10²) = (400 − 300)/(150 − 100) = 100/50 = **2**. Then b = ȳ − a·x̄ = 6 − 2 × 2 = 2, so the line is ŷ = 2x + 2.

</Mcq>

</Drill>

<Drill n="2" tag="Gradient descent">

<FillIn q="Minimise f(w) = (w − 5)² from w = 0 with α = 0.1. What is w after ONE step?" answer="1|1.0">

f′(w) = 2(w − 5) = −10 at w = 0, so w ← 0 − 0.1 × (−10) = 1.

</FillIn>

</Drill>

<Drill n="3" tag="Gradient descent">

The cost grows bigger at every iteration. What is the most likely cause?

<Mcq :options="['The learning rate is too small', 'The learning rate is too large', 'The data is not scaled to [0, 1]', 'The model is underfitting']" answer="b">

Each step overshoots the minimum by more than the last: divergence. Lower α.

</Mcq>

</Drill>

<Drill n="4" tag="Gradient descent">

Which variant computes the gradient from a single random example per step?

<Mcq :options="['Batch', 'Stochastic', 'Mini-batch', 'Newton']" answer="b">

Stochastic gradient descent: fast but noisy. Batch uses all the data; mini-batch a small group.

</Mcq>

</Drill>

<Drill n="5" tag="Logistic">

<FillIn q="z = 0 for a customer. What probability does logistic regression give?" answer="0.5|.5|1/2">

σ(0) = 1/(1 + e⁰) = 1/2. The decision boundary is exactly where z = 0.

</FillIn>

</Drill>

<Drill n="6" tag="Logistic">

In a fitted model, the coefficient of "hours studied" is 0.7. What does e^0.7 ≈ 2.01 mean?

<Mcq :options="['Each extra hour adds 0.7 to the probability of passing', 'Each extra hour roughly doubles the odds of passing', 'Each extra hour doubles the probability of passing', 'The model is 2.01 times better than chance']" answer="b">

e^θ is the odds ratio: odds are multiplied by about 2 per extra hour. The probability changes by different amounts depending on where you start.

</Mcq>

</Drill>

<Drill n="7" tag="Ridge">

As λ in ridge regression grows very large, the weights…

<Mcq :options="['grow without limit', 'approach 0 but never reach it', 'become exactly 0', 'stay the same']" answer="b">

w = (XᵀX + λI)⁻¹Xᵀy shrinks towards 0 as λ grows. Exactly 0 needs lasso (L1).

</Mcq>

</Drill>

<Drill n="8" tag="Multicollinearity">

Two features are perfectly correlated. What happens to the normal equation?

<Mcq :options="['It still gives a unique answer', 'XᵀX has no inverse, so there is no unique answer', 'It gives negative weights', 'R² becomes negative']" answer="b">

Dependent columns make det(XᵀX) = 0. Ridge (adding λI) or dropping one feature restores a unique solution.

</Mcq>

</Drill>
