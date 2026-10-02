"""Unit 3 notes: worked examples and figures for docs/dsml/notes/unit-3.md."""
from _hub import num, tex, table, p, math_block, region, mean
from _svg import Plot, figure


def solve(A, b):
    """Gaussian elimination with partial pivoting (small systems only)."""
    n = len(A)
    M = [row[:] + [b[i]] for i, row in enumerate(A)]
    for c in range(n):
        piv = max(range(c, n), key=lambda r: abs(M[r][c]))
        M[c], M[piv] = M[piv], M[c]
        for r in range(c + 1, n):
            f = M[r][c] / M[c][c]
            M[r] = [a - f * bb for a, bb in zip(M[r], M[c])]
    x = [0.0] * n
    for i in range(n - 1, -1, -1):
        x[i] = (M[i][n] - sum(M[i][j] * x[j] for j in range(i + 1, n))) / M[i][i]
    return x


def polyfit(xs, ys, deg):
    A = [[sum(x ** (i + j) for x in xs) for j in range(deg + 1)] for i in range(deg + 1)]
    b = [sum(y * x ** i for x, y in zip(xs, ys)) for i in range(deg + 1)]
    c = solve(A, b)
    return lambda x: sum(ci * x ** i for i, ci in enumerate(c))


def lagrange(xs, ys):
    def f(x):
        tot = 0.0
        for i, (xi, yi) in enumerate(zip(xs, ys)):
            term = yi
            for j, xj in enumerate(xs):
                if j != i:
                    term *= (x - xj) / (xi - xj)
            tot += term
        return tot
    return f


# ---------------------------------------------------------------- LMS (Mitchell's checkers learner)
with region('lms'):
    f1, vtrain, c = 4, 10, 0.1
    w0 = w1 = 0.0
    vhat = w0 + w1 * f1
    err = vtrain - vhat
    nw1 = w1 + c * f1 * err
    nw0 = w0 + c * 1 * err
    table(['Step', 'Working', 'Result'], [
        ['predict', f'V̂ = w₀ + w₁·f₁ = 0 + 0 × {f1}', num(vhat)],
        ['error', f'V_train − V̂ = {vtrain} − {num(vhat)}', num(err)],
        ['update w₁', f'w₁ + c·f₁·error = 0 + {c} × {f1} × {num(err)}', f'**{num(nw1)}**'],
        ['update w₀', f'w₀ + c·1·error = 0 + {c} × 1 × {num(err)}', f'**{num(nw0)}**'],
        ['re-check', f'V̂ = {num(nw0)} + {num(nw1)} × {f1}', num(nw0 + nw1 * f1)],
    ], 'lll')
    p(f'The prediction jumped from 0 to {num(nw0 + nw1 * f1)}, overshooting the target {vtrain}; the next update pulls it back. '
      'This rule is gradient descent on the squared error, one example at a time (stochastic gradient descent).')

# ---------------------------------------------------------------- Q-learning
with region('qlearn'):
    gamma = 0.9
    nxt = [63, 81, 100]
    q = 0 + gamma * max(nxt)
    math_block(f'\\hat Q(s_1, a_{{\\text{{right}}}}) \\leftarrow r + \\gamma \\max_{{a\'}} \\hat Q(s_2, a\') = 0 + {gamma} \\times \\max\\{{{", ".join(map(str, nxt))}\\}} = 0 + {gamma} \\times {max(nxt)} = \\mathbf{{{tex(q)}}}')
    rows = []
    for steps in range(0, 4):
        rows.append([steps, ' + '.join(['0'] * steps + ['100']) if steps else '100', f'0.9{"⁰¹²³"[steps]} × 100' if steps else '100', num(gamma ** steps * 100)])
    p('**Why the values fall by 0.9 per step.** With reward 100 only on reaching the goal G and γ = 0.9, a state k moves from G is worth γᵏ × 100:')
    table(['Moves to G', 'Rewards on the way', 'Discounted value', 'V*'], rows, 'clll')

# ---------------------------------------------------------------- under / good / over fitting
with region('fitting'):
    true = lambda x: 0.4 * (x - 3) ** 2 + 1
    xs = [0.5, 1.2, 2.0, 2.8, 3.5, 4.3, 5.0, 5.8]
    noise = [0.6, -0.5, 0.4, -0.6, 0.5, -0.4, 0.6, -0.3]
    ys = [true(x) + e for x, e in zip(xs, noise)]
    xt = [0.8, 1.6, 2.4, 3.2, 3.9, 4.7, 5.4]
    nt = [-0.3, 0.4, -0.2, 0.3, -0.5, 0.2, -0.4]
    yt = [true(x) + e for x, e in zip(xt, nt)]
    fits = [('Degree 1: underfits', polyfit(xs, ys, 1)), ('Degree 2: fits', polyfit(xs, ys, 2)), ('Degree 7: overfits', lagrange(xs, ys))]
    rows = []
    print('<div class="fig-row">')
    for title, fn in fits:
        pl = Plot(0, 6.3, -0.5, 6, w=240, h=200, pad=(22, 6, 22, 22), label=title)
        pl.axes()
        pts, prev = [], None
        segs = []
        for i in range(0, 301):
            x = 0.3 + i * (5.7 / 300)
            y = fn(x)
            if -0.5 <= y <= 6:
                pts.append((x, y))
            elif pts:
                segs.append(pts)
                pts = []
        if pts:
            segs.append(pts)
        for sgm in segs:
            pl.line(sgm, 'a')
        for x, y in zip(xs, ys):
            pl.dot(x, y, 'fb', r=3)
        for x, y in zip(xt, yt):
            pl.dot(x, y, 'hollow', r=3)
        pl.text(0.2, 5.75, title, cls='lbl')
        print(pl.svg())
        tr = mean([(fn(x) - y) ** 2 for x, y in zip(xs, ys)])
        te = mean([(fn(x) - y) ** 2 for x, y in zip(xt, yt)])
        rows.append([title.split(':')[0], num(tr, 2), num(te, 2), title.split(': ')[1]])
    print('</div>')
    print()
    print('<p class="fig-cap">Filled dots: the 8 training points. Open dots: 7 unseen test points from the same curve. The line is the model.</p>')
    print()
    table(['Model', 'Training MSE', 'Test MSE', 'Verdict'], rows, 'lrrl')
    p('Degree 7 passes through every training point (training error 0) and has the worst test error: it learned the noise. '
      'Degree 1 cannot bend, so it is poor on both. Degree 2 matches the true shape and is best on unseen data. **Zero training error is not the goal.**')

# ---------------------------------------------------------------- bias-variance curve
with region('biasvar'):
    cs = [1 + i * 0.05 for i in range(181)]
    bias = [(c_, 4 / c_) for c_ in cs]
    var = [(c_, 0.04 * c_ * c_) for c_ in cs]
    tot = [(c_, 4 / c_ + 0.04 * c_ * c_ + 0.3) for c_ in cs]
    best = min(tot, key=lambda t: t[1])
    pl = Plot(1, 10, 0, 5, w=520, h=280, pad=(40, 16, 14, 34), label='Bias, variance and total error against model complexity')
    pl.axes('Model complexity', 'Error')
    pl.line(bias, 'a')
    pl.line(var, 'b')
    pl.line(tot, 'c')
    pl.seg(best[0], 0, best[0], 5, 'm')
    pl.text(1.35, 3.3, 'bias²', cls='ta')
    pl.text(8.6, 3.35, 'variance', cls='tb')
    pl.text(8.5, 4.7, 'total error', cls='tc')
    pl.text(best[0], 0.15, 'best complexity', anchor='middle')
    pl.text(1.15, 4.7, '← underfitting (high bias)')
    pl.text(7.6, 4.7, 'overfitting (high variance) →', anchor='end')
    figure(pl, 'More complexity lowers bias and raises variance. The best model sits where the total is lowest, not where either one is zero.')

# ---------------------------------------------------------------- SSE and R²
with region('sse'):
    y = [5, 7, 3, 6, 8]
    yh = [4.8, 7.5, 2.9, 5.7, 8.2]
    yb = mean(y)
    rows = []
    for a, b in zip(y, yh):
        rows.append([a, b, num(a - b, 2), num((a - b) ** 2, 4), num(a - yb, 2), num((a - yb) ** 2, 4)])
    sse = sum((a - b) ** 2 for a, b in zip(y, yh))
    tss = sum((a - yb) ** 2 for a in y)
    rows.append(['', '', '', f'**SSE = {num(sse, 4)}**', '', f'**TSS = {num(tss, 4)}**'])
    p(f'The slides’ SSE example, extended to R². Mean of the actual values ȳ = {num(yb)}.')
    table(['Actual y', 'Predicted ŷ', 'y − ŷ', '(y − ŷ)²', 'y − ȳ', '(y − ȳ)²'], rows, 'ccrrrr')
    r2 = 1 - sse / tss
    mse = sse / len(y)
    math_block(f'R^2 = 1 - \\frac{{\\text{{SSE}}}}{{\\text{{TSS}}}} = 1 - \\frac{{{tex(sse, 4)}}}{{{tex(tss, 4)}}} = \\mathbf{{{tex(r2, 4)}}}, \\qquad '
               f'\\text{{MSE}} = \\frac{{\\text{{SSE}}}}{{n}} = {tex(mse, 4)}, \\qquad \\text{{RMSE}} = \\sqrt{{\\text{{MSE}}}} = {tex(mse ** 0.5, 4)}')
    p(f'The model explains {num(100 * r2, 1)}% of the variation in y. RMSE ({num(mse ** 0.5, 2)}) is in the same units as y, so it is the error to quote.')

# ---------------------------------------------------------------- confusion matrix
with region('cm'):
    TP, FN, FP, TN = 30, 10, 20, 140
    tot = TP + FN + FP + TN
    p(f'A screening test on {tot} patients, {TP + FN} of whom have the disease. The test flags {TP + FP} people, {TP} of them really ill.')
    table(['', 'Predicted ill', 'Predicted healthy', 'Total'], [
        ['**Actually ill**', f'TP = {TP}', f'FN = {FN}', TP + FN],
        ['**Actually healthy**', f'FP = {FP}', f'TN = {TN}', FP + TN],
        ['**Total**', TP + FP, FN + TN, tot],
    ], 'lccc')
    acc = (TP + TN) / tot
    pr = TP / (TP + FP)
    rc = TP / (TP + FN)
    f1 = 2 * TP / (2 * TP + FP + FN)
    sp = TN / (TN + FP)
    table(['Metric', 'Formula', 'Value', 'Reads as'], [
        ['Accuracy', '(TP + TN)/total', f'{TP + TN}/{tot} = **{num(acc, 3)}**', 'share of all calls that were right'],
        ['Precision', 'TP/(TP + FP)', f'{TP}/{TP + FP} = **{num(pr, 3)}**', 'when it says ill, how often it is right'],
        ['Recall (sensitivity, TPR)', 'TP/(TP + FN)', f'{TP}/{TP + FN} = **{num(rc, 3)}**', 'of the ill, how many it catches'],
        ['F1', '2PR/(P + R) = 2TP/(2TP + FP + FN)', f'{2 * TP}/{2 * TP + FP + FN} = **{num(f1, 3)}**', 'balance of precision and recall'],
        ['Specificity (TNR)', 'TN/(TN + FP)', f'{TN}/{TN + FP} = **{num(sp, 3)}**', 'of the healthy, how many it clears'],
        ['FPR', 'FP/(FP + TN) = 1 − specificity', f'{FP}/{FP + TN} = **{num(1 - sp, 3)}**', 'false alarms among the healthy'],
    ], 'llll')
    lazy = (FP + TN) / tot
    p(f'**The accuracy paradox:** a "test" that calls everyone healthy scores {FP + TN}/{tot} = **{num(lazy, 2)}** accuracy, '
      f'close to this one’s {num(acc, 2)}, while catching **no** ill patient (recall 0). With imbalanced classes, never report accuracy alone.')

# ---------------------------------------------------------------- ROC sweep
with region('roc'):
    data = [(0.95, 1), (0.85, 1), (0.78, 0), (0.66, 1), (0.60, 0), (0.55, 1), (0.43, 0), (0.30, 0)]
    P = sum(l for _, l in data)
    N = len(data) - P
    rows, pts = [], [(0.0, 0.0)]
    for t in [s for s, _ in data]:
        tp = sum(1 for s, l in data if s >= t and l == 1)
        fp = sum(1 for s, l in data if s >= t and l == 0)
        pts.append((fp / N, tp / P))
        rows.append([t, tp, fp, P - tp, N - fp, f'{tp}/{P} = {num(tp / P, 2)}', f'{fp}/{N} = {num(fp / N, 2)}'])
    p(f'Eight emails with the model’s spam probability; {P} are spam (1), {N} are not (0): ' +
      ', '.join(f'{s} ({l})' for s, l in data) + '. Use each score as a threshold (spam if p ≥ t):')
    table(['Threshold t', 'TP', 'FP', 'FN', 'TN', 'TPR', 'FPR'], rows, 'cccccrr')
    area = sum((b[0] - a[0]) * (a[1] + b[1]) / 2 for a, b in zip(pts, pts[1:]))
    pl = Plot(0, 1, 0, 1, w=340, h=310, pad=(46, 14, 12, 40), label='ROC curve for the eight emails', narrow=True)
    pl.axes('FPR', 'TPR', [0, 0.25, 0.5, 0.75, 1], [0, 0.25, 0.5, 0.75, 1], xfmt=lambda v: num(v, 2), yfmt=lambda v: num(v, 2), grid=True)
    pl.area(pts + [(1, 0)])
    pl.seg(0, 0, 1, 1, 'm')
    pl.line(pts, 'a')
    for x, y in pts:
        pl.dot(x, y, 'fa')
    pl.text(0.45, 0.25, f'AUC = {num(area, 3)}', cls='ta')
    figure(pl, 'Each threshold is one point. Moving the threshold down walks the curve from (0, 0) to (1, 1).')
    pos = [s for s, l in data if l == 1]
    neg = [s for s, l in data if l == 0]
    wins = sum(1 for a in pos for b in neg if a > b)
    p(f'**AUC = {num(area, 4)}** by trapezoids. Check by pairs: {wins} of the {len(pos) * len(neg)} (spam, not-spam) pairs have the spam scored higher, '
      f'{wins}/{len(pos) * len(neg)} = {num(wins / (len(pos) * len(neg)), 4)}. On the slides’ scale, 0.8–0.9 is "considerable".')

# ---------------------------------------------------------------- k-fold picture
with region('kfold'):
    k = 5
    w, h = 520, 30 + 26 * k
    parts = [f'<svg class="fig" viewBox="0 0 {w} {h}" role="img" aria-label="Five-fold cross-validation">']
    left, top, cw, chh = 80, 8, 80, 18
    for r in range(k):
        y = top + r * 26
        parts.append(f'<text x="8" y="{y + 13}">Round {r + 1}</text>')
        for c in range(k):
            cls = 'fb' if c == r else 'area'
            parts.append(f'<rect class="{cls}" x="{left + c * (cw + 4)}" y="{y}" width="{cw}" height="{chh}" rx="2"/>')
            if c == r:
                parts.append(f'<text x="{left + c * (cw + 4) + cw / 2}" y="{y + 13}" text-anchor="middle" style="fill:#fff;font-weight:600">test</text>')
    parts.append(f'<text x="{left}" y="{top + k * 26 + 14}">Each round trains on the 4 shaded folds and tests on the red one; the 5 errors are averaged.</text>')
    parts.append('</svg>')
    print('\n'.join(parts))
    print()
