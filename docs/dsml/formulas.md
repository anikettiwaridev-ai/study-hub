---
title: Formula sheet
---

# Formula sheet

Every formula the Units 1–4 papers need, in one place. Symbols: n = number of examples, $\bar x$ = mean of x, $\hat y$ = prediction, α (or η, γ) = learning rate.

## Statistics and correlation (Unit 1) {#statistics}

| Quantity | Formula |
|---|---|
| Mean | $\bar x = \dfrac{1}{n}\sum x_i$ |
| Population / sample standard deviation | $\sigma = \sqrt{\dfrac{\sum (x - \bar x)^2}{n}}$, $\quad s = \sqrt{\dfrac{\sum (x - \bar x)^2}{n - 1}}$ |
| Covariance (sample) | $\text{cov}(x, y) = \dfrac{\sum (x - \bar x)(y - \bar y)}{n - 1}$ |
| Pearson correlation | $r = \dfrac{\sum (x - \bar x)(y - \bar y)}{\sqrt{\sum (x - \bar x)^2\,\sum (y - \bar y)^2}}$, $\ -1 \le r \le 1$ |
| Dot product | $u \cdot v = \sum u_i v_i = \lVert u\rVert\,\lVert v\rVert\cos\theta$ |
| Cross product (3-D) | $u \times v = (u_2v_3 - u_3v_2,\ u_3v_1 - u_1v_3,\ u_1v_2 - u_2v_1)$ |
| 2 × 2 determinant and inverse | $\det = ad - bc$, $\quad \begin{bmatrix} a & b \\ c & d \end{bmatrix}^{-1} = \dfrac{1}{ad - bc}\begin{bmatrix} d & -b \\ -c & a \end{bmatrix}$ |
| Eigenvalues (2 × 2) | $\lambda^2 - (\text{trace})\lambda + \det = 0$; $\ \lambda_1 + \lambda_2 = \text{trace}$, $\ \lambda_1\lambda_2 = \det$ |
| Matrix product shape | (m × n)(n × p) = m × p |

## Preprocessing (Unit 2) {#preprocessing}

| Quantity | Formula |
|---|---|
| Min-max to [0, 1] | $x' = \dfrac{x - \min}{\max - \min}$ |
| Min-max to [a, b] | $x' = a + \dfrac{(x - \min)(b - a)}{\max - \min}$ |
| Z-score (standardisation) | $z = \dfrac{x - \mu}{\sigma}$ (mean 0, sd 1, unbounded) |
| Mean normalisation | $x' = \dfrac{x - \mu}{\max - \min}$ |
| L1 / L2 normalisation (per row) | $x_i / \sum \lvert x_j\rvert$ $\ /\ $ $x_i / \sqrt{\sum x_j^2}$ |
| IQR outlier fences | below $Q_1 - 1.5\,\text{IQR}$ or above $Q_3 + 1.5\,\text{IQR}$, $\ \text{IQR} = Q_3 - Q_1$ |
| Z-score outlier rule | $\lvert z\rvert > 3$ (or 2) |
| Equal-width bin size | (max − min) / number of bins |
| Encoding columns, N categories | label 1, one-hot N, dummy N − 1 |

## Evaluation (Unit 3) {#evaluation}

| Quantity | Formula |
|---|---|
| SSE (RSS), MSE, RMSE | $\sum (y - \hat y)^2$, $\ \text{SSE}/n$, $\ \sqrt{\text{MSE}}$ |
| TSS, ESS | $\sum (y - \bar y)^2$, $\ \sum (\hat y - \bar y)^2$; TSS = ESS + RSS |
| R² | $1 - \dfrac{\text{SSE}}{\text{TSS}} = \dfrac{\text{ESS}}{\text{TSS}}$ |
| Adjusted R² (p features) | $1 - (1 - R^2)\dfrac{n - 1}{n - p - 1}$ |
| Accuracy | $\dfrac{TP + TN}{TP + TN + FP + FN}$ |
| Precision | $\dfrac{TP}{TP + FP}$ |
| Recall = sensitivity = TPR | $\dfrac{TP}{TP + FN}$ |
| Specificity = TNR | $\dfrac{TN}{TN + FP}$ |
| FPR = 1 − specificity | $\dfrac{FP}{FP + TN}$ |
| FNR = 1 − recall | $\dfrac{FN}{FN + TP}$ |
| F1 | $\dfrac{2PR}{P + R} = \dfrac{2\,TP}{2\,TP + FP + FN}$ |
| AUC | area under (FPR, TPR) points by trapezoids $= \dfrac{\#\{\text{positive scored above negative}\}}{\#\text{pos} \times \#\text{neg}}$ |
| k-fold on n | N1 = k models; train $\dfrac{(k - 1)n}{k}$; test $\dfrac{n}{k}$. LOOCV: k = n |
| LMS (Mitchell) | $w_i \leftarrow w_i + c\,x_i\,(V_{\text{train}} - \hat V)$ |
| Q-learning | $\hat Q(s, a) \leftarrow r + \gamma \max_{a'} \hat Q(s', a')$ |
| Discounted return | $r_t + \gamma r_{t+1} + \gamma^2 r_{t+2} + \dots$ |

## Regression and gradient descent (Unit 4A) {#regression}

| Quantity | Formula |
|---|---|
| Least-squares slope | $a = \dfrac{n\sum xy - \sum x\sum y}{n\sum x^2 - (\sum x)^2} = \dfrac{\sum (x - \bar x)(y - \bar y)}{\sum (x - \bar x)^2}$ |
| Intercept | $b = \bar y - a\bar x$ |
| Normal equation | $\beta = (X^TX)^{-1}X^Ty$ |
| Ridge | minimise $\sum (y - \hat y)^2 + \lambda\sum w_j^2$; $\ w = (X^TX + \lambda I)^{-1}X^Ty$ |
| Gradient-descent update | $\theta_j \leftarrow \theta_j - \alpha\,\dfrac{\partial J}{\partial \theta_j}$ (all from the old values) |
| MSE gradient, $J = \frac{1}{n}\sum(\hat y - y)^2$ | $\dfrac{\partial J}{\partial \theta_j} = \dfrac{2}{n}\sum (\hat y - y)\,x_j$, $\ x_0 = 1$ |
| Same with $J = \frac{1}{2n}\sum(\hat y - y)^2$ | $\dfrac{\partial J}{\partial \theta_j} = \dfrac{1}{n}\sum (\hat y - y)\,x_j$ |
| Sigmoid | $\sigma(z) = \dfrac{1}{1 + e^{-z}}$, $\ z = \theta_0 + \theta_1x_1 + \dots$ |
| Odds, logit | odds = $\dfrac{p}{1 - p}$, $\ \ln(\text{odds}) = z$ |
| Odds ratio per unit of $x_1$ | $e^{\theta_1}$; over c units $e^{c\theta_1}$ |
| Log loss | $J = -\dfrac{1}{m}\sum\big[y\ln p + (1 - y)\ln(1 - p)\big]$ |
| Logistic gradient | $\dfrac{\partial J}{\partial w_j} = \dfrac{1}{m}\sum (p - y)\,x_j$, $\ \dfrac{\partial J}{\partial b} = \dfrac{1}{m}\sum (p - y)$ |

## Classifiers (Unit 4B) {#classifiers}

| Quantity | Formula |
|---|---|
| Euclidean | $\sqrt{\sum (p_i - q_i)^2}$ |
| Manhattan | $\sum \lvert p_i - q_i\rvert$ |
| Minkowski | $\left(\sum \lvert p_i - q_i\rvert^r\right)^{1/r}$ (r = 1 Manhattan, r = 2 Euclidean) |
| Cosine similarity | $\dfrac{p \cdot q}{\lVert p\rVert\,\lVert q\rVert}$ |
| Weighted KNN vote | $w = 1/d^2$ |
| k rule of thumb | $k \approx \sqrt{n}$, odd |
| SVM boundary, margin planes | $w \cdot x + b = 0$, $\ w \cdot x + b = \pm 1$ |
| SVM margin | $\dfrac{2}{\lVert w\rVert}$ |
| SVM training (hard margin) | minimise $\tfrac{1}{2}w \cdot w$ s.t. $y_k(w \cdot x_k + b) \ge 1$ |
| Soft margin | minimise $\tfrac{1}{2}w \cdot w + C\sum \varepsilon_k$ s.t. $y_k(w \cdot x_k + b) \ge 1 - \varepsilon_k$, $\varepsilon_k \ge 0$ |
| Kernels | polynomial $(a \cdot b + 1)^d$; RBF $\exp\!\left(-\dfrac{\lVert a - b\rVert^2}{2\sigma^2}\right)$; sigmoid $\tanh(\kappa\,a\cdot b - \delta)$ |
| Bayes' theorem | $P(c \mid x) = \dfrac{P(x \mid c)\,P(c)}{P(x)}$ |
| Naive Bayes score | $P(c)\prod_i P(x_i \mid c)$ |
| Laplace smoothing | $P(x_i = v \mid c) = \dfrac{\text{count} + 1}{n_c + k}$ (k = number of values) |
| Entropy | $H = -\sum_c p_c\log_2 p_c$; $\ \log_2 x = \ln x / \ln 2$ |
| Information gain | $H(S) - \sum_v \dfrac{\lvert S_v\rvert}{\lvert S\rvert}H(S_v)$ |
| Gini impurity | $1 - \sum_c p_c^2$ |

## Numbers worth remembering {#numbers}

| | |
|---|---|
| σ(0), σ(±1), σ(±2), σ(±3) | 0.5, 0.731 / 0.269, 0.881 / 0.119, 0.953 / 0.047 |
| e⁻¹, e⁻², ln 2 | 0.3679, 0.1353, 0.6931 |
| Entropy of (1/2, 1/2), (1/4, 3/4), (1/3, 2/3), (2/5, 3/5) | 1, 0.8113, 0.9183, 0.9710 |
| AUC scale (slides) | ≥ 0.9 excellent · 0.8–0.9 considerable · 0.7–0.8 fair · 0.6–0.7 poor · 0.5–0.6 fail |
