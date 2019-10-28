def ex8(*lists):
    res = []
    maxLen = max([len(lista) for lista in lists])
    for i in range(maxLen):
        tupla = ()
        for lista in lists:
            if i >= len(lista):
                tupla +=(None,)
            else:
                tupla +=(lista[i],)
        res.append(tupla)
    return res


print(ex8([1,2,3], [5,6,7], ["a", "b", "c", "d"]))
