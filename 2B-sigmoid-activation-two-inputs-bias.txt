import math

x1 = float(input("Enter the input X1: "))
x2 = float(input("Enter the input X2: "))
w1 = float(input("Enter the weight W1: "))
w2 = float(input("Enter the weight W2: "))
bias = float(input("Enter bias: "))
yin = (x1 * w1) + (x2 * w2) + bias
ybin = 1 / (1 + math.exp(-yin))
ybipolar = (2 / (1 + math.exp(-yin))) - 1
print("Input X1 = ", x1)
print("Input X2 = ", x2)
print("Weight W1 = ", w1)
print("Weight W2 = ", w2)
print("Bias = ", bias)
print("Net Input yin = ", yin)
print("Output BINARY SIGMOIDAL FUNCTION Y = ", ybin)
print("Output BIPOLAR SIGMOIDAL FUNCTION Y = ", ybipolar)
