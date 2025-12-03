def sum_of_multiples(num, multiples=[3,5]):
    """sum_of_multiples sums multiples less than num"""
    if num <= 0:
        return 0
    
    multiples = [m for m in multiples if m != 0 and m < num]
    if not multiples:
        return 0
    
    seen = set()
    total = 0
    
    for mul in multiples:
        if mul > 0:
            for n in range(mul, num, mul):
                if n not in seen:
                    seen.add(n)
                    total += n
        else:
            for n in range(mul, num - mul, -mul):
                if n not in seen:
                    seen.add(n)
                    total += n
    
    return total