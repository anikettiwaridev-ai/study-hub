"""Shared helpers for the DSML worked numericals. Standard library only, so CI can run them.

Every script prints a Markdown fragment. Pages pull a region of it in with
<!--@include: @/../code/dsml/<folder>/<script>.out#<region>-->, so every number on a
DSML page comes from running code, never from typing.
"""
import math
from contextlib import contextmanager
from fractions import Fraction

MINUS = '−'


def num(x, d=4, minus=True):
    """Round to d decimals and drop trailing zeros: 0.8000 -> 0.8, 2.0 -> 2.

    Text tables use a real minus sign; pass minus=False inside LaTeX.
    """
    if isinstance(x, Fraction):
        x = float(x)
    if isinstance(x, int):
        s = str(x)
    else:
        s = f'{x:.{d}f}'
        if '.' in s:
            s = s.rstrip('0').rstrip('.')
    if s in ('-0', '-0.0'):
        s = '0'
    return s.replace('-', MINUS) if minus else s


def sci(x, sig=4):
    """2925000000 -> '2.925 × 10⁹' (for text, not LaTeX)."""
    m, e = f'{x:.{sig - 1}e}'.split('e')
    sup = str.maketrans('-0123456789', '⁻⁰¹²³⁴⁵⁶⁷⁸⁹')
    m = m.rstrip('0').rstrip('.')
    return f'{m} × 10{str(int(e)).translate(sup)}'.replace('-', MINUS)


def tex(x, d=4):
    """A number for use inside $...$."""
    return num(x, d, minus=False)


def fixed(x, d=4, minus=True):
    """Exactly d decimals (keeps trailing zeros), for columns that should line up."""
    s = f'{float(x):.{d}f}'
    if float(s) == 0:
        s = s.lstrip('-')
    return s.replace('-', MINUS) if minus else s


def table(head, rows, align=None):
    """A Markdown table. align is a string like 'lrrc' (left/right/center)."""
    align = align or 'l' * len(head)
    rule = {'l': '---', 'r': '--:', 'c': ':-:'}
    out = ['| ' + ' | '.join(str(h) for h in head) + ' |',
           '|' + '|'.join(rule[a] for a in align) + '|']
    out += ['| ' + ' | '.join(str(c) for c in r) + ' |' for r in rows]
    print('\n'.join(out))
    print()


def p(*lines):
    """Print lines, then a blank line (a Markdown paragraph break)."""
    for line in lines:
        print(line)
    print()


def math_block(*lines):
    """Display maths. Several lines become an aligned block."""
    if len(lines) == 1:
        print(f'$$ {lines[0]} $$')
    else:
        body = ' \\\\ '.join(lines)
        print(f'$$ \\begin{{aligned}} {body} \\end{{aligned}} $$')
    print()


@contextmanager
def region(name):
    print(f'<!-- #region {name} -->')
    print()
    yield
    print(f'<!-- #endregion {name} -->')


def mean(xs):
    return sum(xs) / len(xs)


def pstdev(xs):
    m = mean(xs)
    return math.sqrt(sum((x - m) ** 2 for x in xs) / len(xs))


def sstdev(xs):
    m = mean(xs)
    return math.sqrt(sum((x - m) ** 2 for x in xs) / (len(xs) - 1))


def sigmoid(z):
    return 1 / (1 + math.exp(-z))


def entropy(counts):
    n = sum(counts)
    return -sum(c / n * math.log2(c / n) for c in counts if c)
