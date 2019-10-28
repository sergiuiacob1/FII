def ex7(lista):
    even = list(filter(lambda x: x % 2 == 0, lista))
    uneven = list(filter(lambda x: x % 2 != 0, lista))
    return list(zip(even, uneven))


print(ex7([1, 3, 5, 2, 8, 7, 4, 10, 9, 2]))
