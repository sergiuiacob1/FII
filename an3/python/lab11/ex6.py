import re


def replace_with(s):
    s = s.group(0)
    return ''.join([str(x) if index % 2 == 0 else '*' for (index, x) in enumerate(s)])


def ex6(s):
    r = r'[aeiou]+'
    return re.sub(r, replace_with, text, flags=re.IGNORECASE)


text = 'Saalut ce maai faci eeeu sunt bbbbiiiiiiiiine, mersi'
print(ex6(text))
