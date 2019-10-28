def customSort(a):
    _, second = a
    return second[2]


lista = [('abc', 'bcd'), ('abc', 'zza'), ('abc', 'zza')]
print(sorted(lista, key=customSort))
