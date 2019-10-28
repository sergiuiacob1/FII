def binarySearch(tuples, name):
    st, dr = -1, len(tuples)
    while dr - st > 1:
        mid = (st + dr)//2
        if tuples[mid][1] < name:
            st = mid
        else:
            dr = mid

    if dr == len(tuples) or tuples[dr][1] != name:
        return -1
    return dr


tuples = [('ana', 'banana'), ('buh', 'frunza'), ('carina', 'nume'), ('zeu', 'popescu')]
print(binarySearch(tuples, 'frunza'))
