def problema1(numar, cifra):
    return str(numar).count(str(cifra))


def problema2(*args, **kwargs):
    kwargs_values = []
    res = 0
    for key in kwargs:
        kwargs_values.append(kwargs[key])
    for arg in args:
        if arg in kwargs_values:
            res += 1
    return res


def problema3(matrice):
    for (line_index, _) in enumerate(matrice):
        for col_index in range(0, line_index):
            matrice[line_index][col_index] = 0
    return matrice


def problema4(notes, moves, start):
    current_pos = start % len(notes)
    res = [notes[current_pos]]
    for move in moves:
        current_pos += move
        current_pos = current_pos % len(notes)
        res.append(notes[current_pos])

    return res


def problema5(cod):
    def equal(*args, val): return val
    def add(x, val): return x + val
    def minus(x, val): return x - val
    def divide(x, val): return x // val
    def multiply(x, val): return x * val
    commands = ['egal', 'plus', 'minus', 'impartit', 'inmultit']
    functions = [equal, add, minus, divide, multiply]
    lines = cod.split('\n')
    d = {'x': None}
    for line in lines:
        for index, command in enumerate(commands):
            if command in line:
                var_val = line.split(command)
                var = var_val[0].strip()
                val = int(var_val[1].strip())
                d[var] = functions[index](d[var], val = val)
                
        # if 'egal' in line:
        #     d[var] = val
        # if 'plus' in line:
        #     d[var] += val
        # if 'minus' in line:
        #     d[var] -= val
        # if 'impartit' in line:
        #     d[var] = d[var]//val
        # if 'inmultit' in line:
        #     d[var] = d[var]*val

    for key in d:
        return d[key]


if __name__ == '__main__':
    # print(problema1(123151, 1))
    # print(problema2(1, 1, 2, x=1, y=4, z=3, w=5))
    # print(problema3([1, 2, 3], [4, 5, 6], [7, 8, 9]]))
    # print(problema4(["do", "re", "mi", "fa", "sol"], [1, -3, 4, 2], 2))
    print(problema5("x egal 15\nx plus 6\nx impartit 3"	))
