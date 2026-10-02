# Assignment 2: the lab script as submitted (10-09-26_Lab_Pandas.py).
# Only the "# region" / "# endregion" marker lines were added, so the site can show one question at a time.

# region imports
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
# endregion imports

# region q1
# ---------------------------------------------------------------
# 1. Series from a list and from a dictionary
# ---------------------------------------------------------------
s_list = pd.Series([10, 20, 30, 40])
s_dict = pd.Series({"a": 10, "b": 20, "c": 30})

print("Series from list:\n", s_list)
print("\nSeries from dict:\n", s_dict)
# endregion q1

# region q2
# ---------------------------------------------------------------
# 2. DataFrame from a dictionary
# ---------------------------------------------------------------
data = {
    "Name":  ["Amit", "Bhavna", "Chirag", "Divya", "Eshan", "Farah"],
    "Dept":  ["CSE", "ECE", "CSE", "ME", "ECE", "CSE"],
    "Marks": [85, 78, 92, 61, 74, 88],
    "Age":   [20, 21, 20, 22, 21, 20],
}
df = pd.DataFrame(data)
print("\nDataFrame:\n", df)
# endregion q2

# region q3
# ---------------------------------------------------------------
# 3. Save DataFrame to CSV and load it back
# ---------------------------------------------------------------
df.to_csv("students.csv", index=False)
loaded_df = pd.read_csv("students.csv")
print("\nLoaded from CSV:\n", loaded_df)
# endregion q3

# region q4
# ---------------------------------------------------------------
# 4. Shape, column names, first 5 rows
# ---------------------------------------------------------------
print("\nShape:", df.shape)
print("Columns:", list(df.columns))
print("First 5 rows:\n", df.head())
# endregion q4

# region q5
# ---------------------------------------------------------------
# 5. Select a specific column and a specific row
# ---------------------------------------------------------------
print("\nColumn 'Marks':\n", df["Marks"])
print("\nRow at index 2:\n", df.loc[2])
# endregion q5

# region q6
# ---------------------------------------------------------------
# 6. Filter rows based on a condition
# ---------------------------------------------------------------
toppers = df[df["Marks"] > 80]
print("\nMarks > 80:\n", toppers)
# endregion q6

# region q7
# ---------------------------------------------------------------
# 7. Missing values
# ---------------------------------------------------------------
df2 = df.copy()
df2.loc[1, "Marks"] = np.nan
df2.loc[4, "Age"] = np.nan
print("\nWith missing values:\n", df2)

# a. check null / missing values
print("\nNull check:\n", df2.isnull())
print("Null count per column:\n", df2.isnull().sum())

# b. fill null values with 0 or with mean
print("\nFilled with 0:\n", df2.fillna(0))
print("\nMarks filled with mean:\n", df2.fillna({"Marks": df2["Marks"].mean()}))

# c. drop rows having null values
print("\nAfter dropping null rows:\n", df2.dropna())
# endregion q7

# region q8
# ---------------------------------------------------------------
# 8. Sorting and grouping
# ---------------------------------------------------------------
# a. sort by a column
print("\nSorted by Marks (descending):\n", df.sort_values("Marks", ascending=False))

# b. group by a column and calculate average
print("\nAverage marks per Dept:\n", df.groupby("Dept")["Marks"].mean())
# endregion q8

# region q9
# ---------------------------------------------------------------
# 9. Simple line graph
# ---------------------------------------------------------------
plt.figure()
plt.plot(df["Name"], df["Marks"], marker="o")
plt.title("Marks of Students")
plt.xlabel("Name")
plt.ylabel("Marks")
plt.grid(True)
plt.show()
# endregion q9

# region q10
# ---------------------------------------------------------------
# 10. Bar chart, scatter plot, pie chart
# ---------------------------------------------------------------
# a. bar chart
plt.figure()
plt.bar(df["Name"], df["Marks"], color="skyblue")
plt.title("Bar Chart - Marks")
plt.xlabel("Name")
plt.ylabel("Marks")
plt.show()

# b. scatter plot
plt.figure()
plt.scatter(df["Age"], df["Marks"], color="red")
plt.title("Scatter Plot - Age vs Marks")
plt.xlabel("Age")
plt.ylabel("Marks")
plt.show()

# c. pie chart
dept_counts = df["Dept"].value_counts()
plt.figure()
plt.pie(dept_counts, labels=dept_counts.index, autopct="%1.1f%%")
plt.title("Pie Chart - Students per Dept")
plt.show()
# endregion q10
