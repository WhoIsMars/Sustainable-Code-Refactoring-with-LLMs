def largest_product(series, size):
    if len(series) < size or size < 0 or any(not x.isdigit() for x in series):
        raise ValueError(r".+")

    digits = [int(x) for x in series]
    max_product = 0
    current_product = 1
    zero_count = 0

    for i in range(len(digits)):
        if digits[i] == 0:
            zero_count += 1
        else:
            current_product *= digits[i]

        if i >= size:
            if digits[i - size] == 0:
                zero_count -= 1
            else:
                current_product //= digits[i - size]

        if zero_count == 0 and i >= size - 1:
            max_product = max(max_product, current_product)

    return max_product