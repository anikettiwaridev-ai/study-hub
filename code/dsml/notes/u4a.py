"""Unit 4A notes: worked examples and figures for docs/dsml/notes/unit-4a.md."""
import math
from _hub import num, tex, fixed, table, p, math_block, region, mean, sigmoid
from _svg import Plot, figure

# ---------------------------------------------------------------- least squares, the slides' 7 points
with region('ls'):
    X = [1.2, 2.3, 3.1, 3.4, 4.0, 4.6, 5.5]
    Y = [4.0, 5.6, 7.9, 8.0, 10.1, 10.4, 12.0]
    n = len(X)
    rows = [[num(x, 2), num(y, 2), num(x * x, 2), num(x * y, 2)] for x, y in zip(X, Y)]
    sx, sy, sxx, sxy = sum(X), sum(Y), sum(x * x for x in X), sum(x * y for x, y in zip(X, Y))
    rows.append([f'**{num(sx, 2)}**', f'**{num(sy, 2)}**', f'**{num(sxx, 2)}**', f'**{num(sxy, 2)}**'])
    table(['x', 'y', 'x²', 'xy'], rows, 'rrrr')
    a = (n * sxy - sx * sy) / (n * sxx - sx * sx)
    b = sy / n - a * sx / n
    math_block(
        f'a &= \\frac{{n\\sum xy - \\sum x\\sum y}}{{n\\sum x^2 - (\\sum x)^2}} = \\frac{{7({tex(sxy, 2)}) - ({tex(sx, 2)})({tex(sy, 2)})}}{{7({tex(sxx, 2)}) - ({tex(sx, 2)})^2}}'
        f' = \\frac{{{tex(n * sxy, 2)} - {tex(sx * sy, 2)}}}{{{tex(n * sxx, 2)} - {tex(sx * sx, 2)}}} = \\frac{{{tex(n * sxy - sx * sy, 2)}}}{{{tex(n * sxx - sx * sx, 2)}}} = {tex(a, 2)}',
        f'b &= \\bar y - a\\bar x = {tex(sy / n, 4)} - {tex(a, 4)} \\times {tex(sx / n, 4)} = {tex(b, 2)}',
    )
    yb = sy / n
    sse = sum((y - (a * x + b)) ** 2 for x, y in zip(X, Y))
    tss = sum((y - yb) ** 2 for y in Y)
    p(f'**Line: ŷ = {num(a, 2)}x + {num(b, 2)}.** The data was made from y = 2x + 1.5 plus noise, and the fit recovers it closely. '
      f'SSE = {num(sse, 3)}, TSS = {num(tss, 3)}, so R² = 1 − {num(sse, 3)}/{num(tss, 3)} = **{num(1 - sse / tss, 2)}**: the line explains 98% of the variation.')
    pl = Plot(0, 6, 0, 13, w=460, h=260, pad=(36, 14, 12, 34), label='The least-squares line through seven points')
    pl.axes('x', 'y', [0, 1, 2, 3, 4, 5, 6], [0, 4, 8, 12])
    pl.line([(0.8, a * 0.8 + b), (5.8, a * 5.8 + b)], 'a')
    for x, y in zip(X, Y):
        pl.seg(x, y, x, a * x + b, 'm')
        pl.dot(x, y, 'fb')
    pl.text(4.3, 3.0, f'ŷ = {num(a, 2)}x + {num(b, 2)}', cls='ta')
    figure(pl, 'The dashed lines are the residuals. Least squares picks the one line that makes the sum of their squares smallest.')

# ---------------------------------------------------------------- ridge shrinkage on one feature
with region('ridge'):
    X = [1, 2, 3]
    Y = [2, 4, 6]
    sxx, sxy = sum(x * x for x in X), sum(x * y for x, y in zip(X, Y))
    p(f'One feature, no intercept, data (1, 2), (2, 4), (3, 6). Then $X^TX = \\sum x^2 = {sxx}$ and $X^Ty = \\sum xy = {sxy}$, and the ridge weight is '
      f'$w = \\dfrac{{\\sum xy}}{{\\sum x^2 + \\lambda}}$.')
    rows = []
    for lam in [0, 1, 7, 14, 100]:
        w = sxy / (sxx + lam)
        rows.append([lam, f'{sxy}/({sxx} + {lam})', f'**{num(w, 4)}**', ', '.join(num(w * x, 2) for x in X)])
    table(['λ', 'Working', 'w', 'Predictions for x = 1, 2, 3'], rows, 'clrl')
    p('λ = 0 is ordinary least squares (w = 2, a perfect fit). As λ grows the weight **shrinks towards 0** but never reaches it. '
      'Ridge trades a little bias (worse fit on training data) for lower variance (a steadier model on new data).')

# ---------------------------------------------------------------- GD on f(w) = (w - 3)^2: the slides' example and learning rates
with region('gd1'):
    f = lambda w: (w - 3) ** 2
    df = lambda w: 2 * (w - 3)
    rows = []
    w = 0.0
    for it in range(0, 6):
        g = df(w)
        nw = w - 0.1 * g
        rows.append([it, num(w, 4), num(g, 4), f'{num(w, 4)} − 0.1 × ({num(g, 4)}) = {num(nw, 4)}', num(f(nw), 4)])
        w = nw
    p('The slides’ example: minimise $f(w) = (w - 3)^2$ from $w_0 = 0$ with $\\alpha = 0.1$. The gradient is $f\'(w) = 2(w - 3)$.')
    table(['Iteration', 'w', "f′(w) = 2(w − 3)", 'Update w ← w − α f′(w)', 'f(new w)'], rows, 'crrlr')
    p('After two steps **w = 1.08** (the slides’ answer). Each step closes 20% of the remaining gap to 3, so the steps shrink as the slope flattens: '
      'gradient descent slows down near the minimum by itself.')

with region('lr-cases'):
    f = lambda w: (w - 3) ** 2
    print('<div class="fig-row">')
    for alpha, title in [(0.1, 'α = 0.1: small, slow'), (0.85, 'α = 0.85: large, zig-zags in'), (1.05, 'α = 1.05: too large, diverges')]:
        pl = Plot(-1.5, 7.5, 0, 22, w=240, h=200, pad=(22, 6, 22, 22), label=title)
        pl.axes()
        pl.line([(-1.4 + i * 0.05, f(-1.4 + i * 0.05)) for i in range(178) if f(-1.4 + i * 0.05) <= 22], 'a')
        w = 0.0
        pts = [(w, f(w))]
        for _ in range(7):
            w = w - alpha * 2 * (w - 3)
            if f(w) > 22:
                break
            pts.append((w, f(w)))
        pl.line(pts, 'b')
        for x, y in pts:
            pl.dot(x, y, 'fb', r=2.8)
        pl.text(-1.2, 20.5, title, cls='lbl')
        print(pl.svg())
    print('</div>')
    print()
    print('<p class="fig-cap">Seven steps from w = 0 on f(w) = (w − 3)². Too small: crawls. Large: overshoots back and forth but still settles. Too large: every step overshoots further and the cost grows.</p>')
    print()

# ---------------------------------------------------------------- simple linear regression by GD, two iterations
with region('gd-lr'):
    X = [1, 2, 4]
    Y = [3, 4, 8]
    n = len(X)
    w = b = 0.0
    alpha = 0.05
    for it in (1, 2):
        yh = [w * x + b for x in X]
        e = [p_ - y for p_, y in zip(yh, Y)]
        rows = [[x, y, num(h, 4), num(ei, 4), num(ei * x, 4)] for x, y, h, ei in zip(X, Y, yh, e)]
        se, sex = sum(e), sum(ei * x for ei, x in zip(e, X))
        rows.append(['', '', '**Σ**', f'**{num(se, 4)}**', f'**{num(sex, 4)}**'])
        p(f'**Iteration {it}** (w = {num(w, 4)}, b = {num(b, 4)}):')
        table(['x', 'y', 'ŷ = wx + b', 'e = ŷ − y', 'e·x'], rows, 'ccrrr')
        gw, gb = 2 / n * sex, 2 / n * se
        nw, nb = w - alpha * gw, b - alpha * gb
        math_block(
            f'\\frac{{\\partial J}}{{\\partial w}} &= \\tfrac{{2}}{{n}}\\textstyle\\sum e\\,x = \\tfrac{{2}}{{3}}({tex(sex, 4)}) = {tex(gw, 4)}, &'
            f'w &\\leftarrow {tex(w, 4)} - 0.05({tex(gw, 4)}) = \\mathbf{{{tex(nw, 4)}}}',
            f'\\frac{{\\partial J}}{{\\partial b}} &= \\tfrac{{2}}{{n}}\\textstyle\\sum e = \\tfrac{{2}}{{3}}({tex(se, 4)}) = {tex(gb, 4)}, &'
            f'b &\\leftarrow {tex(b, 4)} - 0.05({tex(gb, 4)}) = \\mathbf{{{tex(nb, 4)}}}',
        )
        w, b = nw, nb
    J = lambda w_, b_: mean([(w_ * x + b_ - y) ** 2 for x, y in zip(X, Y)])
    xb, yb = mean(X), mean(Y)
    a_ls = sum((x - xb) * (y - yb) for x, y in zip(X, Y)) / sum((x - xb) ** 2 for x in X)
    b_ls = yb - a_ls * xb
    p(f'MSE: {num(J(0, 0), 4)} at the start → {num(J(w, b), 4)} after two iterations. (The least-squares answer for this data is w = {num(a_ls, 4)}, b = {num(b_ls, 4)}; gradient descent is walking towards it.)')

# ---------------------------------------------------------------- non-convex function
with region('nonconvex'):
    f = lambda x: x ** 4 - 3 * x ** 2 + x
    df = lambda x: 4 * x ** 3 - 6 * x + 1
    pl = Plot(-2.2, 2.2, -4, 4, w=520, h=280, pad=(36, 14, 12, 30), label='A non-convex function with a local and a global minimum')
    pl.axes('parameter', 'cost')
    xs = [-2.0 + i * 0.01 for i in range(401)]
    pl.line([(x, f(x)) for x in xs if -4 <= f(x) <= 4], 'a')
    for start, cls in ((-2.0, 'fc'), (1.9, 'fb')):
        x = start
        pts = [(x, f(x))]
        for _ in range(40):
            x -= 0.02 * df(x)
            pts.append((x, f(x)))
        pl.line([q for q in pts if -4 <= q[1] <= 4], 'c' if cls == 'fc' else 'b')
        pl.dot(start, f(start), cls, r=4)
        pl.dot(pts[-1][0], pts[-1][1], cls, r=5)
    gx = -1.3008
    lx = 1.1309
    pl.text(gx, f(gx) - 0.4, 'global minimum', anchor='middle', cls='tc', dy=8)
    pl.text(lx, f(lx) - 0.45, 'local minimum', anchor='middle', cls='tb', dy=8)
    mx = 0.1693
    pl.dot(mx, f(mx), 'fm', r=3.5)
    pl.text(mx, f(mx) + 0.45, 'local maximum: slope 0 here too', anchor='middle')
    figure(pl, 'Two runs of gradient descent on f(x) = x⁴ − 3x² + x. The green start rolls into the global minimum; the red start gets stuck in the local one. The slope is zero at both, so the algorithm cannot tell them apart.')

# ---------------------------------------------------------------- sigmoid
with region('sigmoid'):
    pl = Plot(-6, 6, 0, 1, w=480, h=250, pad=(40, 14, 12, 34), label='The sigmoid function')
    pl.axes('z = b₀ + b₁x₁ + …', 'σ(z)', [-6, -3, 0, 3, 6], [0, 0.5, 1], yfmt=lambda v: num(v, 1), grid=True)
    pl.line([(-6 + i * 0.05, sigmoid(-6 + i * 0.05)) for i in range(241)], 'a')
    for z, (tx, ty, anc) in {-3: (-5.8, 0.16, 'start'), 0: (-0.35, 0.53, 'end'), 1.9: (2.05, 0.68, 'start'), 3: (3.3, 0.82, 'start')}.items():
        pl.dot(z, sigmoid(z), 'fb')
        pl.text(tx, ty, f'σ({num(z)}) = {num(sigmoid(z), 3)}', anchor=anc)
    pl.text(5.8, 0.53, 'threshold 0.5 → class 1 above', anchor='end')
    figure(pl, 'Any real z is squashed into (0, 1). σ(0) = 0.5, so the decision boundary is the line z = 0.')

# ---------------------------------------------------------------- odds and odds ratios (the LogReg deck's numbers)
with region('odds'):
    pn = 402 / 4016
    on = pn / (1 - pn)
    oh = 101 / 345
    table(['Group', 'Delinquent / total', 'p', 'odds = p/(1 − p)'], [
        ['Normal testosterone', '402 / 4016', num(pn, 4), f'{num(pn, 4)} / {num(1 - pn, 4)} = **{num(on, 3)}**'],
        ['High testosterone', '101 / 446', num(101 / 446, 4), f'101/345 = **{num(oh, 3)}**'],
    ], 'llrl')
    p(f'**Odds ratio** = {num(oh, 4)} / {num(on, 4)} = **{num(oh / on, 2)}**: the odds of delinquency are about {num(oh / on, 1)} times higher in the high group. '
      f'(The slide divides the rounded odds, 0.293/0.111, and gets 2.64. Either is fine; show the working.)')
    b0, b1 = -2.6837, 0.0812
    rows = []
    for s in (40, 41):
        lo = b0 + b1 * s
        o = math.exp(lo)
        rows.append([s, f'−2.6837 + 0.0812 × {s} = {num(lo, 4)}', f'e^{num(lo, 4)} = {num(o, 3)}', num(o / (1 + o), 4)])
    p('**Cancer study:** log odds = −2.6837 + 0.0812 × SurvRate.')
    table(['SurvRate', 'log odds (z)', 'odds = e^z', 'p = odds/(1 + odds)'], rows, 'clll')
    p(f'Odds ratio for one extra unit: {num(math.exp(b0 + b1 * 41), 3)}/{num(math.exp(b0 + b1 * 40), 3)} = {num(math.exp(b1), 4)} = e^0.0812: the odds rise by {num(100 * (math.exp(b1) - 1), 1)}% per unit, '
      f'while the probability only moves from {num(sigmoid(b0 + b1 * 40), 4)} to {num(sigmoid(b0 + b1 * 41), 4)}.')
    b0, b1 = -3.0597, 0.1615
    p14 = sigmoid(b0 + b1 * 14)
    p(f'**Programming-task study:** b₀ = −3.0597, b₁ = 0.1615 (x = months of experience). '
      f'p(14 months) = 1/(1 + e^−(−3.0597 + 0.1615 × 14)) = **{num(p14, 2)}**. '
      f'Odds ratio per month = e^0.1615 = **{num(math.exp(b1), 3)}** (+{num(100 * (math.exp(b1) - 1), 1)}% per month); '
      f'over 15 months (10 vs 25) it is e^(15 × 0.1615) = **{num(math.exp(15 * b1), 1)}**, an eleven-fold rise in the odds.')

# ---------------------------------------------------------------- one gradient step for logistic regression
with region('logistic-gd'):
    X = [1, 2, 4]
    Y = [0, 1, 1]
    w = b = 0.0
    alpha = 0.1
    m = len(X)
    rows = []
    for x, y in zip(X, Y):
        z = w * x + b
        pr = sigmoid(z)
        rows.append([x, y, num(z), num(pr, 4), num(pr - y, 4), num((pr - y) * x, 4)])
    s0 = sum(sigmoid(w * x + b) - y for x, y in zip(X, Y))
    s1 = sum((sigmoid(w * x + b) - y) * x for x, y in zip(X, Y))
    rows.append(['', '', '', '**Σ**', f'**{num(s0, 4)}**', f'**{num(s1, 4)}**'])
    table(['x', 'y', 'z = wx + b', 'p = σ(z)', 'p − y', '(p − y)x'], rows, 'ccrrrr')
    gw, gb = s1 / m, s0 / m
    nw, nb = w - alpha * gw, b - alpha * gb
    loss = lambda w_, b_: -mean([y * math.log(sigmoid(w_ * x + b_)) + (1 - y) * math.log(1 - sigmoid(w_ * x + b_)) for x, y in zip(X, Y)])
    math_block(
        f'\\frac{{\\partial J}}{{\\partial w}} &= \\tfrac{{1}}{{m}}\\textstyle\\sum (p - y)x = \\tfrac{{1}}{{3}}({tex(s1, 4)}) = {tex(gw, 4)}, & w &\\leftarrow 0 - 0.1({tex(gw, 4)}) = \\mathbf{{{tex(nw, 4)}}}',
        f'\\frac{{\\partial J}}{{\\partial b}} &= \\tfrac{{1}}{{m}}\\textstyle\\sum (p - y) = \\tfrac{{1}}{{3}}({tex(s0, 4)}) = {tex(gb, 4)}, & b &\\leftarrow 0 - 0.1({tex(gb, 4)}) = \\mathbf{{{tex(nb, 4)}}}',
    )
    p(f'Log loss falls from {num(loss(0, 0), 4)} (that is ln 2: every p = 0.5) to {num(loss(nw, nb), 4)}. The update has exactly the shape of linear regression’s; only ŷ = σ(z) is different.')
