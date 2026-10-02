---
title: Assignments
---

# Assignments

All six lab assignments, every question answered with the lab script **as it was submitted** and the output it **really printed**, plus the charts. Only one thing was added to the scripts: `# region` and `# endregion` marker lines, so each question's code can be shown on its own. The explanations come from the assignment write-ups.

<SourceTable kinds="assignment" />

| Assignment | Best for | Start with |
|---|---|---|
| [4 · Preprocessing](./a4) | The mid-semester's scaling and encoding questions, in code; the two leakage traps for the viva | Q3, Q5–Q7, Q9 |
| [5 · Logistic regression](./a5) | Scaling done right; probabilities and thresholds; a confusion matrix read by hand | Q5, Q8, Q9 |
| [6 · KNN](./a6) | The Id-column leak; a 3-class confusion matrix; choosing k without leaking | Q3, Q8, Q9–Q10 |
| [3 · Linear regression](./a3) | Why X needs double brackets; slope, intercept, MSE vs R² | Q3, Q8, Q9 |
| [2 · Pandas and Matplotlib](./a2) | Theory-quiz behaviour: Series vs DataFrame, NaN → float, groupby, which chart | Q5, Q7, Q8, Q10 |
| [1 · NumPy](./a1) | Theory-quiz behaviour: copy vs alias, split, vstack vs hstack, dot vs cross | Q7–Q10 |

::: info How the outputs were produced
The scripts use NumPy, Pandas, Matplotlib and scikit-learn, so each was run once in the lab's own Python environment and its output and charts recorded (`scripts/record-labs.py`). NumPy's random generator was seeded with 0 for the record, so Assignment 1's random array is reproducible; on your machine it will differ. The CSV files the scripts read are in the repository beside them.
:::
