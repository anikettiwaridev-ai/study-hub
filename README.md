# Study hub

Past papers, assignments and notes for B.Tech CSE (AI) at Punjab Engineering College, solved and checked. It installs on a phone like an app and works offline.

Every C++ program on the site is compiled and run before it is published, and the output you see is the program's real output. Every worked calculation in the DSML section (each table, number and graph) is printed by a Python script that is re-run the same way. A change that breaks either is not published.

## Run it on your computer

You need [Node.js](https://nodejs.org) 20 or newer. g++ and Python 3 are optional: you only need them to add or change programs and DSML calculations.

```bash
npm install
npm run dev
```

Open the address it prints. Pages reload as you edit them.

## Publish it

The site is published by GitHub Pages every time you push to `main`.

1. Create a **public** repository on GitHub and push this folder to it.
2. In the repository, open **Settings → Pages** and set **Source** to **GitHub Actions**.
3. Open the **Actions** tab and wait for "Check and deploy" to finish.

The site appears at `https://<your-username>.github.io/<repo-name>/`. If a run fails, open it: the "npm run check" step says exactly which program or data entry is wrong.

Pull requests are checked the same way but are not published until merged.

## How it's organised

```
docs/
  index.md                 the subject list
  guide.md                 how to use the site, with a worked example
  oop/                     one folder per subject
    index.md               study order, exam format, syllabus
    repeats.md             how often each topic has been asked
    traps.md               the most-trapped questions, ranked
    how-to-answer.md       how marks are earned in the mid-semester and quizzes
    mock-mst.md            a mock mid-semester paper
    quiz-practice.md       a mock quiz and rapid-recall blanks
    papers/  assignments/  notes/
  ds/                      Data Structures: the same layout, plus
    quiz-clock.md          the 10-minute quiz routine and timed drills
    quizzes/  practice/    every quiz (answerable on the page) and practice sheet
  dsml/                    Data Science and Machine Learning: the same layout, plus
    formulas.md            the formula sheet
    practice.md            numerical drills
    quiz-practice.md       two timed quiz sets
    papers/  notes/  assignments/
  .vitepress/
    config.mts             site settings, offline support
    subjects.js            the list of subjects and their sidebars
    theme/
      data/oop.js          every paper, assignment and repeat cluster for OOP
      data/ds.js           the same for Data Structures (papers, quizzes, practice sheets)
      data/dsml.js         the same for DSML (papers, assignments, the mock)
      components/          question rows, MCQs, the repeat map and so on
code/
  oop/                     every C++ program, as real files
    papers/ assignments/ notes/ mock/ quiz/
  ds/
    papers/ notes/ quiz/ practice/ mock/
  dsml/                    Python scripts that print the DSML worked answers (standard library only)
    _hub.py  _svg.py       shared helpers: number formatting, tables, regions, SVG figures
    papers/ notes/ practice/ mock/
    assignments/           the six lab scripts as submitted, their data, and recorded output
scripts/
  verify.mjs               compiles and runs every program, runs every script, saves the output
  check-data.mjs           checks the repeat data is consistent
  record-labs.py           records a run of the DSML lab scripts (needs pandas and scikit-learn)
```

## Adding a question

Questions live in the subject's Markdown pages. Wrap each one in `<Q>` with its id:

```md
<Q id="S24.Q4a">

The question text, exactly as in the paper.

::::: details Solution

Your explanation.

::: danger
The mistake students make here.
:::

:::::

</Q>
```

- The id is `<source>.<question>`, with sources defined in `docs/.vitepress/theme/data/<subject>.js`. The question number, marks and repeat labels are filled in from there automatically.
- Leave a blank line after `<Q ...>` and before `</Q>`, or the Markdown inside won't render.
- A solution that contains other blocks (code groups, traps) needs a longer fence, `:::::`, so the inner `:::` doesn't close it early.
- Put traps inside the solution so they don't give the answer away. **Traps only** still finds them.
- Callout types: `::: tip` is a rule, `::: warning` is a correction, `::: danger` is a trap, `::: info` is a note.

For a multiple-choice question, use `<Mcq>` inside the `<Q>`; `answer` is a letter, or several separated by commas. See `docs/guide.md` for a full example of both.

For a fill in the blank, use `<FillIn q="Static variables live in the ____." answer="data segment|data">explanation</FillIn>`. Every accepted answer goes in `answer`, separated by `|`; the first is the one shown by "Show answer". Matching ignores case and extra spaces.

Quiz-style practice items that are not from a paper go in `<Drill n="3" tag="Output">…</Drill>`, which numbers them and needs no data-file entry.

Containers inside containers need longer fences: a `::: code-group` inside a `::: danger` makes the outer one `:::: danger … ::::`, and a solution holding either uses `::::: details`.

## Adding a program

1. Save it as `code/<subject>/<folder>/<name>.cpp`, exactly as it appears in the paper.
2. Run `npm run verify`. This compiles it, runs it, and writes `<name>.out` next to it.
3. Show both on the page as tabs:

```md
::: code-group
<<< @/../code/oop/papers/s24-q4a.cpp [Program]
<<< @/../code/oop/papers/s24-q4a.out{txt} [Output]
:::
```

4. Commit the `.cpp` and the `.out` together.

Some programs need a sidecar file next to them:

| File | Contains | Use it when |
|---|---|---|
| `<name>.in` | The keyboard input | The program reads with `cin` |
| `<name>.expect` | `compile-error` | The point is that it doesn't compile |
| `<name>.expect` | `ub` | It has undefined behaviour, such as `x = ++x + x++` |
| `<name>.expect` | `nondeterministic` | It prints garbage values or anything else that varies |
| `<name>.expect` | `platform` | The output depends on the machine, such as `sizeof(long)` (4 on Windows, 8 on Linux) |
| `<name>.expect` | `warning-ok` | GCC warns "may be undefined" but the code is well defined (the output is still checked) |
| `<name>.with` | other `.cpp` files, one per line | The program is two or more files linked together |

Files whose name starts with `_` are never compiled on their own; use them as the extra files listed in a `.with`.

Programs are compiled as strict standard C++17 (`-std=c++17 -Wall -Wextra -pedantic-errors`), so anything GCC only accepts as an extension counts as an error, the way it would in an exam answer.

If the compiler warns about undefined behaviour and there is no `ub` file, the check fails on purpose.

## Adding a DSML calculation

DSML answers are calculations, so instead of programs the section uses scripts that print the worked answer as Markdown.

1. Write `code/dsml/<folder>/<name>.py` using only the standard library. Import the helpers with `from _hub import num, tex, table, p, math_block, region` (and `from _svg import Plot, figure` for a graph). Wrap each answer in `with region('q2'):`.
2. Run `npm run verify`. It runs the script and saves `<name>.out`.
3. Pull a region into a page:

```md
<!--@include: @/../code/dsml/papers/s25.out#q2-->
```

4. Commit the `.py` and the `.out` together. `npm run check` re-runs the script in CI and fails if the output changed.

Write formulas as `$…$` or `$$…$$` (MathJax, rendered at build time). In a Markdown table, never use a bare `|` inside a cell, even inside maths: write `\lvert x\rvert`, `\mid`, or the character `∣`. Do not write a currency `$` in prose; it starts a formula.

**The lab assignments** need pandas and scikit-learn, which CI does not install. Each has a `.expect` file containing `recorded`, so verify only checks that its output exists. To refresh the output and the charts, run `scripts/record-labs.py` with a Python that has those packages; it writes one `.out` per `# region qN` of each script and the charts to `docs/public/dsml/assignments/`.

## Recording repeats

Each subject's data file lists **clusters**: topics that keep coming back. Inside a cluster, appearances are grouped:

```js
groups: [
  { kind: 'exact', refs: ['O25.Q3a', 'A5.Q8'] },   // word for word: ⟳ Exact
  { kind: 'reworded', refs: ['O25.Q1a', 'N25.Q1'] }, // same ask, new words: ≈ Reworded
  { kind: 'single', refs: ['S24.Q3'] },            // on its own
]
```

Two appearances in the same `exact` or `reworded` group get that label. Two in different groups are labelled **Δ Variant**. A question asked only once goes in `singles`.

Every mid-semester question must be filed exactly once, in one cluster or in `singles`, so the marks table adds up. `npm run check` enforces this.

When a paper's page is ready, set its `href` in the data file (for example `href: '/oop/papers/mst-2024-sep'`) and every chip pointing at it becomes a link.

## Adding a subject

1. Add it to `docs/.vitepress/subjects.js`, with a `sidebar`. The sidebar is one list for the whole site: each subject is a collapsible group in it, the one you are in opens by itself, and subjects without a `sidebar` show "Not added yet". Copy the OOP entry as the template.
2. Create `docs/<id>/index.md`.
3. If it has papers, create `docs/.vitepress/theme/data/<id>.js` shaped like `oop.js`, and register it in `data/index.js`.
4. Formulas (`$…$`, `$$…$$`) already render everywhere; see "Adding a DSML calculation".

## Checking everything before you push

```bash
npm run check   # repeat data, and every program against its saved output
npm run build   # the site itself
```
