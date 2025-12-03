def factors(value):
    if value <= 1:
        return []
    
    ret = []
    
    # Handle factor 2 separately
    while value % 2 == 0:
        ret.append(2)
        value //= 2
    
    # Check odd factors starting from 3
    i = 3
    while i * i <= value:
        while value % i == 0:
            ret.append(i)
            value //= i
        i += 2
    
    # If value is still > 1, it's a prime factor
    if value > 1:
        ret.append(value)
    
    return ret