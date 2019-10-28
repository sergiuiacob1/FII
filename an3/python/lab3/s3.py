def problema1(n):
    suma = 0
    for i in range(0, n+1):
        suma += i

    return suma


def problema5(n):
    base10 = int(n, 8)

    if (str(base10) == str(base10)[::-1]):
        return True
    return False


print(problema5(n="30041"))
