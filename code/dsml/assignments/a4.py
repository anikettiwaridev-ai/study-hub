# Assignment 4: the lab script as submitted (17-09-26_Lab_DataPreProcessing.py).
# Only the "# region" / "# endregion" marker lines were added, so the site can show one question at a time.

# region imports
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.impute import SimpleImputer
from sklearn.preprocessing import LabelEncoder, OneHotEncoder, MinMaxScaler, StandardScaler
from sklearn.model_selection import train_test_split
# endregion imports

# region q1
# ---------------------------------------------------------------
# 1. Create a dataset with numerical, categorical and missing values
# ---------------------------------------------------------------
data = {
    "Name":       ["Amit", "Bhavna", "Chirag", "Divya", "Eshan",
                   "Farah", "Gaurav", "Divya", "Isha", "Jatin"],
    "Age":        [25, 32, np.nan, 28, 41, 36, np.nan, 28, 23, 45],
    "Salary":     [50000, 62000, 58000, np.nan, 91000, 75000, 67000, np.nan, 48000, 99000],
    "City":       ["Delhi", "Mumbai", "Delhi", "Pune", np.nan,
                   "Mumbai", "Delhi", "Pune", "Pune", np.nan],
    "Department": ["IT", "HR", "IT", "Sales", "IT", "HR", "Sales", "Sales", "IT", "HR"],
    "Experience": [2, 8, 5, 3, 15, 10, 6, 3, 1, 20],
}
df = pd.DataFrame(data)
print("Original dataset:\n", df)
# endregion q1

# region q2
# ---------------------------------------------------------------
# 2. Inspect shape, data types and missing value counts
# ---------------------------------------------------------------
print("\nShape:", df.shape)
print("\nData types:\n", df.dtypes)
print("\nMissing values per column:\n", df.isnull().sum())
print("\nInfo summary:")
df.info()
# endregion q2

# region q3
# ---------------------------------------------------------------
# 3. Handle missing values using SimpleImputer
# ---------------------------------------------------------------
df_imputed = df.copy()

# a. mean / median imputation for numerical columns
num_cols = ["Age", "Salary"]
mean_imputer = SimpleImputer(strategy="mean")
df_imputed[num_cols] = mean_imputer.fit_transform(df_imputed[num_cols])
print("\nAfter mean imputation (Age, Salary):\n", df_imputed[num_cols])

# median version shown separately for comparison
median_imputer = SimpleImputer(strategy="median")
print("\nMedian-imputed version:\n",
      pd.DataFrame(median_imputer.fit_transform(df[num_cols]), columns=num_cols))

# b. most frequent (mode) imputation for categorical columns
cat_cols = ["City"]
mode_imputer = SimpleImputer(strategy="most_frequent")
df_imputed[cat_cols] = mode_imputer.fit_transform(df_imputed[cat_cols])
print("\nAfter mode imputation (City):\n", df_imputed["City"])

print("\nMissing values now:\n", df_imputed.isnull().sum())
# endregion q3

# region q4
# ---------------------------------------------------------------
# 4. Identify and remove duplicate records
# ---------------------------------------------------------------
print("\nDuplicate rows flagged:\n", df_imputed.duplicated())
print("Number of duplicates:", df_imputed.duplicated().sum())

df_nodup = df_imputed.drop_duplicates()
print("Shape before:", df_imputed.shape, "| after:", df_nodup.shape)

# duplicates based on selected columns only
print("Duplicates on Name only:", df_imputed.duplicated(subset=["Name"]).sum())
# endregion q4

# region q5
# ---------------------------------------------------------------
# 5. Label Encoding (ordinal / binary categorical -> numbers)
# ---------------------------------------------------------------
df_enc = df_nodup.copy()
le = LabelEncoder()
df_enc["Department_LE"] = le.fit_transform(df_enc["Department"])

print("\nLabel encoding of Department:")
print(df_enc[["Department", "Department_LE"]])
print("Classes learned:", list(le.classes_))
print("Inverse check:", le.inverse_transform([0, 1, 2]))
# endregion q5

# region q6
# ---------------------------------------------------------------
# 6. One-Hot Encoding (nominal categorical -> 0/1 columns)
# ---------------------------------------------------------------
# a. using pandas get_dummies
dummies = pd.get_dummies(df_enc["City"], prefix="City")
print("\nOne-hot via pd.get_dummies:\n", dummies)

# b. using sklearn OneHotEncoder
ohe = OneHotEncoder(sparse_output=False, handle_unknown="ignore")
ohe_array = ohe.fit_transform(df_enc[["City"]])
ohe_df = pd.DataFrame(ohe_array, columns=ohe.get_feature_names_out(["City"]),
                      index=df_enc.index)
print("\nOne-hot via OneHotEncoder:\n", ohe_df)

df_final = pd.concat([df_enc, ohe_df], axis=1)
# endregion q6

# region q7
# ---------------------------------------------------------------
# 7. Feature scaling
# ---------------------------------------------------------------
scale_cols = ["Age", "Salary", "Experience"]

# a. MinMaxScaler -> squeeze into [0, 1]
mm = MinMaxScaler()
minmax_scaled = pd.DataFrame(mm.fit_transform(df_final[scale_cols]),
                             columns=scale_cols, index=df_final.index)
print("\nMinMax scaled:\n", minmax_scaled.round(3))

# b. StandardScaler -> mean 0, variance 1
ss = StandardScaler()
std_scaled = pd.DataFrame(ss.fit_transform(df_final[scale_cols]),
                          columns=scale_cols, index=df_final.index)
print("\nStandard scaled:\n", std_scaled.round(3))
print("\nMeans after standardising:", std_scaled.mean().round(6).values)
print("Std devs after standardising:", std_scaled.std(ddof=0).round(6).values)
# endregion q7

# region q8
# ---------------------------------------------------------------
# 8. Feature engineering - build a new column from existing ones
# ---------------------------------------------------------------
df_final["Salary_per_Year_Exp"] = df_final["Salary"] / df_final["Experience"]
df_final["Senior"] = (df_final["Experience"] >= 10).astype(int)
df_final["Age_Group"] = pd.cut(df_final["Age"],
                               bins=[0, 30, 40, 100],
                               labels=["Young", "Mid", "Senior"])

print("\nEngineered features:\n",
      df_final[["Age", "Salary", "Experience",
                "Salary_per_Year_Exp", "Senior", "Age_Group"]].round(2))
# endregion q8

# region q9
# ---------------------------------------------------------------
# 9. Split into training (80%) and testing (20%) sets
# ---------------------------------------------------------------
X = df_final[["Age", "Salary", "Experience", "Department_LE"]]
y = df_final["Senior"]

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)
print("\nX_train shape:", X_train.shape, "| X_test shape:", X_test.shape)
print("y_train shape:", y_train.shape, "| y_test shape:", y_test.shape)
# endregion q9

# region q10
# ---------------------------------------------------------------
# 10. Visualisation
# ---------------------------------------------------------------
# a. Boxplot to check for outliers
plt.figure(figsize=(7, 4))
plt.boxplot([df_final["Age"], df_final["Experience"]],
            tick_labels=["Age", "Experience"])
plt.title("Boxplot - Outlier Check")
plt.ylabel("Value")
plt.grid(True, alpha=0.3)
plt.show()

# separate boxplot for Salary (different scale)
plt.figure(figsize=(5, 4))
plt.boxplot(df_final["Salary"], tick_labels=["Salary"])
plt.title("Boxplot - Salary")
plt.ylabel("Rupees")
plt.grid(True, alpha=0.3)
plt.show()

# b. Histograms before and after scaling
fig, axes = plt.subplots(1, 2, figsize=(10, 4))

axes[0].hist(df_final["Salary"], bins=8, color="steelblue", edgecolor="black")
axes[0].set_title("Salary - Before Scaling")
axes[0].set_xlabel("Rupees")
axes[0].set_ylabel("Frequency")

axes[1].hist(std_scaled["Salary"], bins=8, color="seagreen", edgecolor="black")
axes[1].set_title("Salary - After StandardScaler")
axes[1].set_xlabel("Standard deviations from mean")
axes[1].set_ylabel("Frequency")

plt.tight_layout()
plt.show()
# endregion q10
