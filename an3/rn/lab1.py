import os
import numpy as np


def isPrime(no):
    i = 2
    while i*i <= no:
        if no % i == 0:
            return False
        i += 1
    return True


print(isPrime(2))
print(isPrime(3))
print(isPrime(10))
print(isPrime(11))

words = []
with open('words.txt', 'r') as f:
    words = f.read().split()
    # for line in f:
    #     for word in line.split():
    #         words.append(word)
words.sort()
print(words)


matrix = [[1, 2, 3, 4], [11, 12, 13, 14], [21, 22, 23, 24]]
matrix2 = [[2], [-5], [7], [-10]]
matrixRes = []
for line in matrix:
    lineRes = []
    for colNo in range(len(matrix2[0])):
        currentColumn = [matrix2[i][colNo] for i in range(len(matrix2))]
        prod = [a*b for a, b in zip(line, currentColumn)]
        lineRes.append(sum(prod))
    matrixRes.append(lineRes)
print(matrixRes)
print(np.dot(matrix, matrix2))


a = np.array(matrix)
print(a.shape)
print(a[:2, -2:])
c = np.random.rand(5)

