"""Unit 1 notes: worked examples for docs/dsml/notes/unit-1.md."""
import math
from fractions import Fraction as Fr
from _hub import num, tex, table, p, math_block, region, mean

# ---------------------------------------------------------------- vector operations
with region('vectors'):
    u, w = [1, 2, 3], [4, 5, 6]
    k = 3
    dot = sum(a * b for a, b in zip(u, w))
    cross = [u[1] * w[2] - u[2] * w[1], u[2] * w[0] - u[0] * w[2], u[0] * w[1] - u[1] * w[0]]
    table(['Operation', 'Working', 'Result'], [
        ['u + w', '(1 + 4, 2 + 5, 3 + 6)', f'({", ".join(str(a + b) for a, b in zip(u, w))})'],
        ['w − u', '(4 − 1, 5 − 2, 6 − 3)', f'({", ".join(str(b - a) for a, b in zip(u, w))})'],
        [f'{k}u (scalar multiple)', '(3·1, 3·2, 3·3)', f'({", ".join(str(k * a) for a in u)})'],
        ['u · w (dot product)', '1·4 + 2·5 + 3·6 = 4 + 10 + 18', f'**{dot}** (a scalar)'],
        ['u × w (cross product)', '(2·6 − 3·5, 3·4 − 1·6, 1·5 − 2·4)', f'**({", ".join(num(c) for c in cross)})** (a vector)'],
        ['‖u‖ (length)', '√(1² + 2² + 3²) = √14', num(math.sqrt(14), 4)],
    ], 'lll')
    check = [sum(a * b for a, b in zip(cross, u)), sum(a * b for a, b in zip(cross, w))]
    p(f'Check the cross product: (u × w) · u = {check[0]} and (u × w) · w = {check[1]}. Both are 0, so u × w is perpendicular to both, as it must be. '
      'These are the same vectors as Assignment 1 Q10, where `np.dot(u, w)` printed 32 and `np.cross(u, w)` printed [−3, 6, −3].')

# ---------------------------------------------------------------- matrix multiplication
with region('matmul'):
    A = [[1, 2, 3], [4, 5, 6]]
    B = [[1, 0], [2, 1], [0, 3]]
    C = [[sum(A[i][k] * B[k][j] for k in range(3)) for j in range(2)] for i in range(2)]
    D = [[sum(B[i][k] * A[k][j] for k in range(2)) for j in range(3)] for i in range(3)]
    mat = lambda M: '\\begin{bmatrix}' + ' \\\\ '.join(' & '.join(str(v) for v in r) for r in M) + '\\end{bmatrix}'
    math_block(f'\\underbrace{{{mat(A)}}}_{{2\\times 3}}\\;\\underbrace{{{mat(B)}}}_{{3\\times 2}} = '
               f'\\begin{{bmatrix}} 1\\cdot1+2\\cdot2+3\\cdot0 & 1\\cdot0+2\\cdot1+3\\cdot3 \\\\ 4\\cdot1+5\\cdot2+6\\cdot0 & 4\\cdot0+5\\cdot1+6\\cdot3 \\end{{bmatrix}}'
               f' = \\underbrace{{{mat(C)}}}_{{2\\times 2}}')
    p(f'Entry (i, j) is row i of the first matrix **dotted with** column j of the second. Shapes: (2 × **3**)(**3** × 2) works because the inner numbers match, and the answer takes the outer numbers, 2 × 2. '
      f'In the other order, BA is (3 × 2)(2 × 3) = 3 × 3: a different size altogether, so **AB ≠ BA** (matrix multiplication is not commutative).')

# ---------------------------------------------------------------- determinant, inverse, eigenvalues (2x2)
with region('eigen'):
    M = [[4, 1], [2, 3]]
    det = M[0][0] * M[1][1] - M[0][1] * M[1][0]
    tr = M[0][0] + M[1][1]
    inv = [[Fr(M[1][1], det), Fr(-M[0][1], det)], [Fr(-M[1][0], det), Fr(M[0][0], det)]]
    disc = tr * tr - 4 * det
    l1, l2 = (tr + math.isqrt(disc)) // 2, (tr - math.isqrt(disc)) // 2
    fr = lambda q: (str(q.numerator) if q.denominator == 1
                    else ('-' if q < 0 else '') + f'\\tfrac{{{abs(q.numerator)}}}{{{q.denominator}}}')
    p('Take $M = \\begin{bmatrix} 4 & 1 \\\\ 2 & 3 \\end{bmatrix}$.')
    math_block(
        f'\\det M &= ad - bc = 4\\cdot3 - 1\\cdot2 = {det}',
        f'M^{{-1}} &= \\frac{{1}}{{\\det M}}\\begin{{bmatrix}} d & -b \\\\ -c & a \\end{{bmatrix}} = \\frac{{1}}{{{det}}}\\begin{{bmatrix}} 3 & -1 \\\\ -2 & 4 \\end{{bmatrix}}'
        f' = \\begin{{bmatrix}} {fr(inv[0][0])} & {fr(inv[0][1])} \\\\ {fr(inv[1][0])} & {fr(inv[1][1])} \\end{{bmatrix}}',
        f'\\det(M - \\lambda I) &= (4-\\lambda)(3-\\lambda) - 2 = \\lambda^2 - {tr}\\lambda + {det} = (\\lambda - {l1})(\\lambda - {l2}) = 0',
        f'\\lambda_1 &= {l1}, \\quad \\lambda_2 = {l2}',
    )
    v1 = (1, l1 - M[0][0])
    v2 = (1, l2 - M[0][0])
    p(f'**Eigenvectors.** For λ = {l1}: (M − {l1}I)v = 0 gives −v₁ + v₂ = 0, so v = ({v1[0]}, {v1[1]}). '
      f'For λ = {l2}: 2v₁ + v₂ = 0, so v = ({v2[0]}, {num(v2[1])}). Check: M(1, 1) = (5, 5) = 5 × (1, 1). '
      f'Two shortcuts that catch mistakes: λ₁ + λ₂ = trace = 4 + 3 = {tr}, and λ₁ × λ₂ = det = {det}.')

# ---------------------------------------------------------------- Pearson r, worked on fresh data
with region('pearson'):
    X = [1, 2, 3, 4, 5]          # hours studied
    Y = [52, 55, 61, 60, 72]     # marks
    mx, my = mean(X), mean(Y)
    rows = []
    for x, y in zip(X, Y):
        dx, dy = x - mx, y - my
        rows.append([x, y, num(dx), num(dy, 2), num(dx * dy, 2), num(dx * dx, 2), num(dy * dy, 2)])
    sxy = sum((x - mx) * (y - my) for x, y in zip(X, Y))
    sxx = sum((x - mx) ** 2 for x in X)
    syy = sum((y - my) ** 2 for y in Y)
    rows.append(['**Σ 15**', f'**Σ {sum(Y)}**', '0', '0', f'**{num(sxy, 2)}**', f'**{num(sxx, 2)}**', f'**{num(syy, 2)}**'])
    p(f'Hours studied (x) and marks (y) for five students. Means: x̄ = {num(mx)}, ȳ = {num(my)}.')
    table(['x', 'y', 'x − x̄', 'y − ȳ', '(x − x̄)(y − ȳ)', '(x − x̄)²', '(y − ȳ)²'], rows, 'ccrrrrr')
    r = sxy / math.sqrt(sxx * syy)
    cov = sxy / (len(X) - 1)
    math_block(f'r = \\frac{{{tex(sxy, 2)}}}{{\\sqrt{{{tex(sxx, 2)} \\times {tex(syy, 2)}}}}} = \\frac{{{tex(sxy, 2)}}}{{{tex(math.sqrt(sxx * syy), 4)}}} = \\mathbf{{{tex(r, 4)}}}')
    p(f'**r = {num(r, 2)}: a strong positive linear relationship.** More hours go with more marks, though not perfectly (the fourth student studied more and scored less). '
      f'The sample covariance on the way there is Σ(x − x̄)(y − ȳ)/(n − 1) = {num(sxy, 2)}/4 = {num(cov, 2)}: its sign gives the direction, but its size depends on the units, which is why r divides it out.')
