from functools import reduce


def largest_product(series, size):
    if size < 0:
        raise ValueError(r".+")
    
    if len(series) < size:
        raise ValueError(r".+")
    
    if size == 0:
        return 1
    
    digits = []
    for char in series:
        if not char.isdigit():
            raise ValueError(r".+")
        digits.append(int(char))
    
    if size == 1:
        return max(digits)
    
    max_product = 0
    current_product = 1
    
    for i in range(size):
        current_product *= digits[i]
    max_product = current_product
    
    for i in range(size, len(digits)):
        if digits[i - size] == 0:
            current_product = 1
            for j in range(i - size + 1, i + 1):
                current_product *= digits[j]
        else:
            current_product = (current_product * digits[i]) // digits[i - size]
        
        if current_product > max_product:
            max_product = current_product
    
    return max_product