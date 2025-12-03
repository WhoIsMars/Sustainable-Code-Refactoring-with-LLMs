def rebase(input_base, digits, output_base):
    if input_base < 2 or output_base < 2 or any(not 0 <= digit < input_base for digit in digits):
        raise ValueError("Invalid input.")

    number = 0
    for digit in digits:
        number = number * input_base + digit

    if number == 0:
        return [0]

    output = []
    while number > 0:
        output.append(number % output_base)
        number //= output_base

    return output[::-1]