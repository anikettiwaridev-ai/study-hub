"""End-semester, spring 2025 (DSN4005): every worked number on docs/dsml/papers/endsem-2025.md (Units 1-4)."""
import math
from fractions import Fraction as Fr
from _hub import num, tex, fixed, table, p, math_block, region, mean, pstdev, sstdev, entropy

# ---------------------------------------------------------------- Q1(a): least-squares line by year
with region('q1a'):
    years = [2005, 2006, 2007, 2008, 2009]
    sales = [12, 19, 29, 37, 45]
    u = [y - 2007 for y in years]
    n = len(u)
    rows = [[yr, num(ui), s, ui * ui, num(ui * s)] for yr, ui, s in zip(years, u, sales)]
    su, ss, suu, sus = sum(u), sum(sales), sum(ui * ui for ui in u), sum(ui * s for ui, s in zip(u, sales))
    rows.append(['**Σ**', f'**{su}**', f'**{ss}**', f'**{suu}**', f'**{sus}**'])
    p('**Trick: code the years** as u = year − 2007, so u = −2, −1, 0, 1, 2 and Σu = 0. Shifting x never changes the slope, and the sums stay tiny.')
    table(['Year', 'u', 'y (sales)', 'u²', 'u·y'], rows, 'ccccc')
    a = Fr(n * sus - su * ss, n * suu - su * su)
    b = Fr(ss, n) - a * Fr(su, n)
    math_block(
        f'a &= \\frac{{n\\sum uy - \\sum u \\sum y}}{{n\\sum u^2 - (\\sum u)^2}} = \\frac{{{n}({sus}) - ({su})({ss})}}{{{n}({suu}) - ({su})^2}} = \\frac{{{n * sus}}}{{{n * suu}}} = {tex(a)}',
        f'b &= \\bar y - a\\,\\bar u = {tex(Fr(ss, n))} - {tex(a)}(0) = {tex(b)}',
    )
    b_year = b - a * 2007
    p(f'So **y = {num(a)}u + {num(b)}**. Back in years (u = year − 2007): y = {num(a)}(year − 2007) + {num(b)}, i.e. '
      f'**y = {num(a)} × year − {num(-b_year)}** (a = {num(a)}, b = −{num(-b_year)}).')
    pred = a * (2012 - 2007) + b
    p(f'**(ii) 2012:** u = 2012 − 2007 = 5, so y = {num(a)}(5) + {num(b)} = **{num(pred)} million dollars**.')

# ---------------------------------------------------------------- Q1(b): min-max and z-score
with region('q1b'):
    M = [8, 10, 15, 20]
    lo, hi = min(M), max(M)
    mu, sp, ss_ = mean(M), pstdev(M), sstdev(M)
    p(f'min = {lo}, max = {hi}; mean μ = {sum(M)}/4 = {num(mu)}; population σ = √(Σ(x − μ)²/4) = √({num(sum((x - mu) ** 2 for x in M) / 4, 4)}) = {num(sp, 4)}.')
    rows = [[x, f'({x} − {lo})/{hi - lo}', f'**{num((x - lo) / (hi - lo), 4)}**', f'({x} − {num(mu)})/{num(sp, 4)}', f'**{num((x - mu) / sp, 4)}**', num((x - mu) / ss_, 4)] for x in M]
    table(['Marks', 'Min-max: (x − min)/(max − min)', 'x′', 'Z-score: (x − μ)/σ', 'z', 'z with sample σ = ' + num(ss_, 4)], rows, 'clrlrr')
    p('Check: the min-max values run exactly from 0 to 1; the z-scores add up to 0. '
      'Use the population σ unless your teacher uses the sample one; write which you used.')

# ---------------------------------------------------------------- Q3(a): KNN with an assumed new customer
with region('q3a'):
    data = [(1, 25, 40, 'No'), (2, 30, 60, 'No'), (3, 35, 65, 'Yes'), (4, 40, 80, 'Yes'),
            (5, 45, 60, 'Yes'), (6, 50, 50, 'No'), (7, 55, 90, 'Yes')]
    qa, qi = 42, 70
    d = []
    for i, a_, inc, lab in data:
        dd = math.sqrt((a_ - qa) ** 2 + (inc - qi) ** 2)
        d.append((dd, i, a_, inc, lab))
    rows = [[i, a_, inc, lab, f'√(({a_} − {qa})² + ({inc} − {qi})²) = √{(a_ - qa) ** 2 + (inc - qi) ** 2}', num(dd, 3)] for dd, i, a_, inc, lab in d]
    p(f'**(i) Euclidean distance** from the new customer (Age {qa}, Income {qi}) to every row:')
    table(['ID', 'Age', 'Income', 'Buys', 'Distance', 'Value'], rows, 'cccclr')
    d.sort()
    rows = [[k + 1, i, lab, num(dd, 3)] for k, (dd, i, _, _, lab) in enumerate(d)]
    p('**(ii) Sort by distance** and take the 3 nearest:')
    table(['Rank', 'ID', 'Buys', 'Distance'], rows, 'cccr')
    top = [lab for _, _, _, _, lab in d[:3]]
    p(f'**(iii) Vote:** the 3 nearest are IDs {", ".join(str(x[1]) for x in d[:3])}, labelled {", ".join(top)}. '
      f'Yes = {top.count("Yes")}, No = {top.count("No")}, so the prediction is **{max(set(top), key=top.count)}: the customer buys**.')

# ---------------------------------------------------------------- Q3(b): entropy and information gain
with region('q3b'):
    rows_ = [('<=30', 'High', 'No', 'No'), ('<=30', 'High', 'Yes', 'Yes'), ('31-40', 'High', 'No', 'Yes'),
             ('>40', 'Medium', 'No', 'Yes'), ('>40', 'Low', 'Yes', 'No'), ('>40', 'Low', 'Yes', 'Yes'),
             ('31-40', 'Low', 'Yes', 'Yes')]
    yes = sum(r[3] == 'Yes' for r in rows_)
    no = len(rows_) - yes
    H = entropy([yes, no])
    p(f'**(i) Entropy of the whole dataset:** {yes} Yes, {no} No out of 7.')
    math_block(f'H(S) = -\\tfrac{{{yes}}}{{7}}\\log_2\\tfrac{{{yes}}}{{7}} - \\tfrac{{{no}}}{{7}}\\log_2\\tfrac{{{no}}}{{7}}'
               f' = {tex(yes / 7 * -math.log2(yes / 7), 4)} + {tex(no / 7 * -math.log2(no / 7), 4)} = \\mathbf{{{tex(H, 4)}}}')
    gains = {}
    p('**(ii) Information gain of each attribute.**')
    for a, name in enumerate(['Age', 'Income', 'Student']):
        vals = []
        for r in rows_:
            if r[a] not in vals:
                vals.append(r[a])
        trows, wsum = [], 0.0
        for v in vals:
            sub = [r for r in rows_ if r[a] == v]
            y_ = sum(r[3] == 'Yes' for r in sub)
            n_ = len(sub) - y_
            h = entropy([y_, n_])
            wsum += len(sub) / 7 * h
            trows.append([v.replace('<=', '≤'), y_, n_, num(h, 4), f'{len(sub)}/7 × {num(h, 4)} = {num(len(sub) / 7 * h, 4)}'])
        gains[name] = H - wsum
        table([name, 'Yes', 'No', 'Entropy', 'Weighted'], trows, 'lccrr')
        p(f'Gain({name}) = {num(H, 4)} − {num(wsum, 4)} = **{num(gains[name], 4)}**')
    best = max(gains, key=gains.get)
    p(f'**(iii)** {", ".join(f"{k} {num(v, 4)}" for k, v in gains.items())}. **{best}** has the highest gain, so it is the root.')

# ---------------------------------------------------------------- Q4(a): Naive Bayes
with region('q4a'):
    D = [('Red', 'Round', 'Apple'), ('Red', 'Long', 'Chilli'), ('Green', 'Round', 'Apple'),
         ('Green', 'Long', 'Cucumber'), ('Red', 'Round', 'Apple')]
    classes = ['Apple', 'Chilli', 'Cucumber']
    rows = []
    best, scores = None, {}
    for c in classes:
        sub = [r for r in D if r[2] == c]
        nr, nl, nc = sum(r[0] == 'Red' for r in sub), sum(r[1] == 'Long' for r in sub), len(sub)
        sc = Fr(nc, len(D)) * Fr(nr, nc) * Fr(nl, nc)
        scores[c] = sc
        rows.append([c, f'{nc}/5', f'{nr}/{nc}', f'{nl}/{nc}', f'{nc}/5 × {nr}/{nc} × {nl}/{nc} = **{num(sc, 3)}**'])
    table(['Class c', 'P(c)', 'P(Red ∣ c)', 'P(Long ∣ c)', 'P(c) · P(Red ∣ c) · P(Long ∣ c)'], rows, 'lcccl')
    win = max(scores, key=scores.get)
    p(f'The largest score is **{win}** ({num(scores[win], 3)}), so the new object (Red, Long) is classified as **{win}**.')
    # Laplace smoothing view
    rows = []
    for c in classes:
        sub = [r for r in D if r[2] == c]
        nr, nl, nc = sum(r[0] == 'Red' for r in sub), sum(r[1] == 'Long' for r in sub), len(sub)
        sc = Fr(nc, len(D)) * Fr(nr + 1, nc + 2) * Fr(nl + 1, nc + 2)
        rows.append([c, f'({nr} + 1)/({nc} + 2) = {nr + 1}/{nc + 2}', f'({nl} + 1)/({nc} + 2) = {nl + 1}/{nc + 2}', num(sc, 4)])
    p('**With Laplace smoothing** (add 1 to every count; each feature has 2 values, so add 2 to the denominator), no probability is exactly 0:')
    table(['Class c', 'P(Red ∣ c)', 'P(Long ∣ c)', 'Score = P(c) × both'], rows, 'lccr')
    p('Chilli still wins. Smoothing matters when a zero would otherwise wipe out a class that should win.')
