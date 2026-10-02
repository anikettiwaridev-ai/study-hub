# Assignment 6: the lab script as submitted (24-09-26_Lab_KNN.py).
# Only the "# region" / "# endregion" marker lines were added, so the site can show one question at a time.

# region imports
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import (accuracy_score, confusion_matrix,
                             classification_report, ConfusionMatrixDisplay)
# endregion imports

# region q1
# ---------------------------------------------------------------
# 1. Load the dataset (Iris.csv) and display the first 5 rows
# ---------------------------------------------------------------
df = pd.read_csv("Iris.csv")
print("First 5 rows:\n", df.head())
# endregion q1

# region q2
# ---------------------------------------------------------------
# 2. Shape of the dataset and missing values
# ---------------------------------------------------------------
print("\nShape:", df.shape)
print("\nMissing values:\n", df.isnull().sum())
print("\nClass balance:\n", df["Species"].value_counts())
# endregion q2

# region q3
# ---------------------------------------------------------------
# 3. Separate features (X) and target (y)
# ---------------------------------------------------------------
# "Id" is just a row number - it carries no information about the flower,
# so it must NOT be a feature. KNN measures distance, and a row number would
# add a meaningless dimension to that distance.
X = df.drop(columns=["Id", "Species"])     # 4 measurements, 2-D
y = df["Species"]                           # 3 classes, 1-D

print("\nX shape:", X.shape, "| y shape:", y.shape)
print("Feature columns:", list(X.columns))
# endregion q3

# region q4
# ---------------------------------------------------------------
# 4. Split into training (80%) and testing (20%) sets
# ---------------------------------------------------------------
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)
print("\nTrain size:", X_train.shape, "| Test size:", X_test.shape)
print("Test class counts:", y_test.value_counts().to_dict())
# endregion q4

# region q5
# ---------------------------------------------------------------
# 5. Scale the features using StandardScaler
# ---------------------------------------------------------------
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)   # LEARN + apply on train
X_test_scaled = scaler.transform(X_test)         # only APPLY on test

print("\nLearned means :", scaler.mean_.round(3))
print("Learned scales:", scaler.scale_.round(3))
# endregion q5

# region q6
# ---------------------------------------------------------------
# 6. Create and train KNN with k = 5
# ---------------------------------------------------------------
knn = KNeighborsClassifier(n_neighbors=5)
knn.fit(X_train_scaled, y_train)
print("\nModel trained (k = 5).")
print("Samples stored inside the model:", knn.n_samples_fit_)
# endregion q6

# region q7
# ---------------------------------------------------------------
# 7. Predict target classes on the test data
# ---------------------------------------------------------------
y_pred = knn.predict(X_test_scaled)
print("\nPredicted (first 10):", list(y_pred[:10]))
print("Actual    (first 10):", list(y_test.values[:10]))

# Look inside one prediction: which 5 training flowers voted?
distances, indices = knn.kneighbors(X_test_scaled[:1])
print("\nFirst test flower - its 5 nearest training neighbours:")
for d, i in zip(distances[0], indices[0]):
    print(f"   distance {d:.4f}  ->  {y_train.values[i]}")
# endregion q7

# region q8
# ---------------------------------------------------------------
# 8. Evaluate the model
# ---------------------------------------------------------------
# a. accuracy
acc = accuracy_score(y_test, y_pred)
print("\nAccuracy:", round(acc, 4))

# b. confusion matrix
cm = confusion_matrix(y_test, y_pred, labels=knn.classes_)
print("\nConfusion Matrix (rows = actual, cols = predicted):")
print(pd.DataFrame(cm, index=knn.classes_, columns=knn.classes_))

# c. classification report
print("\nClassification Report:\n", classification_report(y_test, y_pred))

disp = ConfusionMatrixDisplay(confusion_matrix=cm,
                              display_labels=["setosa", "versicolor", "virginica"])
disp.plot(cmap="Blues", values_format="d")
plt.title("KNN (k = 5) - Confusion Matrix")
plt.tight_layout()
plt.show()
# endregion q8

# region q9
# ---------------------------------------------------------------
# 9. Train KNN for k = 1 to 15 and print accuracy
# ---------------------------------------------------------------
k_values = range(1, 16)
test_accuracies = []

print("\n k | test accuracy")
print("---+--------------")
for k in k_values:
    model = KNeighborsClassifier(n_neighbors=k)
    model.fit(X_train_scaled, y_train)
    a = accuracy_score(y_test, model.predict(X_test_scaled))
    test_accuracies.append(a)
    print(f"{k:2d} | {a:.4f}")

best_k = k_values[test_accuracies.index(max(test_accuracies))]
print("\nBest k on the test set:", best_k, "with accuracy", round(max(test_accuracies), 4))
# endregion q9

# region q10
# ---------------------------------------------------------------
# 10. Plot k versus accuracy
# ---------------------------------------------------------------
plt.figure(figsize=(8, 4.5))
plt.plot(list(k_values), test_accuracies, marker="o", color="steelblue")
plt.title("KNN - k value vs Test Accuracy")
plt.xlabel("k (number of neighbours)")
plt.ylabel("Accuracy")
plt.xticks(list(k_values))
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.show()
# endregion q10

# region extra
# ---------------------------------------------------------------
# EXTRA (beyond the sheet): choosing k the leakage-free way
# ---------------------------------------------------------------
# Steps 9-10 pick k by looking at TEST accuracy. That uses the test set to
# make a decision, so the test score stops being an honest estimate.
# 5-fold cross-validation on the TRAINING set chooses k without ever
# touching the test set.
cv_means = []
for k in k_values:
    scores = cross_val_score(KNeighborsClassifier(n_neighbors=k),
                             X_train_scaled, y_train, cv=5)
    cv_means.append(scores.mean())

cv_best_k = k_values[cv_means.index(max(cv_means))]
print("\nCross-validated accuracy on training set:")
for k, m in zip(k_values, cv_means):
    print(f"{k:2d} | {m:.4f}")
print("Best k by 5-fold CV:", cv_best_k)

final = KNeighborsClassifier(n_neighbors=cv_best_k).fit(X_train_scaled, y_train)
print("Test accuracy of CV-chosen k:",
      round(accuracy_score(y_test, final.predict(X_test_scaled)), 4))

plt.figure(figsize=(8, 4.5))
plt.plot(list(k_values), test_accuracies, marker="o", label="Test accuracy")
plt.plot(list(k_values), cv_means, marker="s", label="5-fold CV accuracy (train)")
plt.title("KNN - test accuracy vs cross-validated accuracy")
plt.xlabel("k (number of neighbours)")
plt.ylabel("Accuracy")
plt.xticks(list(k_values))
plt.legend()
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.show()
# endregion extra
