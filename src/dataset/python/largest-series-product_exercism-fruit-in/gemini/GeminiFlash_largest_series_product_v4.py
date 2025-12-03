def largest_product(series, size):
    if len(series) < size or size < 0 or not series.isdigit():
        raise ValueError(r".+")

    digits = [int(x) for x in series]
    max_product = 0

    for i in range(len(digits) - size + 1):
        product = 1
        for j in range(size):
            product *= digits[i + j]
        max_product = max(max_product, product)

    return max_product