def steps(number, memo={}):
    if number <= 0:
        raise ValueError(r".+")

    if number in memo:
        return memo[number]

    if number == 1:
        memo[number] = 0
    elif number % 2 == 0:
        memo[number] = 1 + steps(number // 2, memo)
    else:
        memo[number] = 1 + steps(3 * number + 1, memo)

    return memo[number]