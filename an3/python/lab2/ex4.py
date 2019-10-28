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


list1 = [1, 2, 3, 4, 5, 6]
list2 = [4, 5, 7, 8]

print (intersection(list1, list2))
print (union(list1, list2))
print (difference(list1, list2))
print (difference(list2, list1))