def process(**kwargs):
    fibs = getFibNumbers(100)
    if 'filters' in kwargs:
        predicates = kwargs['filters']
        def f(x): return all([predicate(x) for predicate in predicates])
        fibs = list(filter(f, fibs))
    if 'offset' in kwargs:
        fibs = fibs[kwargs['offset']:]
    if 'limit' in kwargs:
        fibs = fibs[:kwargs['offset']]
    return fibs


def getFibNumbers(n):
    fibs = [0, 1]
    for i in range(2, n):
        fibs.append(fibs[i - 1] + fibs[i - 2])
    return fibs


def sum_digits(x):
    return sum(map(int, str(x)))


print(process(filters=[lambda item: item % 2 == 0, lambda item: item ==
                       2 or 4 <= sum_digits(item) <= 20], limit=2, offset=2))
