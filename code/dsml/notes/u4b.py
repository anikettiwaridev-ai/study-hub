"""Unit 4B notes: worked examples and figures for docs/dsml/notes/unit-4b.md."""
import math
from fractions import Fraction as Fr
from _hub import num, tex, table, p, math_block, region, entropy
from _svg import Plot, figure

# ---------------------------------------------------------------- distance metrics
with region('distances'):
    P, Q = (1, 2, 3), (4, 6, 3)
    d = [abs(a - b) for a, b in zip(P, Q)]
    eu = math.sqrt(sum(x * x for x in d))
    ma = sum(d)
    mi3 = sum(x ** 3 for x in d) ** (1 / 3)
    dot = sum(a * b for a, b in zip(P, Q))
    cos = dot / (math.sqrt(sum(a * a for a in P)) * math.sqrt(sum(b * b for b in Q)))
    p(f'p = {P}, q = {Q}; the differences are ∣pᵢ − qᵢ∣ = {", ".join(map(str, d))}.')
    table(['Metric', 'Formula', 'Working', 'Value'], [
        ['Euclidean (L2)', '√Σ(pᵢ − qᵢ)²', f'√({" + ".join(f"{x}²" for x in d)}) = √{sum(x * x for x in d)}', f'**{num(eu, 4)}**'],
        ['Manhattan (L1)', 'Σ∣pᵢ − qᵢ∣', ' + '.join(map(str, d)), f'**{ma}**'],
        ['Minkowski, r = 3', '(Σ∣pᵢ − qᵢ∣³)^(1/3)', f'({" + ".join(str(x ** 3) for x in d)})^(1/3) = {sum(x ** 3 for x in d)}^(1/3)', f'**{num(mi3, 4)}**'],
        ['Cosine similarity', 'p·q / (‖p‖ ‖q‖)', f'{dot} / (√14 × √61)', f'**{num(cos, 4)}**'],
    ], 'llll')
    p('Minkowski with r = 1 is Manhattan and with r = 2 is Euclidean. Cosine is a **similarity** (1 = same direction), not a distance; it ignores length, which is why it suits text.')

# ---------------------------------------------------------------- KNN worked example + figure
with region('knn'):
    data = [(158, 58, 'M'), (158, 59, 'M'), (160, 59, 'M'), (163, 61, 'M'),
            (165, 61, 'L'), (165, 62, 'L'), (168, 63, 'L'), (170, 64, 'L')]
    qx, qy = 161, 61
    rows, ds = [], []
    for i, (h, w, s) in enumerate(data, 1):
        dd = math.sqrt((h - qx) ** 2 + (w - qy) ** 2)
        ds.append((dd, i, s))
        rows.append([i, h, w, s, f'√({(h - qx) ** 2} + {(w - qy) ** 2}) = √{(h - qx) ** 2 + (w - qy) ** 2}', num(dd, 3)])
    p(f'T-shirt sizes by height (cm) and weight (kg). New customer: **({qx}, {qy})**.')
    table(['#', 'Height', 'Weight', 'Size', 'Distance to (161, 61)', 'd'], rows, 'cccclr')
    ds.sort()
    lines = []
    for k in (3, 5):
        top = ds[:k]
        m = sum(1 for _, _, s in top if s == 'M')
        lines.append(f'- **k = {k}:** nearest are #{", #".join(str(i) for _, i, _ in top)} → M {m}, L {k - m} → **{"M" if m > k - m else "L"}**')
    wm = sum(1 / dd ** 2 for dd, _, s in ds[:5] if s == 'M')
    wl = sum(1 / dd ** 2 for dd, _, s in ds[:5] if s == 'L')
    lines.append(f'- **k = 5, weighted** (w = 1/d²): M = {num(wm, 3)}, L = {num(wl, 3)} → **M**, more decisively, because the M neighbours are closer.')
    p(*lines)
    pl = Plot(156, 172, 56, 66, w=480, h=300, pad=(40, 14, 12, 34), label='T-shirt sizes and the new customer')
    pl.axes('Height (cm)', 'Weight (kg)', [156, 160, 164, 168, 172], [56, 60, 64])
    for h, w, s in data:
        pl.mark(h, w, s, 'ta' if s == 'M' else 'tb')
    pl.dot(qx, qy, 'hollow', r=5)
    for k, cls, pos in ((3, 'a', (-0.75, -0.75)), (5, 'm', (0.72, 0.72))):
        r = (ds[k - 1][0] + ds[k][0]) / 2
        # rings in data units; axes are not equally scaled, so draw an ellipse in pixels
        rx = abs(pl.X(qx + r) - pl.X(qx))
        ry = abs(pl.Y(qy + r) - pl.Y(qy))
        pl.raw(f'<ellipse class="{cls}" style="stroke-width:1.2" cx="{pl.X(qx):.1f}" cy="{pl.Y(qy):.1f}" rx="{rx:.1f}" ry="{ry:.1f}"/>')
        pl.text(qx + r * pos[0], qy + r * pos[1], f'k = {k}', cls='ta' if k == 3 else '', anchor='end' if k == 3 else 'start', dx=-4 if k == 3 else 4)
    pl.text(qx, qy, 'new', dx=8, dy=16)
    figure(pl, 'M = medium, L = large. The solid ring holds the 3 nearest customers, the dashed ring the 5 nearest (the rings look oval only because the axes have different scales).')

# ---------------------------------------------------------------- curse of dimensionality (the slide's vectors)
with region('curse'):
    A = [1] * 11 + [0]
    B = [0] + [1] * 11
    C = [1] + [0] * 11
    D = [0] * 11 + [1]
    def eu(u, v): return math.sqrt(sum((a - b) ** 2 for a, b in zip(u, v)))
    def cs(u, v): return sum(a * b for a, b in zip(u, v)) / (math.sqrt(sum(a * a for a in u)) * math.sqrt(sum(b * b for b in v)))
    table(['Pair', 'Ones shared', 'Euclidean', 'Cosine'], [
        ['111111111110 vs 011111111111', sum(a * b for a, b in zip(A, B)), num(eu(A, B), 4), num(cs(A, B), 4)],
        ['100000000000 vs 000000000001', sum(a * b for a, b in zip(C, D)), num(eu(C, D), 4), num(cs(C, D), 4)],
    ], 'lccc')
    p('Euclidean distance calls both pairs equally far apart, although the first pair has 10 ones in common and the second none. '
      'Normalising to unit length (cosine) separates them. In high dimensions points become almost equidistant, so "nearest" stops meaning "similar".')

# ---------------------------------------------------------------- SVM margin
with region('svm'):
    w, b = (1, 1), -3
    nrm = math.sqrt(sum(x * x for x in w))
    plus = [(3, 1), (2, 2), (4, 2), (3, 3)]
    minus = [(1, 1), (0, 2), (0, 0), (1, 0)]
    rows = []
    for pt, lab in [(q, '+1') for q in plus] + [(q, '−1') for q in minus]:
        v = w[0] * pt[0] + w[1] * pt[1] + b
        where = 'on the margin: **support vector**' if abs(v) == 1 else 'outside the margin'
        rows.append([f'({pt[0]}, {pt[1]})', lab, f'{pt[0]} + {pt[1]} − 3', num(v), where])
    p('A trained linear SVM with **w = (1, 1), b = −3**: the boundary is x₁ + x₂ = 3, the plus-plane x₁ + x₂ = 4, the minus-plane x₁ + x₂ = 2.')
    table(['Point', 'Class', 'w·x + b', 'Value', 'Where it sits'], rows, 'cclrl')
    p(f'**Margin = 2/‖w‖ = 2/√2 = {num(2 / nrm, 4)}.** Four points touch the margin planes (value ±1): they are the support vectors, and only they decide the boundary. '
      f'A new point (2.5, 1) gives 2.5 + 1 − 3 = 0.5 > 0 → class **+1** (inside the margin, so the classifier is less sure of it).')
    pl = Plot(-0.5, 4.5, -0.5, 3.6, w=400, h=300, pad=(34, 12, 12, 30), label='A maximum-margin linear SVM', narrow=True)
    pl.axes('x₁', 'x₂', [0, 1, 2, 3, 4], [0, 1, 2, 3])
    for c, cls in ((3, 'a'), (4, 'm'), (2, 'm')):
        pl.seg(c - 3.6, 3.6, c + 0.5, -0.5, cls)
    for x, y in plus:
        pl.mark(x, y, '+', 'ta')
    for x, y in minus:
        pl.mark(x, y, '−', 'tb')
    for x, y in [(3, 1), (2, 2), (1, 1), (0, 2)]:
        pl.raw(f'<circle class="m" cx="{pl.X(x):.1f}" cy="{pl.Y(y):.1f}" r="10"/>')
    pl.text(0.2, 3.1, 'margin = 2/‖w‖', anchor='start')
    figure(pl, 'Solid line: the decision boundary. Dashed: the two margin planes. Circled: the support vectors.')

# ---------------------------------------------------------------- kernel trick
with region('kernel'):
    xs = [-3, -2, -1, 0, 1, 2, 3]
    lab = ['+', '+', '−', '−', '−', '+', '+']
    print('<div class="fig-row">')
    pl = Plot(-3.6, 3.6, -1, 1, w=240, h=200, pad=(10, 10, 22, 30), label='One dimension: not separable by a single threshold')
    pl.seg(-3.5, 0, 3.5, 0, 'ax')
    for x, l in zip(xs, lab):
        pl.mark(x, 0, l, 'ta' if l == '+' else 'tb')
        pl.text(x, 0, str(x), anchor='middle', dy=22)
    pl.text(-3.4, 0.85, '1-D: no single cut works', cls='lbl')
    print(pl.svg())
    pl = Plot(-3.6, 3.6, -0.8, 10, w=240, h=200, pad=(26, 10, 22, 22), label='Mapped to (x, x squared): separable by a line')
    pl.axes()
    pl.line([(-3.3 + i * 0.05, (-3.3 + i * 0.05) ** 2) for i in range(133)], 'm')
    for x, l in zip(xs, lab):
        pl.mark(x, x * x, l, 'ta' if l == '+' else 'tb')
    pl.seg(-3.5, 2.5, 3.5, 2.5, 'a')
    pl.text(-3.4, 9.2, 'z = (x, x²): a line works', cls='lbl')
    pl.text(3.4, 3.0, 'x² = 2.5', anchor='end', cls='ta')
    print(pl.svg())
    print('<div></div>')
    print('</div>')
    print()
    print('<p class="fig-cap">No threshold on x separates the classes (− in the middle, + on both sides). Add the feature x² and the horizontal line x² = 2.5 separates them.</p>')
    print()
    a, b_ = (1, 2), (3, 1)
    k = (a[0] * b_[0] + a[1] * b_[1] + 1) ** 2
    r2 = math.sqrt(2)
    phi = lambda v: [1, r2 * v[0], r2 * v[1], v[0] ** 2, v[1] ** 2, r2 * v[0] * v[1]]
    terms = [x * y for x, y in zip(phi(a), phi(b_))]
    p(f'**Why the kernel is a trick.** For a = (1, 2) and b = (3, 1), the polynomial kernel is (a·b + 1)² = (3 + 2 + 1)² = **{k}**: one dot product and a square. '
      f'The same number by building the 6-dimensional features φ(x) = (1, √2x₁, √2x₂, x₁², x₂², √2x₁x₂) and taking their dot product: '
      f'{" + ".join(num(t, 0) for t in terms)} = **{num(sum(terms), 0)}**. The kernel gets the high-dimensional answer without ever building φ.')

# ---------------------------------------------------------------- Naive Bayes worked example
with region('nb'):
    D = [('Sunny', 'Working', 'Go out'), ('Rainy', 'Broken', 'Go out'), ('Sunny', 'Working', 'Go out'),
         ('Sunny', 'Working', 'Go out'), ('Sunny', 'Working', 'Go out'), ('Rainy', 'Broken', 'Stay home'),
         ('Rainy', 'Broken', 'Stay home'), ('Sunny', 'Working', 'Stay home'), ('Sunny', 'Broken', 'Stay home'),
         ('Rainy', 'Broken', 'Stay home')]
    classes = ['Go out', 'Stay home']
    rows = []
    for i, (w_, c_, y) in enumerate(D, 1):
        rows.append([i, w_, c_, y])
    p('Ten days: the weather, the state of the car, and whether the person went out.')
    table(['Day', 'Weather', 'Car', 'Decision'], rows, 'clll')
    p('**Step 1. Count, per class** (the "training" of Naive Bayes is just this table):')
    crow = []
    for c in classes:
        sub = [r for r in D if r[2] == c]
        n = len(sub)
        crow.append([c, f'{n}/10', f'{sum(r[0] == "Sunny" for r in sub)}/{n}', f'{sum(r[0] == "Rainy" for r in sub)}/{n}',
                     f'{sum(r[1] == "Working" for r in sub)}/{n}', f'{sum(r[1] == "Broken" for r in sub)}/{n}'])
    table(['Class', 'P(class)', 'P(Sunny ∣ c)', 'P(Rainy ∣ c)', 'P(Working ∣ c)', 'P(Broken ∣ c)'], crow, 'lccccc')
    for qw, qc in (('Sunny', 'Working'), ('Rainy', 'Working')):
        sc = {}
        parts = []
        for c in classes:
            sub = [r for r in D if r[2] == c]
            n = len(sub)
            a_ = sum(r[0] == qw for r in sub)
            b2 = sum(r[1] == qc for r in sub)
            sc[c] = Fr(n, 10) * Fr(a_, n) * Fr(b2, n)
            parts.append(f'{c}: {n}/10 × {a_}/{n} × {b2}/{n} = **{num(sc[c], 3)}**')
        win = max(sc, key=sc.get)
        tot = sum(sc.values())
        p(f'**Classify ({qw}, {qc}).** ' + '; '.join(parts) + f'. → **{win}**. '
          f'Normalised, P({win} ∣ {qw}, {qc}) = {num(sc[win], 3)}/{num(tot, 3)} = {num(sc[win] / tot, 3)}.')

# ---------------------------------------------------------------- decision tree worked example (entropy, gain, Gini)
with region('tree'):
    D = [('High', 'Good', 'Yes'), ('High', 'Bad', 'Yes'), ('High', 'Good', 'Yes'), ('Low', 'Good', 'Yes'),
         ('Low', 'Bad', 'No'), ('Low', 'Bad', 'No'), ('High', 'Bad', 'No'), ('Low', 'Good', 'Yes')]
    table(['#', 'Income', 'Credit', 'Loan approved'], [[i + 1, *r] for i, r in enumerate(D)], 'clll')
    yes = sum(r[2] == 'Yes' for r in D)
    no = len(D) - yes
    H = entropy([yes, no])
    gini = lambda c: 1 - sum((x / sum(c)) ** 2 for x in c)
    G = gini([yes, no])
    p(f'**Parent:** {yes} Yes, {no} No. Entropy H = −(5/8)log₂(5/8) − (3/8)log₂(3/8) = **{num(H, 4)}**; Gini = 1 − (5/8)² − (3/8)² = **{num(G, 4)}**.')
    rows = []
    best = None
    for a, name in ((0, 'Income'), (1, 'Credit')):
        wh, wg, detail = 0.0, 0.0, []
        for v in sorted(set(r[a] for r in D)):
            sub = [r for r in D if r[a] == v]
            y_ = sum(r[2] == 'Yes' for r in sub)
            n_ = len(sub) - y_
            wh += len(sub) / len(D) * entropy([y_, n_])
            wg += len(sub) / len(D) * gini([y_, n_])
            detail.append(f'{v}: {y_}Y {n_}N (H = {num(entropy([y_, n_]), 4)}, Gini = {num(gini([y_, n_]), 4)})')
        rows.append([name, '; '.join(detail), num(wh, 4), f'**{num(H - wh, 4)}**', num(wg, 4), f'**{num(G - wg, 4)}**'])
    table(['Split on', 'Branches', 'Weighted H', 'Info gain', 'Weighted Gini', 'Gini decrease'], rows, 'llrrrr')
    p('**Credit wins on both measures.** Its Good branch is pure (4 Yes, 0 No), so it becomes a leaf at once. '
      'The Bad branch (rows 2, 5, 6, 7: 1 Yes, 3 No) is split again on Income: Low → No (2 of 2), High → mixed (1 Yes, 1 No: a leaf by majority, or a tie to report).')

with region('golftree'):
    W, H = 560, 230
    box = lambda x, y, t, cls='box': (f'<rect class="{cls}" x="{x - 46}" y="{y - 14}" width="92" height="26" rx="4"/>'
                                      f'<text x="{x}" y="{y + 4}" text-anchor="middle" class="lbl">{t}</text>')
    leaf = lambda x, y, t: (f'<rect class="area" x="{x - 30}" y="{y - 14}" width="60" height="26" rx="13"/>'
                            f'<text x="{x}" y="{y + 4}" text-anchor="middle" class="{"tc" if t == "Yes" else "tb"}" style="font-weight:600">{t}</text>')
    edge = lambda x1, y1, x2, y2, t: (f'<line class="ax" x1="{x1}" y1="{y1 + 12}" x2="{x2}" y2="{y2 - 14}"/>'
                                      f'<text x="{(x1 + x2) / 2 + (8 if x2 >= x1 else -8)}" y="{(y1 + y2) / 2 + 2}" text-anchor="{"start" if x2 >= x1 else "end"}">{t}</text>')
    parts = [f'<svg class="fig" viewBox="0 0 {W} {H}" role="img" aria-label="The Play Golf decision tree">']
    parts += [edge(280, 26, 100, 110, 'Sunny'), edge(280, 26, 280, 110, 'Overcast'), edge(280, 26, 460, 110, 'Rainy'),
              edge(100, 110, 40, 200, 'High'), edge(100, 110, 160, 200, 'Normal'),
              edge(460, 110, 400, 200, 'Strong'), edge(460, 110, 520, 200, 'Weak')]
    parts += [box(280, 26, 'Outlook'), box(100, 110, 'Humidity'), leaf(280, 110, 'Yes'), box(460, 110, 'Wind'),
              leaf(40, 200, 'No'), leaf(160, 200, 'Yes'), leaf(400, 200, 'No'), leaf(520, 200, 'Yes')]
    parts.append('</svg>')
    print('\n'.join(parts))
    print()
    print('<p class="fig-cap">The full tree ID3 grows from the Play Golf table. Outlook wins at the root; Overcast is pure; Sunny splits on Humidity and Rainy on Wind, and every leaf is then pure.</p>')
    print()
