import re


def fibo(n):
    no = [None] * (n + 1)
    no[0] = 1
    no[1] = 1
    for i in range(2, n):
        no[i] = no[i - 1] + no[i - 2]
    return no[n - 1]


def is_prime(number):
    if number == 1:
        return False
    if number % 2 == 0 and number != 2:
        return False
    d = 3
    while d*d <= number:
        if number % d == 0:
            return False
        d += 2
    return True


def getAllFiboNumbers(limit):
    no = [1, 1]
    while no[-1] < limit:
        no.append(no[-1] + no[-2])
    return no


def custom_filter(my_list):
    maxim = max(my_list)
    fibs = getAllFiboNumbers(limit=maxim)
    filtered = list(filter(lambda x: is_prime(x) and x in fibs, my_list))
    filtered.sort()
    return filtered


def extract_numbers(text):
    # numbers = []
    # currentNumber = 0
    # changed = False
    # for i in text:
    #     if ('0' <= i and i <= '9'):
    #         currentNumber = currentNumber*10 + int(i)
    #         changed = True
    #     else:
    #         if changed:
    #             numbers.append(currentNumber)
    #         changed = False
    #         currentNumber = 0

    # if changed:
    #     numbers.append(currentNumber)

    # numbers.sort(reverse=True)
    # return numbers

    numbers = re.findall("\d+", text)
    numbers = list(map(lambda x: int(x), numbers))
    numbers.sort(reverse=True)
    return numbers


def special_sum(*strings):
    mySum = 0
    for string in strings:
        numbers = list(filter(lambda x: x % 2 == 0, extract_numbers(string)))
        mySum += numbers[0]
    return mySum


def loop(mapping):
    res = []
    visited = set()
    currentKey = 'start'
    while currentKey not in visited:
        res.append(mapping[currentKey])
        visited.add(currentKey)
        currentKey = mapping[currentKey]
    res.pop(-1)
    return res


def sequence(n):
    # seq(n) = 2 * seq(int(n/2)) - seq(n-2), where seq(0) = 2 and seq(1) = 4.
    seq = [2, 4]
    seq.extend([None] * (n - 1))
    for i in range(2, n+1):
        seq[i] = 2 * seq[i//2] - seq[i - 2]
    return seq[n]


if __name__ == '__main__':
    # print(fibo(n=1))
    # print(is_prime(number=29))
    # print(custom_filter([29, 13, 5, 18, 21, 2, 9]))
    print(extract_numbers("R24SwT6Bl2r18c68ytwYLk125NkBgh943qTgkfp10jJoU"))
    # print(special_sum("tPt82eWq31d10P","Lkn111N6aRekJ30E","90n32k1L8dnBa33"	))
    # print(loop(mapping={'start': 'a', 'a': 'e', 'e': 'b',
    #                     'b': 'c', 'c': 'd', 'd': 'f', 'f': 'g', 'g': 'b'}))
    print(sequence(7617))
