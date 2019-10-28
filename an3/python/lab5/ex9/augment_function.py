from functools import reduce
from print_arguments import *
from multiply_output import *


def augment_function(function, decorators):
    # return reduce(lambda f1, f2: f2(f1(function)), decorators[::-1])
    function = decorators[-1](function)
    for decorator in reversed(decorators[:-1]):
        function = decorator(function)
    return function


def add_numbers(a, b):
    return a + b


decorated_function = augment_function(
    add_numbers, [print_arguments, multiply_output])
print(decorated_function)
# this will print: Arguments are: (3, 4), {} and will return (2 * (3 + 4))
x = decorated_function(3, 4)
# print(x)
