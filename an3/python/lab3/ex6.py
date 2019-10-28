lambdas = {    
    "+": 'lambda a, b: a + b',     
    "*": lambda a, b: a * b,
    "/": lambda a, b: a / b,
    "%": lambda a, b: a % b
}

def apply_operator(operator, a, b):
    return lambdas[operator](a, b)

print(apply_operator('*', 2, 5))