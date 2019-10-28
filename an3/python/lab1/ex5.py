import math

with open('matrix.txt', 'r') as f:
    matrix = [[character for character in line.strip()] for line in f]

print(matrix, '\n')


for r in range(int(math.sqrt(len(matrix)))):
    # r o sa fie deplasamentul
    # right
    for i in range(len(matrix) - r - 1):
        print(matrix[r][r + i], end='')
    # down
    for i in range(len(matrix) - r - 1):
        print(matrix[r + i][len(matrix) - r - 1], end='')
    # left
    for i in range(len(matrix) - r - 1):
        print(matrix[len(matrix) - r - 1][len(matrix) - i - 1], end='')
    # up
    for i in range(len(matrix) - r - 1):
        print(matrix[len(matrix) - i - 1][r], end='')

print('\n')
