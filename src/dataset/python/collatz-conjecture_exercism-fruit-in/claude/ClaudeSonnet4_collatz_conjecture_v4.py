def steps(number):
    if number <= 0:
        raise ValueError(r".+")
    
    count = 0
    while number != 1:
        if number & 1:
            number = 3 * number + 1
        else:
            number >>= 1
        count += 1
    
    return count