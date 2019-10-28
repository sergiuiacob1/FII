def ex3(dic1, dic2):
    common = []
    onlyInFirst = []
    onlyInSecond = []
    for key in dic1:
        if key in dic2:
            if (valuesAreDifferent(dic1[key], dic2[key])):
                common.append(key)
        else:
            onlyInFirst.append(key)

    for key in dic2:
        if key not in dic1:
            onlyInSecond.append(key)
    
    return (common, onlyInFirst, onlyInSecond)


def valuesAreDifferent(val1, val2):
    if (type(val1) != type(val2)):
        return True

    try:
        _ = iter(val1)
    except TypeError:
        # not iterable
        # simply compare its values
        return val1 != val2
    else:
        # iterable
        if (len(val1) != len(val2)):
            return True

        for x, y in zip (val1, val2):
            if (valuesAreDifferent(x, y) == True):
                return True

    return False
        

dic1 = {"a" : 1, "b": 2}
dic2 = {"a" : 1, "c": 3}
print (ex3(dic1, dic2))

dic1 = {"a" : 1, "b": 2}
dic2 = {"a" : 10, "c": 3}
print (ex3(dic1, dic2))

dic1 = {"a" : [1, 2], "b": 2}
dic2 = {"a" : 1, "c": 3}
print (ex3(dic1, dic2))

dic1 = {"a" : [1, 2], "b": 2}
dic2 = {"a" : [1, 2], "c": 3}
print (ex3(dic1, dic2))

dic1 = {"a" : [1, 3], "b": 2}
dic2 = {"a" : [1, 2], "c": 3}
print (ex3(dic1, dic2))

dic1 = {"a" : [1, [1, 2]], "b": 2}
dic2 = {"a" : [1, [1, 2]], "c": 3}
print (ex3(dic1, dic2))

dic1 = {"a" : [1, [1, 2]], "b": 2}
dic2 = {"a" : [1, [1, 3]], "c": 3}
print (ex3(dic1, dic2))