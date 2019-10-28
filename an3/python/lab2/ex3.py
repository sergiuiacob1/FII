def lineEcuationParameters(coordinates):
    # slope = D(y)/D(x)
    x, y= coordinates
    slope = y/x
    b = y - slope*x
    # ax + by + c = 0
    return (1, -slope, -b)

def buildLineEcuations(listOfCoordinates):
    res = []
    for coordinates in listOfCoordinates:
        res.append(lineEcuationParameters(coordinates))
    return res


print(buildLineEcuations([(2, 3), (5, 1), (5, 10)]))