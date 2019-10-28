def ex4(*args, **kwargs):
    res = []
    for arg in args:
        if dictIsGood(arg):
            res.append(arg)
    for key in kwargs:
        if dictIsGood(kwargs[key]):
            res.append(kwargs[key])
    return res


def dictIsGood(dictionar):
    if (type(dictionar) != dict):
        return False
    if (len(dictionar) < 2):
        return False
    for key in dictionar:
        if type(key) == str and len(key) >= 3:
            return True
    return False


print(ex4(
    {1: 2, 3: 4, 5: 6},
    {'a': 5, 'b': 7, 'c': 'e'},
    {2: 3},
    [1, 2, 3],
    {'abc': 4, 'def': 5},
    3764,
    dictionar={'ab': 4, 'ac': 'abcde', 'fg': 'abc'},
    test={1: 1, 'test': True}
))
