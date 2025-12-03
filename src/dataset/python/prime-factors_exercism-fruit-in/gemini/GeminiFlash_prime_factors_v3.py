def factors(value):
    i = 2
    ret = []

    while i * i <= value:
        while value % i == 0:
            ret.append(i)
            value //= i
        i += 1

    if value > 1:
        ret.append(value)

    return ret