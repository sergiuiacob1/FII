def firstNFib(n):
    numbers = [1, 1]
    if n <= 2:
        return [1] * n
    for i in range(2, n):
        numbers.append(numbers[i-1] + numbers[i - 2])
    return numbers


print(firstNFib(10))
