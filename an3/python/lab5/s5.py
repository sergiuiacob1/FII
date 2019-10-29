def problem1(my_list):
    even = list(filter(lambda x: x % 2 == 0, my_list))
    odd = list(filter(lambda x: x % 2 != 0, my_list))
    return list(zip(even, odd))


def problem2(pairs):
    res = []
    for pair in pairs:
        dic = {}
        dic['sum'] = sum(pair)
        dic['prod'] = pair[0]*pair[1]
        dic['pow'] = pair[0]**pair[1]
        res.append(dic)
    return res


if __name__ == '__main__':
    print(problem1(my_list=[5, 51, 3, 35, 24, 32, 2, 54, 44, 40,
                              70, 80, 48, 0, 36, 1, 82, 83, 11, 99, 41, 71, 35, 73]))
    print(problem2(pairs=[(-1, -1), (10, -3), (3, 5), (-2, 9)]))
