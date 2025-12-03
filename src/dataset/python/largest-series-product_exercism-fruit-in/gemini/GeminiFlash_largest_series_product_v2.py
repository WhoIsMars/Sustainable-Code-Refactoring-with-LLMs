def largest_product(series, size):
    if size < 0:
        raise ValueError("Size must be non-negative")
    if size > len(series):
        raise ValueError("Size cannot exceed the length of the series.")
    if not all(c.isdigit() for c in series):
        raise ValueError("Series must contain only digits.")

    if size == 0:
        return 1

    digits = [int(c) for c in series]
    max_product = 0
    product = 1

    # Initial product calculation
    for i in range(size):
        product *= digits[i]
    max_product = product

    # Sliding window approach
    for i in range(size, len(digits)):
        product = (product // digits[i - size]) * digits[i]
        max_product = max(max_product, product)

    return max_product