def rebase(input_base, digits, output_base):
    if input_base < 2 or output_base < 2 or any(not (0 <= digit < input_base) for digit in digits):
        raise ValueError(r".+")

    number = sum(digit * (input_base ** i) for i, digit in enumerate(reversed(digits)))

    if number == 0:
        return [0]

    output = []
    while number:
        number, remainder = divmod(number, output_base)
        output.append(remainder)

    return output[::-1]