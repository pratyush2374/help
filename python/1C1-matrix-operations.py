import numpy as np

x = np.matrix([[1, 2],
               [3, 4]])
y = np.matrix([[5, 6],
               [7, 8]])
print("Matrix 1: ", x)
print("Matrix 2: ", y)
print("Shape matrix 1: ", x.shape)
print("Shape matrix 2: ", y.shape)
print("Matrix multiplication: ", np.matmul(x, y))
print("Matrix 1 Transpose: ", np.transpose(x))
print("Matrix Addition: ", np.add(x, y))
