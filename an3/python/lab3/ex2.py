def ex2(sir):
    res = {}
    for i in sir:
        res[i] = sir.count(i)
    return res

print (ex2('salut, ce mai faci?'))