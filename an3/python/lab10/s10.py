import sys
from datetime import datetime


def problema1():
    d1, d2 = sys.argv[1], sys.argv[2]
    d1 = datetime.strptime(d1, "%m/%d/%Y")
    d2 = datetime.strptime(d2, "%m/%d/%Y")
    return ((d1 - d2).days)


def problema2():
    dates = []
    biggestDifference = None
    for i in range(1, len(sys.argv)):
        currentDate = datetime.strptime(sys.argv[i], "%m/%d/%Y_%H.%M.%S")
        dates.append(currentDate)

    dates.sort(reverse=True)
    biggestDifference = (dates[0] - dates[-1]).days * \
        24 * 60 * 60 + (dates[0] - dates[-1]).seconds
    for i in range(0, len(dates)):
        dates[i] = str(dates[i])
    return (dates, biggestDifference)


if __name__ == '__main__':
    # print(problema1())
    print(problema2())
