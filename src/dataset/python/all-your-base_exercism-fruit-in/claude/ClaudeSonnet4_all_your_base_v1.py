def rebase(input_base, digits, output_base):
    if input_base < 2 or output_base < 2:
        raise ValueError(r".+")
    
    if not digits:
        return [0]
    
    # Check digits validity while converting to decimal
    number = 0
    power = 1
    for digit in reversed(digits):
        if digit >= input_base or digit < 0:
            raise ValueError(r".+")
        number += power * digit
        power *= input_base
    
    if number == 0:
        return [0]
    
    # Convert to output base
    output = []
    while number > 0:
        output.append(number % output_base)
        number //= output_base
    
    output.reverse()
    return output