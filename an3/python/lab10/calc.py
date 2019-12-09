import os
import sys
import time


def calc(a, b, op, path):
    def add(x, y): return x + y
    def subtract(x, y): return x - y
    def divide(x, y): return x/y
    def multiply(x, y): return x * y
    func = {'+': add, '-': subtract, '/': divide, '*': multiply}
    res = func[op](a, b)
    path = os.path.join(os.getcwd(), path)
    with open(path, 'a') as f:
        f.write(f'{time.ctime()} {a} {op} {b} {res}\n')


if __name__ == '__main__':
    a, b = int(sys.argv[1]), int(sys.argv[3])
    op = sys.argv[2]
    path = sys.argv[4]
    calc(a, b, op, path)
