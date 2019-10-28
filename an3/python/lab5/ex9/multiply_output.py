def multiply_output(function):
    return lambda x: 2 * function(x)


def multiply_by_three(x):
    return x * 3

if __name__=='__main__':
    augmented_multiply_by_three = multiply_output(multiply_by_three)
    x = augmented_multiply_by_three(10)  # this will return 2 * (10 * 3)
    print(x)
