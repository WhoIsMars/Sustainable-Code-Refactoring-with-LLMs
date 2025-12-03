from math import prod

def largest_product(series, size):
    if len(series) < size or size < 0 or any(not x.isdigit() for x in series):
        raise ValueError(r".+")

    digits = [int(x) for x in series]
    max_product = 0
    current_product = prod(digits[:size]) if size > 0 else 0

    for i in range(len(digits) - size):
        if digits[i] != 0:
            current_product = current_product // digits[i] * digits[i + size]
        else:
            current_product = prod(digits[i + 1:i + 1 + size])
        max_product = max(max_product, current_product)

    return max_product