def rebase(input_base, digits, output_base):
    if input_base < 2 or output_base < 2 or any(digit >= input_base or digit < 0 for digit in digits):
        raise ValueError(r".+")

    number = sum(digit * (input_base ** idx) for idx, digit in enumerate(reversed(digits)))

    if number == 0:
        return [0]

    output = []
    while number:
        output.append(number % output_base)
        number //= output_base

    output.reverse()
    return output