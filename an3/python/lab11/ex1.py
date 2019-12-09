import re

words = re.compile(r'\w+')
text = 'salut ce mai       faci?   hah0 ce bine!!!'
print(words.findall(text))
