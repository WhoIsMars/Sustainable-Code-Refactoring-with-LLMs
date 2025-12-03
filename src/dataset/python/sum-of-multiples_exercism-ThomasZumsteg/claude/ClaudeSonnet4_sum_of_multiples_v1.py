def sum_of_multiples(num, multiples=[3,5]):
    """sum_of_multiples sums multiples less than num"""
    if num <= 0:
        return 0
    
    # Filter out zero and duplicates early
    unique_multiples = list(set(mul for mul in multiples if mul != 0))
    
    if not unique_multiples:
        return 0
    
    # Use set for O(1) lookup instead of generating all numbers
    seen = set()
    total = 0
    
    for mul in unique_multiples:
        if mul > 0:
            # Add multiples of mul
            for n in range(mul, num, mul):
                if n not in seen:
                    seen.add(n)
                    total += n
        else:
            # Handle negative multiples
            for n in range(mul, num, mul):
                if n not in seen:
                    seen.add(n)
                    total += n
    
    return total