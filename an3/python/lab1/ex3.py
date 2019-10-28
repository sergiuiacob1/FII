str1 = input('First string: ')
str2 = input('Second string: ')

count = 0
index = 0
while index < len(str2):
    try:
        index = index + str2[index:].index(str1)
        count = count + 1
        index = index + 1
    except:
        break

print(f'First string appears in the second {count} times')
