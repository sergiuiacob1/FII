def ex6(liste, x):
    union = []
    for lista in liste:
        union += lista
    res = []
    for i in union:
        count = union.count(i)
        if count == x:
            res.append(i)
    return list(set(res))


print(ex6([[1, 2, 3], [2, 3, 4], [4, 5, 6], [4, 1, "test"]], 2))
