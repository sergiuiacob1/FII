def sortTuples(tuples):
    return sorted(tuples, key=lambda x: x[1])


print(sortTuples([('ana', 'banana'), ('zeu', 'popescu'), ('buh', 'frunza'), ('carina', 'nume')]))
