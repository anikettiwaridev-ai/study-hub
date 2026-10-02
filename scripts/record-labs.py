#!/usr/bin/env python3
"""Records a real run of every DSML lab assignment (code/dsml/assignments/a*.py).

The lab scripts need NumPy, Pandas, Matplotlib and scikit-learn, which CI does not install,
so their output is recorded once on a machine that has them and committed. verify.mjs only
checks that the recording exists (each script has a "recorded" .expect file).

Run it with a Python that has those packages, from the repo root:
    <path to python with sklearn> scripts/record-labs.py

For each aN.py it writes:
    code/dsml/assignments/aN.out          the whole standard output
    code/dsml/assignments/aN-qK.out       the output printed by the lines inside "# region qK"
    docs/public/dsml/assignments/aN-qK-i.png   every figure that region shows with plt.show()
NumPy's random generator is seeded with 0 so a re-run gives the same numbers.
"""
import os
import re
import shutil
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LABS = os.path.join(ROOT, 'code', 'dsml', 'assignments')
FIGS = os.path.join(ROOT, 'docs', 'public', 'dsml', 'assignments')

RUNNER = r'''
import io, os, re, sys, runpy
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np
np.random.seed(0)

script, figdir, name = sys.argv[1], sys.argv[2], sys.argv[3]
regions, current = [], None
for no, line in enumerate(open(script, encoding="utf-8"), 1):
    m = re.match(r"\s*# region (\S+)", line)
    if m:
        current = [m.group(1), no, None]
    elif re.match(r"\s*# endregion", line) and current:
        current[2] = no
        regions.append(tuple(current))
        current = None

def region_of(lineno):
    for reg, a, b in regions:
        if a < lineno < b:
            return reg
    return "other"

def calling_region():
    f = sys._getframe(1)
    while f is not None:
        if os.path.abspath(f.f_code.co_filename) == os.path.abspath(script):
            return region_of(f.f_lineno)
        f = f.f_back
    return "other"

chunks = {}
full = io.StringIO()
real = sys.stdout

class Splitter(io.TextIOBase):
    def write(self, s):
        full.write(s)
        chunks.setdefault(calling_region(), []).append(s)
        return len(s)

counts = {}
def show(*a, **k):
    reg = calling_region()
    for num in plt.get_fignums():
        counts[reg] = counts.get(reg, 0) + 1
        plt.figure(num).savefig(os.path.join(figdir, f"{name}-{reg}-{counts[reg]}.png"), dpi=80, bbox_inches="tight")
    plt.close("all")
plt.show = show

sys.stdout = Splitter()
try:
    runpy.run_path(script, run_name="__main__")
finally:
    sys.stdout = real
print("\u0000FULL\u0000" + full.getvalue())
for reg, parts in chunks.items():
    print("\u0000REGION " + reg + "\u0000" + "".join(parts))
'''


def main():
    os.makedirs(FIGS, exist_ok=True)
    for old in os.listdir(FIGS):
        if old.endswith('.png'):
            os.remove(os.path.join(FIGS, old))
    for f in os.listdir(LABS):
        if re.match(r'a\d+-.*\.out$', f):
            os.remove(os.path.join(LABS, f))
    for fn in sorted(os.listdir(LABS)):
        if not re.match(r'a\d+\.py$', fn):
            continue
        name = fn[:-3]
        with tempfile.TemporaryDirectory() as tmp:
            for data in os.listdir(LABS):
                if data.endswith('.csv'):
                    shutil.copy(os.path.join(LABS, data), tmp)
            shutil.copy(os.path.join(LABS, fn), tmp)
            runner = os.path.join(tmp, '_runner.py')
            open(runner, 'w', encoding='utf-8').write(RUNNER)
            env = dict(os.environ, PYTHONIOENCODING='utf-8', MPLBACKEND='Agg')
            res = subprocess.run([sys.executable, '-X', 'utf8', runner, os.path.join(tmp, fn), FIGS, name],
                                 cwd=tmp, capture_output=True, text=True, encoding='utf-8', env=env)
            if res.returncode != 0:
                sys.exit(f'{fn} failed:\n{res.stderr}')
            parts = res.stdout.split('\u0000')
            # parts: ['', 'FULL', text, 'REGION q1', text, ...]
            i = 1
            while i < len(parts) - 1:
                tag, body = parts[i], parts[i + 1]
                body = body.rstrip('\n') + '\n'
                if body.endswith('\n\n'):
                    body = body.rstrip('\n') + '\n'
                if tag == 'FULL':
                    target = os.path.join(LABS, f'{name}.out')
                else:
                    reg = tag.split(' ', 1)[1]
                    target = os.path.join(LABS, f'{name}-{reg}.out')
                    body = body.lstrip('\n')
                open(target, 'w', encoding='utf-8', newline='\n').write(body)
                i += 2
        print(f'{name}: recorded')


if __name__ == '__main__':
    main()
