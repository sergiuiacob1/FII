def isPrime(n):
    if n % 2 == 0:
        return False
    i = 3
    while i*i <= n:
        if n % i == 0:
            return False
        i += 2
    return True


def getPrimeNumbers(numbers):
    primes = []
    for i in numbers:
        if isPrime(i):
            primes.append(i)
    return primes


print(getPrimeNumbers([2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]))
