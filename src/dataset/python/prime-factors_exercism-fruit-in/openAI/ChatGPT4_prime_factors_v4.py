def factors(value):
    ret = []
    while value % 2 == 0:
        ret.append(2)
        value //= 2

    for i in range(3, int(value**0.5) + 1, 2):
        while value % i == 0:
            ret.append(i)
            value //= i

    if value > 1:
        ret.append(value)

    return ret