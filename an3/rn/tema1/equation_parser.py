def parseEquations():
    coefficients = []
    r = []
    with open('equations.txt', 'r') as f:
        for equation in f:
            currentEquationCoefficients = []
            # remove blanks
            equation = equation.replace(' ', '').strip()
            aux = equation.split('x')[0]
            appendStringInt(currentEquationCoefficients, aux)
            aux = equation.split('y')[0].split('x')[1]
            appendStringInt(currentEquationCoefficients, aux)
            aux = equation.split('z')[0].split('y')[1]
            appendStringInt(currentEquationCoefficients, aux)
            aux = equation.split('=')[1]
            appendStringInt(r, aux)

            coefficients.append(currentEquationCoefficients)
    return coefficients, r


def appendStringInt(myList, myString):
    if myString == '+' or len(myString) == 0:
        myList.append(1)
    elif myString == '-':
        myList.append(-1)
    else:
        myString = myString.replace('*', '')
        myList.append(int(myString))


if __name__ == '__main__':
    print(parseEquations())
