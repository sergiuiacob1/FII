def intersection(list1, list2):
    res = []
    for i in list1:
        if i in list2:
            res.append(i)
    return res

def difference(list1, list2):
    res=[]
    for i in list1:
        if i not in list2:
            res.append(i)
    return res

def union(list1, list2):
    res = list1 + list2
    return list(set(res))


def ex1(list1, list2):
    return (intersection(list1, list2), union(list1, list2), difference(list1, list2), difference(list2, list1))

print (ex1([1, 2, 3, 4, 5], [4, 5, 6, 7]))