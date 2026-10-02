"""Mid-semester, spring 2025 (DSN4005): every worked number on docs/dsml/papers/mst-2025-spring.md."""
import math
from _hub import num, tex, sci, table, p, math_block, region, sigmoid

# ---------------------------------------------------------------- Q1: two iterations of GD, three parameters
with region('q1'):
    X1 = [1, 2, 3, 4, 5]
    X2 = [2, 3, 4, 5, 6]
    Y = [40000, 45000, 50000, 60000, 70000]
    n = len(Y)
    alpha = 0.01
    th = [0.0, 0.0, 0.0]

    def cost(t):
        return sum((t[0] + t[1] * a + t[2] * b - y) ** 2 for a, b, y in zip(X1, X2, Y)) / n

    costs = [cost(th)]
    for it in (1, 2):
        pred = [th[0] + th[1] * a + th[2] * b for a, b in zip(X1, X2)]
        err = [yh - y for yh, y in zip(pred, Y)]
        rows = [[i + 1, a, b, y, num(yh, 1), num(e, 1), num(e * a, 1), num(e * b, 1)]
                for i, (a, b, y, yh, e) in enumerate(zip(X1, X2, Y, pred, err))]
        s0, s1, s2 = sum(err), sum(e * a for e, a in zip(err, X1)), sum(e * b for e, b in zip(err, X2))
        rows.append(['**Σ**', '', '', '', '', f'**{num(s0, 1)}**', f'**{num(s1, 1)}**', f'**{num(s2, 1)}**'])
        p(f'**Iteration {it}.** Start: θ₀ = {num(th[0])}, θ₁ = {num(th[1])}, θ₂ = {num(th[2])}.')
        table(['i', 'X₁', 'X₂', 'Y', 'Ŷ = θ₀ + θ₁X₁ + θ₂X₂', 'error e = Ŷ − Y', 'e·X₁', 'e·X₂'], rows, 'ccccrrrr')
        g = [2 / n * s0, 2 / n * s1, 2 / n * s2]
        new = [t - alpha * gi for t, gi in zip(th, g)]
        math_block(
            f'\\frac{{\\partial J}}{{\\partial \\theta_0}} &= \\tfrac{{2}}{{5}}\\textstyle\\sum e = 0.4({tex(s0, 1)}) = {tex(g[0], 1)}'
            f' &\\theta_0 &= {tex(th[0], 2)} - 0.01({tex(g[0], 1)}) = \\mathbf{{{tex(new[0], 2)}}}',
            f'\\frac{{\\partial J}}{{\\partial \\theta_1}} &= \\tfrac{{2}}{{5}}\\textstyle\\sum eX_1 = 0.4({tex(s1, 1)}) = {tex(g[1], 1)}'
            f' &\\theta_1 &= {tex(th[1], 2)} - 0.01({tex(g[1], 1)}) = \\mathbf{{{tex(new[1], 2)}}}',
            f'\\frac{{\\partial J}}{{\\partial \\theta_2}} &= \\tfrac{{2}}{{5}}\\textstyle\\sum eX_2 = 0.4({tex(s2, 1)}) = {tex(g[2], 1)}'
            f' &\\theta_2 &= {tex(th[2], 2)} - 0.01({tex(g[2], 1)}) = \\mathbf{{{tex(new[2], 2)}}}',
        )
        th = new
        costs.append(cost(th))
    p('**Cost after each iteration** (MSE): ' + ' → '.join(sci(c) for c in costs) +
      '. It falls every time, so the steps are going the right way.')
    # the 1/(2n) convention halves the first step
    half = [alpha * (1 / n) * s for s in (sum(-y for y in Y), sum(-y * a for y, a in zip(Y, X1)), sum(-y * b for y, b in zip(Y, X2)))]
    p('**If you use $J = \\frac{1}{2n}\\sum(\\hat Y - Y)^2$ instead**, every gradient is halved, so after iteration 1: '
      f'θ₀ = {num(-half[0], 2)}, θ₁ = {num(-half[1], 2)}, θ₂ = {num(-half[2], 2)}. Either is accepted if you state which one you use.')

# ---------------------------------------------------------------- Q2: logistic probability
with region('q2'):
    b0, b1, b2 = -5, 0.1, 0.00005
    age, inc = 38, 62000
    z = b0 + b1 * age + b2 * inc
    e = math.exp(-z)
    pr = sigmoid(z)
    math_block(
        f'z &= b_0 + b_1\\cdot\\text{{Age}} + b_2\\cdot\\text{{Income}} = -5 + 0.1(38) + 0.00005(62000)',
        f'  &= -5 + {tex(b1 * age)} + {tex(b2 * inc)} = {tex(z)}',
        f'P(\\text{{subscribed}}) &= \\sigma(z) = \\frac{{1}}{{1 + e^{{-{tex(z)}}}}} = \\frac{{1}}{{1 + {tex(e)}}} = \\mathbf{{{tex(pr)}}}',
    )
    p(f'So the probability is **{num(pr, 2)} ({num(100 * pr, 1)}%)**, and with the usual threshold of 0.5 the model predicts **subscribed (1)**. '
      f'The odds are p/(1 − p) = {num(pr / (1 - pr), 2)}, which is $e^{{z}} = e^{{{tex(z)}}}$: about {num(pr / (1 - pr), 1)} to 1 in favour.')

# ---------------------------------------------------------------- Q3: confusion-matrix metrics
with region('q3'):
    TP, FN, FP, TN = 50, 10, 5, 35
    tot = TP + FN + FP + TN
    acc = (TP + TN) / tot
    prec = TP / (TP + FP)
    rec = TP / (TP + FN)
    f1 = 2 * prec * rec / (prec + rec)
    p(f'Read the four cells first: **TP = {TP}** (actual 1, predicted 1), **FN = {FN}** (actual 1, predicted 0), '
      f'**FP = {FP}** (actual 0, predicted 1), **TN = {TN}** (actual 0, predicted 0). Total = {tot}.')
    table(['Metric', 'Formula', 'Substitution', 'Value'], [
        ['a. Accuracy', '(TP + TN) / total', f'({TP} + {TN}) / {tot}', f'**{num(acc, 4)}**'],
        ['b. Precision', 'TP / (TP + FP)', f'{TP} / ({TP} + {FP}) = {TP}/{TP + FP}', f'**{num(prec, 4)}**'],
        ['c. Recall', 'TP / (TP + FN)', f'{TP} / ({TP} + {FN}) = {TP}/{TP + FN}', f'**{num(rec, 4)}**'],
        ['d. F1 score', '2PR / (P + R)', f'2 × {num(prec, 4)} × {num(rec, 4)} / ({num(prec, 4)} + {num(rec, 4)})', f'**{num(f1, 4)}**'],
    ], 'lllr')
    p(f'Shortcut for F1 straight from the counts: F1 = 2TP / (2TP + FP + FN) = {2 * TP} / {2 * TP + FP + FN} = {num(f1, 4)}. '
      f'Specificity, if asked: TN / (TN + FP) = {TN}/{TN + FP} = {num(TN / (TN + FP), 4)}.')

# ---------------------------------------------------------------- Q4(b): fold sizes
with region('q4b'):
    k, n = 10, 100
    table(['Quantity', 'Meaning', 'Formula', 'Value'], [
        ['N1', 'how many times a model is built and its error computed', 'k', f'**{k}**'],
        ['N2', 'training-set size each time', '(k − 1)/k × n = 9/10 × 100', f'**{(k - 1) * n // k}**'],
        ['N3', 'test-set size each time', 'n / k = 100 / 10', f'**{n // k}**'],
    ], 'llll')
    p(f'Check: N2 + N3 = {(k - 1) * n // k} + {n // k} = {n} = n, and over the {k} rounds every example is tested exactly once.')

# ---------------------------------------------------------------- Q5(c): PCA components (Unit 5)
with region('q5c'):
    ev = [5.2, 3.8, 1.5, 0.6, 0.2]
    tot = sum(ev)
    run, rows = 0.0, []
    for i, v in enumerate(ev, 1):
        run += v
        rows.append([f'PC{i}', v, f'{num(100 * v / tot, 1)}%', f'{num(100 * run / tot, 1)}%'])
    p(f'Each eigenvalue is the variance along one principal component. Total variance = {" + ".join(map(str, ev))} = {num(tot)}.')
    table(['Component', 'Eigenvalue', 'Share of variance', 'Cumulative'], rows, 'crrr')
    p('The cumulative share first reaches 90% at PC3 (92.9%), so **retain 3 principal components**.')
