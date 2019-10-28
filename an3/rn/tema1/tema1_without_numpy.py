from equation_parser import parseEquations


def getEmptyMatrix(rows, columns=None):
    if columns is None:
        columns = rows
    return [[None for j in range(columns)] for i in range(rows)]


def getMatrixMinor(matrix, i, j):
    # return the matrix without the ith row and jth column
    submatrixWithoutRow = matrix[:i]
    submatrixWithoutRow.extend(matrix[i+1:])
    submatrix = [row[:j] + row[j+1:] for row in submatrixWithoutRow]
    return submatrix


def getMatrixOfMinors(matrix):
    matrixOfMinors = getEmptyMatrix(len(matrix))
    for i in range(len(matrix)):
        for j in range(len(matrix)):
            matrixOfMinors[i][j] = getMatrixDeterminant(
                getMatrixMinor(matrix, i, j))
    return matrixOfMinors


def getMatrixOfCofactors(matrix):
    sign = 1
    matrixCopy = matrix.copy()
    for i in range(len(matrixCopy)):
        for j in range(len(matrixCopy)):
            matrixCopy[i][j] = sign * matrixCopy[i][j]
            sign *= -1
    return matrixCopy


def getMatrixDeterminant(matrix):
    # cazul de baza, inmultire pe diagonala
    if len(matrix) == 2:
        return matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0]

    determinant = 0
    for c in range(len(matrix)):
        sign = (-1)**c
        determinant += sign * \
            matrix[0][c] * getMatrixDeterminant(getMatrixMinor(matrix, 0, c))
    return determinant


def getMatrixTranspose(matrix):
    transpose = getEmptyMatrix(len(matrix))
    for i in range(len(matrix)):
        for j in range(len(matrix)):
            transpose[i][j] = matrix[j][i]
    return transpose


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
    print(f'A: {A}')
    detA = getMatrixDeterminant(A)
    print(f'det(A) = {detA}')
    matrixOfMinors = getMatrixOfMinors(A)
    print(f'Matrix of minors: {matrixOfMinors}')

    matrixOfCofactors = getMatrixOfCofactors(matrixOfMinors)
    print(f'Matrix of cofactors: {matrixOfCofactors}')

    adjugate = getMatrixTranspose(matrixOfCofactors)
    inverse = getEmptyMatrix(len(adjugate))
    for i in range(len(adjugate)):
        for j in range(len(adjugate)):
            inverse[i][j] = adjugate[i][j]/detA
    print(f'Inverse is: {inverse}')

    print(f'Solution is: {multiplyMatrixes(inverse, r)}')
