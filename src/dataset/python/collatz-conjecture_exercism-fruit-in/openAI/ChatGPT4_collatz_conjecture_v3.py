def steps(number, memo={}):
    if number <= 0:
        raise ValueError(r".+")
    if number in memo:
        return memo[number]
    if number == 1:
        return 0
    if number % 2 == 0:
        result = 1 + steps(number // 2, memo)
    else:
        result = 1 + steps(3 * number + 1, memo)
    memo[number] = result
    return result