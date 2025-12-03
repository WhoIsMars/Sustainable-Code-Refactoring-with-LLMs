def sum_of_multiples(num, multiples=[3,5]):
    """sum_of_multiples sums multiples less than num"""
    if num <= 0:
        return 0
    
    # Filter out zero and duplicates early
    unique_multiples = list(set(m for m in multiples if m != 0))
    if not unique_multiples:
        return 0
    
    # Use set for O(1) lookups instead of generating all multiples
    seen = set()
    total = 0
    
    for mul in unique_multiples:
        if mul >= num:
            continue
        # Calculate multiples directly without range generation
        for i in range(mul, num, mul):
            if i not in seen:
                seen.add(i)
                total += i
    
    return total