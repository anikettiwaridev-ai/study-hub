"""End-semester, autumn 2024: every worked number on docs/dsml/papers/endsem-2024.md (Units 1-4)."""
import math
from fractions import Fraction as Fr
from _hub import num, tex, fixed, table, p, math_block, region, mean, pstdev, sstdev, entropy

# ---------------------------------------------------------------- Q1(II): Pearson r
with region('q1b'):
    X = [2, 4, 5, 7, 8]
    Y = [3, 6, 8, 11, 14]
    mx, my = mean(X), mean(Y)
    rows = []
    for i, (x, y) in enumerate(zip(X, Y), 1):
        dx, dy = x - mx, y - my
        rows.append([i, x, y, num(dx, 2), num(dy, 2), num(dx * dy, 2), num(dx * dx, 2), num(dy * dy, 2)])
    sxy = sum((x - mx) * (y - my) for x, y in zip(X, Y))
    sxx = sum((x - mx) ** 2 for x in X)
    syy = sum((y - my) ** 2 for y in Y)
    rows.append(['**Σ**', sum(X), sum(Y), '0', '0', f'**{num(sxy, 2)}**', f'**{num(sxx, 2)}**', f'**{num(syy, 2)}**'])
    p(f'**Means:** x̄ = {sum(X)}/5 = {num(mx)}, ȳ = {sum(Y)}/5 = {num(my)}.')
    table(['Point', 'x', 'y', 'x − x̄', 'y − ȳ', '(x − x̄)(y − ȳ)', '(x − x̄)²', '(y − ȳ)²'], rows, 'cccrrrrr')
    r = sxy / math.sqrt(sxx * syy)
    math_block(
        f'r = \\frac{{\\sum (x - \\bar x)(y - \\bar y)}}{{\\sqrt{{\\sum (x - \\bar x)^2 \\, \\sum (y - \\bar y)^2}}}}'
        f' = \\frac{{{tex(sxy, 2)}}}{{\\sqrt{{{tex(sxx, 2)} \\times {tex(syy, 2)}}}}}'
        f' = \\frac{{{tex(sxy, 2)}}}{{{tex(math.sqrt(sxx * syy), 4)}}} = \\mathbf{{{tex(r, 4)}}}'
    )

# ---------------------------------------------------------------- Q2(b): z-score outliers
with region('q2b'):
    D = [55, 57, 500, 61, 62, 65, 67, 70, 72, 73, 95, -2]
    m, s = mean(D), pstdev(D)
    p(f'**Pass 1, all 12 values.** Mean μ = {sum(D)}/12 = {num(m, 3)}. Population standard deviation '
      f'σ = √(Σ(x − μ)²/n) = {num(s, 3)}. Then z = (x − μ)/σ:')
    rows = [[num(x), num((x - m) / s, 3), '**outlier**' if abs((x - m) / s) > 3 else ''] for x in D]
    table(['x', 'z = (x − μ)/σ', 'Beyond ±3?'], rows, 'rrl')
    D2 = [x for x in D if abs((x - m) / s) <= 3]
    m2, s2 = mean(D2), pstdev(D2)
    p(f'Only **500** crosses the cut-off (z = {num((500 - m) / s, 3)}). But look at −2: z = {num((-2 - m) / s, 3)}. '
      'It is plainly an outlier, yet it looks ordinary because 500 has dragged the mean up and blown up σ. This is called **masking**.')
    p(f'**Pass 2, after removing 500.** μ = {num(m2, 3)}, σ = {num(s2, 3)}:')
    rows = [[num(x), num((x - m2) / s2, 3), '**outlier**' if abs((x - m2) / s2) > 3 else ('beyond ±2' if abs((x - m2) / s2) > 2 else '')] for x in D2]
    table(['x', 'z', 'Beyond ±3 (or ±2)?'], rows, 'rrl')
    p(f'Now **−2** stands out: z = {num((-2 - m2) / s2, 3)}. With the strict cut-off of 3 it is still just inside; with the other common cut-off, 2, it is flagged. '
      f'95 (z = {num((95 - m2) / s2, 3)}) is not an outlier.')
    p(f'With the sample standard deviation (÷(n − 1)) instead, pass 1 gives σ = {num(sstdev(D), 3)} and z(500) = {num((500 - m) / sstdev(D), 3)}: the same conclusion.')

# ---------------------------------------------------------------- Q3(b): packet filter
with region('q3b'):
    TP, FN, FP, TN = 850, 150, 500, 8500
    p('"Positive" = malicious (the thing the filter is looking for).')
    table(['', 'Predicted malicious', 'Predicted benign', 'Total'], [
        ['**Actual malicious**', f'TP = {TP}', f'FN = {FN}', TP + FN],
        ['**Actual benign**', f'FP = {FP}', f'TN = {TN}', FP + TN],
        ['**Total**', TP + FP, FN + TN, TP + FN + FP + TN],
    ], 'lccc')
    prec = TP / (TP + FP)
    rec = TP / (TP + FN)
    f1 = 2 * TP / (2 * TP + FP + FN)
    spec = TN / (TN + FP)
    fnr = FN / (FN + TP)
    acc = (TP + TN) / (TP + FN + FP + TN)
    table(['Metric', 'Formula', 'Substitution', 'Value'], [
        ['Precision', 'TP / (TP + FP)', f'{TP} / {TP + FP}', f'**{num(prec, 4)}**'],
        ['Recall (sensitivity, TPR)', 'TP / (TP + FN)', f'{TP} / {TP + FN}', f'**{num(rec, 4)}**'],
        ['F1 score', '2TP / (2TP + FP + FN)', f'{2 * TP} / {2 * TP + FP + FN}', f'**{num(f1, 4)}**'],
        ['Specificity (TNR)', 'TN / (TN + FP)', f'{TN} / {TN + FP}', f'**{num(spec, 4)}**'],
        ['False negative rate', 'FN / (FN + TP) = 1 − recall', f'{FN} / {FN + TP}', f'**{num(fnr, 4)}**'],
        ['Accuracy (not asked)', '(TP + TN) / total', f'{TP + TN} / {TP + FN + FP + TN}', num(acc, 4)],
    ], 'lllr')

# ---------------------------------------------------------------- Q4(a): ridge regression
with region('q4a'):
    A = [[Fr(1), Fr(2), Fr(3)], [Fr(4), Fr(5), Fr(6)], [Fr(7), Fr(8), Fr(9)]]
    yv = [Fr(1), Fr(2), Fr(3)]
    lam = 10
    XtX = [[sum(A[k][i] * A[k][j] for k in range(3)) for j in range(3)] for i in range(3)]
    Xty = [sum(A[k][i] * yv[k] for k in range(3)) for i in range(3)]

    def det3(M):
        return (M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1])
                - M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0])
                + M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]))

    mat = lambda M: '\\begin{bmatrix}' + ' \\\\ '.join(' & '.join(tex(v, 4) for v in row) for row in M) + '\\end{bmatrix}'
    vec = lambda v: '\\begin{bmatrix}' + ' \\\\ '.join(tex(x, 4) for x in v) + '\\end{bmatrix}'
    p('**Step 1.** The ridge weights solve $(X^TX + \\lambda I)\\,w = X^Ty$ (no intercept: the question gives only X and y).')
    math_block(f'X^TX = {mat(XtX)}, \\qquad X^Ty = {vec(Xty)}')
    p(f'Note $\\det(X^TX) = {tex(det3(XtX))}$: the columns of X are dependent (column 3 = 2 × column 2 − column 1), so '
      'ordinary least squares has **no unique solution**. Ridge fixes exactly this.')
    M = [[XtX[i][j] + (lam if i == j else 0) for j in range(3)] for i in range(3)]
    math_block(f'X^TX + 10I = {mat(M)}')
    # Gaussian elimination, shown
    aug = [row[:] + [Xty[i]] for i, row in enumerate(M)]
    augtex = lambda G: '\\left[\\begin{array}{ccc|c}' + ' \\\\ '.join(' & '.join(tex(v, 4) for v in row) for row in G) + '\\end{array}\\right]'
    p('**Step 2. Solve by elimination** (R2 ← R2 − (78/76)R1, R3 ← R3 − (90/76)R1, then clear column 2):')
    for c in range(2):
        for r_ in range(c + 1, 3):
            fct = aug[r_][c] / aug[c][c]
            aug[r_] = [a - fct * b for a, b in zip(aug[r_], aug[c])]
    math_block(augtex(aug))
    w = [Fr(0)] * 3
    for i in (2, 1, 0):
        w[i] = (aug[i][3] - sum(aug[i][j] * w[j] for j in range(i + 1, 3))) / aug[i][i]
    p('Back-substitute from the bottom row up:')
    math_block(f'w_3 = \\frac{{{tex(aug[2][3], 4)}}}{{{tex(aug[2][2], 4)}}} = {fixed(w[2], 4, False)},\\quad '
               f'w_2 = {fixed(w[1], 4, False)},\\quad w_1 = {fixed(w[0], 4, False)}')
    p(f'**Ridge weights: w = ({fixed(w[0], 4)}, {fixed(w[1], 4)}, {fixed(w[2], 4)}).**')
    preds = [sum(A[i][j] * w[j] for j in range(3)) for i in range(3)]
    p('**Step 3. Predict the three training examples**, ŷ = Xw:')
    table(['Row', 'x', 'y', 'ŷ = Xw', 'error y − ŷ'], [
        [i + 1, ', '.join(str(int(v)) for v in A[i]), int(yv[i]), f'**{num(preds[i], 4)}**', num(yv[i] - preds[i], 4)] for i in range(3)
    ], 'cccrr')
    p(f'The penalty shrinks the weights towards 0, so the fit is pulled towards the middle: the small y is over-predicted and the large y under-predicted. '
      'That bias is the price of a stable, unique solution.')

# ---------------------------------------------------------------- Q4(b): GD on f(x, y, z)
with region('q4b'):
    x, y, z = 0.1, 0.2, 0.3
    g = 0.01
    p('$f(x, y, z) = 2x^2 - y + \\dfrac{z^3}{3}$, so the gradient is $\\nabla f = \\left(\\dfrac{\\partial f}{\\partial x}, \\dfrac{\\partial f}{\\partial y}, \\dfrac{\\partial f}{\\partial z}\\right) = (4x,\\; -1,\\; z^2)$. '
      'Update rule: each variable ← variable − γ × its partial derivative, all from the old values.')
    rows = [['start', fixed(x, 6), fixed(y, 6), fixed(z, 6), '', '', '', num(2 * x * x - y + z ** 3 / 3, 6)]]
    for it in (1, 2):
        gx, gy, gz = 4 * x, -1.0, z * z
        x, y, z = x - g * gx, y - g * gy, z - g * gz
        rows.append([f'iteration {it}', fixed(x, 6), fixed(y, 6), fixed(z, 6), num(gx, 4), num(gy, 4), num(gz, 6), num(2 * x * x - y + z ** 3 / 3, 6)])
    table(['', 'x', 'y', 'z', '∂f/∂x = 4x (old)', '∂f/∂y', '∂f/∂z = z² (old)', 'f(x, y, z)'], rows, 'lrrrrrrr')
    x, y, z = 0.1, 0.2, 0.3
    lines = []
    for it in (1, 2):
        nx, ny, nz = x - g * 4 * x, y + g, z - g * z * z
        lines.append(f'- **Iteration {it}:** x = {num(x, 6)} − 0.01 × {num(4 * x, 6)} = {num(nx, 6)};  '
                     f'y = {num(y, 6)} − 0.01 × (−1) = {num(ny, 6)};  z = {num(z, 6)} − 0.01 × {num(z * z, 6)} = {num(nz, 6)}')
        x, y, z = nx, ny, nz
    p(*lines)

# ---------------------------------------------------------------- Q4(c): decision-tree root (Play Golf)
with region('q4c'):
    rows_ = [
        ('Sunny', 'Hot', 'High', 'Weak', 'No'), ('Sunny', 'Hot', 'High', 'Strong', 'No'),
        ('Overcast', 'Hot', 'High', 'Weak', 'Yes'), ('Rainy', 'Mild', 'High', 'Weak', 'Yes'),
        ('Rainy', 'Cool', 'Normal', 'Weak', 'Yes'), ('Rainy', 'Cool', 'Normal', 'Strong', 'No'),
        ('Overcast', 'Cool', 'Normal', 'Strong', 'Yes'), ('Sunny', 'Mild', 'High', 'Weak', 'No'),
        ('Sunny', 'Cool', 'Normal', 'Weak', 'Yes'), ('Rainy', 'Mild', 'Normal', 'Weak', 'Yes'),
        ('Sunny', 'Mild', 'Normal', 'Strong', 'Yes'), ('Overcast', 'Mild', 'High', 'Strong', 'Yes'),
        ('Overcast', 'Hot', 'Normal', 'Weak', 'Yes'), ('Rainy', 'Mild', 'High', 'Strong', 'No'),
    ]
    names = ['Outlook', 'Temperature', 'Humidity', 'Wind']
    yes = sum(r[4] == 'Yes' for r in rows_)
    no = len(rows_) - yes
    H = entropy([yes, no])
    p(f'**Entropy of the whole set** ({yes} Yes, {no} No out of 14):')
    math_block(f'H(S) = -\\tfrac{{{yes}}}{{14}}\\log_2\\tfrac{{{yes}}}{{14}} - \\tfrac{{{no}}}{{14}}\\log_2\\tfrac{{{no}}}{{14}} = {tex(H, 4)}')
    gains = {}
    for a, name in enumerate(names):
        vals = []
        for r in rows_:
            if r[a] not in vals:
                vals.append(r[a])
        trows, wsum = [], 0.0
        for v in vals:
            sub = [r for r in rows_ if r[a] == v]
            y_ = sum(r[4] == 'Yes' for r in sub)
            n_ = len(sub) - y_
            h = entropy([y_, n_])
            wsum += len(sub) / 14 * h
            trows.append([v, y_, n_, num(h, 4), f'{len(sub)}/14 × {num(h, 4)} = {num(len(sub) / 14 * h, 4)}'])
        gains[name] = H - wsum
        p(f'**{name}**')
        table([name, 'Yes', 'No', 'Entropy', 'Weighted'], trows, 'lccrr')
        p(f'Gain({name}) = {num(H, 4)} − {num(wsum, 4)} = **{num(gains[name], 4)}**')
    best = max(gains, key=gains.get)
    table(['Attribute', 'Information gain'], [[k, f'**{num(v, 4)}**' if k == best else num(v, 4)] for k, v in gains.items()], 'lr')
    p(f'**{best}** has the largest information gain, so it goes at the root.')
