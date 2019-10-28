def lineEcuationParameters(p1, p2):
    # slope = D(y)/D(x)
    x1, y1 = p1
    x2, y2 = p2
    slope = (y2 - y1) / (x2 - x1)
    # y - y1 = slope * (x - x1)
    # slope * (x - x1) + y1 - y = 0
    # slope * x - slope * x1 + y1 - y = 0
    return (slope, -1, -slope * x1 + y1)


def f1(list1, list2):
    # this one uses map
    return list(map(lambda x, y: lineEcuationParameters(x, y), list1, list2))


def f2(list1, list2):
    # this one uses zip
    res = []
    for p1, p2 in zip(list1, list2):
        res.append(lineEcuationParameters(p1, p2))
    return res


list1 = [(2.5, 1.0), (3.65, 5.0), (1.0, 15.0)]
list2 = [(3.2, 2.5), (2.5, 2.5), (7.3, 13.2)]

pars = f1(list1, list2)
print(pars)
a, b, c = pars[0]
x, y = list2[0]
print(f'This should be equal to 0: {a*x + b*y + c}')


print(f2(list1, list2))
