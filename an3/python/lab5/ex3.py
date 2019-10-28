s = 'Programming in Python is fun'
vowels = ['a', 'e', 'i', 'o', 'u']


def getVowels(s):
    res = []
    for c in s:
        if c.lower() in vowels:
            res += c
    return res


print(getVowels(s))
print([a for a in s if a.lower() in vowels])
print(list(filter(lambda x: True if x.lower() in vowels else False, s)))
