def argSum(*args, **kwargs):
    sum = 0
    for arg in kwargs:
        sum += kwargs[arg]
    return sum


print(argSum(1, 2, c=3, d=4))

f = lambda *args, **kwargs: sum([kwargs[arg] for arg in kwargs])
print(f(1, 2, c=3, d=4))
