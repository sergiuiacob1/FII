lista = [1, "2", {"3": "a"}, {4, 5}, 5, 6, 3.0]


def ex5(lista):
    return list(filter(lambda x: True if type(x) in [int, float] else False, lista))


print(ex5(lista))
