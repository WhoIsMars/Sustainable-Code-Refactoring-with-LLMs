def largest_product(series, size):
    if size < 0:
        raise ValueError(r".+")
    
    series_len = len(series)
    if series_len < size:
        raise ValueError(r".+")
    
    # Convert and validate in one pass
    digits = []
    for char in series:
        if not char.isdigit():
            raise ValueError(r".+")
        digits.append(int(char))
    
    if size == 0:
        return 1
    
    max_product = 0
    
    # Calculate first window
    current_product = 1
    for i in range(size):
        current_product *= digits[i]
    max_product = current_product
    
    # Slide the window
    for i in range(size, series_len):
        if digits[i - size] == 0:
            # Recalculate from scratch when removing a zero
            current_product = 1
            for j in range(i - size + 1, i + 1):
                current_product *= digits[j]
        else:
            # Use sliding window optimization
            current_product = (current_product * digits[i]) // digits[i - size]
        
        if current_product > max_product:
            max_product = current_product
    
    return max_product