vowels = ['a', 'e', 'i', 'o', 'u']

sir = input('Enter string: ')
noVowels = 0
for i in sir:
    if i in vowels:
        noVowels = noVowels  + 1
print(f'There are {noVowels} vowels in the string')
