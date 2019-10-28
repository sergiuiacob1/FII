import itertools

functions = {
    '|': lambda *sets: union(*sets),
    '&': lambda *sets: intersection(*sets),
    '-': lambda *sets: difference(*sets),

}


def union(*sets):
    setRes = set()
    for x in sets:
        setRes = setRes.union(x)
    return setRes


def intersection(*sets):
    setRes = set()
    for x in sets:
        setRes = setRes.intersection(x)
    return setRes


def difference(*sets):
    setRes = set()
    for x in sets:
        setRes = setRes.difference(x)
    return setRes


def ex9(*sets):
    res = {}
    operators = ['|', '&', '-']
    for combination in list(itertools.combinations(sets, 2)):
        firstSet, secondSet = combination
        for operator in operators:
            res[f'{firstSet} {operator} {secondSet}'] = functions[operator](
                firstSet, secondSet)

    return res


print(ex9({1, 2}, {2, 3}))
