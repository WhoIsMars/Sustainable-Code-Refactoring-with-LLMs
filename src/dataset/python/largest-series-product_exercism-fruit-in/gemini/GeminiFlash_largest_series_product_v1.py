def largest_product(series, size):
    if len(series) < size or size < 0 or not series.isdigit():
        raise ValueError(".+")

    if size == 0:
        return 1

    digits = [int(x) for x in series]
    max_product = 0
    current_product = 1

    for i in range(size):
        current_product *= digits[i]

    max_product = current_product

    for i in range(size, len(digits)):
        current_product //= digits[i - size]
        current_product *= digits[i]
        max_product = max(max_product, current_product)

    return max_product