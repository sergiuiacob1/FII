def ex7(*siruri, x=1, flag=True):
    res = ()
    for sir in siruri:
        chars = []
        for char in sir:
            if ord(char) % x == (not flag):
                chars.append(char)
        res += (chars,)

    return res


print(ex7("test", "hello", "lab002", x=2, flag=False))
