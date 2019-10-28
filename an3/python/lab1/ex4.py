sir = input('Enter string: ')
sir2 = ''
for i in sir:
    if i.isupper():
        if (len(sir2) > 0):
            sir2 += '_'
        sir2 += i.lower()
    else:
        sir2 += i
print(sir2)
