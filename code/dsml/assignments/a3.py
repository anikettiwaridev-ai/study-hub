# Assignment 3: the lab script as submitted (10-09-26_Lab_SciKit.py).
# Only the "# region" / "# endregion" marker lines were added, so the site can show one question at a time.

# region imports
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score
# endregion imports

# region q1
# ---------------------------------------------------------------
# 1. Load the dataset (Salary_Data.csv) and show first 5 rows
# ---------------------------------------------------------------
df = pd.read_csv("Salary_Data.csv")
print("First 5 rows:\n", df.head())
# endregion q1

# region q2
# ---------------------------------------------------------------
# 2. Shape of the dataset and missing values
# ---------------------------------------------------------------
print("\nShape:", df.shape)
print("Missing values:\n", df.isnull().sum())
# endregion q2

# region q3
# ---------------------------------------------------------------
# 3. Separate feature (X) and target (y)
# ---------------------------------------------------------------
X = df[["YearsExperience"]]      # 2-D, as sklearn expects
y = df["Salary"]

print("\nX (first 5):\n", X.head())
print("y (first 5):\n", y.head())
# endregion q3

# region q4
# ---------------------------------------------------------------
# 4. Split into training (80%) and testing (20%) sets
# ---------------------------------------------------------------
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)
print("\nTrain size:", X_train.shape, "| Test size:", X_test.shape)
# endregion q4

# region q5
# ---------------------------------------------------------------
# 5. Create the Linear Regression model
# ---------------------------------------------------------------
model = LinearRegression()
# endregion q5

# region q6
# ---------------------------------------------------------------
# 6. Train (fit) the model on training data
# ---------------------------------------------------------------
model.fit(X_train, y_train)
print("\nModel trained.")
# endregion q6

# region q7
# ---------------------------------------------------------------
# 7. Predict salaries on the test data
# ---------------------------------------------------------------
y_pred = model.predict(X_test)
print("\nPredicted salaries:\n", y_pred)
print("Actual salaries:\n", y_test.values)
# endregion q7

# region q8
# ---------------------------------------------------------------
# 8. Slope and intercept
# ---------------------------------------------------------------
# a. slope / coefficient
print("\nSlope (coefficient):", model.coef_[0])

# b. intercept
print("Intercept:", model.intercept_)
# endregion q8

# region q9
# ---------------------------------------------------------------
# 9. Evaluate the model
# ---------------------------------------------------------------
# a. Mean Squared Error
print("\nMean Squared Error:", mean_squared_error(y_test, y_pred))

# b. R-squared score
print("R2 Score:", r2_score(y_test, y_pred))
# endregion q9

# region q10
# ---------------------------------------------------------------
# 10. Plot actual points and the regression line
# ---------------------------------------------------------------
plt.figure()

# a. actual data points
plt.scatter(X, y, color="blue", label="Actual data")

# b. regression line on top
plt.plot(X, model.predict(X), color="red", label="Regression line")

plt.title("Salary vs Years of Experience")
plt.xlabel("Years of Experience")
plt.ylabel("Salary")
plt.legend()
plt.show()
# endregion q10
