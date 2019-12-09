# 2) Write a function that receives as a parameter a regex string, a text string and a whole number x, and returns those long-length x substrings that match the regular expression.
import re


def ex2(regex_string, text, x):
    r = re.compile(regex_string)
    res = [string for string in r.findall(text) if len(string) == x]
    return res


print(ex2(r'\w+', 'salll cmf eu bine tuu?', 3))

