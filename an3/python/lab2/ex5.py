def combUtil(res, x, k, currentTuple, currentTupleIndex, xStart):
    if currentTupleIndex == k:
        res.append(currentTuple)
        currentTuple = ()
        return

    for i in range(xStart, len(x)):
        currentTuple += (x[i],)
        combUtil(res, x, k, currentTuple, currentTupleIndex + 1, i + 1)
        # remove last element
        currentTuple = currentTuple[:len(currentTuple) - 1]


def combinari(x, k):
    res = []
    currentTuple = ()
    combUtil(res, x, k, currentTuple, 0, 0)
    return res


print(combinari([1, 2, 3, 4], 2))
