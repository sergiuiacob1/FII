def print_arguments(function):
    def f(*args, **kwargs):
        print(
            f'The arguments are ({args}, {{{kwargs}}})')
        return function(*args, **kwargs)
    return f


def multiply_by_two(x):
    return x * 2


def add_numbers(a, b):
    return a + b


if __name__ == '__main__':
    augmented_multiply_by_two = print_arguments(multiply_by_two)
    # this will print: Arguments are: (10,), {} and will return 20.
    x = augmented_multiply_by_two(10)
    print(x)

    augmented_add_numbers = print_arguments(add_numbers)
    # this will print: Arguments are: (3, 4), {} and will return 7.
    x = augmented_add_numbers(3, 4)
    print(x)
