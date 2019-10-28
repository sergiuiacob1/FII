def gcd(a, b):
    r = 0
    while b > 0:
        r = a % b
        a = b
        b = r
    return a


if __name__ == '__main__':
    currentGCD = int(input('Enter first number: '))
    while True:
        nr = int(input('Enter number: '))
        currentGCD = gcd(currentGCD, nr)
        print(f'Current GCD: {currentGCD}')
        if (currentGCD == 1):
            print('GCD will be 1 from now on')
            break
    print(currentGCD)
