def rebase(input_base, digits, output_base):
    if input_base < 2 or output_base < 2:
        raise ValueError(r".+")
    
    # Convert to decimal using built-in functions
    number = 0
    for digit in digits:
        if digit >= input_base or digit < 0:
            raise ValueError(r".+")
        number = number * input_base + digit
    
    if number == 0:
        return [0]
    
    # Convert to output base
    output = []
    while number:
        output.append(number % output_base)
        number //= output_base
    
    return output[::-1]