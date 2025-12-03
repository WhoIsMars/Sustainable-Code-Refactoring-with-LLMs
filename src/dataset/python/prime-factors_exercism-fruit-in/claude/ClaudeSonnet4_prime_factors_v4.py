def factors(value):
    if value <= 1:
        return []
    
    ret = []
    
    while value % 2 == 0:
        ret.append(2)
        value //= 2
    
    i = 3
    while i * i <= value:
        while value % i == 0:
            ret.append(i)
            value //= i
        i += 2
    
    if value > 1:
        ret.append(value)
    
    return ret