def unifyDictionaryes(*dictionaries):
    res = {}
    for mappp in dictionaries:
        for key in mappp:
            if key in res:
                if type(res[key]) != list:
                    res[key] = [res[key]]
                res[key].append(mappp[key])
            else:
                res[key] = mappp[key]
    return res


print(unifyDictionaryes({'a': 1, 'b': 2}, {
      'a': 3, 'b': {'altaCheie': 4}, 'c': 'dadada'}, {'c': 1}))
