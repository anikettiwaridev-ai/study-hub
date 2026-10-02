"""Numerical drills: every answer on docs/dsml/practice.md."""
import math
from fractions import Fraction as Fr
from _hub import num, tex, fixed, table, p, math_block, region, mean, pstdev, sstdev, sigmoid, entropy

# 1. min-max and z-score
with region('d1'):
    x = [5, 10, 15, 30]
    lo, hi, m, s = min(x), max(x), mean(x), pstdev(x)
    table(['x', 'Min-max', 'Z-score (population σ)'], [[v, num((v - lo) / (hi - lo), 4), num((v - m) / s, 4)] for v in x], 'crr')
    p(f'min = {lo}, max = {hi}, μ = {num(m)}, σ = √(Σ(x − μ)²/4) = {num(s, 4)}. Check: the z-scores add to 0.')

# 2. min-max to [-1, 1]
with region('d2'):
    x = [-10, 0, 10, 20, 30]
    lo, hi = min(x), max(x)
    table(['x', "x′ = 2(x − min)/(max − min) − 1"], [[num(v), num(2 * (v - lo) / (hi - lo) - 1, 4)] for v in x], 'cr')
    p('Min-max to a range [a, b] is a + (x − min)(b − a)/(max − min); for [−1, 1] that is the formula above.')

# 3. z-score outliers
with region('d3'):
    x = [12, 14, 15, 13, 16, 14, 13, 60]
    m, s = mean(x), pstdev(x)
    table(['x', 'z'], [[v, num((v - m) / s, 3)] for v in x], 'cr')
    out = [v for v in x if abs((v - m) / s) > 2]
    p(f'μ = {num(m, 3)}, σ = {num(s, 3)}. With |z| > 2: **{", ".join(map(str, out))}** is an outlier '
      f'(z = {num((60 - m) / s, 3)}). With the stricter |z| > 3, nothing is flagged: one big value inflates σ enough to hide itself.')

# 4. Pearson r, negative
with region('d4'):
    X = [10, 20, 30, 40, 50]
    Y = [40, 35, 30, 22, 18]
    mx, my = mean(X), mean(Y)
    sxy = sum((a - mx) * (b - my) for a, b in zip(X, Y))
    sxx = sum((a - mx) ** 2 for a in X)
    syy = sum((b - my) ** 2 for b in Y)
    table(['x', 'y', 'x − x̄', 'y − ȳ', 'product', '(x − x̄)²', '(y − ȳ)²'],
          [[a, b, num(a - mx), num(b - my, 2), num((a - mx) * (b - my), 2), num((a - mx) ** 2), num((b - my) ** 2, 2)] for a, b in zip(X, Y)]
          + [['', '', '', '**Σ**', f'**{num(sxy, 2)}**', f'**{num(sxx)}**', f'**{num(syy, 2)}**']], 'ccrrrrr')
    r = sxy / math.sqrt(sxx * syy)
    p(f'x̄ = {num(mx)}, ȳ = {num(my)}. r = {num(sxy, 2)}/√({num(sxx)} × {num(syy, 2)}) = **{num(r, 4)}**: a very strong **negative** linear relationship.')

# 5. least squares, the slides' advertising data
with region('d5'):
    X = [90, 120, 150, 100, 130]
    Y = [1000, 1300, 1800, 1200, 1380]
    n = len(X)
    sx, sy, sxx, sxy = sum(X), sum(Y), sum(a * a for a in X), sum(a * b for a, b in zip(X, Y))
    a = (n * sxy - sx * sy) / (n * sxx - sx * sx)
    b = sy / n - a * sx / n
    pred = a * 200 + b
    yb = sy / n
    sse = sum((y - (a * x + b)) ** 2 for x, y in zip(X, Y))
    tss = sum((y - yb) ** 2 for y in Y)
    p(f'Σx = {sx}, Σy = {sy}, Σx² = {sxx}, Σxy = {sxy}, n = {n}.')
    math_block(
        f'a &= \\frac{{{n}({sxy}) - ({sx})({sy})}}{{{n}({sxx}) - ({sx})^2}} = \\frac{{{n * sxy - sx * sy}}}{{{n * sxx - sx * sx}}} = {tex(a, 4)}',
        f'b &= \\bar y - a\\bar x = {tex(yb, 2)} - {tex(a, 4)} \\times {tex(sx / n, 2)} = {tex(b, 2)}',
    )
    p(f'**ŷ = {num(a, 4)}x − {num(-b, 2)}.** For an advertisement spend of 200 the predicted sales are {num(a, 4)} × 200 − {num(-b, 2)} = **{num(pred, 2)}**. '
      f'R² = 1 − {num(sse, 1)}/{num(tss, 1)} = {num(1 - sse / tss, 3)}. (200 is outside the data, 90–150, so this is an extrapolation.)')

# 6. GD on a single-variable function
with region('d6'):
    w, a_ = 0.0, 0.25
    rows = []
    for it in range(1, 4):
        g = 2 * w - 4
        nw = w - a_ * g
        rows.append([it, num(w, 4), num(g, 4), f'{num(w, 4)} − 0.25 × ({num(g, 4)}) = **{num(nw, 4)}**'])
        w = nw
    p('f(w) = w² − 4w + 5, so f′(w) = 2w − 4; the minimum is at w = 2.')
    table(['Iteration', 'w (old)', 'f′(w)', 'new w'], rows, 'crrl')
    p('Each step halves the gap to 2 (2 → 1 → 0.5 → 0.25 away).')

# 7. GD for linear regression, the 1/(2n) convention
with region('d7'):
    X, Y = [2, 4, 6], [5, 9, 13]
    w = b = 0.0
    al = 0.01
    e = [w * x + b - y for x, y in zip(X, Y)]
    gw = sum(ei * x for ei, x in zip(e, X)) / len(X)
    gb = sum(e) / len(X)
    table(['x', 'y', 'ŷ', 'e = ŷ − y', 'e·x'], [[x, y, 0, num(ei), num(ei * x)] for x, y, ei in zip(X, Y, e)]
          + [['', '', '**Σ**', f'**{num(sum(e))}**', f'**{num(sum(ei * x for ei, x in zip(e, X)))}**']], 'ccrrr')
    math_block(
        f'\\frac{{\\partial J}}{{\\partial w}} &= \\tfrac{{1}}{{n}}\\textstyle\\sum e\\,x = \\tfrac{{1}}{{3}}({tex(sum(ei * x for ei, x in zip(e, X)))}) = {tex(gw, 4)}, & w &= 0 - 0.01({tex(gw, 4)}) = \\mathbf{{{tex(w - al * gw, 4)}}}',
        f'\\frac{{\\partial J}}{{\\partial b}} &= \\tfrac{{1}}{{n}}\\textstyle\\sum e = \\tfrac{{1}}{{3}}({tex(sum(e))}) = {tex(gb, 4)}, & b &= 0 - 0.01({tex(gb, 4)}) = \\mathbf{{{tex(b - al * gb, 4)}}}',
    )
    p('With J = (1/2n)Σ(ŷ − y)² the 2 cancels, so the gradient has 1/n in front. With the 2/n convention every gradient, and so every step, doubles.')

# 8. GD, two features, one iteration
with region('d8'):
    D = [(1, 1, 4), (2, 0, 5), (0, 2, 6)]
    th = [0.0, 0.0, 0.0]
    al = 0.1
    n = len(D)
    e = [th[0] + th[1] * a + th[2] * b - y for a, b, y in D]
    s0, s1, s2 = sum(e), sum(ei * a for ei, (a, _, _) in zip(e, D)), sum(ei * b for ei, (_, b, _) in zip(e, D))
    table(['x₁', 'x₂', 'y', 'ŷ', 'e', 'e·x₁', 'e·x₂'], [[a, b, y, 0, num(ei), num(ei * a), num(ei * b)] for (a, b, y), ei in zip(D, e)]
          + [['', '', '', '**Σ**', f'**{num(s0)}**', f'**{num(s1)}**', f'**{num(s2)}**']], 'cccrrrr')
    g = [2 / n * s0, 2 / n * s1, 2 / n * s2]
    new = [t - al * gi for t, gi in zip(th, g)]
    p(f'Gradients (2/n convention): ∂J/∂θ₀ = (2/3)({num(s0)}) = {num(g[0], 4)}, ∂J/∂θ₁ = (2/3)({num(s1)}) = {num(g[1], 4)}, ∂J/∂θ₂ = (2/3)({num(s2)}) = {num(g[2], 4)}.')
    p(f'**After one iteration: θ₀ = {num(new[0], 4)}, θ₁ = {num(new[1], 4)}, θ₂ = {num(new[2], 4)}.**')

# 9. logistic regression
with region('d9'):
    b0, b1 = -4, 0.05
    z = b0 + b1 * 60
    pr = sigmoid(z)
    p(f'z = −4 + 0.05 × 60 = {num(z)}; p = 1/(1 + e^{num(-z)}) = 1/(1 + {num(math.exp(-z), 4)}) = **{num(pr, 4)}** → predicted class **0** (fail) at threshold 0.5.')
    p(f'Odds = p/(1 − p) = {num(pr / (1 - pr), 4)} (= e^z = e^−1). Odds ratio per extra hour = e^0.05 = **{num(math.exp(b1), 4)}**: each hour multiplies the odds of passing by about 1.05 (+{num(100 * (math.exp(b1) - 1), 2)}%). '
      f'p = 0.5 exactly when z = 0, that is −4 + 0.05x = 0, so **x = {num(4 / 0.05)} hours**.')

# 10. confusion matrix from a story
with region('d10'):
    TP, FP, FN, TN = 150, 30, 50, 770
    table(['', 'Flagged spam', 'Let through', 'Total'], [
        ['**Actually spam**', f'TP = {TP}', f'FN = {FN}', TP + FN],
        ['**Actually genuine**', f'FP = {FP}', f'TN = {TN}', FP + TN],
    ], 'lccc')
    table(['Metric', 'Value'], [
        ['Accuracy', f'{TP + TN}/1000 = **{num((TP + TN) / 1000, 4)}**'],
        ['Precision', f'{TP}/{TP + FP} = **{num(TP / (TP + FP), 4)}**'],
        ['Recall', f'{TP}/{TP + FN} = **{num(TP / (TP + FN), 4)}**'],
        ['F1', f'{2 * TP}/{2 * TP + FP + FN} = **{num(2 * TP / (2 * TP + FP + FN), 4)}**'],
        ['Specificity', f'{TN}/{TN + FP} = **{num(TN / (TN + FP), 4)}**'],
    ], 'lr')
    p('For a spam filter, precision matters most: 30 genuine emails went to spam, and each one is a message someone may never read.')

# 11. ROC and AUC
with region('d11'):
    data = [(0.9, 1), (0.75, 1), (0.7, 0), (0.5, 1), (0.4, 0), (0.2, 0)]
    P = sum(l for _, l in data)
    N = len(data) - P
    rows, pts = [], [(0.0, 0.0)]
    for t, _ in data:
        tp = sum(1 for s, l in data if s >= t and l)
        fp = sum(1 for s, l in data if s >= t and not l)
        pts.append((fp / N, tp / P))
        rows.append([t, tp, fp, num(tp / P, 3), num(fp / N, 3)])
    table(['t', 'TP', 'FP', 'TPR', 'FPR'], rows, 'ccccc')
    area = sum((b[0] - a[0]) * (a[1] + b[1]) / 2 for a, b in zip(pts, pts[1:]))
    wins = sum(1 for s, l in data if l for s2, l2 in data if not l2 and s > s2)
    p(f'Points: {", ".join(f"({num(x, 3)}, {num(y, 3)})" for x, y in pts)}. **AUC = {num(area, 4)}** '
      f'(check: {wins} of {P * N} positive–negative pairs correctly ordered = {num(wins / (P * N), 4)}).')

# 12. cross-validation sizes
with region('d12'):
    table(['Set-up', 'N1 (models)', 'N2 (train size)', 'N3 (test size)'], [
        ['4-fold on 60 examples', 4, 3 * 60 // 4, 60 // 4],
        ['LOOCV on 25 examples', 25, 24, 1],
        ['10-fold on 250 examples', 10, 225, 25],
    ], 'lccc')

# 13. KNN classification
with region('d13'):
    T = [('A', 1, 1, 'Red'), ('B', 2, 1, 'Red'), ('C', 4, 3, 'Blue'), ('D', 5, 4, 'Blue'), ('E', 3, 5, 'Blue'), ('F', 1, 3, 'Red')]
    q = (3, 2)
    rows, ds = [], []
    for nm, x, y, c in T:
        de = math.sqrt((x - q[0]) ** 2 + (y - q[1]) ** 2)
        dm = abs(x - q[0]) + abs(y - q[1])
        ds.append((de, nm, c, dm))
        rows.append([nm, f'({x}, {y})', c, num(de, 3), dm])
    table(['Point', 'Coordinates', 'Class', 'Euclidean to (3, 2)', 'Manhattan'], rows, 'cccrc')
    ds.sort()
    top = ds[:3]
    p(f'Sorted (Euclidean): {", ".join(f"{nm} {num(d, 3)}" for d, nm, _, _ in ds)}. '
      f'The 3rd place is a tie between A and F at {num(ds[2][0], 3)}, but both are Red, so the vote is unaffected: '
      f'k = 3 → B (Red), C (Blue), A or F (Red) → **Red**. '
      f'k = 5 → {", ".join(c for _, _, c, _ in ds[:5])} → **Red** (3 to 2).')

# 14. KNN regression
with region('d14'):
    nb = [(2.0, 52), (3.0, 48), (4.0, 60)]
    avg = mean([v for _, v in nb])
    w = [1 / d ** 2 for d, _ in nb]
    wavg = sum(wi * v for wi, (_, v) in zip(w, nb)) / sum(w)
    p(f'The 3 nearest houses (distance, price in lakh): {", ".join(f"({num(d)}, {v})" for d, v in nb)}. '
      f'Plain KNN regression: the **average**, ({" + ".join(str(v) for _, v in nb)})/3 = **{num(avg, 2)}**. '
      f'Distance-weighted (w = 1/d²: {", ".join(num(x, 4) for x in w)}): Σw·price/Σw = **{num(wavg, 2)}**, pulled towards the nearest house.')

# 15. decision tree
with region('d15'):
    D = [('Sunny', 'Low', 'Yes'), ('Sunny', 'High', 'No'), ('Rainy', 'High', 'No'),
         ('Rainy', 'Low', 'No'), ('Sunny', 'Low', 'Yes'), ('Rainy', 'Low', 'Yes')]
    yes = sum(r[2] == 'Yes' for r in D)
    H = entropy([yes, len(D) - yes])
    rows = []
    for a, name in ((0, 'Weather'), (1, 'Wind')):
        wh = 0.0
        parts = []
        for v in sorted(set(r[a] for r in D)):
            sub = [r for r in D if r[a] == v]
            y_ = sum(r[2] == 'Yes' for r in sub)
            h = entropy([y_, len(sub) - y_])
            wh += len(sub) / len(D) * h
            parts.append(f'{v} {y_}Y/{len(sub) - y_}N (H = {num(h, 4)})')
        rows.append([name, '; '.join(parts), num(wh, 4), f'**{num(H - wh, 4)}**'])
    p(f'Parent: {yes} Yes, {len(D) - yes} No, so H = **{num(H, 4)}** (a 50/50 split).')
    table(['Attribute', 'Branches', 'Weighted H', 'Gain'], rows, 'llrr')
    p('**Wind** has the higher gain, so it is the root: its High branch is pure (both No).')

# 16. Naive Bayes with Laplace smoothing
with region('d16'):
    D = [('Yes', 'Yes', 'Spam'), ('Yes', 'No', 'Spam'), ('Yes', 'Yes', 'Spam'), ('No', 'Yes', 'Spam'),
         ('No', 'No', 'Ham'), ('No', 'No', 'Ham'), ('Yes', 'No', 'Ham'), ('No', 'No', 'Ham')]
    q = ('Yes', 'Yes')
    rows, sc, scl = [], {}, {}
    for c in ('Spam', 'Ham'):
        sub = [r for r in D if r[2] == c]
        n = len(sub)
        a_ = sum(r[0] == q[0] for r in sub)
        b_ = sum(r[1] == q[1] for r in sub)
        sc[c] = Fr(n, 8) * Fr(a_, n) * Fr(b_, n)
        scl[c] = Fr(n, 8) * Fr(a_ + 1, n + 2) * Fr(b_ + 1, n + 2)
        rows.append([c, f'{n}/8', f'{a_}/{n}', f'{b_}/{n}', num(sc[c], 4), f'({a_}+1)/({n}+2) × ({b_}+1)/({n}+2) × {n}/8 = {num(scl[c], 4)}'])
    table(['Class', 'P(c)', 'P(free = Yes ∣ c)', 'P(link = Yes ∣ c)', 'Score', 'With Laplace smoothing'], rows, 'lcccrl')
    p(f'Without smoothing, Ham scores exactly 0 because no Ham email had a link (P(link ∣ Ham) = 0/4), whatever the other feature says. '
      f'Either way **Spam** wins; normalised with smoothing, P(Spam ∣ free, link) = {num(scl["Spam"] / sum(scl.values()), 4)}.')

# 17. SVM margin
with region('d17'):
    w, b = (2, -1), -1
    nrm = math.sqrt(5)
    rows = []
    for pt in [(1, 0), (0, 1), (2, 1), (1, 1)]:
        v = w[0] * pt[0] + w[1] * pt[1] + b
        rows.append([f'({pt[0]}, {pt[1]})', f'2({pt[0]}) − ({pt[1]}) − 1', num(v), '+1' if v > 0 else ('−1' if v < 0 else 'on the boundary'),
                     'support vector (on a margin plane)' if abs(v) == 1 else ''])
    table(['Point', 'w·x + b', 'Value', 'Class', ''], rows, 'cccll')
    p(f'‖w‖ = √(2² + (−1)²) = √5, so the margin = 2/√5 = **{num(2 / nrm, 4)}**.')

# 18. Q-learning
with region('d18'):
    p(f'Q̂(s, a) ← r + γ max Q̂(s′, a′) = 10 + 0.8 × max(20, 35, 5) = 10 + 0.8 × 35 = **{num(10 + 0.8 * 35)}**.')
