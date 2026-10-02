"""Mock mid-semester paper: every worked number on docs/dsml/mock-mst.md."""
import math
from _hub import num, tex, table, p, math_block, region, mean, pstdev, sigmoid

# Q1(a): scale a skewed income column
with region('q1a'):
    x = [20, 25, 30, 35, 90]
    lo, hi, m, s = min(x), max(x), mean(x), pstdev(x)
    table(['Income (thousand)', 'Min-max', 'Z-score'], [[v, num((v - lo) / (hi - lo), 4), num((v - m) / s, 4)] for v in x], 'crr')
    p(f'min = {lo}, max = {hi}, μ = {num(m)}, σ = {num(s, 4)} (population).')

# Q2: gradient descent, two iterations
with region('q2'):
    X, Y = [1, 2, 3], [3, 5, 7]
    w = b = 0.0
    al = 0.05
    n = len(X)
    for it in (1, 2):
        e = [w * x + b - y for x, y in zip(X, Y)]
        se, sex = sum(e), sum(ei * x for ei, x in zip(e, X))
        p(f'**Iteration {it}** (w = {num(w, 4)}, b = {num(b, 4)}):')
        table(['x', 'y', 'ŷ = wx + b', 'e = ŷ − y', 'e·x'], [[x, y, num(w * x + b, 4), num(ei, 4), num(ei * x, 4)] for x, y, ei in zip(X, Y, e)]
              + [['', '', '**Σ**', f'**{num(se, 4)}**', f'**{num(sex, 4)}**']], 'ccrrr')
        gw, gb = 2 / n * sex, 2 / n * se
        nw, nb = w - al * gw, b - al * gb
        math_block(
            f'\\frac{{\\partial J}}{{\\partial w}} &= \\tfrac{{2}}{{3}}({tex(sex, 4)}) = {tex(gw, 4)}, & w &\\leftarrow {tex(w, 4)} - 0.05({tex(gw, 4)}) = \\mathbf{{{tex(nw, 4)}}}',
            f'\\frac{{\\partial J}}{{\\partial b}} &= \\tfrac{{2}}{{3}}({tex(se, 4)}) = {tex(gb, 4)}, & b &\\leftarrow {tex(b, 4)} - 0.05({tex(gb, 4)}) = \\mathbf{{{tex(nb, 4)}}}',
        )
        w, b = nw, nb
    J = lambda w_, b_: mean([(w_ * x + b_ - y) ** 2 for x, y in zip(X, Y)])
    p(f'MSE: {num(J(0, 0), 4)} → {num(J(w, b), 4)}. The data lies on y = 2x + 1, so the steps are heading towards w = 2, b = 1.')

# Q3(a): confusion matrix from a story
with region('q3a'):
    TP, FP, FN, TN = 40, 20, 10, 430
    table(['', 'Flagged fraud', 'Not flagged', 'Total'], [
        ['**Actually fraud**', f'TP = {TP}', f'FN = {FN}', TP + FN],
        ['**Actually genuine**', f'FP = {FP}', f'TN = {TN}', FP + TN],
    ], 'lccc')
    table(['Metric', 'Working', 'Value'], [
        ['Precision', f'{TP}/({TP} + {FP})', f'**{num(TP / (TP + FP), 4)}**'],
        ['Recall', f'{TP}/({TP} + {FN})', f'**{num(TP / (TP + FN), 4)}**'],
        ['F1', f'2 × {TP}/(2 × {TP} + {FP} + {FN})', f'**{num(2 * TP / (2 * TP + FP + FN), 4)}**'],
        ['Specificity', f'{TN}/({TN} + {FP})', f'**{num(TN / (TN + FP), 4)}**'],
        ['Accuracy', f'({TP} + {TN})/500', num((TP + TN) / 500, 4)],
    ], 'llr')

# Q3(b): ROC and AUC
with region('q3b'):
    data = [(0.9, 1), (0.7, 1), (0.6, 0), (0.4, 1), (0.2, 0)]
    P = sum(l for _, l in data)
    N = len(data) - P
    rows, pts = [], [(0.0, 0.0)]
    for t, _ in data:
        tp = sum(1 for s, l in data if s >= t and l)
        fp = sum(1 for s, l in data if s >= t and not l)
        pts.append((fp / N, tp / P))
        rows.append([t, tp, fp, P - tp, N - fp, f'{tp}/{P} = {num(tp / P, 3)}', f'{fp}/{N} = {num(fp / N, 3)}'])
    table(['Threshold', 'TP', 'FP', 'FN', 'TN', 'TPR', 'FPR'], rows, 'cccccrr')
    area = sum((b[0] - a[0]) * (a[1] + b[1]) / 2 for a, b in zip(pts, pts[1:]))
    wins = sum(1 for s, l in data if l for s2, l2 in data if not l2 and s > s2)
    p(f'ROC points: {", ".join(f"({num(x, 3)}, {num(y, 3)})" for x, y in pts)}. '
      f'**AUC = {num(area, 4)}** (pairs check: {wins}/{P * N}).')

# Q4: KNN, the answer changes with k
with region('q4'):
    T = [('P1', 1, 2, 'A'), ('P2', 2, 3, 'A'), ('P3', 3, 1, 'A'), ('P4', 5, 5, 'B'), ('P5', 6, 5, 'B'), ('P6', 7, 7, 'B'), ('P7', 8, 6, 'B')]
    q = (4, 4)
    rows, ds = [], []
    for nm, x, y, c in T:
        d = math.sqrt((x - q[0]) ** 2 + (y - q[1]) ** 2)
        ds.append((d, nm, c))
        rows.append([nm, f'({x}, {y})', c, f'√({(x - q[0]) ** 2} + {(y - q[1]) ** 2}) = √{(x - q[0]) ** 2 + (y - q[1]) ** 2}', num(d, 3)])
    table(['Point', 'Coordinates', 'Class', 'Distance to (4, 4)', 'd'], rows, 'ccclr')
    ds.sort(key=lambda t: (t[0], t[1]))
    p('Sorted: ' + ', '.join(f'{nm} ({c}) {num(d, 3)}' for d, nm, c in ds) + '.')
    lines = []
    for k in (1, 3, 5, 7):
        top = [c for _, _, c in ds[:k]]
        a, b = top.count('A'), top.count('B')
        lines.append(f'- **k = {k}:** A {a}, B {b} → **{"A" if a > b else "B"}**')
    p(*lines)

# Q5(a): logistic regression
with region('q5a'):
    b0, b1 = -2.5, 0.8
    rows = []
    for x in (2, 5):
        z = b0 + b1 * x
        rows.append([x, f'−2.5 + 0.8 × {x} = {num(z, 2)}', num(sigmoid(z), 4), '1 (buys)' if sigmoid(z) >= 0.5 else '0'])
    table(['Past purchases', 'z', 'p = σ(z)', 'Class at 0.5'], rows, 'clrc')
    p(f'Odds ratio per extra past purchase = e^0.8 = **{num(math.exp(b1), 4)}**: each one multiplies the odds of buying by about 2.2. '
      f'p = 0.5 where z = 0: x = 2.5/0.8 = **{num(2.5 / 0.8, 4)}** purchases.')

# Q5(b): cross-validation sizes
with region('q5b'):
    n = 300
    table(['Method', 'N1 (models)', 'N2 (train)', 'N3 (test)'], [
        ['6-fold', 6, 5 * n // 6, n // 6],
        ['LOOCV', n, n - 1, 1],
    ], 'lccc')
