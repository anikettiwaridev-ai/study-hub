"""Unit 2 notes: worked examples for docs/dsml/notes/unit-2.md."""
import math
import statistics
from _hub import num, tex, table, p, math_block, region, mean, pstdev

# ---------------------------------------------------------------- imputation (Assignment 4's data)
with region('impute'):
    age = [25, 32, None, 28, 41, 36, None, 28, 23, 45]
    sal = [50000, 62000, 58000, None, 91000, 75000, 67000, None, 48000, 99000]
    city = ['Delhi', 'Mumbai', 'Delhi', 'Pune', None, 'Mumbai', 'Delhi', 'Pune', 'Pune', None]
    a = [x for x in age if x is not None]
    s = [x for x in sal if x is not None]
    c = [x for x in city if x is not None]
    counts = {k: c.count(k) for k in sorted(set(c))}
    table(['Column', 'Kind', 'Present values', 'Mean', 'Median', 'Mode'], [
        ['Age', 'numeric', ', '.join(map(str, a)), f'{sum(a)}/{len(a)} = **{num(mean(a))}**', f'**{num(statistics.median(a))}**', '–'],
        ['Salary', 'numeric', ', '.join(f'{x // 1000}k' for x in s), f'**{num(mean(s))}**', f'**{num(statistics.median(s))}**', '–'],
        ['City', 'categorical', ', '.join(c), '–', '–', ', '.join(f'{k} {v}' for k, v in counts.items())],
    ], 'lllrrl')
    p('Age and Salary are numeric, so fill with the mean (or the median if skewed). '
      'City is categorical, so the mean is meaningless: use the **mode**. Here Delhi and Pune tie at 3; '
      'scikit-learn’s `most_frequent` breaks ties by taking the value that sorts first, Delhi. That is a convention, not a finding.')

# ---------------------------------------------------------------- binning
with region('binning'):
    x = [4, 8, 9, 15, 21, 21, 24, 25, 26, 28, 29, 34]
    bins = [x[0:4], x[4:8], x[8:12]]
    rows = []
    for i, b in enumerate(bins, 1):
        m = mean(b)
        bound = [b[0] if abs(v - b[0]) <= abs(v - b[-1]) else b[-1] for v in b]
        rows.append([f'Bin {i}', ', '.join(map(str, b)), ', '.join([num(m, 2)] * len(b)), ', '.join(map(str, bound))])
    p(f'Sorted prices: {", ".join(map(str, x))} (12 values). **Equal-depth (equal-frequency)** bins of 4 values each:')
    table(['Bin', 'Values', 'Smoothed by bin mean', 'Smoothed by bin boundaries'], rows, 'llll')
    lo, hi, k = min(x), max(x), 3
    w = (hi - lo) / k
    edges = [lo + i * w for i in range(k + 1)]
    rows = []
    for i in range(k):
        a, b = edges[i], edges[i + 1]
        vals = [v for v in x if (a <= v < b) or (i == k - 1 and v == b)]
        rows.append([f'[{num(a)}, {num(b)}{"]" if i == k - 1 else ")"}', ', '.join(map(str, vals)), len(vals)])
    p(f'**Equal-width (equal-interval)** bins instead: width = (max − min)/3 = ({hi} − {lo})/3 = {num(w)}.')
    table(['Interval', 'Values', 'Count'], rows, 'llc')
    p('Equal width gives equal-sized intervals with uneven counts; equal depth gives equal counts with uneven widths. '
      'Smoothing by **boundaries** replaces each value by the nearer edge of its bin (ties go to the lower edge).')

# ---------------------------------------------------------------- the four scalers
with region('scaling'):
    x = [20, 25, 30, 45, 80]
    lo, hi, m, s = min(x), max(x), mean(x), pstdev(x)
    p(f'Ages: {", ".join(map(str, x))}. min = {lo}, max = {hi}, mean μ = {num(m)}, population σ = {num(s, 3)}.')
    rows = [[v, num((v - lo) / (hi - lo), 4), num((v - m) / s, 4), num((v - m) / (hi - lo), 4)] for v in x]
    table(['x', 'Min-max (x − min)/(max − min)', 'Z-score (x − μ)/σ', 'Mean normalisation (x − μ)/(max − min)'], rows, 'crrr')
    z = [(v - m) / s for v in x]
    p(f'Min-max lands exactly in [0, 1]. Z-scores have mean 0 and standard deviation 1, with no fixed range (here {num(min(z), 2)} to {num(max(z), 2)}). '
      'Mean normalisation has mean 0 and stays within [−1, 1].')

with region('outlier-effect'):
    inc = [20, 25, 30, 35, 400]
    lo, hi = min(inc), max(inc)
    rows = [[v, num((v - lo) / (hi - lo), 4)] for v in inc]
    p(f'Incomes in thousands: {", ".join(map(str, inc))}. One outlier (400) becomes the max:')
    table(['Income', 'Min-max'], rows, 'cr')
    p('The four ordinary incomes, which differ by 15 thousand, are crushed into 0 to 0.04. Any model now sees them as practically identical. '
      'That is why min-max is "sensitive to outliers" and standardisation (or removing the outlier first) is preferred when outliers exist.')

with region('l1l2'):
    v = [3, 4]
    l1 = sum(abs(a) for a in v)
    l2 = math.sqrt(sum(a * a for a in v))
    table(['Row', 'L1 norm (sum of absolute values)', 'L1-normalised', 'L2 norm (√ sum of squares)', 'L2-normalised'], [
        ['(3, 4)', l1, f'(3/{l1}, 4/{l1}) = ({num(3 / l1, 4)}, {num(4 / l1, 4)})', num(l2), f'(3/{num(l2)}, 4/{num(l2)}) = ({num(3 / l2)}, {num(4 / l2)})'],
    ], 'lclcl')
    p('After L1, the absolute values add to 1 (0.4286 + 0.5714). After L2, the squares add to 1 (0.36 + 0.64): the row becomes a **unit vector**, which is the slides’ "unit vector" scaling.')

# ---------------------------------------------------------------- IQR rule on the end-semester data
with region('iqr'):
    D = sorted([55, 57, 500, 61, 62, 65, 67, 70, 72, 73, 95, -2])
    lower, upper = D[:6], D[6:]
    q1, q3 = statistics.median(lower), statistics.median(upper)
    iqr = q3 - q1
    lo_f, hi_f = q1 - 1.5 * iqr, q3 + 1.5 * iqr
    out = [v for v in D if v < lo_f or v > hi_f]
    p(f'The autumn 2024 values, sorted: {", ".join(num(v) for v in D)}. Split into halves; Q1 is the median of the lower half, Q3 of the upper half.')
    math_block(
        f'Q_1 &= \\tfrac{{{lower[2]} + {lower[3]}}}{{2}} = {tex(q1)}, \\qquad Q_3 = \\tfrac{{{upper[2]} + {upper[3]}}}{{2}} = {tex(q3)}, \\qquad \\text{{IQR}} = Q_3 - Q_1 = {tex(iqr)}',
        f'\\text{{fences}} &= Q_1 - 1.5\\,\\text{{IQR}} = {tex(lo_f)}, \\qquad Q_3 + 1.5\\,\\text{{IQR}} = {tex(hi_f)}',
    )
    p(f'Outside the fences: **{", ".join(num(v) for v in out)}**. The IQR rule catches −2 in one pass, because quartiles are not dragged by 500 the way the mean and σ are. '
      f'(It also flags 95, which the z-score method calls normal: different rules, different cut-offs. Say which rule you use.)')
