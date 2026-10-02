"""Mid-semester, September 2025: every worked number on docs/dsml/papers/mst-2025.md."""
import math
from _hub import num, tex, table, p, math_block, region, mean
from _svg import Plot, figure

# ---------------------------------------------------------------- Q2: one step of GD
with region('q2'):
    xs, ys = [1, 2, 3], [2, 4, 6]
    w = b = 0.0
    eta = 0.1
    n = len(xs)
    yhat = [w * x + b for x in xs]
    r = [y - yh for y, yh in zip(ys, yhat)]
    rows = [[i + 1, x, y, num(yh), num(e), num(x * e)] for i, (x, y, yh, e) in enumerate(zip(xs, ys, yhat, r))]
    rows.append(['**Σ**', '', '', '', f'**{num(sum(r))}**', f'**{num(sum(x * e for x, e in zip(xs, r)))}**'])
    p('**Step 1. Predict with the starting values** $w_0 = 0,\\ b_0 = 0$, so every $\\hat y_i = 0$.')
    table(['i', '$x_i$', '$y_i$', '$\\hat y_i = wx_i + b$', '$y_i - \\hat y_i$', '$x_i(y_i - \\hat y_i)$'], rows, 'cccrrr')
    sx = sum(x * e for x, e in zip(xs, r))
    se = sum(r)
    gw = -2 / n * sx
    gb = -2 / n * se
    p('**Step 2. The gradients** (formulas given in the question):')
    math_block(
        f'\\frac{{\\partial J}}{{\\partial w}} &= -\\frac{{2}}{{n}}\\sum x_i\\,(y_i - \\hat y_i) = -\\frac{{2}}{{3}}({tex(sx)}) = {tex(gw)}',
        f'\\frac{{\\partial J}}{{\\partial b}} &= -\\frac{{2}}{{n}}\\sum (y_i - \\hat y_i) = -\\frac{{2}}{{3}}({tex(se)}) = {tex(gb)}',
    )
    w1 = w - eta * gw
    b1 = b - eta * gb
    p('**Step 3. Update both from the old values** (move against the gradient):')
    math_block(
        f'w_1 &= w_0 - \\eta\\,\\frac{{\\partial J}}{{\\partial w}} = 0 - 0.1\\,({tex(gw)}) = \\mathbf{{{tex(w1)}}}',
        f'b_1 &= b_0 - \\eta\\,\\frac{{\\partial J}}{{\\partial b}} = 0 - 0.1\\,({tex(gb)}) = \\mathbf{{{tex(b1)}}}',
    )
    J0 = sum(e * e for e in r) / n
    r1 = [y - (w1 * x + b1) for x, y in zip(xs, ys)]
    J1 = sum(e * e for e in r1) / n
    p(f'**Check that it worked.** The cost before the step is $J(0, 0) = \\frac{{1}}{{3}}(2^2 + 4^2 + 6^2) = {tex(J0)}$. '
      f'After it, the predictions are {", ".join(num(w1 * x + b1) for x in xs)}, so '
      f'$J({tex(w1)}, {tex(b1)}) = {tex(J1)}$. The cost fell, so the step went the right way.')

# ---------------------------------------------------------------- Q3: ROC table and AUC
with region('q3'):
    labels = [1, 0, 1, 0, 1, 0]
    probs = [0.9, 0.8, 0.7, 0.6, 0.4, 0.3]
    P = sum(labels)
    N = len(labels) - P
    p(f'There are **{P} positives** (S1, S3, S5) and **{N} negatives** (S2, S4, S6). '
      'At threshold t, predict positive when the probability is **≥ t**.')
    rows, pts = [], [(0.0, 0.0)]
    for t in [0.9, 0.8, 0.7, 0.6, 0.4, 0.3]:
        pred = [1 if q >= t else 0 for q in probs]
        tp = sum(1 for y, h in zip(labels, pred) if y == 1 and h == 1)
        fp = sum(1 for y, h in zip(labels, pred) if y == 0 and h == 1)
        fn, tn = P - tp, N - fp
        tpr, fpr = tp / P, fp / N
        pts.append((fpr, tpr))
        called = ', '.join(f'S{i + 1}' for i, h in enumerate(pred) if h)
        rows.append([t, called, tp, fp, fn, tn, f'{tp}/{P} = {num(tpr, 3)}', f'{fp}/{N} = {num(fpr, 3)}'])
    table(['Threshold', 'Called positive', 'TP', 'FP', 'FN', 'TN', 'TPR = TP/(TP+FN)', 'FPR = FP/(FP+TN)'], rows, 'clccccrr')
    # area by trapezoids over the sorted points
    pts_sorted = sorted(set(pts))
    area = 0.0
    steps = []
    for (xa, ya), (xb, yb) in zip(pts_sorted, pts_sorted[1:]):
        piece = (xb - xa) * (ya + yb) / 2
        if piece:
            steps.append((xa, xb, ya, yb, piece))
        area += piece
    p('**The ROC points**, adding (0, 0) for a threshold above every score: ' +
      ', '.join(f'({num(x, 3)}, {num(y, 3)})' for x, y in pts_sorted) + '.')
    pl = Plot(0, 1, 0, 1, w=360, h=320, pad=(46, 14, 12, 40), label='ROC curve for the six samples', narrow=True)
    pl.axes('False positive rate (FPR)', 'True positive rate (TPR)', [0, 1 / 3, 2 / 3, 1], [0, 1 / 3, 2 / 3, 1],
            xfmt=lambda v: num(v, 2), yfmt=lambda v: num(v, 2), grid=True)
    pl.area([(0, 0)] + pts_sorted + [(1, 0)])
    pl.seg(0, 0, 1, 1, 'm')
    pl.line(pts_sorted, 'a')
    for x, y in pts_sorted:
        pl.dot(x, y, 'fa')
    pl.text(0.55, 0.45, 'random guess (AUC 0.5)', anchor='start', dy=0)
    pl.text(0.25, 0.8, f'AUC = {num(area, 3)}', cls='ta')
    figure(pl, 'The staircase rises one step for every positive and moves right for every negative. The shaded area is the AUC.')
    parts = ' + '.join(f'{num(xb - xa, 3)} × {num((ya + yb) / 2, 3)}' for xa, xb, ya, yb, _ in steps)
    p(f'**AUC by rectangles** (each piece is width × height): {parts} = **{num(area, 3)}**.')
    # pair counting check
    pos = [q for q, y in zip(probs, labels) if y == 1]
    neg = [q for q, y in zip(probs, labels) if y == 0]
    wins = sum(1 for a in pos for b in neg if a > b)
    p(f'**Check by counting pairs.** AUC is also the chance that a random positive scores higher than a random negative: '
      f'{wins} of the {len(pos) * len(neg)} (positive, negative) pairs are ordered correctly, and {wins}/{len(pos) * len(neg)} = {num(wins / (len(pos) * len(neg)), 3)}.')

# ---------------------------------------------------------------- Q4: k-means (Unit 5)
with region('q4'):
    data = [0, 2, 4, 6, 24, 26]
    c1, c2 = 3.0, 4.0
    for it in (1, 2):
        rows, g1, g2 = [], [], []
        for v in data:
            d1, d2 = abs(v - c1), abs(v - c2)
            g = 'C1' if d1 <= d2 else 'C2'
            (g1 if g == 'C1' else g2).append(v)
            rows.append([v, num(d1), num(d2), g])
        p(f'**Iteration {it}** with c1 = {num(c1)}, c2 = {num(c2)}. Assign each point to the nearer centre:')
        table(['Point', f'Distance to c1 = {num(c1)}', f'Distance to c2 = {num(c2)}', 'Cluster'], rows, 'crrc')
        n1, n2 = mean(g1), mean(g2)
        p(f'New centres: c1 = mean({", ".join(map(str, g1))}) = **{num(n1)}**, '
          f'c2 = mean({", ".join(map(str, g2))}) = **{num(n2)}**.')
        c1, c2 = n1, n2

# ---------------------------------------------------------------- Q5: KNN off the scatter plot
with region('q5'):
    # Pixel positions read off a 400-dpi scan of the paper's figure; converted to axis units.
    plus_px = [(250, 180), (210, 235), (285, 235), (250, 275), (305, 290), (355, 268), (395, 268), (410, 188),
               (408, 220), (235, 340), (278, 352), (358, 347), (428, 362), (463, 348), (512, 348), (547, 338),
               (242, 378), (322, 392), (427, 400), (390, 428), (463, 422), (512, 375), (552, 450), (563, 503),
               (681, 385), (697, 374), (695, 398)]
    minus_px = [(597, 222), (670, 203), (707, 190), (688, 303), (697, 313)]
    test_px = (683, 330)
    to = lambda q: ((q[0] - 150) / 68, (525 - q[1]) / 47)
    plus = [to(q) for q in plus_px]
    minus = [to(q) for q in minus_px]
    tx, ty = to(test_px)
    pts = [(math.dist((tx, ty), q), '−') for q in minus] + [(math.dist((tx, ty), q), '+') for q in plus]
    pts.sort()
    pl = Plot(0, 10, 0, 7.6, w=520, h=360, pad=(30, 14, 12, 30), label='The training points and the test instance')
    pl.axes('X', 'Y')
    for x, y in plus:
        pl.mark(x, y, '+', 'ta')
    for x, y in minus:
        pl.mark(x, y, '−', 'tb')
    pl.dot(tx, ty, 'hollow', r=4.5)
    for k, cls in ((1, 'm'), (3, 'm'), (5, 'm')):
        pl.ring(tx, ty, (pts[k - 1][0] + pts[k][0]) / 2, cls)
    pl.text(tx, ty, 'test', dx=10, dy=-8)
    figure(pl, 'Redrawn from the paper (positions read off the scan, so approximate). Rings enclose the 1, 3 and 5 nearest points.')
    rows = []
    for i, (d, c) in enumerate(pts[:7], 1):
        rows.append([i, c, num(d, 2)])
    p('**The nearest training points, in order** (distances in the plot’s units, measured on the redrawn figure):')
    table(['Rank', 'Class', 'Distance'], rows, 'ccr')
    lines = []
    for k in (1, 3, 5):
        votes = [c for _, c in pts[:k]]
        m, pl_ = votes.count('−'), votes.count('+')
        win = '−' if m > pl_ else '+'
        lines.append(f'- **K = {k}:** {pl_} × (+), {m} × (−) → **{win}**')
    p(*lines)
    p(f'The whole training set has only **{len(minus)}** negatives and **{len(plus)}** positives.')
