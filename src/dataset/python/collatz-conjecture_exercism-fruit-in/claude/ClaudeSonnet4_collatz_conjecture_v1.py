def steps(number):
    if number <= 0:
        raise ValueError(r".+")

    count = 0
    while number != 1:
        if number % 2 == 0:
            number //= 2
        else:
            number = 3 * number + 1
        count += 1
    
    return count