# Assignment 5: the lab script as submitted (17-09-26_Lab_LogReg.py).
# Only the "# region" / "# endregion" marker lines were added, so the site can show one question at a time.

# region imports
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import (accuracy_score, confusion_matrix,
                             classification_report, ConfusionMatrixDisplay)
# endregion imports

# region q1
# ---------------------------------------------------------------
# 1. Load the dataset and display the first 5 rows
# ---------------------------------------------------------------
df = pd.read_csv("Social_Network_Ads.csv")
print("First 5 rows:\n", df.head())
# endregion q1

# region q2
# ---------------------------------------------------------------
# 2. Check the shape and look for missing values
# ---------------------------------------------------------------
print("\nShape:", df.shape)
print("\nMissing values:\n", df.isnull().sum())
print("\nClass balance:\n", df["Purchased"].value_counts())
# endregion q2

# region q3
# ---------------------------------------------------------------
# 3. Separate features (X) and target (y)
# ---------------------------------------------------------------
X = df[["Age", "EstimatedSalary"]]     # 2-D: 2 features this time
y = df["Purchased"]                     # 1-D: 0 or 1

print("\nX shape:", X.shape, "| y shape:", y.shape)
print("X (first 5):\n", X.head())
print("y (first 5):", y.head().values)
# endregion q3

# region q4
# ---------------------------------------------------------------
# 4. Split into training (80%) and testing (20%) sets
# ---------------------------------------------------------------
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)
print("\nTrain size:", X_train.shape, "| Test size:", X_test.shape)
# endregion q4

# region q5
# ---------------------------------------------------------------
# 5. Scale the features using StandardScaler
# ---------------------------------------------------------------
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)   # LEARN + apply on train
X_test_scaled = scaler.transform(X_test)         # only APPLY on test

print("\nBefore scaling (first row of train):", X_train.iloc[0].values)
print("After scaling  (first row of train):", X_train_scaled[0].round(4))
print("Learned means :", scaler.mean_.round(2))
print("Learned scales:", scaler.scale_.round(2))
# endregion q5

# region q6
# ---------------------------------------------------------------
# 6. Create and train the Logistic Regression model
# ---------------------------------------------------------------
model = LogisticRegression(random_state=42)
model.fit(X_train_scaled, y_train)
print("\nModel trained.")
print("Coefficients:", model.coef_)
print("Intercept:", model.intercept_)
# endregion q6

# region q7
# ---------------------------------------------------------------
# 7. Predict the class labels on the test data
# ---------------------------------------------------------------
y_pred = model.predict(X_test_scaled)
print("\nPredicted classes:\n", y_pred)
print("Actual classes   :\n", y_test.values)
# endregion q7

# region q8
# ---------------------------------------------------------------
# 8. Predict class probabilities
# ---------------------------------------------------------------
y_proba = model.predict_proba(X_test_scaled)
print("\nProbabilities (first 5 rows):\n", y_proba[:5].round(4))
print("Columns mean:", model.classes_, "-> [P(class 0), P(class 1)]")
print("Each row sums to:", y_proba[:5].sum(axis=1))

# probability of the positive class only
print("\nP(Purchased=1) for first 5:", y_proba[:5, 1].round(4))

# showing the 0.5 threshold that turns probability into a class
comparison = pd.DataFrame({
    "P(class 1)": y_proba[:8, 1].round(4),
    "Predicted": y_pred[:8],
    "Actual": y_test.values[:8],
})
print("\nThreshold check:\n", comparison)
# endregion q8

# region q9
# ---------------------------------------------------------------
# 9. Evaluate the model
# ---------------------------------------------------------------
# a. accuracy
acc = accuracy_score(y_test, y_pred)
print("\nAccuracy:", round(acc, 4))

# b. confusion matrix
cm = confusion_matrix(y_test, y_pred)
print("\nConfusion Matrix:\n", cm)
tn, fp, fn, tp = cm.ravel()
print(f"TN={tn}  FP={fp}  FN={fn}  TP={tp}")

# c. classification report
print("\nClassification Report:\n", classification_report(y_test, y_pred))
# endregion q9

# region q10
# ---------------------------------------------------------------
# 10. Visualise the confusion matrix
# ---------------------------------------------------------------
# a. quick way - sklearn's built-in display
disp = ConfusionMatrixDisplay(confusion_matrix=cm,
                              display_labels=["Not Purchased", "Purchased"])
disp.plot(cmap="Blues", values_format="d")
plt.title("Confusion Matrix - ConfusionMatrixDisplay")
plt.show()

# b. manual way - pure Matplotlib with imshow
plt.figure(figsize=(5.5, 5))
plt.imshow(cm, cmap="Blues")
plt.title("Confusion Matrix - Manual imshow")
plt.colorbar(label="Count")

labels = ["Not Purchased", "Purchased"]
plt.xticks([0, 1], labels)
plt.yticks([0, 1], labels)
plt.xlabel("Predicted label")
plt.ylabel("True label")

# write the number inside each cell
for i in range(cm.shape[0]):
    for j in range(cm.shape[1]):
        plt.text(j, i, cm[i, j], ha="center", va="center",
                 color="white" if cm[i, j] > cm.max() / 2 else "black",
                 fontsize=14)

plt.tight_layout()
plt.show()
# endregion q10
