# Assignment 1: the lab script as submitted (13-08-26_Lab_Numpy.py).
# Only the "# region" / "# endregion" marker lines were added, so the site can show one question at a time.

# region imports
import numpy as np
# endregion imports

# region q1
# ---------------------------------------------------------------
# 1. Create 1D, 2D, and multi-dimensional arrays
# ---------------------------------------------------------------
arr_1d = np.array([1, 2, 3, 4])
arr_2d = np.array([[1, 2, 3], [4, 5, 6]])
arr_nd = np.array([[[1, 2], [3, 4]], [[5, 6], [7, 8]]])   # 3-D

print("1D:", arr_1d, arr_1d.shape)
print("2D:\n", arr_2d, arr_2d.shape)
print("ND:\n", arr_nd, arr_nd.shape)
# endregion q1

# region q2
# ---------------------------------------------------------------
# 2. Array with random values
# ---------------------------------------------------------------

rand_arr = np.random.random((3, 3))          
print("\nRandom array:\n", rand_arr)
# endregion q2

# region q3
# ---------------------------------------------------------------
# 3. Save array to file and load it back
# ---------------------------------------------------------------
np.save("my_array.npy", arr_2d)
loaded_arr = np.load("my_array.npy")
print("\nLoaded array:\n", loaded_arr)
# endregion q3

# region q4
# ---------------------------------------------------------------
# 4. Get shape of array, then reshape it
# ---------------------------------------------------------------
a = np.arange(12)
print("\nOriginal shape:", a.shape)
reshaped = a.reshape(3, 4)
print("Reshaped:\n", reshaped, reshaped.shape)
# endregion q4

# region q5
# ---------------------------------------------------------------
# 5. Arrays with all zeros and all ones
# ---------------------------------------------------------------
zeros_arr = np.zeros((2, 3))
ones_arr = np.ones((2, 3))
print("\nZeros:\n", zeros_arr)
print("Ones:\n", ones_arr)
# endregion q5

# region q6
# ---------------------------------------------------------------
# 6. Initialize array with a range of numbers
# ---------------------------------------------------------------
range_arr = np.arange(0, 20, 2)        # 0 to 18, step 2
print("\nRange array:", range_arr)
# endregion q6

# region q7
# ---------------------------------------------------------------
# 7. Indexing, rows, columns, splitting, iterating
# ---------------------------------------------------------------
m = np.arange(1, 17).reshape(4, 4)
print("\nMatrix:\n", m)

# a. access element using index
print("Element at [1,2]:", m[1, 2])

# b. get specific row
print("Row 1:", m[0])

# c. get specific column
print("Column 2:", m[:, 1])

# d. split array into smaller arrays
splits = np.split(m, 2)                # splits along axis 0 into 2 equal parts
print("Split into 2:\n", splits[0], "\n---\n", splits[1])

# e. iterate over array
print("Iterating:")
for row in m:
    for val in row:
        print(val, end=" ")
print()
# endregion q7

# region q8
# ---------------------------------------------------------------
# 8. Copy, concatenate, reverse, add arrays
# ---------------------------------------------------------------
x = np.array([1, 2, 3])
y = np.array([4, 5, 6])

# a. duplicate/copy array
x_copy = x.copy()
x_copy[0] = 99
print("\nOriginal x:", x, "| copy modified:", x_copy)

# b. concatenate arrays
concat = np.concatenate((x, y))
print("Concatenated:", concat)

# c. reverse array
reversed_arr = x[::-1]
print("Reversed:", reversed_arr)

# d. add two arrays
sum_arr = x + y
print("Sum:", sum_arr)
# endregion q8

# region q9
# ---------------------------------------------------------------
# 9. Vertical and horizontal stacking
# ---------------------------------------------------------------
p = np.array([1, 2, 3])
q = np.array([4, 5, 6])

v_stacked = np.vstack((p, q))
h_stacked = np.hstack((p, q))
print("\nVertical stack:\n", v_stacked)
print("Horizontal stack:", h_stacked)
# endregion q9

# region q10
# ---------------------------------------------------------------
# 10. Dot product and cross product
# ---------------------------------------------------------------
u = np.array([1, 2, 3])
w = np.array([4, 5, 6])

dot_result = np.dot(u, w)          # same as u @ w
cross_result = np.cross(u, w)

print("\nDot product:", dot_result)
print("Cross product:", cross_result)
# endregion q10
