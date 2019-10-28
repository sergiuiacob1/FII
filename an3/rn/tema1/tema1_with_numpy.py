from equation_parser import parseEquations
import numpy as np


def getEmptyMatrix(rows, columns=None):
    if columns is None:
        columns = rows
    return np.empty([rows, columns])


def getMatrixMinor(matrix, i, j):
    submatrix = matrix.copy()
    submatrix = np.delete(matrix, i, axis=0)
    submatrix = np.delete(submatrix, j, axis=1)
    return submatrix


def getMatrixOfMinors(matrix):
    matrixOfMinors = getEmptyMatrix(len(matrix))
    for i in range(len(matrix)):
        for j in range(len(matrix)):
            matrixOfMinors[i][j] = np.linalg.det(getMatrixMinor(matrix, i, j))
    return matrixOfMinors


def getMatrixOfCofactors(matrix):
    sign = 1
    matrixCopy = matrix.copy()
    for i in range(len(matrixCopy)):
        for j in range(len(matrixCopy)):
            matrixCopy[i][j] = sign * matrixCopy[i][j]
            sign *= -1
    return matrixCopy


def multiplyMatrixes(matrix1, matrix2):
    matrix1Copy = []
    matrix2Copy = []
    for row in matrix2:
        if type(row) != list:
            matrix2Copy.append([row])
        else:
            matrix2Copy.append(row)

    for row in matrix1:
        if type(row) != list:
            matrix1Copy.append([row])
        else:
            matrix1Copy.append(row)

    matrixRes = []
    for line in matrix1Copy:
        lineRes = []
        for colNo in range(len(matrix2Copy[0])):
            currentColumn = [matrix2Copy[i][colNo]
                             for i in range(len(matrix2Copy))]
            prod = [a*b for a, b in zip(line, currentColumn)]
            lineRes.append(sum(prod))
        matrixRes.append(lineRes)
    return matrixRes


if __name__ == '__main__':
    A, r = parseEquations()
    A = np.matrix(A)
    # print (np.linalg.solve(A, r))
    print(f'A: {A}')
    print(f'r: {r}')
    detA = np.linalg.det(A)
    print(f'det(A) = {detA}')
    matrixOfMinors = getMatrixOfMinors(A)
    print(f'Matrix of minors: {matrixOfMinors}')

    matrixOfCofactors = getMatrixOfCofactors(matrixOfMinors)
    print(f'Matrix of cofactors: {matrixOfCofactors}')

    adjugate = matrixOfCofactors.transpose()
    inverse = adjugate / detA
    print(f'Inverse is: {inverse}')

    print(f'Solution is: {np.matmul(inverse, r)}')
