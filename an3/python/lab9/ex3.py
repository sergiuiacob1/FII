import os

def ex3(filename):
    with open(filename, 'w') as f:
        for key in os.environ:
            f.write (f'{key}    {os.environ[key]}\n')


ex3('test.txt')