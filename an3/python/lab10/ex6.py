import timeit

testSlow = '''
def isPrimeSlow(n):
    if n is 2:
        return True
    i = 2
    while i < n:
        if n % i == 0:
            return False
        i += 1
    return True

isPrimeSlow(99190020031231)
'''

testFast = '''
def isPrimeFast(n):
    if n % 2 == 0:
        return False
    i = 3
    while i*i <= n:
        if n % i == 0:
            return False
        i += 2
    return True

isPrimeFast(99190020031231)
'''

print(timeit.timeit(stmt=testFast, number=1000))
print(timeit.timeit(stmt=testSlow, number=1000))
