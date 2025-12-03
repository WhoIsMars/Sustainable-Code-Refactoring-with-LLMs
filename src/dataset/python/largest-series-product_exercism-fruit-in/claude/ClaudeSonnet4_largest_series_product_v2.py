def largest_product(series, size):
    if len(series) < size or size < 0 or any(not x.isdigit() for x in series):
        raise ValueError(r".+")

    if size == 0:
        return 1

    digits = [int(x) for x in series]
    max_product = 0

    for i in range(len(digits) - size + 1):
        if 0 in digits[i:i + size]:
            continue
        
        product = 1
        for j in range(i, i + size):
            product *= digits[j]
        
        if product > max_product:
            max_product = product

    return max_product