import numpy as np

A = np.array([[1, -1, 2], [4, 0, 6], [0, -1, 1]])
invmatrix = np.linalg.inv(A)
print("Matrix: \n", A)
print("Shape of matrix: ", A.shape)
print("Inverse of Matrix: \n", invmatrix)
