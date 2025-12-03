def rebase(input_base, digits, output_base):
    if input_base < 2 or output_base < 2:
        raise ValueError(r".+")
    
    if not digits:
        return [0]
    
    for digit in digits:
        if digit >= input_base or digit < 0:
            raise ValueError(r".+")
    
    number = 0
    for digit in digits:
        number = number * input_base + digit
    
    if number == 0:
        return [0]
    
    output = []
    while number > 0:
        output.append(number % output_base)
        number //= output_base
    
    output.reverse()
    return output