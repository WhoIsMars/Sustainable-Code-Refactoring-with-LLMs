def factors(value):
    ret = []
    for i in range(2, int(value**0.5) + 1):
        while value % i == 0:
            ret.append(i)
            value //= i
    if value > 1:
        ret.append(value)
    return ret