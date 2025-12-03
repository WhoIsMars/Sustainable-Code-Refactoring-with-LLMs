def sum_of_multiples(num, multiples=None):
    """sum_of_multiples sums multiples less than num"""
    if multiples is None:
        multiples = [3, 5]
    
    if num <= 0:
        return 0
    
    seen = set()
    total = 0
    
    for mul in multiples:
        if mul != 0 and mul < num:
            start = mul
            while start < num:
                if start not in seen:
                    seen.add(start)
                    total += start
                start += mul
    
    return total