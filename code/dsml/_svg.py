"""Tiny SVG plotting for the DSML figures. Standard library only.

The SVG is printed on consecutive lines with no blank line, so Markdown treats it as one
HTML block. Colours come from CSS classes (see the "Figures" block in style.css), so every
figure follows the light and dark themes:
  a / b / c   blue, red, green strokes       fa / fb / fc   the same as fills
  m           dashed grey guide line          fm             grey fill
  ax          axes                            hollow         an open circle
  area        shaded region                   box            a labelled box
"""
from html import escape


def f(v):
    s = f'{v:.1f}'
    return s[:-2] if s.endswith('.0') else s


class Plot:
    def __init__(self, x0, x1, y0, y1, w=560, h=300, pad=(46, 16, 14, 40), label='', narrow=False):
        self.x0, self.x1, self.y0, self.y1 = x0, x1, y0, y1
        self.w, self.h = w, h
        self.l, self.r, self.t, self.b = pad
        self.parts = []
        self.label = label
        self.narrow = narrow

    # data -> pixel
    def X(self, x):
        return self.l + (x - self.x0) / (self.x1 - self.x0) * (self.w - self.l - self.r)

    def Y(self, y):
        return self.h - self.b - (y - self.y0) / (self.y1 - self.y0) * (self.h - self.t - self.b)

    def raw(self, s):
        self.parts.append(s)

    def axes(self, xlabel='', ylabel='', xticks=(), yticks=(), xfmt=str, yfmt=str, grid=False):
        X, Y = self.X, self.Y
        if grid:
            for t in yticks:
                self.raw(f'<line class="grid" x1="{f(X(self.x0))}" y1="{f(Y(t))}" x2="{f(X(self.x1))}" y2="{f(Y(t))}"/>')
        self.raw(f'<line class="ax" x1="{f(X(self.x0))}" y1="{f(Y(self.y0))}" x2="{f(X(self.x1))}" y2="{f(Y(self.y0))}"/>')
        self.raw(f'<line class="ax" x1="{f(X(self.x0))}" y1="{f(Y(self.y0))}" x2="{f(X(self.x0))}" y2="{f(Y(self.y1))}"/>')
        for t in xticks:
            self.raw(f'<line class="ax" x1="{f(X(t))}" y1="{f(Y(self.y0))}" x2="{f(X(t))}" y2="{f(Y(self.y0) + 4)}"/>')
            self.raw(f'<text x="{f(X(t))}" y="{f(Y(self.y0) + 16)}" text-anchor="middle">{escape(xfmt(t))}</text>')
        for t in yticks:
            self.raw(f'<line class="ax" x1="{f(X(self.x0) - 4)}" y1="{f(Y(t))}" x2="{f(X(self.x0))}" y2="{f(Y(t))}"/>')
            self.raw(f'<text x="{f(X(self.x0) - 7)}" y="{f(Y(t) + 4)}" text-anchor="end">{escape(yfmt(t))}</text>')
        if xlabel:
            self.raw(f'<text class="lbl" x="{f((X(self.x0) + X(self.x1)) / 2)}" y="{f(self.h - 6)}" text-anchor="middle">{escape(xlabel)}</text>')
        if ylabel:
            cy = (Y(self.y0) + Y(self.y1)) / 2
            self.raw(f'<text class="lbl" x="12" y="{f(cy)}" text-anchor="middle" transform="rotate(-90 12 {f(cy)})">{escape(ylabel)}</text>')

    def line(self, pts, cls='a'):
        d = ' '.join(f'{f(self.X(x))},{f(self.Y(y))}' for x, y in pts)
        self.raw(f'<polyline class="{cls}" points="{d}"/>')

    def area(self, pts, cls='area'):
        d = ' '.join(f'{f(self.X(x))},{f(self.Y(y))}' for x, y in pts)
        self.raw(f'<polygon class="{cls}" points="{d}"/>')

    def seg(self, x1, y1, x2, y2, cls='m'):
        self.raw(f'<line class="{cls}" x1="{f(self.X(x1))}" y1="{f(self.Y(y1))}" x2="{f(self.X(x2))}" y2="{f(self.Y(y2))}"/>')

    def arrow(self, x1, y1, x2, y2, cls='b'):
        self.seg(x1, y1, x2, y2, cls)
        import math
        a = math.atan2(self.Y(y2) - self.Y(y1), self.X(x2) - self.X(x1))
        px, py = self.X(x2), self.Y(y2)
        pts = [(px, py),
               (px - 8 * math.cos(a - 0.4), py - 8 * math.sin(a - 0.4)),
               (px - 8 * math.cos(a + 0.4), py - 8 * math.sin(a + 0.4))]
        fill = {'a': 'fa', 'b': 'fb', 'c': 'fc'}.get(cls, 'fm')
        self.raw(f'<polygon class="{fill}" points="{" ".join(f"{f(x)},{f(y)}" for x, y in pts)}"/>')

    def dot(self, x, y, cls='fa', r=3.5):
        self.raw(f'<circle class="{cls}" cx="{f(self.X(x))}" cy="{f(self.Y(y))}" r="{r}"/>')

    def ring(self, x, y, r, cls='m'):
        """A circle whose radius r is in x-units (assumes equal x and y scales)."""
        rp = abs(self.X(x + r) - self.X(x))
        self.raw(f'<circle class="{cls}" cx="{f(self.X(x))}" cy="{f(self.Y(y))}" r="{f(rp)}"/>')

    def mark(self, x, y, sym, cls='ta'):
        """A text symbol such as + or − centred on a data point."""
        self.raw(f'<text class="{cls}" x="{f(self.X(x))}" y="{f(self.Y(y) + 5)}" text-anchor="middle" style="font-size:15px;font-weight:600">{escape(sym)}</text>')

    def text(self, x, y, s, cls='', anchor='start', dx=0, dy=0):
        c = f' class="{cls}"' if cls else ''
        self.raw(f'<text{c} x="{f(self.X(x) + dx)}" y="{f(self.Y(y) + dy)}" text-anchor="{anchor}">{escape(s)}</text>')

    def svg(self):
        cls = 'fig narrow' if self.narrow else 'fig'
        head = f'<svg class="{cls}" viewBox="0 0 {self.w} {self.h}" role="img" aria-label="{escape(self.label)}">'
        return '\n'.join([head, *self.parts, '</svg>'])


def figure(plot, caption=''):
    print(plot.svg())
    print()
    if caption:
        print(f'<p class="fig-cap">{escape(caption)}</p>')
        print()
