import tensorflow as tf

print("Matrix Multiplication Demo")
x = tf.constant([1, 2, 3, 4, 5, 6], shape=[2, 3])
print("Matrix 1: \n", x)
y = tf.constant([7, 8, 9, 10, 11, 12], shape=[3, 2])
print("Matrix 2: \n", y)
z = tf.matmul(x, y)
print("Product: ", z)
e_matrix = tf.random.uniform([2, 2], minval=3, maxval=10, dtype=tf.float32, name="matrixA")
print("Matrix A: \n", e_matrix)
eigen_values, eigen_vectors = tf.linalg.eig(e_matrix)
print("Eigen Vectors: \n", eigen_vectors)
print("\n Eigen Values: \n", eigen_values)
