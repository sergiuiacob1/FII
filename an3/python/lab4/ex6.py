currentValues = []


def recursiveSearch(currentDictionary, separator=' - '):
    global currentValues
    for key in currentDictionary:
        if type(currentDictionary[key]) == dict:
            currentValues += key
            recursiveSearch(currentDictionary[key])
            currentValues.pop()
        else:
            print(separator.join(currentValues +
                                 [key, str(currentDictionary[key])]))


dictionar = {
    'a': 1,
    'b':
    {
        'c': 3,
        'd':
        {
            'e': 5,
            'f': 6
        }
    }
}

recursiveSearch(dictionar)
