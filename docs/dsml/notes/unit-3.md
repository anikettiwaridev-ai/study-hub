---
title: Unit 3 · Machine learning fundamentals
---

# Unit 3 · Machine learning fundamentals

What learning means, the kinds of learning, why models fail (too simple or too complex), and how to **measure** a model honestly: SSE and R² for regression; the confusion matrix, ROC and AUC for classification; cross-validation for both.

::: info How this unit is examined
- **Mid-semester:** an **evaluation calculation** was on both papers: confusion-matrix metrics ([spring 2025 Q3](../papers/mst-2025-spring#q3)) or an ROC table with AUC ([Sep 2025 Q3](../papers/mst-2025#q3)). Cross-validation fold sizes and the effect of k ([spring 2025 Q4](../papers/mst-2025-spring#q4a)).
- **End-semester:** a confusion matrix built from a story (6), LOOCV vs 5-fold (4), which model overfits (5).
- **Theory quiz:** Mitchell's T, P, E; the paradigms; overfitting vs underfitting; which metric when; ROC axes; k-fold sizes.
:::

## Read this first: the unit on one screen {#toolkit}

| Topic | The one thing to remember |
|---|---|
| Learning | improving at task **T**, measured by **P**, with experience **E** (Mitchell) |
| Paradigms | supervised (labels), unsupervised (none), semi-supervised (some), reinforcement (rewards), instance-based (stored cases) |
| Overfitting | great on train, poor on test: **low bias, high variance** |
| Underfitting | poor on both: **high bias, low variance** |
| Regression metrics | SSE = Σ(y − ŷ)²; R² = 1 − SSE/TSS |
| Precision / recall | TP/(TP + **FP**) / TP/(TP + **FN**) |
| F1 | 2PR/(P + R) = 2TP/(2TP + FP + FN) |
| ROC | x = FPR = FP/(FP + TN), y = TPR = recall; one point per threshold |
| AUC | 1 perfect, 0.5 random, below 0.5 worse than random |
| k-fold | k models, each trains on (k − 1)n/k and tests on n/k; k = 10 recommended |

## 1. What machine learning is {#what-is-ml}

**Mitchell's definition** (every slide in the intro deck cites it): a program **learns** from experience **E** with respect to a task **T** and performance measure **P** if its performance at T, as measured by P, improves with E.

| | Task T | Performance P | Experience E |
|---|---|---|---|
| Checkers (the slides) | play checkers | % of games won in a tournament | games played against itself |
| Spam filter | classify email as spam or not | accuracy or F1 on emails | emails already labelled |
| Handwriting | recognise handwritten words | % recognised correctly | a database of labelled images |

P is always a **measurement**; the data belongs to E.

**Other definitions on the slides:** "programming computers to optimise a performance criterion using example data or past experience"; "learning general models from data of particular examples". **Role of statistics:** inference from a sample. **Role of computer science:** efficient algorithms to solve the optimisation, and to represent and evaluate the model.

**When to learn instead of programming** (there is no need to "learn" payroll):
1. human expertise does not exist (navigating on Mars);
2. humans cannot explain their expertise (speech recognition);
3. the solution changes over time (routing in a network);
4. the solution must be adapted to particular cases (personalised recommendations).

**Why ML took off:** better algorithms and theory, a flood of online data, cheap computing power, and a budding industry. **Three niches:** data mining (historical records → better decisions), software too hard to program by hand (ALVINN drove at 70 mph from a 30 × 32 camera image), and self-customising programs (a newsreader that learns your interests).

### Designing a learner: four choices, in order

| Choice | Checkers example |
|---|---|
| 1. Type of training experience | direct or indirect feedback? a teacher or not? is it **representative** of the real goal? (the seed of overfitting) |
| 2. Target function | ChooseMove: Board → Move, or **V: Board → ℝ** (a score for each board) |
| 3. Representation | $\hat V(b) = w_0 + w_1 x_1 + \dots + w_6 x_6$, where the x's count black and red pieces, kings, and threatened pieces |
| 4. Learning algorithm | the **LMS** weight update |

The ideal V is "correct but not operational": computing it means already playing perfectly to the end of the game. So ML never learns V itself, only an approximation **V̂**. The LMS rule: for each training board, $w_i \leftarrow w_i + c \cdot x_i \cdot (V_{\text{train}}(b) - \hat V(b))$ with a small c (say 0.1).

<!--@include: @/../code/dsml/notes/u3.out#lms-->

## 2. Problem types and applications {#problems}

| Problem | Learns | Output | Example algorithm |
|---|---|---|---|
| **Classification** | to classify unseen examples from labelled ones | a **discrete** class | decision trees (the slide's "C5.4" means C4.5) |
| **Regression** | to predict a number from labelled examples ("numeric classification") | a **continuous** value | support vector regression; price of a used car, y = wx + w₀ |
| **Association** | which features occur together (not only input → output) | rules: apples ⇒ cereals | Apriori |
| **Clustering** | natural groupings, no labels | groups | k-means |

**Applications on the slides:** face recognition (pose, lighting, occlusion), character recognition, speech recognition, sensor fusion, **medical diagnosis**, web advertising (will the user click?), **credit scoring** (low vs high risk from income and savings: IF income > θ₁ AND savings > θ₂ THEN low risk), retail baskets ("people who bought milk also bought eggs and bread").

::: tip Classification vs regression
The **output type** decides it, nothing else: a category → classification; a number → regression. Both are supervised. "Logistic regression" is a classifier despite its name.
:::

## 3. Learning paradigms {#paradigms}

| Paradigm | Data | Goal | Example |
|---|---|---|---|
| **Supervised** | inputs **with** correct labels | predict the label of new inputs | classification, regression |
| **Unsupervised** | inputs only; labels unknown | find structure | clustering, association |
| **Semi-supervised** | a few labelled + many unlabelled | a better classifier than the labelled part alone | transductive SVM |
| **Reinforcement** | states and **rewards**, no labels | actions that maximise **cumulative** reward | Q-learning, SARSA; a game agent |
| **Instance-based** | stored specific cases | match a new case to stored ones | k-nearest neighbours |

**The one question that separates them:** does the data come with answers? All of them (supervised), none (unsupervised), some (semi-supervised), or only a delayed reward signal (reinforcement)?

## 4. Reinforcement learning and Q-learning {#rl}

An **agent** observes a **state** s, takes an **action** a, gets a **reward** r and lands in a new state. It must learn a **policy** π: S → A that maximises the discounted return

$$ r_t + \gamma r_{t+1} + \gamma^2 r_{t+2} + \dots, \qquad 0 \le \gamma < 1. $$

What makes it different from supervised learning: **delayed reward** (the agent must work out which earlier action earned it: credit assignment), the chance to **explore**, states that may be only partly observable, and no examples of the form ⟨state, correct action⟩, only ⟨state, action, reward⟩.

**Markov decision process:** the next state and the reward depend only on the current state and action: $s_{t+1} = \delta(s_t, a_t)$, $r_t = r(s_t, a_t)$. The agent need not know δ or r.

**The Q function:** $Q(s, a) = r(s, a) + \gamma V^*(\delta(s, a))$, the value of doing a in s and acting optimally afterwards. Learning Q (instead of V*) lets the agent pick the best action **without knowing δ**: $\pi^*(s) = \arg\max_a Q(s, a)$.

**Q-learning (deterministic world):** start with every $\hat Q(s, a) = 0$; repeatedly choose and execute an action a, receive r, observe the new state s′, and update

$$ \hat Q(s, a) \leftarrow r + \gamma \max_{a'} \hat Q(s', a'). $$

<!--@include: @/../code/dsml/notes/u3.out#qlearn-->

In a nondeterministic world the update is averaged in with a decaying rate: $\hat Q_n \leftarrow (1 - \alpha_n)\hat Q_{n-1} + \alpha_n[r + \gamma \max \hat Q_{n-1}(s', a')]$ with $\alpha_n = 1/(1 + \text{visits}_n(s, a))$. **TD(λ)** blends one-step, two-step, … lookaheads; Tesauro's TD-Gammon learned backgammon this way by playing 1.5 million games against itself.

## 5. Overfitting, underfitting and bias–variance {#bias-variance}

A model is good if it does well on data it has **not** seen.

| | Underfitting | Overfitting |
|---|---|---|
| Train / test | poor / poor | great / poor |
| What happened | too simple: misses real patterns | learned the noise and quirks: memorised |
| Bias / variance | **high bias**, low variance | low bias, **high variance** |
| Causes | model too simple; very high regularisation; weak or missing features; not enough training | model too complex; too many features; too little data; no regularisation |
| Fixes | more complex model; add features (feature engineering); less regularisation; train longer; scale features properly | more training data; simpler model; regularisation (L1/L2); dropout and early stopping (neural networks); clean noisy data |

**Bias** is error from wrong built-in assumptions (the slide: assuming all birds are small and fly, so ostriches are misclassified). **Variance** is error from over-sensitivity to the particular training sample: retrain on slightly different data and the model changes a lot.

<!--@include: @/../code/dsml/notes/u3.out#fitting-->

<!--@include: @/../code/dsml/notes/u3.out#biasvar-->

::: tip Diagnose from two numbers
(1) Is training accuracy high (is it learning)? (2) Is the train–test gap small (does it transfer)? **Big gap → overfitting. Both low → underfitting. Both high, small gap → good.** [Spring 2025 end-semester Q2b](../papers/endsem-2025#q2b) is exactly this, with models at 99/72, 68/68 and 88/85.
:::

## 6. Evaluating regression: SSE, MSE, RMSE and R² {#regression-metrics}

| Quantity | Formula | Meaning |
|---|---|---|
| Residual | y − ŷ | one prediction's error |
| **SSE** (= RSS) | Σ(y − ŷ)² | total squared error; lower is better |
| **MSE**, **RMSE** | SSE/n, √MSE | average squared error; RMSE is back in y's units |
| **TSS** | Σ(y − ȳ)² | total variation: the error of always guessing the mean |
| **ESS** | Σ(ŷ − ȳ)² | the variation the model explains |
| **R²** | 1 − SSE/TSS = ESS/TSS | share of the variation explained (TSS = ESS + RSS for least-squares fits) |

**Why square the errors?** So positive and negative errors cannot cancel, and so big errors count more (an error of 10 costs 100, an error of 2 costs 4). That makes SSE **sensitive to outliers**, which the slides list as both a strength and a limitation. SSE alone is hard to interpret (500 is tiny for house prices and huge for marks), which is what R² fixes.

<!--@include: @/../code/dsml/notes/u3.out#sse-->

::: warning Correction: R² is not always between 0 and 1
The slide's range holds for a least-squares fit with an intercept, measured on its own training data. On new data, a model worse than "always predict the mean" has SSE > TSS, so **R² is negative**. Also, training R² never goes down when you add a feature, even a useless one, which is why **adjusted R²** exists (not on your slides; a common follow-up).
:::

## 7. The confusion matrix and its metrics {#confusion-matrix}

| | Predicted positive | Predicted negative |
|---|---|---|
| **Actual positive** | **TP** (true positive) | **FN** (false negative): **Type II** error |
| **Actual negative** | **FP** (false positive): **Type I** error | **TN** (true negative) |

$$ \text{Accuracy} = \frac{TP + TN}{\text{total}},\quad \text{Precision} = \frac{TP}{TP + FP},\quad \text{Recall} = \frac{TP}{TP + FN},\quad F_1 = \frac{2PR}{P + R},\quad \text{Specificity} = \frac{TN}{TN + FP} $$

<!--@include: @/../code/dsml/notes/u3.out#cm-->

| Use | When |
|---|---|
| **Precision** | false alarms are costly: spam filtering (do not bin a real email), fraud alerts |
| **Recall** | misses are costly: medical diagnosis, security screening |
| **F1** | both matter; it is a **harmonic** mean, so it is low if **either** is low |
| **Specificity** | how well the negatives are cleared |

Type I (FP) hurts **precision**; Type II (FN) hurts **recall**.

::: danger The sklearn layout is upside down
`confusion_matrix(y_test, y_pred)` puts class 0 first: `[[TN, FP], [FN, TP]]`, and `cm.ravel()` returns `tn, fp, fn, tp`. Exam questions use the positive-first layout above. Read the labels, not the positions. In Assignment 5 the matrix printed `[[48 3] [10 19]]`, so TP = 19, not 48.
:::

**More than two classes** (Assignment 6, Iris): the matrix is k × k, rows are actual, columns predicted, the diagonal is correct. Precision and recall are computed **per class** (versicolor precision = 10/12 = 0.83), and the macro average is their plain mean.

## 8. ROC curve and AUC {#roc}

A classifier usually outputs a **probability**, and a **threshold** turns it into a class (default 0.5, but it is a choice). Every threshold gives a different confusion matrix. The **ROC curve** (receiver operating characteristic) plots all of them at once: **x = FPR = FP/(FP + TN) = 1 − specificity**, **y = TPR = recall**. The **AUC** (area under the curve) summarises it in one number: the probability that a random positive is scored higher than a random negative.

**Method:** sort by score, use each score as a threshold (positive if p ≥ t), make the confusion matrix, compute (FPR, TPR), add (0, 0) and (1, 1), join the points, measure the area.

<!--@include: @/../code/dsml/notes/u3.out#roc-->

| AUC (the slides' scale) | Meaning |
|---|---|
| 0.9–1.0 | excellent |
| 0.8–0.9 | considerable |
| 0.7–0.8 | fair |
| 0.6–0.7 | poor |
| 0.5–0.6 | fail |
| 0.5 | the diagonal: **random**, no ability to separate the classes |
| 1.0 | perfect separation (the curve hugs the top-left corner) |
| below 0.5 | **worse than random**: the model ranks backwards (flip its output) |

**Comparing curves:** the curve closer to the top-left is better; with no crossings, the higher AUC wins. **PR curve vs ROC:** use a precision–recall curve when positives are rare and true negatives are plentiful (fraud, rare disease): a big TN count keeps FPR low and makes a mediocre model look good on ROC.

## 9. Cross-validation {#cross-validation}

One train/test split can be lucky or unlucky. Cross-validation evaluates on several different held-out parts and **averages**, giving a more reliable estimate of performance on unseen data. Its main purpose is to detect and prevent **overfitting**.

| Type | How | Strength | Weakness |
|---|---|---|---|
| **Holdout** | train on 50%, test on 50%, once | simple and fast | **high bias**: half the data never trains the model |
| **LOOCV** | train on n − 1, test on the 1 left out; repeat n times | **low bias**: uses almost all the data | **high variance** (one-point tests; outliers swing it); n fits: very slow |
| **k-fold** | split into k folds; train on k − 1, test on 1; repeat k times; average | balanced; **k = 10** recommended | k times the cost of one fit |
| **Stratified k-fold** | k-fold keeping the class proportions in every fold | needed for **imbalanced** classes | same cost as k-fold |

<!--@include: @/../code/dsml/notes/u3.out#kfold-->

**Sizes for k-fold on n examples:** the number of models (errors computed) N1 = **k**; training size N2 = **(k − 1)n/k**; test size N3 = **n/k**. For 10-fold on 100: 10, 90, 10.

| | Few folds (2–3) | Many folds (→ LOOCV) |
|---|---|---|
| Bias of the estimate | higher (small training sets) | lower |
| Variance of the estimate | lower (big test folds) | higher (tiny test folds, overlapping training sets) |
| Computation | low | high (n fits for LOOCV) |

**Advantages:** fights overfitting, supports model selection and hyperparameter tuning (choosing k in KNN, λ in ridge), and is data-efficient (every row is used for both training and testing). **Disadvantages:** computationally expensive, time-consuming, and the choice of k is itself a bias–variance trade-off.

::: danger Tune on validation folds, never on the test set
Assignment 6's sheet picks k for KNN by test accuracy. That makes the test score optimistic, because the test set helped choose the model. The leak-free way is `cross_val_score` on the training set; touch the test set once, at the end.
:::

## Traps and the 5-minute checklist {#traps}

| # | Trap | Correct version |
|---|---|---|
| 1 | Precision = TP/(TP + FN) | that is recall; precision divides by **predicted** positives, TP + FP |
| 2 | FPR = FP/(FP + TP) | FPR = FP/(FP + **TN**), over the actual negatives |
| 3 | ROC y-axis is precision | y = TPR (recall), x = FPR. Precision is the PR curve |
| 4 | AUC 0.3 is just bad | it is worse than random: the ranking is inverted |
| 5 | 95% accuracy means a good model | not on imbalanced data: always predicting the majority class can score that |
| 6 | Type I = missed positive | Type I = **false positive**; Type II = false negative |
| 7 | Overfitting = high bias | overfitting = **high variance**; underfitting = high bias |
| 8 | Fix underfitting with regularisation | regularisation fights overfitting; reduce it for underfitting |
| 9 | LOOCV has low variance | low **bias**, high variance |
| 10 | 5-fold on 200: train on 160, 4 models | train 160, test 40, **5** models |
| 11 | R² is always in [0, 1] | negative on new data for a model worse than the mean |
| 12 | Forgetting (0, 0) on the ROC | add it before measuring the area |

**The checklist:**
1. Confusion matrix: draw the 2 × 2 with labels first, fill TP, FN, FP, TN, check that the totals match the story.
2. Write the formula, substitute, then give the value to 3–4 decimals.
3. ROC: one row per threshold with TP, FP, FN, TN, TPR, FPR; then the points; then the area.
4. Interpret every number in one line (what it means for this problem).

## Quick check {#quick-check}

<Drill n="1" tag="Definition">

In Mitchell's definition, for a spam filter, which of these is P?

<Mcq :options="['The emails labelled spam or not spam', 'Classifying emails', 'The percentage of emails classified correctly', 'The filter program']" answer="c">

P is always a measurement. The labelled emails are E; classifying them is T.

</Mcq>

</Drill>

<Drill n="2" tag="Paradigm">

An agent learns to play a game from the final score alone. Which paradigm?

<Mcq :options="['Supervised', 'Unsupervised', 'Semi-supervised', 'Reinforcement']" answer="d">

No labels, only a (delayed) reward: reinforcement learning, with the credit-assignment problem of deciding which moves earned the score.

</Mcq>

</Drill>

<Drill n="3" tag="Q-learning">

<FillIn q="γ = 0.9, reward r = 0, and the next state's Q-values are 40, 70 and 50. What is the new Q̂(s, a)?" answer="63">

Q̂ ← r + γ max Q̂(s′, a′) = 0 + 0.9 × 70 = 63.

</FillIn>

</Drill>

<Drill n="4" tag="Fitting">

Train accuracy 97%, test accuracy 70%. What is happening, and what helps?

<Mcq :options="['Underfitting; add features', 'Overfitting; get more data or regularise', 'Underfitting; reduce regularisation', 'Nothing wrong; test accuracy is always lower']" answer="b">

A 27-point gap means the model memorised the training set: high variance. More data, a simpler model or regularisation all help.

</Mcq>

</Drill>

<Drill n="5" tag="Metrics">

<FillIn q="TP = 40, FP = 10, FN = 20, TN = 130. What is the precision? Give a decimal." answer="0.8|.8|4/5">

Precision = TP/(TP + FP) = 40/50 = 0.8. (Recall would be 40/60 = 0.667.)

</FillIn>

</Drill>

<Drill n="6" tag="Metrics">

With TP = 40, FP = 10, FN = 20, what is F1?

<Mcq :options="['0.727', '0.733', '0.667', '0.8']" answer="a">

2TP/(2TP + FP + FN) = 80/110 = 0.727. Check: P = 0.8, R = 0.667, 2PR/(P + R) = 1.0667/1.4667 = 0.727. The harmonic mean is below the plain average (0.733).

</Mcq>

</Drill>

<Drill n="7" tag="ROC">

What are the ROC axes?

<Mcq :options="['x = precision, y = recall', 'x = FPR, y = TPR', 'x = TPR, y = FPR', 'x = threshold, y = accuracy']" answer="b">

x = FPR = 1 − specificity, y = TPR = recall. Precision against recall is the PR curve.

</Mcq>

</Drill>

<Drill n="8" tag="AUC">

A model's AUC is 0.35. What is the best description?

<Mcq :options="['Poor but better than random', 'Random', 'Worse than random: it ranks the classes backwards', 'Impossible; AUC cannot be below 0.5']" answer="c">

Below 0.5 means negatives are usually scored above positives. Flipping the predictions would give AUC 0.65.

</Mcq>

</Drill>

<Drill n="9" tag="Cross-validation">

<FillIn q="5-fold cross-validation on 200 examples: how many examples does each model train on?" answer="160">

N2 = (k − 1)/k × n = 4/5 × 200 = 160; each test fold has 40, and 5 models are built.

</FillIn>

</Drill>

<Drill n="10" tag="Cross-validation">

Compared with 5-fold, LOOCV gives an error estimate with…

<Mcq :options="['higher bias, lower variance', 'lower bias, higher variance', 'lower bias, lower variance', 'the same bias and variance']" answer="b">

Each LOOCV model trains on almost everything (low bias), but each test is one point and the training sets nearly coincide (high variance). It is also n fits instead of 5.

</Mcq>

</Drill>
