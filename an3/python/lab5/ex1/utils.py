import math


def process_item(x):
    for y in range(x, 2*x*x):
        if isPrime(y):
            return y


def isPrime(x):
    if x % 2 == 0 and x != 2:
        return False
    d = 3
    while d * d <= x:
        if x % d == 0:
            return False
        d += 2
    return True


if __name__ == '__main__':
    a = int(input('Enter x: '))
    print(process_item(a))
