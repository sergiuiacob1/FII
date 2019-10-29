import numbers


def ex5(lista):
    return list(filter(lambda x: isinstance(x, numbers.Number), lista))


lista = [1, "2", {"3": "a"}, {4, 5}, 5, 6, 3.0]
print(ex5(lista))
